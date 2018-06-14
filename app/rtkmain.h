#ifndef RTKMAIN_H
#define RTKMAIN_H

#include <QObject>
#include <QLocalSocket>
#include <QTcpSocket>
#include "rtklib.h"
#define SOCKET_PORT 5000

class rtkMain : public QObject
{
    Q_OBJECT
public:
    explicit rtkMain(QObject *parent = nullptr);

private:

    rtksvr_t *svr;
    int svrcycle     =10;
    int buffsize     =32768;


    int strtype[8]={                  // stream types
        STR_SERIAL,STR_TCPCLI,STR_NONE,STR_TCPSVR,STR_FILE,STR_FILE,STR_FILE,STR_NONE
    };
    //Paths
    char strpath[8][MAXSTRMSG];//={"","","","","","","",""}; // stream paths

    int strfmt[5]={                   // stream formats
        STRFMT_UBX,STRFMT_UBX,STRFMT_SP3,SOLF_LLH,SOLF_LLH
    };

    int navmsgsel    =0;             // navigation mesaage select

    //char *cmds = {NULL, NULL. NULL};
    char s1[3][MAXRCVCMD];//={"","",""};

    //char *cmds_periodic = {NULL, NULL. NULL};
    char s2[3][MAXRCVCMD];//={"","",""};

    int nmeacycle    =5000;                             // nmea request cycle (ms)
    int nmeareq      =0;                                // nmea request type (0:off,1:lat/lon,2:single)
    double npos[3];
    prcopt_t prcopt = prcopt_default;                   // processing options
    solopt_t solopt[2]={solopt_default , solopt_default}; // solution options
    stream_t moni;                               // monitor stream
    char errmsg[2048];//="";

    QTcpSocket *socket;

    double Latitude;
    double prevLatitude;
    double Longitude;
    double prevLongitude;
signals:
    void centerChanged(double lati, double longi);

public slots:

    void setParameters(QString serialPort, QString ntripAdress, QString ntripPort, QString ntripMount, QString ntripUser, QString ntripPwd);
    void setParameters(QString serialPort, QString TCPAdress, QString TCPPort);
    int startRtk();
    void stopRtk();

    QVariant getLatitude() {return QVariant(Latitude);}
    QVariant getLongitude() {return QVariant(Longitude);}
    QVariant getBearing();

private slots:
    void socketFinished();

};

#endif // RTKMAIN_H
