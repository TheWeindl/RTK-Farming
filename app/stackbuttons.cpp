#include "stackbuttons.h"

#define RTK_SETTINGS_STACK 0
#define RTK_MAIN_STACK 1
#define VEHICLE_SETTINGS_STACK 2

StackButtons::StackButtons(QWidget *parent, QStackedWidget* stackWidget) : QWidget(parent)
{
    pbLeft = new QPushButton(cRTKSettings);
    pbRight = new QPushButton(cVehicleSettings);
    buttonLayout = new QHBoxLayout();
    stack = stackWidget;

    buttonLayout->addWidget(pbLeft,0,Qt::AlignLeft);
    buttonLayout->addWidget(pbRight,0,Qt::AlignRight);

    // TODO Add Vehicle Settings menu
    pbRight->hide();

    setLayout(buttonLayout);

    connect(pbLeft,SIGNAL(clicked(bool)),this,SLOT(leftButtonPressed()));
    connect(pbRight, SIGNAL(clicked(bool)),this,SLOT(rightButtonPressed()));
}

void StackButtons::leftButtonPressed()
{
    if(stack->currentIndex() == RTK_MAIN_STACK)
    {
        stack->setCurrentIndex(RTK_SETTINGS_STACK);
        pbRight->setText(cBack);
        pbLeft->hide();

        //TODO: Remove if vehicle settings is ready
        pbRight->show();
    }
    else if (stack->currentIndex() == VEHICLE_SETTINGS_STACK)
    {
        //TODO
    }
}

void StackButtons::rightButtonPressed()
{
    if(stack->currentIndex() == RTK_MAIN_STACK)
    {
        //TODO
    }
    else if (stack->currentIndex() == RTK_SETTINGS_STACK)
    {
        stack->setCurrentIndex(RTK_MAIN_STACK);
        pbRight->setText(cVehicleSettings);
        pbLeft->show();

        //TODO: Remove if vehicle settings is ready
        pbRight->hide();
    }
}

