#include "binarywidget.h"
#include "mousegroupbox.h"
#include "util.h"

#include <QButtonGroup>
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

BinaryWidget::BinaryWidget(QWidget *parent)
    : QWidget{parent}
    , m_binaryBtnGroup(new QButtonGroup())
{
    auto *mainLayout = new QHBoxLayout(this);
    auto *mouseGroupBox = new MouseGroupBox(this);
    auto *groupBoxLayout = new QHBoxLayout(mouseGroupBox);
    auto *binaryLayout_1 = new QGridLayout();
    auto *binaryLayout_2 = new QGridLayout();
    auto *binaryLayout_3 = new QGridLayout();
    auto *binaryLayout_4 = new QGridLayout();

    auto *line_1 = createLine();
    auto *line_2 = createLine();
    auto *line_3 = createLine();
    QFont samplefont;
    for (int i = 0; i < Bit; i++) {
        auto *binaryNumLabel = new QLabel(QString::number(Bit - i - 1), this);
        (i % HexMaxLength == 0)
            ? binaryNumLabel->setStyleSheet("QLabel{font-weight:bold;color:#9933FA;}")
            : binaryNumLabel->setStyleSheet("QLabel{font-weight:bold;color:#FF7F50;}");

        auto *binaryLabel = new QLabel(QString::number(0), this);
        binaryLabel->setStyleSheet(QString::fromUtf8("QLabel{background-color:#B0E0E6;}"));
        binaryLabel->setAlignment(Qt::AlignCenter);
        m_labelList.append(binaryLabel);

        auto *binaryBtn = new QPushButton(QString::number(0), this);
        binaryBtn->setStyleSheet(QString::fromUtf8("QPushButton{background-color:#B0E0E6;}"));
        m_binaryBtnGroup->addButton(binaryBtn, i);
        //TODO: size adjust
        binaryBtn->setMaximumWidth(25);
        binaryLabel->setMinimumWidth(binaryBtn->width());

        auto *checkBox = new QCheckBox(this);
        m_checkBoxList.append(checkBox);
        QGridLayout *binaryLayout = nullptr;
        switch (i / HexMaxLength) {
        case 0:
            binaryLayout = binaryLayout_1;
            break;
        case 1:
            binaryLayout = binaryLayout_2;
            break;
        case 2:
            binaryLayout = binaryLayout_3;
            break;
        case 3:
            binaryLayout = binaryLayout_4;
            break;
        default:
            break;
        }
        binaryLayout->addWidget(binaryNumLabel, 0, i, Qt::AlignCenter);
        binaryLayout->addWidget(binaryLabel, 1, i, Qt::AlignCenter);
        binaryLayout->addWidget(binaryBtn, 2, i);
        binaryLayout->addWidget(checkBox, 3, i, Qt::AlignCenter);
        binaryLayout->setSpacing(binaryBtn->width() / 5);
    }
    groupBoxLayout->addLayout(binaryLayout_1);
    groupBoxLayout->addWidget(line_1);
    groupBoxLayout->addLayout(binaryLayout_2);
    groupBoxLayout->addWidget(line_2);
    groupBoxLayout->addLayout(binaryLayout_3);
    groupBoxLayout->addWidget(line_3);
    groupBoxLayout->addLayout(binaryLayout_4);

    mainLayout->addWidget(mouseGroupBox);
    mouseGroupBox->addBtnList(m_binaryBtnGroup);
    mouseGroupBox->addCheckBoxList(m_checkBoxList);
    mouseGroupBox->setFlat(false);
    initConnection();
}

void BinaryWidget::onInputChanged(const QString &input)
{
    ulong hex = input.toULong(nullptr, Hex);
    for (int i = 0; i < Bit; i++) {
        if (((1 << i) & hex) != 0U) {
            m_labelList.at(Bit - i - 1)->setText("1");
            m_labelList.at(Bit - i - 1)
                ->setStyleSheet(QString::fromUtf8("QLabel{background-color:#FA8072;}"));
            m_binaryBtnGroup->button(Bit - i - 1)->setText("1");
            m_binaryBtnGroup->button(Bit - i - 1)
                ->setStyleSheet(QString::fromUtf8("QPushButton{background-color:#FA8072;}"));
        } else {
            m_labelList.at(Bit - i - 1)->setText("0");
            m_labelList.at(Bit - i - 1)
                ->setStyleSheet(QString::fromUtf8("QLabel{background-color:#B0E0E6;}"));
            m_binaryBtnGroup->button(Bit - i - 1)->setText("0");
            m_binaryBtnGroup->button(Bit - i - 1)
                ->setStyleSheet(QString::fromUtf8("QPushButton{background-color:#B0E0E6;}"));
        }
    }
}

void BinaryWidget::onBtnClicked(QAbstractButton *clickedBtn)
{
    clickedBtn->setText(QString::number(static_cast<int>(clickedBtn->text().toInt() == 0)));
    if (clickedBtn->styleSheet() == "QPushButton{background-color:#FFD700;}") {
        if (clickedBtn->text().toInt() != 0) {
            clickedBtn->setStyleSheet(QString::fromUtf8("QPushButton{background-color:#FA8072;}"));
        } else {
            clickedBtn->setStyleSheet(QString::fromUtf8("QPushButton{background-color:#B0E0E6;}"));
        }
    } else {
        clickedBtn->setStyleSheet(QString::fromUtf8("QPushButton{background-color:#FFD700;}"));
    }
    ulong hex = 0;
    for (int i = 0; i < Bit; i++) {
        hex |= (m_binaryBtnGroup->button(Bit - i - 1)->text().toUInt(nullptr, 2)) << i;
    }
    emit btnClicked(hex);
}

void BinaryWidget::onCheckBoxClicked()
{
    int from = 0;
    ulong hexInput = 0;
    ulong hexOutput = 0;
    for (int i = 0; i < Bit; i++) {
        auto *checkedBox = m_checkBoxList.at(Bit - i - 1);
        if (checkedBox->isChecked()) {
            hexInput |= m_labelList.at(Bit - i - 1)->text().toUInt(nullptr, 2) << from;
            hexOutput |= m_binaryBtnGroup->button(Bit - i - 1)->text().toUInt(nullptr, 2) << from;
            from++;
        }
    }
    emit checkLabelOutput(hexInput);
    emit checkBtnOutput(hexOutput);
}

void BinaryWidget::onClearBtnClicked()
{
    for (int i = 0; i < Bit; i++) {
        m_checkBoxList.at(i)->setChecked(false);
    }
}

void BinaryWidget::onResetBtnClicked()
{
    for (int i = 0; i < Bit; i++) {
        m_checkBoxList.at(i)->setChecked(false);
        m_labelList.at(i)->setText("0");
        m_binaryBtnGroup->button(i)->setText("0");
        m_binaryBtnGroup->button(i)->setStyleSheet(
            QString::fromUtf8("QPushButton{background-color:#B0E0E6;}"));
        m_labelList.at(i)->setStyleSheet(QString::fromUtf8("QLabel{background-color:#B0E0E6;}"));
    }
}

void BinaryWidget::initConnection()
{
    connect(m_binaryBtnGroup,
            QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this,
            &BinaryWidget::onBtnClicked);
    for (int i = 0; i < Bit; i++)
        connect(m_checkBoxList.at(i), &QCheckBox::clicked, this, &BinaryWidget::onCheckBoxClicked);
}

QFrame *BinaryWidget::createLine()
{
    auto *line = new QFrame;
    line->setFrameShape(QFrame::VLine);
    return line;
}
