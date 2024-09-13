import QtQuick 2.15
import QtQuick.Window 2.15
import QtGraphicalEffects 1.15
import QtQuick.Controls 2.15

Rectangle {
    visible: true
    width: 400
    height: 400
    // 使用 Canvas 进行绘制
    color: "transparent"
    border.color: "red"
    border.width: 1
    Text {
        text: "QML"
        anchors.top: parent.top
        anchors.left: parent.left
    }
    Canvas {
        // 保存鼠标点击的点
        property var points: []

        id: myCanvas
        anchors.fill: parent
        onPaint: {
            var ctx = getContext("2d");
            ctx.clearRect(0, 0, width, height);
            ctx.fillStyle = "blue";
            ctx.lineWidth = 10;
            ctx.lineCap = "round";   // 线条端点样式 (butt, round, square)
            ctx.lineJoin = "round";  // 线条连接样式 (bevel, round, miter)
            ctx.strokeStyle = "#3fff0000"
            ctx.fillStyle = "#3fff0000"
            ctx.beginPath();
            console.log("points.length: ", points.length);
            if (points.length > 0) {
                ctx.moveTo(points[0].x, points[0].y);
                for (var i = 1; i < points.length; i++) {
                    ctx.lineTo(points[i].x, points[i].y);
                }
                //save the path
                ctx.stroke();
                //save to file
                //myCanvas.save("/Users/yanhuajian/Desktop/3/test.png");
            }

            ctx.stroke();
        }

        // process mouse events
        MouseArea {
            anchors.fill: parent
            onPressed: {
                myCanvas.points = [];
                myCanvas.requestPaint();
            }
            //add 2 draw path
            onPositionChanged: {
                myCanvas.points.push(Qt.point(mouseX, mouseY));
                myCanvas.requestPaint();
            }
            onReleased: {
                canvasProvider.toImage(myCanvas)
            }
        }
    }

    // 使用 QtGraphicalEffects 模糊
    GaussianBlur {
        anchors.fill: parent
        source: myCanvas
        radius: 15  // 模糊半径，控制羽化效果
    }

}
