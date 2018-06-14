#include "test.h"
#include <QDebug>

Test::Test(QObject *parent) : QObject(parent)
{

}

void Test::testSlot(double la, double lo)
{
    qDebug() << "La: " << la << " Lo: " << lo;
}
