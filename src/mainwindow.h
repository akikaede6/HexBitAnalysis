#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>
#include <QVector>

class QDockWidget;
class QAction;
class QMenu;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:
    void updateBit(int bit);

public slots:
    void onAddBtnClicked();
    void onDeleteBtnClicked();
    void onEditBitClicked();
    void onBitChanged(int bit);

private:
    QDockWidget *createAnalysisDock();
    QDockWidget *focusedDockWidget() const;
    void addAnalysisDockTwoColumn(QDockWidget *analysisDock);
    int dockCount(const QVector<QDockWidget *> &docks) const;
    QDockWidget *lastDock(const QVector<QDockWidget *> &docks) const;
    void createMenus();
    void createActions();

private:
    QVector<QDockWidget *> m_dockWidgets;
    QVector<QDockWidget *> m_leftColumnDocks;
    QVector<QDockWidget *> m_rightColumnDocks;
    QPointer<QDockWidget> m_lastFocusedDock;
    int m_nextDockIndex = 1;
    QMenu *m_editMenu{};
    QAction* m_addAct{};
    QAction *m_bitAct{};
};
#endif // MAINWINDOW_H
