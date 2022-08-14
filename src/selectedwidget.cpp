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
    QFontMetrics fm = m_hexDisEdit->fontMetrics();
    m_hexDisEdit->setFixedWidth(fm.boundingRect(QString(MaxHexWidth)).width() + 6);
    m_decDisEdit->setFixedWidth(fm.boundingRect(QString(MaxDecWidth)).width() + 6);
    m_hexDisEdit->setReadOnly(true);
    m_decDisEdit->setReadOnly(true);
    mainLayout->setSpacing(10);
    mainLayout->addWidget(hexLabel, 0, Qt::AlignCenter);
    mainLayout->addWidget(m_hexDisEdit, 0, Qt::AlignCenter);
    mainLayout->addWidget(decLabel, 0, Qt::AlignCenter);
    mainLayout->addWidget(m_decDisEdit, 0, Qt::AlignCenter);
}

void SelectedWidget::onCheckBoxClicked(const quint64 &dec)
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
    // FIXME: hard coded width
    QFontMetrics fm = m_hexDisEdit->fontMetrics();
    m_hexDisEdit->setFixedWidth(fm.boundingRect(QString(MaxHexWidth)).width() + 6);
    m_decDisEdit->setFixedWidth(fm.boundingRect(QString(MaxDecWidth)).width() + 6);
}
