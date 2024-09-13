#include <QApplication>
#include <QPushButton>
#include "FeatherWidget.h"
#include "CanvasProvider.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>
#include <QQuickWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QQuickWindow>
#include <QQuickItem>
#include <QPainter>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    FeatherWidget w;
    w.setMinimumSize(500, 500);
    w.show();
    //load qml
    QQmlApplicationEngine engine;

    //register c++ object to qml
    engine.rootContext()->setContextProperty("canvasProvider", CanvasProvider::instance());

    engine.load(QUrl(QStringLiteral("qrc:/feather.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    auto obj = engine.rootContext()->contextProperty("canvasProvider").value<QObject*>();

    auto quickWidget = new QQuickWidget(&w);
    quickWidget->setAttribute(Qt::WA_TranslucentBackground); // 设置窗口背景透明
    quickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
    quickWidget->setStyleSheet("background:transparent;");
    quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    quickWidget->setSource(QUrl(QStringLiteral("qrc:/feather.qml")));
    quickWidget->setClearColor(Qt::transparent);
    quickWidget->raise();
    QVBoxLayout *layout = new QVBoxLayout(&w);
    layout->addWidget(quickWidget);
    QLabel *label = new QLabel("Hello World");
    label->setFixedHeight(200);
    layout->addWidget(label);
    return QApplication::exec();
}
