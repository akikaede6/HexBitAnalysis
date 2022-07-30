#include "mainwindow.h"
#include "analsiswidget.h"
#include "util.h"
#include "widget/fontdialog.h"

#include <QLabel>
#include <QMenuBar>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_mainWidget(new QWidget(this))
    , m_mainLayout(new QVBoxLayout(m_mainWidget))
{
    setFont(FontSize::fontSize());
    auto *titleLayout = new QHBoxLayout();
    auto *titleLabel = new QLabel(tr("Hex Bit Analysis"), this);
    titleLabel->setText("Hex Bit Analysis");
    auto *addBtn = new QPushButton(this);
    auto *deleteBtn = new QPushButton(this);
    setBtnIcon(":/icon/plus.png", addBtn);
    setBtnIcon(":/icon/minus.png", deleteBtn);
    titleLayout->addWidget(titleLabel, this->geometry().width() / 2, Qt::AlignCenter);
    titleLayout->addWidget(addBtn, 0, Qt::AlignRight);
    titleLayout->addWidget(deleteBtn, 0, Qt::AlignRight);

    auto *analysisWidget = new AnalsisWidget(this);
    connect(this, &MainWindow::onFontSizeChanged, analysisWidget, &AnalsisWidget::onFontSizeChanged);
    m_mainLayout->addLayout(titleLayout);
    m_mainLayout->addWidget(analysisWidget);

    setCentralWidget(m_mainWidget);
    connect(addBtn, &QPushButton::clicked, this, &MainWindow::onAddBtnClicked);
    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::onDeleteBtnClicked);

    createActions();
    createMenus();
}

void MainWindow::onAddBtnClicked()
{
    auto *analysisWidget = new AnalsisWidget(this);
    connect(this, &MainWindow::onFontSizeChanged, analysisWidget, &AnalsisWidget::onFontSizeChanged);
    m_mainLayout->addWidget(analysisWidget);
}

void MainWindow::onDeleteBtnClicked()
{
    QWidget *deletedWidget = m_mainLayout->itemAt(m_mainLayout->count() - 1)->widget();
    if (m_mainLayout->count() > 2) {
        m_mainLayout->removeWidget(deletedWidget);
        deletedWidget->deleteLater();
    }

    QTimer::singleShot(0, this, [&] { adjustSize(); });
}

void MainWindow::onEditFontClicked()
{
    auto *fontDialog = new FontDialog(this);
    connect(fontDialog, &FontDialog::fontChanged, this, [&] {
        this->setFont(FontSize::fontSize());
        m_fontAct->setFont(FontSize::fontSize());
        QTimer::singleShot(0, this, [&] { adjustSize(); });
    });
    connect(fontDialog, &FontDialog::fontChanged, this, &MainWindow::onFontSizeChanged);
    fontDialog->show();
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
    m_editMenu = menuBar()->addMenu(tr("&Edit"));
    m_editMenu->addAction(m_fontAct);
}

void MainWindow::createActions()
{
    m_fontAct = new QAction(tr("&Font"), this);
    m_fontAct->setStatusTip(tr("edit font size"));
    connect(m_fontAct, &QAction::triggered, this, &MainWindow::onEditFontClicked);
}
