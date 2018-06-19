#include "mainwindow.h"
#include <QLabel>
#include <QTextBrowser>
#include <QDebug>
#include <fstream>

QLabel *MainWindow::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setFrameStyle(QFrame::Box | QFrame::Raised);
    return label;
}

void MainWindow::testSlot(double la, double lo)
{
    qDebug() << "La: " << la << " Lo: " << lo;
}

void MainWindow::initGpsSim(std::string const & filename)
{
    std::ifstream file(filename, std::ios::in);
    if (!file.is_open())
    {
        std::cerr << "There was a problem opening the coordinate input file!\n";
        return;
    }
    double num = 0.0;
    int cnt = 0;
    
    //Read all coordinates from the file (must always be in la lo pairs)
    while(file >> num)
    {
        GPSPoint * point = new GPSPoint();
        
        //First is always LA
        if((cnt % 2) == 0)
        {
            point->mLat = num;
        }
        //Second is always LO
        else
        {
            point->mLong = num;
            tractorPosition.push_back(point);
        }
            
        cnt++;
    }
}


MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    setFixedSize(480,480);

    rtkmain = new rtkMain();
    rtkSettings = new RTKSettings(nullptr, rtkmain);

    Navigation_GUI = new SFML_Navigation(this, QPoint(0,0), QSize(this->width(),this->height()), 16);

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

