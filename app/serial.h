#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QTimer>
#include <QSerialPort>

class serial : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList portsNames READ portsNames WRITE setPortsNames NOTIFY sig_portsNamesChanged)
public:
    explicit serial(QObject *parent = nullptr);

    QStringList portsNames() const { return mPortNames; }

private:
    QStringList mPortNames;
signals:
    void sig_portsNamesChanged(QStringList portsNames);

public slots:

    void getPorts();
    QString getPortDescription(QString portName);

    void setPortsNames(QStringList portsNames)
    {
        if (mPortNames == portsNames)
            return;

        mPortNames = portsNames;
        emit sig_portsNamesChanged(portsNames);
    }
};

#endif // SERIAL_H
