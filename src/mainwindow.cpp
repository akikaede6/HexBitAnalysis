#include "mainwindow.h"
#include "analsiswidget.h"
#include "util.h"
#include "widget/bitdialog.h"
#include "widget/controlbutton.h"
#include "widget/fontdialog.h"

#include <QLabel>
#include <QMenuBar>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_mainWidget(new QWidget(this))
    , m_mainLayout(new QGridLayout(m_mainWidget))
{
    setFont(FontSize::fontSize());
    auto *titleLayout = new QHBoxLayout();
    auto *titleLabel = new QLabel(tr("Hex Bit Analysis"), this);
    QFont font;
    font.setPixelSize(44);
    titleLabel->setFont(font);
    titleLabel->setText("Hex Bit Analysis");

    auto *controlBtn = new ControlButton(this);
    titleLayout->addWidget(controlBtn, 0, Qt::AlignRight);
    titleLayout->addWidget(titleLabel, this->geometry().width() / 2, Qt::AlignCenter);

    auto *analysisWidget = new AnalsisWidget(this);
    connect(this, &MainWindow::onFontSizeChanged, analysisWidget, &AnalsisWidget::onFontSizeChanged);
    m_mainLayout->addLayout(titleLayout, 0, 0);
    m_mainLayout->addWidget(analysisWidget, 1, 0);

    setCentralWidget(m_mainWidget);
    connect(controlBtn, &ControlButton::belowAddBtnClicked, this, &MainWindow::onBelowAddBtnClicked);
    connect(controlBtn,
            &ControlButton::belowDeleteBtnClicked,
            this,
            &MainWindow::onBelowDeleteBtnClicked);
    connect(controlBtn, &ControlButton::rightAddBtnClicked, this, &MainWindow::onRightAddBtnClicked);
    connect(controlBtn,
            &ControlButton::rightDeleteBtnClicked,
            this,
            &MainWindow::onRightDeleteBtnClicked);
    connect(this, &MainWindow::onBitChanged, analysisWidget, &AnalsisWidget::onBitChanged);
    createActions();
    createMenus();
    this->setFixedSize(sizeHint());
}

void MainWindow::onBelowAddBtnClicked()
{
    auto *analysisWidget = new AnalsisWidget(this);
    connect(this, &MainWindow::onFontSizeChanged, analysisWidget, &AnalsisWidget::onFontSizeChanged);
    connect(this, &MainWindow::onBitChanged, analysisWidget, &AnalsisWidget::onBitChanged);
    m_mainLayout->addWidget(analysisWidget, m_currentRow, 0);
    if (m_currentCol != 1) {
        for (int i = 1; i < m_currentCol; i++) {
            auto *analysisWidget = new AnalsisWidget(this);
            m_mainLayout->addWidget(analysisWidget, m_currentRow, i);
            connect(this, &MainWindow::onBitChanged, analysisWidget, &AnalsisWidget::onBitChanged);
        }
    }
    m_currentRow++;
    QTimer::singleShot(0, this, [&] {
        adjustSize();
        this->setFixedSize(sizeHint());
    });
}

void MainWindow::onBelowDeleteBtnClicked()
{
    for (int i = m_currentCol - 1; i >= 0; i--) {
        if (m_mainLayout->count() - 1 > m_currentCol) {
            QWidget *deletedWidget = m_mainLayout->itemAtPosition(m_currentRow - 1, i)->widget();
            m_mainLayout->removeWidget(deletedWidget);
            deletedWidget->deleteLater();
            if (i == 0) {
                m_currentRow--;
            }
        }
    }
    QTimer::singleShot(0, this, [&] {
        adjustSize();
        this->setFixedSize(sizeHint());
    });
}

void MainWindow::onRightAddBtnClicked()
{
    auto *analysisWidget = new AnalsisWidget(this);
    connect(this, &MainWindow::onFontSizeChanged, analysisWidget, &AnalsisWidget::onFontSizeChanged);
    connect(this, &MainWindow::onBitChanged, analysisWidget, &AnalsisWidget::onBitChanged);
    m_mainLayout->addWidget(analysisWidget, 1, m_currentCol);
    if (m_currentRow != 2) {
        for (int i = 2; i < m_currentRow; i++) {
            auto *analysisWidget = new AnalsisWidget(this);
            m_mainLayout->addWidget(analysisWidget, i, m_currentCol);
            connect(this, &MainWindow::onBitChanged, analysisWidget, &AnalsisWidget::onBitChanged);
        }
    }
    m_currentCol++;
    QTimer::singleShot(0, this, [&] {
        adjustSize();
        this->setFixedSize(sizeHint());
    });
}

void MainWindow::onRightDeleteBtnClicked()
{
    for (int i = m_currentRow - 1; i >= 1; i--) {
        if (m_mainLayout->count() > m_currentRow) {
            QWidget *deletedWidget = m_mainLayout->itemAtPosition(i, m_currentCol - 1)->widget();
            m_mainLayout->removeWidget(deletedWidget);
            deletedWidget->deleteLater();
            if (i == 1) {
                m_currentCol--;
            }
        }
    }

    QTimer::singleShot(0, this, [&] {
        adjustSize();
        this->setFixedSize(sizeHint());
    });
}

void MainWindow::onEditFontClicked()
{
    auto *fontDialog = new FontDialog(this);
    connect(fontDialog, &FontDialog::fontChanged, this, [&] {
        this->setFont(FontSize::fontSize());
        m_fontAct->setFont(FontSize::fontSize());
        m_bitAct->setFont(FontSize::fontSize());
        QTimer::singleShot(0, this, [&] {
            adjustSize();
            this->setFixedSize(sizeHint());
        });
    });
    connect(fontDialog, &FontDialog::fontChanged, this, &MainWindow::onFontSizeChanged);
    fontDialog->show();
}

void MainWindow::onEditBitClicked()
{
    auto *bitDialog = new BitDialog(this);
    connect(bitDialog, &BitDialog::bitChanged, this, &MainWindow::onBitChanged);
    // FIXME: time to resize is not property
    connect(bitDialog, &BitDialog::bitChanged, this, [&] {
        QTimer::singleShot(1, this, [&] {
            adjustSize();
            this->setFixedSize(sizeHint());
        });
    });
    bitDialog->show();
}

void MainWindow::setBtnIcon(const QString &path, QPushButton *button)
{
    QPixmap pixmap(path);
    QIcon ButtonIcon(pixmap);
    button->setIcon(ButtonIcon);
    button->setIconSize(pixmap.rect().size());
}

void MainWindow::createMenus()
{
    m_editMenu = menuBar()->addMenu(tr("&Option"));
    m_editMenu->addAction(m_fontAct);
    m_editMenu->addAction(m_bitAct);
}

void MainWindow::createActions()
{
    m_fontAct = new QAction(tr("&Font Size"), this);
    m_fontAct->setStatusTip(tr("edit font size"));
    connect(m_fontAct, &QAction::triggered, this, &MainWindow::onEditFontClicked);

    m_bitAct = new QAction(tr("&Bit"), this);
    m_bitAct->setStatusTip(tr("change bit"));
    connect(m_bitAct, &QAction::triggered, this, &MainWindow::onEditBitClicked);
}
