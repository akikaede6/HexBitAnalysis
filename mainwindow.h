#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMap>
#include <QWidget>

class QLineEdit;
class QLabel;
class QPushButton;
class QCheckBox;
class QButtonGroup;
class QAbstractButton;
class QGridLayout;
class QVBoxLayout;
class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:
    void onAddBtnClicked();
    void onDeleteBtnClicked();

private:
    void initUI();
    void initTitle();
    void initConnection();

private:
    QVBoxLayout *m_mainLayout;
    QPushButton *addBtn;
    QPushButton *deleteBtn;
};
#endif // MAINWINDOW_H
