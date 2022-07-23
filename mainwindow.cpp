#include "mainwindow.h"
#include "analsiswidget.h"

#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , m_mainLayout(new QVBoxLayout(this))
{
    auto *titleLayout = new QHBoxLayout();
    auto *titleLabel = new QLabel(tr("Hex Bit Analysis"), this);
    titleLabel->setText("Hex Bit Analysis");
    auto *addBtn = new QPushButton(this);
    auto *deleteBtn = new QPushButton(this);
    setBtnIcon(":/icon/icon/plus.png", addBtn);
    setBtnIcon(":/icon/icon/minus.png", deleteBtn);
    titleLayout->addWidget(titleLabel, this->geometry().width() / 2, Qt::AlignCenter);
    titleLayout->addWidget(addBtn, 0, Qt::AlignRight);
    titleLayout->addWidget(deleteBtn, 0, Qt::AlignRight);
    m_mainLayout->addLayout(titleLayout);

    auto *analysisWidget = new AnalsisWidget(this);
    m_mainLayout->addWidget(analysisWidget);
    connect(addBtn, &QPushButton::clicked, this, &MainWindow::onAddBtnClicked);
    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::onDeleteBtnClicked);
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

void MainWindow::setBtnIcon(const QString &path, QPushButton *button)
{
    QPixmap pixmap(path);
    QIcon ButtonIcon(pixmap);
    button->setIcon(ButtonIcon);
    button->setIconSize(pixmap.rect().size());
}
