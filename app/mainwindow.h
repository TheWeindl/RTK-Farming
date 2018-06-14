#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "sfml_navigation.h"
#include "borderlayout.h"
#include "stackbuttons.h"
#include "rtksettings.h"
#include "rtkmain.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
private:
    rtkMain* rtkmain;
    RTKSettings* rtkSettings;
    SFML_Navigation* Navigation_GUI;

    QStackedWidget* stackWidget;
    StackButtons* menuButtons;
    BorderLayout* mainLayout;

    QLabel *createLabel(const QString &text);
public slots:
    void testSlot(double la, double lo);
};

#endif // MAINWINDOW_H
