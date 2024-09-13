//********************************************************
/// @brief 
/// @author yanhuajian
/// @date 2024/9/13
/// @note
/// @version 1.0.0
//********************************************************

#include "CanvasProvider.h"
#include <QEventLoop>
#include <QQuickItem>
#include <QImage>
#include <QQuickItemGrabResult>

CanvasProvider::CanvasProvider(QObject* parent)
    : QObject(parent)
{
}

CanvasProvider* CanvasProvider::instance()
{
    static CanvasProvider s_instance;
    return &s_instance;
}

void CanvasProvider::toImage(QObject* object)
{
    auto item = qobject_cast<QQuickItem*>(object);
    if(!item) { return; }

    QEventLoop eventLoop;
    QImage buf;
    auto grad = item->grabToImage();

    auto c = QObject::connect(grad.data(), &QQuickItemGrabResult::ready, [&]()
    {
        buf = grad->image();
        eventLoop.exit();
    });
    eventLoop.exec();
    QObject::disconnect(c);

    emit imageReady(buf);
}
