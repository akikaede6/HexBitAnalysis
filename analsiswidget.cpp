#include "analsiswidget.h"

#include <QButtonGroup>
#include <QCheckBox>
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include "binarywidget.h"
#include "util.h"

AnalsisWidget::AnalsisWidget(QWidget *parent)
    : QWidget{parent}
    , m_inputEdit(new QLineEdit(this))
    , m_outputEdit(new QLineEdit(this))
    , m_mainLayout(new QVBoxLayout(this))
    , m_binaryWidget(new BinaryWidget(this))
{
    //new layout
    auto *dataLayout = new QHBoxLayout();
    //label
    auto *inputLabel = new QLabel(tr("Input Data"), this);
    auto *outputLabel = new QLabel(tr("Output Data"), this);
    auto *restoreBtn = new QPushButton(tr("Restore"), this);
    auto *clearBtn = new QPushButton(tr("Clear"), this);
    auto *resetBtn = new QPushButton(tr("Reset"), this);

    m_outputEdit->setText("00000000");
    m_inputEdit->setMaxLength(8);
    m_inputEdit->setMaximumWidth(editMaxWidth);
    m_outputEdit->setMaximumWidth(editMaxWidth);
    m_outputEdit->setReadOnly(true);

    dataLayout->addWidget(inputLabel, 0, Qt::AlignLeft);
    dataLayout->addWidget(m_inputEdit, 0, Qt::AlignLeft);
    dataLayout->addWidget(outputLabel, 0, Qt::AlignLeft);
    dataLayout->addWidget(m_outputEdit, 0, Qt::AlignLeft);
    dataLayout->addWidget(restoreBtn, 10, Qt::AlignRight);
    dataLayout->addWidget(clearBtn, 0, Qt::AlignRight);
    dataLayout->addWidget(resetBtn, 0, Qt::AlignRight);

    m_mainLayout->addLayout(dataLayout);
    m_mainLayout->addWidget(m_binaryWidget);
    initConnection();
}

void AnalsisWidget::initConnection()
{
    connect(m_inputEdit, &QLineEdit::textEdited, this, &AnalsisWidget::onInputChanged);
    connect(m_inputEdit, &QLineEdit::textEdited, m_binaryWidget, &BinaryWidget::onInputChanged);
    connect(m_binaryWidget, &BinaryWidget::btnClicked, this, &AnalsisWidget::onBtnClicked);
}

void AnalsisWidget::onInputChanged(const QString &input)
{
    bool ok = false;
    ulong hex = input.toULong(&ok, 16);
    int pos = m_inputEdit->cursorPosition();
    m_inputEdit->setText(input.toUpper());
    m_inputEdit->setCursorPosition(pos);
    m_outputEdit->setText(QString("%1").arg(hex, 8, 16, QChar('0')).toUpper());
    m_outputEdit->text();
}

void AnalsisWidget::onBtnClicked(ulong hex)
{
    m_outputEdit->setText(QString("%1").arg(hex, 8, 16, QChar('0')).toUpper());
}
