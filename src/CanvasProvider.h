//********************************************************
/// @brief 
/// @author yanhuajian
/// @date 2024/9/13
/// @note
/// @version 1.0.0
//********************************************************

#pragma once

#include <QObject>

class CanvasProvider : public QObject
{
    Q_OBJECT
public:
    CanvasProvider(QObject* parent = nullptr);
    ~CanvasProvider() {}
    static CanvasProvider* instance();

    Q_INVOKABLE void toImage(QObject* object);

Q_SIGNALS:
    void imageReady(const QImage& image);
};
