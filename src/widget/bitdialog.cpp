#include "bitdialog.h"
#include "../util.h"

#include <QButtonGroup>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>

BitDialog::BitDialog(QWidget *parent)
    : QDialog(parent)
    , m_confirmBtn(new QPushButton(tr("confirm"), this))
    , m_cancelBtn(new QPushButton(tr("cancel"), this))
    , m_btnGroup(new QButtonGroup)
{
    auto *mainLayout = new QVBoxLayout(this);
    auto *buttonLayout = new QHBoxLayout();
    auto *bit32Btn = new QRadioButton(tr("32 bit"), this);
    auto *bit64Btn = new QRadioButton(tr("64 bit"), this);
    m_btnGroup->addButton(bit32Btn, 0);
    m_btnGroup->addButton(bit64Btn, 1);
    buttonLayout->addWidget(m_confirmBtn);
    buttonLayout->addWidget(m_cancelBtn);
    mainLayout->addWidget(bit32Btn, 0, Qt::AlignCenter);
    mainLayout->addWidget(bit64Btn, 0, Qt::AlignCenter);
    mainLayout->addLayout(buttonLayout);
    if (BitChange::bit() == 32) {
        m_btnGroup->button(0)->setChecked(true);
    } else {
        m_btnGroup->button(1)->setChecked(true);
    }
    connect(m_confirmBtn, &QPushButton::clicked, this, &BitDialog::onConfirmBtnClicked);
    connect(m_cancelBtn, &QPushButton::clicked, this, [&] { this->close(); });
}

void BitDialog::onConfirmBtnClicked()
{
    if (m_btnGroup->checkedId() == 0) {
        BitChange::setBit(Bit32);
        emit bitChanged(Bit32);
    } else {
        BitChange::setBit(Bit64);
        emit bitChanged(Bit64);
    }
    this->close();
    this->deleteLater();
}
