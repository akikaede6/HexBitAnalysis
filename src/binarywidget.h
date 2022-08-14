#ifndef BINARYWIDGET_H
#define BINARYWIDGET_H

#include <QWidget>

class QLabel;
class QButtonGroup;
class QCheckBox;
class QAbstractButton;
class QFrame;
class QVBoxLayout;
class MouseGroupBox;
class BinaryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BinaryWidget(QWidget *parent = nullptr);

public slots:
    void onInputChanged(const QString &input);
    void onBtnClicked(QAbstractButton *clickedBtn);
    void onCheckBoxClicked();
    void onClearBtnClicked();
    void onResetBtnClicked();
    void onFontSizeChanged();
    void onBitChanged(int bit);

signals:
    void btnClicked(quint64 hex);
    void checkLabelOutput(const quint64 &dec);
    void checkBtnOutput(const quint64 &dec);

private:
    void initConnection();
    static QFrame *createLine();
    void init32Bit();
    void init64Bit();
    void hide64Bit();
    void show64Bit();

private:
    QList<QLabel *> m_numLabelList;
    QList<QLabel *> m_labelList;
    QButtonGroup *m_binaryBtnGroup;
    QList<QCheckBox *> m_checkBoxList;
    MouseGroupBox *m_mouseGroupBox;
    QVBoxLayout *m_mouseMainLayout;
};

#endif // BINARYWIDGET_H
