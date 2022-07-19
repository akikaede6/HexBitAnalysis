#include "mainwindow.h"

#include <QButtonGroup>
#include <QCheckBox>
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <iostream>

#include "analsiswidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , m_mainLayout(new QVBoxLayout(this))
    , addBtn(new QPushButton("add"))
    , deleteBtn(new QPushButton("delete"))
{
    initUI();
    initConnection();
}

void MainWindow::onAddBtnClicked()
{
    auto *analysisWidget = new AnalsisWidget(this);
    m_mainLayout->addWidget(analysisWidget);
}

void MainWindow::onDeleteBtnClicked()
{
    QWidget *deletedWidget = m_mainLayout->itemAt(m_mainLayout->count() - 1)->widget();
    if (m_mainLayout->count() > 2) {
        m_mainLayout->removeWidget(deletedWidget);
        deletedWidget->deleteLater();
    }
    QTimer::singleShot(0, this, [&] { resize(sizeHint()); });
}

void MainWindow::initUI()
{
    //title layout
    auto *titleLayout = new QHBoxLayout();
    auto *titleLabel = new QLabel(tr("Hex Bit Analysis"), this);

    titleLabel->setMaximumHeight(25);
    titleLayout->addWidget(titleLabel, 0, Qt::AlignHCenter);
    titleLayout->addWidget(addBtn, 20, Qt::AlignRight);
    titleLayout->addWidget(deleteBtn, 0, Qt::AlignRight);
    m_mainLayout->addLayout(titleLayout);

    //analysis widget
    auto *analysisWidget = new AnalsisWidget(this);
    m_mainLayout->addWidget(analysisWidget);
}

void MainWindow::initConnection()
{
    connect(addBtn, &QPushButton::clicked, this, &MainWindow::onAddBtnClicked);
    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::onDeleteBtnClicked);
}
