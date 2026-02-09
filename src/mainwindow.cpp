#include "mainwindow.h"
#include "analsiswidget.h"
#include "util.h"
#include "widget/bitdialog.h"
#include "widget/controlbutton.h"

#include <QApplication>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QMenuBar>
#include <QSizePolicy>
#include <QtGlobal>
#include <QTimer>
#include <QToolBar>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto dockOptions = QMainWindow::AnimatedDocks | QMainWindow::AllowTabbedDocks
                       | QMainWindow::AllowNestedDocks;
#if QT_VERSION >= QT_VERSION_CHECK(5, 6, 0)
    dockOptions |= QMainWindow::GroupedDragging;
#endif
    setDockOptions(dockOptions);
    setDockNestingEnabled(true);

    auto *titleWidget = new QWidget(this);
    auto *titleLayout = new QHBoxLayout(titleWidget);
    titleLayout->setContentsMargins(0, 0, 0, 0);
    auto *titleLabel = new QLabel(tr("Hex Bit Analysis"), titleWidget);
    QFont font;
    font.setPixelSize(28);
    titleLabel->setFont(font);
    titleLabel->setText("Hex Bit Analysis");

    auto *controlBtn = new ControlButton(this);
    titleLayout->addWidget(controlBtn, 0, Qt::AlignLeft);
    titleLayout->addWidget(titleLabel, 1, Qt::AlignCenter);

    auto *toolbar = new QToolBar(this);
    toolbar->setMovable(false);
    toolbar->addWidget(titleWidget);
    addToolBar(Qt::TopToolBarArea, toolbar);

    connect(controlBtn, &ControlButton::addBtnClicked, this, &MainWindow::onAddBtnClicked);
    connect(controlBtn, &ControlButton::deleteBtnClicked, this, &MainWindow::onDeleteBtnClicked);

    auto *central = new QWidget(this);
    auto *centralLayout = new QVBoxLayout(central);
    centralLayout->setContentsMargins(0, 0, 0, 0);
    setCentralWidget(central);

    auto *analysisDock = createAnalysisDock();
    addAnalysisDockTwoColumn(analysisDock);
    createActions();
    createMenus();
}

void MainWindow::onAddBtnClicked()
{
    auto *analysisDock = createAnalysisDock();
    addAnalysisDockTwoColumn(analysisDock);
}

void MainWindow::onDeleteBtnClicked()
{
    auto *targetDock = focusedDockWidget();
    if (!targetDock && !m_dockWidgets.isEmpty()) {
        targetDock = m_dockWidgets.last();
    }
    if (!targetDock) {
        return;
    }
    targetDock->close();
}

void MainWindow::onEditBitClicked()
{
    auto *bitDialog = new BitDialog(this);
    connect(bitDialog, &BitDialog::bitChanged, this, &MainWindow::updateBit);
    bitDialog->show();
}

void MainWindow::onBitChanged(int bit)
{
    Q_UNUSED(bit);
    QTimer::singleShot(0, this, [&] { this->adjustSize(); });
}

void MainWindow::createMenus()
{
    m_editMenu = menuBar()->addMenu(tr("&Option"));
    m_editMenu->addAction(m_bitAct);
    m_editMenu->addAction(m_addAct);
}

void MainWindow::createActions()
{
    m_bitAct = new QAction(tr("&Bit"), this);
    m_bitAct->setStatusTip(tr("change bit"));
    connect(m_bitAct, &QAction::triggered, this, &MainWindow::onEditBitClicked);

    m_addAct = new QAction(tr("New"), this);
    connect(m_addAct, &QAction::triggered, this, &MainWindow::onAddBtnClicked);
}

QDockWidget *MainWindow::createAnalysisDock()
{
    auto *analysisDock = new QDockWidget(tr("Analysis %1").arg(m_nextDockIndex++), this);
    auto *analysisWidget = new AnalsisWidget(analysisDock);
    connect(this, &MainWindow::updateBit, analysisWidget, [this, analysisWidget](int bit) {
        analysisWidget->onBitChanged(bit);
        onBitChanged(bit);
    });
    analysisDock->setWidget(analysisWidget);
    analysisDock->setAllowedAreas(Qt::AllDockWidgetAreas);
    analysisDock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable
                              | QDockWidget::DockWidgetFloatable);
    analysisDock->setAttribute(Qt::WA_DeleteOnClose);

    m_dockWidgets.append(analysisDock);
    connect(analysisDock, &QObject::destroyed, this, [this, analysisDock] {
        m_dockWidgets.removeAll(analysisDock);
        m_leftColumnDocks.removeAll(analysisDock);
        m_rightColumnDocks.removeAll(analysisDock);
    });
    connect(analysisDock, &QDockWidget::topLevelChanged, this, [this, analysisDock](bool floating) {
        if (floating || !m_lastFocusedDock || m_lastFocusedDock == analysisDock) {
            return;
        }
        if (!QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier)) {
            return;
        }
        splitDockWidget(m_lastFocusedDock, analysisDock, Qt::Vertical);
        analysisDock->raise();
    });

    return analysisDock;
}

int MainWindow::dockCount(const QVector<QDockWidget *> &docks) const
{
    int count = 0;
    for (auto *dock : docks) {
        if (dock && !dock->isFloating()) {
            count++;
        }
    }
    return count;
}

QDockWidget *MainWindow::lastDock(const QVector<QDockWidget *> &docks) const
{
    for (int i = docks.size() - 1; i >= 0; i--) {
        auto *dock = docks.at(i);
        if (dock && !dock->isFloating()) {
            return dock;
        }
    }
    return nullptr;
}

void MainWindow::addAnalysisDockTwoColumn(QDockWidget *analysisDock)
{
    const int leftCount = dockCount(m_leftColumnDocks);
    const int rightCount = dockCount(m_rightColumnDocks);
    Qt::DockWidgetArea targetArea = Qt::LeftDockWidgetArea;

    if (leftCount == 0) {
        targetArea = Qt::LeftDockWidgetArea;
    } else if (rightCount == 0 && leftCount < 2) {
        targetArea = Qt::LeftDockWidgetArea;
    } else if (rightCount == 0) {
        targetArea = Qt::RightDockWidgetArea;
    } else if (leftCount <= rightCount) {
        targetArea = Qt::LeftDockWidgetArea;
    } else {
        targetArea = Qt::RightDockWidgetArea;
    }

    if (targetArea == Qt::LeftDockWidgetArea) {
        if (leftCount == 0) {
            addDockWidget(Qt::LeftDockWidgetArea, analysisDock);
        } else if (auto *anchor = lastDock(m_leftColumnDocks)) {
            splitDockWidget(anchor, analysisDock, Qt::Vertical);
        } else {
            addDockWidget(Qt::LeftDockWidgetArea, analysisDock);
        }
        m_leftColumnDocks.append(analysisDock);
    } else {
        if (rightCount == 0) {
            addDockWidget(Qt::RightDockWidgetArea, analysisDock);
        } else if (auto *anchor = lastDock(m_rightColumnDocks)) {
            splitDockWidget(anchor, analysisDock, Qt::Vertical);
        } else {
            addDockWidget(Qt::RightDockWidgetArea, analysisDock);
        }
        m_rightColumnDocks.append(analysisDock);
    }
}

QDockWidget *MainWindow::focusedDockWidget() const
{
    QWidget *focusWidget = QApplication::focusWidget();
    while (focusWidget) {
        auto *dockWidget = qobject_cast<QDockWidget *>(focusWidget);
        if (dockWidget) {
            return dockWidget;
        }
        focusWidget = focusWidget->parentWidget();
    }
    return m_lastFocusedDock;
}
