#ifndef TRACTOR_H
#define TRACTOR_H

#include <QObject>
#include "GPSPoint.h"
#include "SFML/Graphics.hpp"

class Traktor : public QObject
{
    Q_OBJECT
public:
    explicit Traktor(QObject *parent = nullptr);

    sf::CircleShape getShape();

public slots:
    //Updates the current position of the tractor
    void updatePosition(double const & la, double const & lo);
    void updatePosition(GPSPoint const & position);

private:
    GPSPoint mPosition;
    sf::CircleShape mTriangle;
};

#endif
