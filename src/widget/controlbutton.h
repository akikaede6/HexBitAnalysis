#ifndef CONTROLBUTTON_H
#define CONTROLBUTTON_H

#include <QWidget>

class QPushButton;
class ControlButton : public QWidget
{
    Q_OBJECT
public:
    explicit ControlButton(QWidget *parent = nullptr);

signals:
    void rightAddBtnClicked();
    void rightDeleteBtnClicked();
    void belowAddBtnClicked();
    void belowDeleteBtnClicked();

private:
    static void setBtnIcon(const QString &path, QPushButton *button);
};

#endif // CONTROLBUTTON_H
