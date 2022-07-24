#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

class QVBoxLayout;
class QPushButton;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:
    void onFontSizeChanged();

public slots:
    void onAddBtnClicked();
    void onDeleteBtnClicked();
    void onEditFontClicked();

private:
    static void setBtnIcon(const QString &path, QPushButton *button);
    void createMenus();
    void createActions();

private:
    QWidget *m_mainWidget;
    QVBoxLayout *m_mainLayout;
    QMenu *m_editMenu{};
    QAction *m_fontAct{};
};
#endif // MAINWINDOW_H
