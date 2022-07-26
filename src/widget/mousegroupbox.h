#ifndef MOUSEGROUPBOX_H
#define MOUSEGROUPBOX_H

#include <QButtonGroup>
#include <QCheckBox>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

class MouseGroupBox : public QGroupBox
{
    Q_OBJECT
public:
    explicit MouseGroupBox(QWidget *parent = nullptr);

    void addBtnList(QButtonGroup *binaryBtnGroup);
    void addCheckBoxList(QList<QCheckBox *> checkBoxList);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QList<QCheckBox *> m_checkBoxList;
    QButtonGroup *m_binaryBtnGroup{nullptr};

    QPoint point_start;
    QPoint point_end;
    bool mouseDown{false};
};

#endif // MOUSEGROUPBOX_H
