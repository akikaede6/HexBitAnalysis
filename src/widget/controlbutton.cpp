#include "controlbutton.h"

#include <QGridLayout>
#include <QPushButton>

ControlButton::ControlButton(QWidget *parent)
    : QWidget{parent}
{
    auto *mainLayout = new QGridLayout(this);
    auto *leftAdd = new QPushButton(this);
    auto *belowAdd = new QPushButton(this);
    auto *leftDelete = new QPushButton(this);
    auto *belowDelete = new QPushButton(this);
    setBtnIcon(":/icon/plus.png", leftAdd);
    setBtnIcon(":/icon/plus.png", belowAdd);
    setBtnIcon(":/icon/minus.png", leftDelete);
    setBtnIcon(":/icon/minus.png", belowDelete);
    mainLayout->addWidget(leftAdd, 1, 2);
    mainLayout->addWidget(belowAdd, 2, 1);
    mainLayout->addWidget(leftDelete, 1, 0);
    mainLayout->addWidget(belowDelete, 0, 1);

    leftAdd->setIconSize(QSize(30, 30));
    belowAdd->setIconSize(QSize(30, 30));
    leftDelete->setIconSize(QSize(30, 30));
    belowDelete->setIconSize(QSize(30, 30));

    //    leftAdd->setFixedSize(30, 30);
    //    belowAdd->setFixedSize(30, 30);
    //    leftDelete->setFixedSize(30, 30);
    //    belowDelete->setFixedSize(30, 30);

    leftAdd->setStyleSheet("QPushButton{border: none;}");
    belowAdd->setStyleSheet("QPushButton{border: none;}");
    leftDelete->setStyleSheet("QPushButton{border: none;}");
    belowDelete->setStyleSheet("QPushButton{border: none;}");

    connect(leftAdd, &QPushButton::clicked, this, &ControlButton::rightAddBtnClicked);
    connect(leftDelete, &QPushButton::clicked, this, &ControlButton::rightDeleteBtnClicked);
    connect(belowAdd, &QPushButton::clicked, this, &ControlButton::belowAddBtnClicked);
    connect(belowDelete, &QPushButton::clicked, this, &ControlButton::belowDeleteBtnClicked);

    setFixedHeight(150);
}
void ControlButton::setBtnIcon(const QString &path, QPushButton *button)
{
    QPixmap pixmap(path);
    QIcon ButtonIcon(pixmap);
    button->setIcon(ButtonIcon);
    button->setIconSize(pixmap.rect().size());
}
