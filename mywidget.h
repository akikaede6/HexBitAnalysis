#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QCheckBox>
#include <QLineEdit>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    
signals:
    
public slots:
    
};

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = 0);
    void text_toggle(void);

protected:

signals:

public:
    QString style_sheet;

private:
};

class MyGroupBox : public QGroupBox
{
    Q_OBJECT
public:
    explicit MyGroupBox(QWidget *parent = 0);

    void addBtnList(QList<MyPushButton *> list);
    void addChkList(QList<QCheckBox *> list);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

signals:

public slots:

private:
    QList<MyPushButton *> btnList;
    QList<QCheckBox *> chkList;

    QPoint point_start;
    QPoint point_end;
    bool mouseDown;

};

class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit MyLineEdit(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);

signals:

public slots:

private:
    bool upper_case;
};

#endif // MYLABEL_H
