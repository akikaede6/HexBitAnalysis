#include "binarywidget.h"
#include "util.h"
#include "widget/mousegroupbox.h"

#include <QButtonGroup>
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

BinaryWidget::BinaryWidget(QWidget *parent)
    : QWidget{parent}
    , m_binaryBtnGroup(new QButtonGroup())
    , m_mouseGroupBox(new MouseGroupBox(this))
    , m_mouseMainLayout(new QVBoxLayout(m_mouseGroupBox))
{
    init32Bit();
    init64Bit();
    if (BitChange::bit() == 32)
        hide64Bit();
    initConnection();
}

void BinaryWidget::onInputChanged(const QString &input)
{
    quint64 hex = input.toULongLong(nullptr, Hex);
    for (int i = 0; i < BitChange::bit(); i++) {
        quint64 shiftValue = 1LL << i;
        if ((shiftValue & hex) != 0U) {
            m_labelList.at(i)->setText("1");
            m_labelList.at(i)->setStyleSheet(
                QString::fromUtf8("QLabel{background-color:#FA8072;}"));
            m_binaryBtnGroup->button(i)->setText("1");
            m_binaryBtnGroup->button(i)->setStyleSheet(
                QString::fromUtf8("QPushButton{background-color:#FA8072;}"));
        } else {
            m_labelList.at(i)->setText("0");
            m_labelList.at(i)->setStyleSheet(
                QString::fromUtf8("QLabel{background-color:#B0E0E6;}"));
            m_binaryBtnGroup->button(i)->setText("0");
            m_binaryBtnGroup->button(i)->setStyleSheet(
                QString::fromUtf8("QPushButton{background-color:#B0E0E6;}"));
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
    quint64 hex = 0;
    for (int i = 0; i < BitChange::bit(); i++) {
        hex |= (m_binaryBtnGroup->button(i)->text().toULongLong(nullptr, 2)) << i;
    }
    emit btnClicked(hex);
}

void BinaryWidget::onCheckBoxClicked()
{
    quint64 from = 0;
    quint64 hexInput = 0;
    quint64 hexOutput = 0;
    for (int i = 0; i < BitChange::bit(); i++) {
        auto *checkedBox = m_checkBoxList.at(i);
        if (checkedBox->isChecked()) {
            hexInput |= m_labelList.at(i)->text().toULongLong(nullptr, 2) << from;
            hexOutput |= m_binaryBtnGroup->button(i)->text().toULongLong(nullptr, 2) << from;
            from++;
        }
    }
    emit checkLabelOutput(hexInput);
    emit checkBtnOutput(hexOutput);
}

void BinaryWidget::onClearBtnClicked()
{
    for (int i = 0; i < Bit64; i++) {
        m_checkBoxList.at(i)->setChecked(false);
    }
}

void BinaryWidget::onResetBtnClicked()
{
    for (int i = 0; i < Bit64; i++) {
        m_checkBoxList.at(i)->setChecked(false);
        m_labelList.at(i)->setText("0");
        m_binaryBtnGroup->button(i)->setText("0");
        m_binaryBtnGroup->button(i)->setStyleSheet(
            QString::fromUtf8("QPushButton{background-color:#B0E0E6;}"));
        m_labelList.at(i)->setStyleSheet(QString::fromUtf8("QLabel{background-color:#B0E0E6;}"));
    }
}

void BinaryWidget::onFontSizeChanged()
{
    for (int i = 0; i < Bit64; i++) {
        m_numLabelList.at(i)->setFont(FontSize::fontSize());
        m_labelList.at(i)->setFont(FontSize::fontSize());
        m_binaryBtnGroup->button(i)->setFont(FontSize::fontSize());
        m_binaryBtnGroup->button(i)->setFixedWidth(FontSize::fontPixel());
        m_labelList.at(i)->setFixedWidth(m_binaryBtnGroup->button(i)->width());
    }
}

void BinaryWidget::onBitChanged(int bit)
{
    Q_UNUSED(bit);
    if (BitChange::bit() == Bit32) {
        hide64Bit();
    } else {
        show64Bit();
    }
}

void BinaryWidget::initConnection()
{
    connect(m_binaryBtnGroup,
            QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this,
            &BinaryWidget::onBtnClicked);
}

QFrame *BinaryWidget::createLine()
{
    auto *line = new QFrame;
    line->setFrameShape(QFrame::VLine);
    return line;
}

void BinaryWidget::init32Bit()
{
    auto *mainLayout = new QHBoxLayout(this);
    auto *groupBoxLayoutUp = new QHBoxLayout();
    QVector<QGridLayout *> binaryLayoutVec;
    for (int i = 0; i < Bit32 / BitGroupLength; i++) {
        binaryLayoutVec.push_back(new QGridLayout());
    }

    QVector<QFrame *> line;
    for (int i = 0; i < binaryLayoutVec.length() - 1; i++) {
        line.push_back(createLine());
    }

    for (int i = Bit32 - 1; i >= 0; i--) {
        auto *binaryNumLabel = new QLabel(QString::number(Bit32 - i - 1), this);
        if (i % BitGroupLength == 0)
            binaryNumLabel->setStyleSheet("QLabel{font-weight:bold;color:#9933FA;}");
        else
            binaryNumLabel->setStyleSheet("QLabel{font-weight:bold;color:#FF7F50;}");
        m_numLabelList.append(binaryNumLabel);

        auto *binaryLabel = new QLabel(QString::number(0), this);
        binaryLabel->setStyleSheet(QString::fromUtf8("QLabel{background-color:#B0E0E6;}"));
        binaryLabel->setAlignment(Qt::AlignCenter);
        m_labelList.append(binaryLabel);

        auto *binaryBtn = new QPushButton(QString::number(0), this);
        binaryBtn->setStyleSheet(QString::fromUtf8("QPushButton{background-color:#B0E0E6;}"));
        m_binaryBtnGroup->addButton(binaryBtn, Bit32 - i - 1);

        auto *checkBox = new QCheckBox(this);
        m_checkBoxList.append(checkBox);
        binaryBtn->setFixedWidth(FontSize::fontPixel());
        binaryLabel->setFixedWidth(binaryBtn->width());

        binaryNumLabel->setFont(FontSize::fontSize());
        binaryLabel->setFont(FontSize::fontSize());
        binaryBtn->setFont(FontSize::fontSize());

        QGridLayout *binaryLayout = nullptr;
        switch (i / BitGroupLength) {
        case 0:
            binaryLayout = binaryLayoutVec[0];
            break;
        case 1:
            binaryLayout = binaryLayoutVec[1];
            break;
        case 2:
            binaryLayout = binaryLayoutVec[2];
            break;
        case 3:
            binaryLayout = binaryLayoutVec[3];
            break;
        default:
            break;
        }
        binaryLayout->addWidget(binaryNumLabel, 0, i, Qt::AlignCenter);
        binaryLayout->addWidget(binaryLabel, 1, i, Qt::AlignCenter);
        binaryLayout->addWidget(binaryBtn, 2, i, Qt::AlignCenter);
        binaryLayout->addWidget(checkBox, 3, i, Qt::AlignCenter);
        binaryLayout->setSpacing(binaryBtn->width() / 5);
    }
    int i = 0;
    for (i = 0; i < binaryLayoutVec.length() - 1; i++) {
        groupBoxLayoutUp->addLayout(binaryLayoutVec[i]);
        groupBoxLayoutUp->addWidget(line[i]);
    }
    groupBoxLayoutUp->addLayout(binaryLayoutVec[i]);

    m_mouseMainLayout->insertLayout(1, groupBoxLayoutUp);

    mainLayout->addWidget(m_mouseGroupBox);
    m_mouseGroupBox->addBtnList(m_binaryBtnGroup);
    m_mouseGroupBox->addCheckBoxList(m_checkBoxList);
    m_mouseGroupBox->setFlat(false);
    for (int i = 0; i < Bit32; i++)
        connect(m_checkBoxList.at(i), &QCheckBox::clicked, this, &BinaryWidget::onCheckBoxClicked);
}

void BinaryWidget::init64Bit()
{
    auto *groupBoxLayoutDown = new QHBoxLayout();
    QVector<QGridLayout *> binaryLayoutVec;
    for (int i = Bit32 / BitGroupLength; i < Bit64 / BitGroupLength; i++) {
        binaryLayoutVec.push_back(new QGridLayout());
    }

    QVector<QFrame *> line;
    for (int i = 0; i < binaryLayoutVec.length() - 1; i++) {
        line.push_back(createLine());
    }

    for (int i = Bit64 - 1; i >= Bit32; i--) {
        auto *binaryNumLabel = new QLabel(QString::number(Bit32 - i + Bit64 - 1), this);
        if (i % BitGroupLength == 0)
            binaryNumLabel->setStyleSheet("QLabel{font-weight:bold;color:#9933FA;}");
        else
            binaryNumLabel->setStyleSheet("QLabel{font-weight:bold;color:#FF7F50;}");
        m_numLabelList.append(binaryNumLabel);

        auto *binaryLabel = new QLabel(QString::number(0), this);
        binaryLabel->setStyleSheet(QString::fromUtf8("QLabel{background-color:#B0E0E6;}"));
        binaryLabel->setAlignment(Qt::AlignCenter);
        m_labelList.append(binaryLabel);

        auto *binaryBtn = new QPushButton(QString::number(0), this);
        binaryBtn->setStyleSheet(QString::fromUtf8("QPushButton{background-color:#B0E0E6;}"));
        m_binaryBtnGroup->addButton(binaryBtn, Bit32 - i + Bit64 - 1);

        auto *checkBox = new QCheckBox(this);
        m_checkBoxList.append(checkBox);
        binaryBtn->setFixedWidth(FontSize::fontPixel());
        binaryLabel->setFixedWidth(binaryBtn->width());

        binaryNumLabel->setFont(FontSize::fontSize());
        binaryLabel->setFont(FontSize::fontSize());
        binaryBtn->setFont(FontSize::fontSize());

        QGridLayout *binaryLayout = nullptr;
        switch (i / BitGroupLength) {
        case 4:
            binaryLayout = binaryLayoutVec[0];
            break;
        case 5:
            binaryLayout = binaryLayoutVec[1];
            break;
        case 6:
            binaryLayout = binaryLayoutVec[2];
            break;
        case 7:
            binaryLayout = binaryLayoutVec[3];
            break;
        default:
            break;
        }

        binaryLayout->addWidget(binaryNumLabel, 0, i, Qt::AlignCenter);
        binaryLayout->addWidget(binaryLabel, 1, i, Qt::AlignCenter);
        binaryLayout->addWidget(binaryBtn, 2, i, Qt::AlignCenter);
        binaryLayout->addWidget(checkBox, 3, i, Qt::AlignCenter);
        binaryLayout->setSpacing(binaryBtn->width() / 5);
    }
    int i = 0;
    for (i = 0; i < binaryLayoutVec.length() - 1; i++) {
        groupBoxLayoutDown->addLayout(binaryLayoutVec[i]);
        groupBoxLayoutDown->addWidget(line[i]);
    }
    groupBoxLayoutDown->addLayout(binaryLayoutVec[i]);

    m_mouseMainLayout->insertLayout(0, groupBoxLayoutDown);

    m_mouseGroupBox->addBtnList(m_binaryBtnGroup);
    m_mouseGroupBox->addCheckBoxList(m_checkBoxList);
    for (int i = Bit32; i < Bit64; i++)
        connect(m_checkBoxList.at(i), &QCheckBox::clicked, this, &BinaryWidget::onCheckBoxClicked);
}

void BinaryWidget::hide64Bit()
{
    for (int i = Bit64 - 1; i >= Bit32; i--) {
        m_numLabelList.at(i)->setVisible(false);
        m_labelList.at(i)->setVisible(false);
        m_binaryBtnGroup->button(i)->setVisible(false);
        m_checkBoxList.at(i)->setVisible(false);
    }
}

void BinaryWidget::show64Bit()
{
    for (int i = Bit64 - 1; i >= Bit32; i--) {
        m_numLabelList.at(i)->setVisible(true);
        m_labelList.at(i)->setVisible(true);
        m_binaryBtnGroup->button(i)->setVisible(true);
        m_checkBoxList.at(i)->setVisible(true);
    }
}
