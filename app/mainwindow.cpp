#include "mainwindow.h"
#include <QLabel>
#include <QTextBrowser>
#include <QDebug>
#include <fstream>
#include <QFile>

QLabel *MainWindow::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setFrameStyle(QFrame::Box | QFrame::Raised);
    return label;
}

void MainWindow::testSlot()
{
    static int i = 0;
    qDebug() << "La: " << tractorPosition[i]->mLat << " Lo: " << tractorPosition[i]->mLong;
    Navigation_GUI->traktor->updatePosition(tractorPosition[i]->mLat, tractorPosition[i]->mLong);
    if(i < tractorPosition.length()-1)
    {
        i++;
    }
    else
    {
        i = 0;
    }
}

void MainWindow::initGpsSim(QString const & filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        std::cerr << "There was a problem opening the coordinate input file!\n";
        return;
    }
    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(" ");
        GPSPoint * point = new GPSPoint();
        point->mLat = fields[0].toDouble();
        point->mLong = fields[1].toDouble();
        tractorPosition.push_back(point);
    }

    file.close();
}


MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    setFixedSize(480,480);

    rtkmain = new rtkMain();
    rtkSettings = new RTKSettings(nullptr, rtkmain);

    Navigation_GUI = new SFML_Navigation(this, QPoint(0,0), QSize(this->width(),this->height()), 16);

    //Initialize the simulation of tractor movement from file
    initGpsSim(":/simCoordinates.txt");
    QTimer * GPStimer = new QTimer(this);
    connect(GPStimer, SIGNAL(timeout()), this, SLOT(testSlot()));
    GPStimer->start(1000);

    connect(rtkmain,SIGNAL(centerChanged(double,double)), Navigation_GUI->traktor, SLOT(updatePosition(double,double)));

    stackWidget = new QStackedWidget();
    stackWidget->addWidget(rtkSettings);
    stackWidget->addWidget(Navigation_GUI);
    stackWidget->setCurrentIndex(1);

    menuButtons = new StackButtons(nullptr, stackWidget);

    mainLayout = new BorderLayout;
    mainLayout->addWidget(stackWidget,BorderLayout::Center);
    mainLayout->addWidget(menuButtons,BorderLayout::North);

    setLayout(mainLayout);
}

