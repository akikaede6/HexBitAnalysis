#include <QDebug>
#include <QtGui>
#include "mywidget.h"

MyLabel::MyLabel(QWidget *parent) :
    QLabel(parent)
{
}

void MyLabel::mousePressEvent(QMouseEvent *event)
{
    event->ignore();
}

void MyLabel::mouseReleaseEvent(QMouseEvent *event)
{
    event->ignore();
}

void MyLabel::mouseMoveEvent(QMouseEvent *event)
{
    event->ignore();
}

MyPushButton::MyPushButton(QWidget *parent) :
    QPushButton(parent)
{
}

void MyPushButton::text_toggle(void)
{
    if (text().toUInt() == 0)
        setText("1");
    else
        setText("0");

    if (style_sheet.isEmpty()) {
        style_sheet = styleSheet();
        setStyleSheet(QString::fromUtf8("QPushButton{\n"
                                        "	background-color:rgb(255, 170, 0);\n"
                                        "}"));
    } else {
        setStyleSheet(this->style_sheet);
        style_sheet = QString();
    }
}

MyGroupBox::MyGroupBox(QWidget *parent) :
    QGroupBox(parent)
{
    mouseDown = false;
    btnList.clear();
    chkList.clear();
}

void MyGroupBox::addBtnList(QList<MyPushButton *> list)
{
    btnList = list;
}

void MyGroupBox::addChkList(QList<QCheckBox *> list)
{
    chkList = list;
}

void MyGroupBox::paintEvent(QPaintEvent *event)
{
    if (mouseDown && !point_start.isNull() && !point_end.isNull()) {
        QPainter p(this);
        QBrush b = QBrush(QColor(255,0,0,0));
        p.setPen(QPen(QColor(255,85,0)));
        p.setBackground(b);
        if (point_start.y() < point_end.y())
            p.setBrush(Qt::cyan);
        else
            p.setBrush(Qt::yellow);
        p.drawRect(QRect(point_start, point_end));
        //qDebug() << this << "paintEvent: " << point_start << point_end;
    }

    QGroupBox::paintEvent(event);
}

void MyGroupBox::mousePressEvent(QMouseEvent *event)
{
    mouseDown = true;
    point_start = event->pos();
    point_end = event->pos();
    qDebug() << "mousePressEvent: start: " << point_start << ", end: " << point_end;
}

void MyGroupBox::mouseReleaseEvent(QMouseEvent *event)
{
    if (mouseDown == false)
        return;

    mouseDown = false;
    point_end = event->pos();
    qDebug() << "mouseReleaseEvent: start: " << point_start << ", end: " << point_end;
    update();

    if (point_start.y() < point_end.y()) {
        for (int i = 0; i < 32; i++) {
            if (QRect(point_start, point_end).contains(btnList[i]->geometry().center())) {
                emit btnList[i]->click();
            }
        }
    } else {
        for (int i = 0; i < 32; i++) {
            if (QRect(point_start, point_end).contains(chkList[i]->geometry().center())) {
                emit chkList[i]->click();
            }
        }
    }
}

void MyGroupBox::mouseMoveEvent(QMouseEvent *event)
{
    if (mouseDown) {
        point_end = event->pos();
        update();
    }
}

MyLineEdit::MyLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
    upper_case = true;
}

void MyLineEdit::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        QString val;
        if (upper_case)
            val = text().toLower();
        else
            val = text().toUpper();

        if (val.startsWith("0x", Qt::CaseInsensitive))
            val.replace(0, 2, "0x");

        setText(val);

        upper_case = !upper_case;
    } else if (event->button() == Qt::LeftButton) {
        deselect();
    }
}

void MyLineEdit::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        QString val;
        if (upper_case)
            val = text().toLower();
        else
            val = text().toUpper();

        if (val.startsWith("0x", Qt::CaseInsensitive))
            val.replace(0, 2, "0x");

        setText(val);

        upper_case = !upper_case;
    } else if (event->button() == Qt::LeftButton) {
        selectAll();
    }
}

void MyLineEdit::contextMenuEvent(QContextMenuEvent *event)
{
    event->accept();
}
