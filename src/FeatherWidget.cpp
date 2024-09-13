//********************************************************
/// @brief 
/// @author yanhuajian
/// @date 2024/9/13
/// @note
/// @version 1.0.0
//********************************************************

#include "FeatherWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>

FeatherWidget::FeatherWidget(QWidget *parent)
    : QWidget(parent)
{
    m_btn = new QPushButton("Hello", this);
    m_btn->show();
    m_btn->setStyleSheet("background-color: red;");
}

FeatherWidget::~FeatherWidget()
{
}

void FeatherWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    //draw back image
    {
        painter.fillRect(rect(), Qt::gray);
    }
    if(1) {
        QPen pen = painter.pen();
        pen.setWidth(10);
        pen.setCapStyle(Qt::RoundCap);
        painter.setPen(Qt::NoPen);

        auto size = m_path.boundingRect().size();
        qreal step = 1.0 / ((size.width() / 10) * (size.height() / 10));
        step = std::min(0.1, step);
        for (qreal r = 0; r <= 1.0; r += step)
        {
            auto p = m_path.pointAtPercent(r);
            QRadialGradient g(p, 20, p);
            g.setColorAt(0.0, QColor(255, 0, 0, 128));
            g.setColorAt(0.8, QColor(255, 0, 0, 30));
            g.setColorAt(1.0, Qt::transparent);
            painter.setBrush(g);
            painter.drawEllipse(p, 20, 20);
        }
    } else {


        QBrush brush(QColor(255, 0, 0, 128));
        painter.setPen(QPen(brush, 18, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawPath(m_path);

        //draw circle at the end of the path
        if (!m_path.isEmpty()) {
            painter.setPen(QPen(Qt::green, 1));
            painter.setBrush(Qt::NoBrush);
            painter.drawEllipse(m_path.currentPosition(), 10, 10);
        }
    }
}

void FeatherWidget::mousePressEvent(QMouseEvent *event)
{
    m_path.clear();
    m_path.moveTo(event->pos());
    update();
}

void FeatherWidget::mouseMoveEvent(QMouseEvent *event)
{
    m_path.lineTo(event->pos());
    update();
}

void FeatherWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_path.lineTo(event->pos());
    update();
}

void FeatherWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    if(m_btn) {
        m_btn->move(50, 50);
        m_btn->raise();
    }
}