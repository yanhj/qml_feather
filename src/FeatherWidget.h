//********************************************************
/// @brief 
/// @author yanhuajian
/// @date 2024/9/13
/// @note
/// @version 1.0.0
//********************************************************

#pragma once

#include <QWidget>
#include <QPainterPath>

class QPushButton;

class FeatherWidget : public QWidget{
    Q_OBJECT
    public:
        FeatherWidget(QWidget *parent = nullptr);
        ~FeatherWidget();

        void paintEvent(QPaintEvent *event) override;

        void mousePressEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;

        void resizeEvent(QResizeEvent *event) override;

private:
    QPainterPath m_path;
    QPushButton* m_btn;
};
