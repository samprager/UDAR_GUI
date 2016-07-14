#include <QTGui>
#include "hexspinbox.h"

HexSpinBox::HexSpinBox(QWidget *parent)
    : QSpinBox(parent)
{
    setPrefix("0x");
    setDisplayIntegerBase(16);
    setRange(INT_MIN,INT_MAX);
    //validator = new QRegExpValidator(QRegExp("[0-9A-Fa-f]{1,8}"),this);
}
unsigned int HexSpinBox::hexValue() const
{
    return u(value());
}
void HexSpinBox::setHexValue(unsigned int value)
{
    setValue(i(value));
}
QValidator::State HexSpinBox::validate(QString &text, int &pos) const
{
   // return validator->validate(text,pos);
    QString copy(text);
    if (copy.startsWith("0x"))
        copy.remove(0, 2);
    pos -= copy.size() - copy.trimmed().size();
    copy = copy.trimmed();
    if (copy.isEmpty())
        return QValidator::Intermediate;
    text = QString("0x") + copy.toUpper();
    bool okay;
    unsigned int val = copy.toUInt(&okay, 16);
    if (!okay)
        return QValidator::Invalid;
    return QValidator::Acceptable;
}
QString HexSpinBox::textFromValue( int value) const
{
    return QString::number(u(value),16).toUpper();
}
int HexSpinBox::valueFromText(const QString &text) const
{
    bool ok;
    return i(text.toInt(&ok,16));
}
inline unsigned int HexSpinBox::u(int i) const
{
    return *reinterpret_cast<unsigned int *>(&i);
}
inline int HexSpinBox::i(unsigned int u) const
{
    return *reinterpret_cast<int *>(&u);
}
