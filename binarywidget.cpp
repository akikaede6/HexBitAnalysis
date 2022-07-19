#include "binarywidget.h"

#include <QButtonGroup>
#include <QCheckBox>
#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include "util.h"

BinaryWidget::BinaryWidget(QWidget *parent)
    : QWidget{parent}
    , m_mainLayout(new QHBoxLayout(this))
    , m_binaryLayout_1(new QGridLayout())
    , m_binaryLayout_2(new QGridLayout())
    , m_binaryLayout_3(new QGridLayout())
    , m_binaryLayout_4(new QGridLayout())
    , m_binaryBtnGroup(new QButtonGroup())
{
    auto *line_1 = createLine();
    auto *line_2 = createLine();
    auto *line_3 = createLine();
    for (int i = 0; i < bit; i++) {
        //num label
        auto *binaryNumLabel = new QLabel(QString::number(bit - i - 1), this);
        (i % 8 == 0)
            ? binaryNumLabel->setStyleSheet("QLabel{font-weight:bold;color:rgb(153,51,250);}")
            : binaryNumLabel->setStyleSheet("QLabel{font-weight:bold;color:rgb(255,127,80);}");

        //binary label
        auto *binaryLabel = new QLabel(QString::number(0), this);
        binaryLabel->setStyleSheet(
            QString::fromUtf8("QLabel{background-color:rgb(176, 224,230);}"));
        binaryLabel->setAlignment(Qt::AlignCenter);
        m_labelList.append(binaryLabel);
        //binary button
        auto *binaryBtn = new QPushButton(QString::number(0), this);
        binaryBtn->setStyleSheet(
            QString::fromUtf8("QPushButton{background-color:rgb(176, 224,230);}"));
        m_binaryBtnGroup->addButton(binaryBtn, bit - i - 1);
        binaryBtn->setMaximumWidth(25);
        binaryLabel->setMinimumWidth(binaryBtn->width());
        //check box
        auto *checkBox = new QCheckBox(this);
        m_checkBoxList.append(checkBox);
        QGridLayout *binaryLayout = nullptr;
        switch (i / 8) {
        case 0:
            binaryLayout = m_binaryLayout_1;
            break;
        case 1:
            binaryLayout = m_binaryLayout_2;
            break;
        case 2:
            binaryLayout = m_binaryLayout_3;
            break;
        case 3:
            binaryLayout = m_binaryLayout_4;
            break;
        default:
            break;
        }
        binaryLayout->addWidget(binaryNumLabel, 0, i, Qt::AlignCenter);
        binaryLayout->addWidget(binaryLabel, 1, i, Qt::AlignCenter);
        binaryLayout->addWidget(binaryBtn, 2, i);
        binaryLayout->addWidget(checkBox, 3, i, Qt::AlignCenter);
        binaryLayout->setSpacing(5);
    }
    m_mainLayout->addLayout(m_binaryLayout_1);
    m_mainLayout->addWidget(line_1);
    m_mainLayout->addLayout(m_binaryLayout_2);
    m_mainLayout->addWidget(line_2);
    m_mainLayout->addLayout(m_binaryLayout_3);
    m_mainLayout->addWidget(line_3);
    m_mainLayout->addLayout(m_binaryLayout_4);
    m_mainLayout->setSpacing(30);
    initConnection();
}

void BinaryWidget::onInputChanged(const QString &input)
{
    bool ok = false;
    ulong hex = input.toULong(&ok, 16);
    for (int i = 0; i < bit; i++) {
        if (((1 << i) & hex) != 0U) {
            m_labelList[bit - i - 1]->setText("1");
            m_labelList[bit - i - 1]->setStyleSheet(
                QString::fromUtf8("QLabel{background-color:rgb(250,128,114);}"));
            m_binaryBtnGroup->button(i)->setText("1");
            m_binaryBtnGroup->button(i)->setStyleSheet(
                QString::fromUtf8("QPushButton{background-color:rgb(250,128,114);}"));
        } else {
            m_labelList[bit - i - 1]->setText("0");
            m_labelList[bit - i - 1]->setStyleSheet(
                QString::fromUtf8("QLabel{background-color:rgb(176, 224,230);}"));
            m_binaryBtnGroup->button(i)->setText("0");
            m_binaryBtnGroup->button(i)->setStyleSheet(
                QString::fromUtf8("QPushButton{background-color:rgb(176, 224,230);}"));
        }
    }
}

void BinaryWidget::onBtnClicked(QAbstractButton *clickedBtn)
{
    bool ok = false;
    clickedBtn->setText(QString::number(static_cast<int>(clickedBtn->text().toInt() == 0)));
    if (clickedBtn->styleSheet() == "QPushButton{background-color:rgb(255,215,0);}") {
        if (clickedBtn->text().toInt() != 0) {
            clickedBtn->setStyleSheet(
                QString::fromUtf8("QPushButton{background-color:rgb(250,128,114);}"));
        } else {
            clickedBtn->setStyleSheet(
                QString::fromUtf8("QPushButton{background-color:rgb(176, 224,230);}"));
        }
    } else {
        clickedBtn->setStyleSheet(
            QString::fromUtf8("QPushButton{background-color:rgb(255,215,0);}"));
    }
    ulong hex = 0;
    for (int i = 0; i < bit; i++) {
        hex |= (m_binaryBtnGroup->button(i)->text().toUInt(&ok, 2)) << i;
    }
    emit btnClicked(hex);
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
