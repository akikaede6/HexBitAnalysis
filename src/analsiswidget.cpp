#include "analsiswidget.h"
#include "binarywidget.h"
#include "selectedwidget.h"
#include "util.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
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
    auto *inputLabel = new QLabel(tr("Input Data"), this);
    auto *outputLabel = new QLabel(tr("Output Data"), this);

    m_outputEdit->setText("00000000");
    m_inputEdit->setMaxLength(BitChange::hexMaxLength());
    m_inputEdit->setMaximumWidth(BitChange::hexMaxLength() * FontSize::fontPixel());
    m_outputEdit->setMaximumWidth(BitChange::hexMaxLength() * FontSize::fontPixel());
    m_outputEdit->setReadOnly(true);

    dataLayout->addWidget(inputLabel, 0, Qt::AlignLeft);
    dataLayout->addWidget(m_inputEdit, 0, Qt::AlignLeft);
    dataLayout->addWidget(outputLabel, 0, Qt::AlignLeft);
    dataLayout->addWidget(m_outputEdit, 0, Qt::AlignLeft);
    dataLayout->addStretch();
    dataLayout->addWidget(m_restoreBtn, 0, Qt::AlignRight);
    dataLayout->addWidget(m_clearBtn, 0, Qt::AlignRight);
    dataLayout->addWidget(m_resetBtn, 0, Qt::AlignRight);

    //selected widget
    auto *selectedLayout = new QHBoxLayout();

    selectedLayout->addWidget(m_selectedLabelWidget);
    selectedLayout->addWidget(m_selectedBtnWidget);

    m_mainLayout->addLayout(dataLayout);
    m_mainLayout->addWidget(m_binaryWidget);
    m_mainLayout->addLayout(selectedLayout);
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

    // init font size connect
    connect(this,
            &AnalsisWidget::onFontSizeChanged,
            m_binaryWidget,
            &BinaryWidget::onFontSizeChanged);
    connect(this, &AnalsisWidget::onFontSizeChanged, this, [&] {
        m_inputEdit->setMaximumWidth(BitChange::hexMaxLength() * FontSize::fontPixel());
        m_outputEdit->setMaximumWidth(BitChange::hexMaxLength() * FontSize::fontPixel());
    });
    connect(this,
            &AnalsisWidget::onFontSizeChanged,
            m_selectedLabelWidget,
            &SelectedWidget::onFontSizeChanged);
    connect(this,
            &AnalsisWidget::onFontSizeChanged,
            m_selectedBtnWidget,
            &SelectedWidget::onFontSizeChanged);

    // init bit size connect
    connect(this, &AnalsisWidget::updateBit, this, &AnalsisWidget::updateEdit);
    connect(this,
            &AnalsisWidget::updateBit,
            m_selectedLabelWidget,
            &SelectedWidget::onFontSizeChanged);
    connect(this,
            &AnalsisWidget::updateBit,
            m_selectedBtnWidget,
            &SelectedWidget::onFontSizeChanged);
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
    m_inputEdit->setMaximumWidth(BitChange::hexMaxLength() * FontSize::fontPixel());
    m_outputEdit->setMaximumWidth(BitChange::hexMaxLength() * FontSize::fontPixel());
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
