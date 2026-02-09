#include "controlbutton.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QPixmap>
#include <QPushButton>

ControlButton::ControlButton(QWidget *parent)
    : QWidget{parent}
{
    auto *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(6);

    auto *addBtn = new QPushButton(this);
    auto *deleteBtn = new QPushButton(this);
    setBtnIcon(":/icon/plus.png", addBtn);
    setBtnIcon(":/icon/minus.png", deleteBtn);

    addBtn->setIconSize(QSize(24, 24));
    deleteBtn->setIconSize(QSize(24, 24));

    addBtn->setStyleSheet("QPushButton{border: none;}");
    deleteBtn->setStyleSheet("QPushButton{border: none;}");

    mainLayout->addWidget(addBtn);
    mainLayout->addWidget(deleteBtn);

    connect(addBtn, &QPushButton::clicked, this, &ControlButton::addBtnClicked);
    connect(deleteBtn, &QPushButton::clicked, this, &ControlButton::deleteBtnClicked);
}
void ControlButton::setBtnIcon(const QString &path, QPushButton *button)
{
    QPixmap pixmap(path);
    QIcon ButtonIcon(pixmap);
    button->setIcon(ButtonIcon);
    button->setIconSize(pixmap.rect().size());
}
