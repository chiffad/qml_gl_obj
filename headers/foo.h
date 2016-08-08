#ifndef FOO_H
#define FOO_H
#include <QObject>

class Foo : public QObject
{
  Q_OBJECT
public:
    Foo(QObject* paret = 0) : QObject(paret)
    {m_bar = 5;}
    Q_PROPERTY(int bar READ bar NOTIFY barChanged)
    int bar()const {return m_bar;}

signals:
    void barChanged();

private:
    int m_bar;
};
#endif // FOO_H
