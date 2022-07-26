#include "selectedwidget.h"
#include "util.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

SelectedWidget::SelectedWidget(QWidget *parent)
    : QWidget{parent}
    , m_hexDisEdit(new QLineEdit("0x0", this))
    , m_decDisEdit(new QLineEdit("0", this))
{
    auto *mainLayout = new QHBoxLayout(this);
    auto *hexLabel = new QLabel("HEX", this);
    auto *decLabel = new QLabel("DEC", this);
    m_hexDisEdit->setMaximumWidth(HexMaxLength * FontSize::fontPixel());
    m_decDisEdit->setMaximumWidth(HexMaxLength * FontSize::fontPixel());
    m_hexDisEdit->setReadOnly(true);
    m_decDisEdit->setReadOnly(true);
    mainLayout->addWidget(hexLabel, 0, Qt::AlignCenter);
    mainLayout->addWidget(m_hexDisEdit, 0, Qt::AlignCenter);
    mainLayout->addWidget(decLabel, 0, Qt::AlignCenter);
    mainLayout->addWidget(m_decDisEdit, 0, Qt::AlignCenter);
}

void SelectedWidget::onCheckBoxClicked(const ulong &dec)
{
    m_hexDisEdit->setText(QString("0x") + QString("%1").arg(dec, 0, Hex).toUpper());
    m_decDisEdit->setText(QString("%1").arg(dec));
}

void SelectedWidget::onClearBtnClicked()
{
    m_hexDisEdit->setText("0x0");
    m_decDisEdit->setText("0");
}

void SelectedWidget::onFontSizeChanged()
{
    m_hexDisEdit->setMaximumWidth(HexMaxLength * FontSize::fontPixel());
    m_decDisEdit->setMaximumWidth(HexMaxLength * FontSize::fontPixel());
}
