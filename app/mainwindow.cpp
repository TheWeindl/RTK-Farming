#include "mainwindow.h"
#include <QLabel>
#include<QTextBrowser>
#include <QDebug>

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

