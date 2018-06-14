#ifndef SFML_NAVIGATION_H
#define SFML_NAVIGATION_H

#include <sfml_widget.h>
#include <vector>

#include "sfml/GPSPoint.h"
#include "sfml/Field.h"
#include "sfml/Path.h"
#include "sfml/Traktor.h"

class SFML_Navigation : public SFML_Widget
{
public:
    SFML_Navigation(QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime = 0);

    Traktor* traktor;

private:
    void OnInit() override;
    void OnUpdate() override;

    sf::Vector2f* fieldPosition;
    sf::View* view;
    std::vector<GPSPoint> points = {	{ 47.973607, 13.952491 },
                                        { 47.972866, 13.949628 },
                                        { 47.973522, 13.949010 },
                                        { 47.973733, 13.949565 },
                                        { 47.974926, 13.948515 },
                                        { 47.975569, 13.951953 },
                                        { 47.974847, 13.952697 },
                                        { 47.974686, 13.952145 },
                                        { 47.974349, 13.952088 },
                                        { 47.974278, 13.951889 } };
    Field* field;
    Path* path;
    sf::Event* event;
};

#endif // SFML_NAVIGATION_H
