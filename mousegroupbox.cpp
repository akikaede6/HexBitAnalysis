#include "mousegroupbox.h"
#include "util.h"

#include <QtGui>

MouseGroupBox::MouseGroupBox(QWidget *parent)
    : QGroupBox(parent)
{}

void MouseGroupBox::addBtnList(QButtonGroup *binaryBtnGroup)
{
    m_binaryBtnGroup = binaryBtnGroup;
}

void MouseGroupBox::addCheckBoxList(QList<QCheckBox *> checkBoxList)
{
    m_checkBoxList = std::move(checkBoxList);
}

void MouseGroupBox::paintEvent(QPaintEvent *event)
{
    if (mouseDown && !point_start.isNull() && !point_end.isNull()) {
        QPainter p(this);
        QBrush b = QBrush(QColor(255, 0, 0, 0));
        p.setPen(QPen(QColor(255, 0, 0, 0)));
        p.setBackground(b);
        if (point_start.y() < point_end.y())
            p.setBrush(QColor("#B0E0E6"));
        else
            p.setBrush(QColor("#FFD700"));
        p.drawRect(QRect(point_start, point_end));
    }

    QGroupBox::paintEvent(event);
}

void MouseGroupBox::mousePressEvent(QMouseEvent *event)
{
    mouseDown = true;
    point_start = event->pos();
    point_end = event->pos();
}

void MouseGroupBox::mouseReleaseEvent(QMouseEvent *event)
{
    if (!mouseDown)
        return;

    mouseDown = false;
    point_end = event->pos();
    update();

    if (point_start.y() < point_end.y()) {
        for (int i = 0; i < Bit; i++) {
            if (QRect(point_start, point_end)
                    .contains(m_binaryBtnGroup->button(i)->geometry().center())) {
                m_binaryBtnGroup->button(i)->click();
            }
        }
    } else {
        for (int i = 0; i < Bit; i++) {
            if (QRect(point_start, point_end).contains(m_checkBoxList.at(i)->geometry().center())) {
                m_checkBoxList.at(i)->click();
            }
        }
    }
}

void MouseGroupBox::mouseMoveEvent(QMouseEvent *event)
{
    if (mouseDown) {
        point_end = event->pos();
        update();
    }
}
