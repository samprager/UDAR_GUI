#ifndef HEXSPINBOX_H
#define HEXSPINBOX_H

#include <QSpinBox>

class QRegExpValidator;

class HexSpinBox : public QSpinBox
{
    Q_OBJECT
public:
    HexSpinBox(QWidget *parent = 0);
    unsigned int hexValue() const;
    void setHexValue(unsigned int value);
protected:
    QValidator::State validate(QString &text, int &pos) const;
    int valueFromText(const QString &text) const;
    QString textFromValue( int value) const;
private:
   // QRegExpValidator *validator;
    inline unsigned int u(int i) const;
    inline int i(unsigned int u) const;
};

#endif // HEXSPINBOX_H
