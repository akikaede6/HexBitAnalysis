#include "fontdialog.h"
#include "util.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

FontDialog::FontDialog(QWidget *parent)
    : QDialog(parent)
    , m_fontEdit(new QLineEdit(this))
    , m_confirmBtn(new QPushButton(tr("confirm"), this))
    , m_cancelBtn(new QPushButton(tr("cancel"), this))
{
    setFont(FontSize::fontSize());
    auto *mainLayout = new QVBoxLayout(this);
    auto *fontLayout = new QHBoxLayout(this);
    auto *buttonLayout = new QHBoxLayout(this);
    auto *fontLabel = new QLabel(tr("Font"), this);
    auto *pxLabel = new QLabel(tr("px"), this);
    fontLayout->addWidget(fontLabel);
    fontLayout->addWidget(m_fontEdit);
    fontLayout->addWidget(pxLabel);
    buttonLayout->addWidget(m_confirmBtn);
    buttonLayout->addWidget(m_cancelBtn);
    mainLayout->addLayout(fontLayout);
    mainLayout->addLayout(buttonLayout);

    connect(m_confirmBtn, &QPushButton::clicked, this, &FontDialog::onConfirmBtnClicked);
    connect(m_cancelBtn, &QPushButton::clicked, this, [&] { this->close(); });
}

void FontDialog::onConfirmBtnClicked()
{
    FontSize::setFontSize(m_fontEdit->text().toInt());
    setFont(FontSize::fontSize());
    emit fontChanged();
    this->close();
}
