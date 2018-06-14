#include "rtkmain.h"
#include <QDebug>
#include <QtMath>


rtkMain::rtkMain(QObject *parent) : QObject(parent)
{

    svr = new rtksvr_t;
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(readyRead()), this, SLOT(socketFinished()));

    traceopen("test.trace");
    tracelevel(5);
    rtksvrinit(svr);
    for(int i=0;i<8;i++)
    {
        memset(strpath[i], 0, MAXSTRMSG);
    }

    // Skip header of output
    solopt[0].outhead = 0;

    prcopt.mode = PMODE_KINEMA;
    prcopt.soltype = 0;
    prcopt.nf = 1;
    prcopt.navsys |= SYS_GPS | SYS_SBS | SYS_GLO | SYS_GAL;
    prcopt.modear = 3;
    prcopt.glomodear = 1;
    prcopt.sateph = EPHOPT_BRDC;
    prcopt.minfix = 100;
    prcopt.ionoopt = IONOOPT_BRDC;
    prcopt.tropopt = TROPOPT_SAAS;
    prcopt.maxaveep = 0;
    prcopt.initrst = 0;
    prcopt.outsingle = 1;
    memset(prcopt.rnxopt, 0, 256*2);
    memset(prcopt.posopt, 0, 6);
    prcopt. syncsol = 0;
    memset(prcopt.odisp,0,2*6*11);
    memset(&prcopt.exterr, 0, sizeof(prcopt.exterr));
    prcopt. freqopt = 0;
    memset(prcopt.pppopt, 0, 256);
    solopt[0].posf = SOLF_LLH;
    solopt[0].outhead = 0;
    solopt[0].sstat= 2;
    //solopt[0].trace = 5;
    solopt[0].maxsolstd = 0;

}

void rtkMain::setParameters(QString serialPort, QString ntripAdress, QString ntripPort, QString ntripMount, QString ntripUser, QString ntripPwd)
{
    strtype[1] = STR_NTRIPCLI;
    memset(strpath[0], 0, MAXSTRMSG);
    memset(strpath[1], 0, MAXSTRMSG);

    snprintf(strpath[0], MAXSTRMSG, "%s:115200:8:n:1:off", qPrintable(serialPort));
    if(ntripUser.length() != 0)
    {
        strncat(strpath[1],qPrintable(ntripUser), MAXSTRMSG);
        if(ntripPwd.length() != 0)
        {
            strncat(strpath[1],ntripPwd.prepend(':').append('@').toLocal8Bit().constData(), MAXSTRMSG-ntripUser.length());
        }
        else
        {
            strncat(strpath[1], "@", MAXSTRMSG-ntripUser.length());
        }
    } else {
        strncat(strpath[1],":@", MAXSTRMSG);
    }
    strncat(strpath[1],qPrintable(ntripAdress), MAXSTRMSG - strlen(strpath[1]));

    if(ntripPort.length() != 0)
    {
        strncat(strpath[1],ntripPort.prepend(':').toLocal8Bit().constData(), MAXSTRMSG - strlen(strpath[1]));
    }

    strncat(strpath[1],ntripMount.prepend('/').toLocal8Bit().constData() , MAXSTRMSG - strlen(strpath[1]));

    snprintf(strpath[3], MAXSTRMSG, ":%i", SOCKET_PORT);
    snprintf(strpath[4], MAXSTRMSG, "%s", "sol.pos");
    snprintf(strpath[5], MAXSTRMSG, "%s", "rover.log");
    snprintf(strpath[6], MAXSTRMSG, "%s", "base.log");

    //strncat(strpath[3], qPrintable(QString::number(SOCKET_PORT).prepend(':')), MAXSTRMSG);
    //strncat(strpath[5], "rover.log", MAXSTRMSG);
    //strncat(strpath[6], "base.log", MAXSTRMSG);

    qDebug() << "Serial path: " << strpath[0] << "\n" <<
                "Ntrip path: " << strpath[1] << "\n" <<
                "TPC path: " << strpath[3] << "\n";

}

void rtkMain::setParameters(QString serialPort, QString TCPAdress, QString TCPPort)
{
    strtype[1] = STR_TCPCLI;
    snprintf(strpath[0], MAXSTRMSG, "%s:115200:8:n:1:off", qPrintable(serialPort));
    
    if(TCPAdress != 0 && TCPPort != 0)
    {
        snprintf(strpath[1], MAXSTRMSG, "%s:%s", qPrintable(TCPAdress), qPrintable(TCPPort));
    }

    snprintf(strpath[3], MAXSTRMSG, ":%i", SOCKET_PORT);
    snprintf(strpath[4], MAXSTRMSG, "%s", "sol.pos");
    snprintf(strpath[5], MAXSTRMSG, "%s", "rover.log");
    snprintf(strpath[6], MAXSTRMSG, "%s", "base.log");

    qDebug() << "Serial path: " << strpath[0] << "\n" <<
                "TCP Input path: " << strpath[1] << "\n" <<
                "TPC Output path: " << strpath[3] << "\n";
}

int rtkMain::startRtk()
{
    char *paths[]={
            strpath[0],strpath[1],strpath[2],strpath[3],strpath[4],strpath[5],
            strpath[6],strpath[7]
        };
    char *ropts[]={"","",""};
    char *cmds[]={NULL,NULL,NULL};
    char *cmds_periodic[]={NULL,NULL,NULL};

    qDebug() << "path[0]: " << paths[0] << "\npath[1]: " << paths[1] << "\npath[2]: " << paths[2] << "\npath[3]: " << paths[3] << "\n";

    if(!rtksvrstart(svr,svrcycle, buffsize, strtype, paths, strfmt, navmsgsel,
                    cmds, cmds_periodic, ropts, nmeacycle, nmeareq, npos, &prcopt,
                    solopt, &moni, errmsg)) {
        qDebug() << "Error starting rtksvr: " << errmsg;
        return 0;
    }

    qDebug() << "Starting rtksvr successfull: " << errmsg;

    socket->connectToHost("Localhost", SOCKET_PORT);
    qDebug() << "socket state: " << socket->state();
    qDebug() << "socket valid: " << socket->isValid();
    qDebug() << "socket error: " << socket->errorString();

    return 1;
}

void rtkMain::stopRtk()
{
    char *cmds[]={NULL,NULL,NULL};
    socket->disconnectFromHost();
    rtksvrstop(svr, cmds);
}

QVariant rtkMain::getBearing()
{
    double brng = qAtan2(sin(Longitude - prevLongitude) * qCos(Latitude), qCos(prevLatitude)*sin(Latitude) - qSin(prevLatitude)*qCos(Latitude*qCos(Longitude - prevLongitude)));
    return QVariant(qRadiansToDegrees(brng));
}

void rtkMain::socketFinished()
{
    char readLine[256];
    qint64 read = socket->readLine(readLine, 256);
    char *ptr;
    int i = 0;
    if(read != 0)
    {
        ptr = strtok(readLine, "  ");
        while (ptr != 0 && i <= 3) {
           if(i == 2)
           {
               qDebug() << "Latitude: " << ptr;
               prevLatitude = Latitude;
               Latitude = QString(ptr).toDouble();;
           }
           if(i == 3)
           {

               qDebug() << "Longitude: " << ptr << " " << QString(ptr).toFloat();
               prevLongitude = Longitude;
               Longitude = QString(ptr).toDouble();;
           }
           i++;
           ptr = strtok(NULL, "  ");
        }
        qDebug() << "Latitude: " << Latitude << " Longitude: " << Longitude;
        emit centerChanged(Latitude, Longitude);
    }
}
