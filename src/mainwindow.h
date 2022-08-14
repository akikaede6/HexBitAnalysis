#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

class QGridLayout;
class QPushButton;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:
    void onFontSizeChanged();
    void onBitChanged(int bit);

public slots:
    void onBelowAddBtnClicked();
    void onBelowDeleteBtnClicked();
    void onRightAddBtnClicked();
    void onRightDeleteBtnClicked();
    void onEditFontClicked();
    void onEditBitClicked();

private:
    static void setBtnIcon(const QString &path, QPushButton *button);
    void createMenus();
    void createActions();

private:
    QWidget *m_mainWidget;
    QGridLayout *m_mainLayout;
    QMenu *m_editMenu{};
    QAction *m_fontAct{};
    QAction *m_bitAct{};
    int m_currentRow = 2;
    int m_currentCol = 1;
};
#endif // MAINWINDOW_H
