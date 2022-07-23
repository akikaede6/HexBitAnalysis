#ifndef SELECTEDWIDGET_H
#define SELECTEDWIDGET_H

#include <QWidget>

class QLineEdit;
class SelectedWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SelectedWidget(QWidget *parent = nullptr);

public slots:
    void onCheckBoxClicked(const ulong &dec);
    void onClearBtnClicked();

private:
    QLineEdit *m_hexDisEdit;
    QLineEdit *m_decDisEdit;
};

#endif // SELECTEDWIDGET_H
