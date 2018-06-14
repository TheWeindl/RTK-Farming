#ifndef RTKSETTINGS_H
#define RTKSETTINGS_H

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QRect>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "rtkmain.h"
#include "serial.h"

class RTKSettings : public QWidget
{
    Q_OBJECT
public:
    explicit RTKSettings(QWidget *parent = nullptr, rtkMain* rtk = nullptr);
    
    rtkMain* rtkmain;
private:
    QLabel* laRTKSettingName;
    QComboBox* cbSerial;
    QLabel* laSerialName;
    QLabel* laSerialDesc;
    QLabel* laTCPName;
    QLineEdit* leTCP;
    QLabel* laPortName;
    QLineEdit* lePort;
    QWidget *horizontalLineWidget;
    QPushButton* btReset;
    QPushButton* btStart;
    serial* Serial;
    QLabel* laStartSuccess;

    QVBoxLayout* mainLayout;
    QHBoxLayout* settingLabelLayout;
    QHBoxLayout* serialLabelLayout;
    QHBoxLayout* serialLayout;
    QHBoxLayout* TCPLabelLayout;
    QHBoxLayout* TCPLayout;
    QHBoxLayout* buttonLayout;


    QString cDefaultTCP = "blank.servebeer.com";
    QString cDefaultPort = "5001";

    QString cStart = "Start";
    QString cStop = "Stop";

    QString cStartError = "Unable to start rtk!";

    void enableLayout(bool enable);

private slots:
    void updateComboBox(QStringList portNames);
    void updateSerialDesc(const QString& portDesc);
    void resetPressed();
    void startPressed();

signals:

public slots:

};

#endif // RTKSETTINGS_H
