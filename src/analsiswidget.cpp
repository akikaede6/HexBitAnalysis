#include "analsiswidget.h"
#include "binarywidget.h"
#include "selectedwidget.h"
#include "util.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSizePolicy>
#include <QTimer>
#include <QVBoxLayout>

AnalsisWidget::AnalsisWidget(QWidget *parent)
    : QWidget{parent}
    , m_inputEdit(new QLineEdit(this))
    , m_outputEdit(new QLineEdit(this))
    , m_restoreBtn(new QPushButton(tr("Restore"), this))
    , m_clearBtn(new QPushButton(tr("Clear"), this))
    , m_resetBtn(new QPushButton(tr("Reset"), this))
    , m_mainLayout(new QVBoxLayout(this))
    , m_binaryWidget(new BinaryWidget(this))
    , m_selectedLabelWidget(new SelectedWidget(this))
    , m_selectedBtnWidget(new SelectedWidget(this))
{
    auto *dataLayout = new QHBoxLayout();
    auto *fieldsLayout = new QGridLayout();
    auto *buttonLayout = new QHBoxLayout();
    auto *inputLabel = new QLabel(tr("Input Data"), this);
    auto *outputLabel = new QLabel(tr("Output Data"), this);

    m_outputEdit->setText("00000000");
    m_inputEdit->setMaxLength(BitChange::hexMaxLength());
    // m_inputEdit->setMaximumWidth(BitChange::hexMaxLength() * FontSize::fontPixel());
    // m_outputEdit->setMaximumWidth(BitChange::hexMaxLength() * FontSize::fontPixel());
    m_outputEdit->setReadOnly(true);
    m_inputEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_outputEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    fieldsLayout->setContentsMargins(0, 0, 0, 0);
    fieldsLayout->addWidget(inputLabel, 0, 0);
    fieldsLayout->addWidget(m_inputEdit, 0, 1);
    fieldsLayout->addWidget(outputLabel, 0, 2);
    fieldsLayout->addWidget(m_outputEdit, 0, 3);
    fieldsLayout->setColumnStretch(1, 1);
    fieldsLayout->setColumnStretch(3, 1);

    buttonLayout->setContentsMargins(0, 0, 0, 0);
    buttonLayout->addWidget(m_restoreBtn);
    buttonLayout->addWidget(m_clearBtn);
    buttonLayout->addWidget(m_resetBtn);

    dataLayout->addLayout(fieldsLayout, 1);
    dataLayout->addLayout(buttonLayout, 0);

    //selected widget
    auto *selectedLayout = new QHBoxLayout();

    m_binaryWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_selectedLabelWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_selectedBtnWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    selectedLayout->addWidget(m_selectedLabelWidget);
    selectedLayout->addWidget(m_selectedBtnWidget);
    selectedLayout->setStretch(0, 1);
    selectedLayout->setStretch(1, 1);

    m_mainLayout->addLayout(dataLayout);
    m_mainLayout->addWidget(m_binaryWidget);
    m_mainLayout->addLayout(selectedLayout);
    m_mainLayout->setStretch(1, 1);
    initConnection();
}

void AnalsisWidget::initConnection()
{
    connect(m_inputEdit, &QLineEdit::textEdited, this, &AnalsisWidget::onInputChanged);
    connect(m_inputEdit, &QLineEdit::textEdited, m_binaryWidget, &BinaryWidget::onInputChanged);
    connect(m_binaryWidget, &BinaryWidget::btnClicked, this, &AnalsisWidget::onBtnClicked);
    connect(m_binaryWidget,
            &BinaryWidget::btnClicked,
            m_binaryWidget,
            &BinaryWidget::onCheckBoxClicked);

    // init selected label connect
    connect(m_binaryWidget,
            &BinaryWidget::checkLabelOutput,
            m_selectedLabelWidget,
            &SelectedWidget::onCheckBoxClicked);

    // init selected btn connect
    connect(m_binaryWidget,
            &BinaryWidget::checkBtnOutput,
            m_selectedBtnWidget,
            &SelectedWidget::onCheckBoxClicked);

    // init clear btn connect
    connect(m_clearBtn, &QPushButton::clicked, m_binaryWidget, &BinaryWidget::onClearBtnClicked);
    connect(m_clearBtn,
            &QPushButton::clicked,
            m_selectedLabelWidget,
            &SelectedWidget::onClearBtnClicked);
    connect(m_clearBtn,
            &QPushButton::clicked,
            m_selectedBtnWidget,
            &SelectedWidget::onClearBtnClicked);

    // init reset btn connect
    connect(m_resetBtn, &QPushButton::clicked, m_binaryWidget, &BinaryWidget::onResetBtnClicked);
    connect(m_resetBtn,
            &QPushButton::clicked,
            m_selectedLabelWidget,
            &SelectedWidget::onClearBtnClicked);
    connect(m_resetBtn,
            &QPushButton::clicked,
            m_selectedBtnWidget,
            &SelectedWidget::onClearBtnClicked);
    connect(m_resetBtn, &QPushButton::clicked, this, &AnalsisWidget::onResetBtnClicked);

    connect(m_restoreBtn, &QPushButton::clicked, this, &AnalsisWidget::onRestoreBtnClicked);
    connect(this, &AnalsisWidget::restoreBinary, m_binaryWidget, &BinaryWidget::onInputChanged);
    connect(this, &AnalsisWidget::restoreBinary, this, &AnalsisWidget::onInputChanged);
}

void AnalsisWidget::onInputChanged(const QString &input)
{
    quint64 hex = input.toULongLong(nullptr, Hex);
    int pos = m_inputEdit->cursorPosition();
    m_inputEdit->setText(input.toUpper());
    m_inputEdit->setCursorPosition(pos);
    m_outputEdit->setText(
        QString("%1").arg(hex, BitChange::hexMaxLength(), Hex, QChar('0')).toUpper());
    m_outputEdit->text();
}

void AnalsisWidget::onBtnClicked(quint64 hex)
{
    m_outputEdit->setText(
        QString("%1").arg(hex, BitChange::hexMaxLength(), Hex, QChar('0')).toUpper());
}

void AnalsisWidget::onResetBtnClicked()
{
    m_inputEdit->setText("");
    if (BitChange::bit() == 32) {
        m_outputEdit->setText(default32BitText);
    } else {
        m_outputEdit->setText(default64BitText);
    }
}

void AnalsisWidget::onRestoreBtnClicked()
{
    emit restoreBinary(m_inputEdit->text());
}

void AnalsisWidget::updateEdit(int bit)
{
    Q_UNUSED(bit);
    m_inputEdit->setText("");
    m_inputEdit->setMaxLength(BitChange::hexMaxLength());
    // m_inputEdit->setMaximumWidth(BitChange::hexMaxLength() * FontSize::fontPixel());
    // m_outputEdit->setMaximumWidth(BitChange::hexMaxLength() * FontSize::fontPixel());
    if (BitChange::bit() == 32) {
        m_outputEdit->setText(default32BitText);
    } else {
        m_outputEdit->setText(default64BitText);
    }
    emit restoreBinary(m_inputEdit->text());
    m_selectedLabelWidget->onClearBtnClicked();
    m_selectedBtnWidget->onClearBtnClicked();
    m_binaryWidget->onResetBtnClicked();
}

void AnalsisWidget::onBitChanged(int bit)
{
    m_inputEdit->setText("");
    m_inputEdit->setMaxLength(BitChange::hexMaxLength());
    m_binaryWidget->onBitChanged(bit);
    QTimer::singleShot(0, this, [&] { this->adjustSize(); });
}
