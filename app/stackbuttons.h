#ifndef STACKBUTTONS_H
#define STACKBUTTONS_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QStackedWidget>

class StackButtons : public QWidget
{
    Q_OBJECT
public:
    explicit StackButtons(QWidget *parent = nullptr, QStackedWidget* stackWidget = nullptr);

private:
    QPushButton* pbLeft;
    QPushButton* pbRight;
    QHBoxLayout* buttonLayout;

    QStackedWidget* stack;

    QString cRTKSettings = "RTK-Setting";
    QString cVehicleSettings = "Vehicle-Setting";
    QString cBack = "Back";
signals:

public slots:
    void leftButtonPressed();
    void rightButtonPressed();
};

#endif // STACKBUTTONS_H
