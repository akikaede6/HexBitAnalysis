#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class QVBoxLayout;
class QPushButton;
class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

public slots:
    void onAddBtnClicked();
    void onDeleteBtnClicked();

private:
    static void setBtnIcon(const QString &path, QPushButton *button);

private:
    QVBoxLayout *m_mainLayout;
};
#endif // MAINWINDOW_H
