#include "sfml_navigation.h"
#include <QDebug>
#define PRINT_INFO



SFML_Navigation::SFML_Navigation(QWidget *Parent, const QPoint &Position, const QSize &Size, unsigned int FrameTime) :
    SFML_Widget(Parent, Position, Size, FrameTime)
{
    traktor = new Traktor;
}

void SFML_Navigation::OnInit()
{
    fieldPosition = new sf::Vector2f(9750.0f, 9500.0f);
    view = new sf::View(*fieldPosition, sf::Vector2f(512.0f, 512.0f));
    view->setSize(sf::Vector2f(100.0f, 100.0f));
    field = new Field(points);
    field->getShape().setFillColor(sf::Color::Yellow);
    view->setCenter(*fieldPosition);

    path = new Path();
    path->calcPath(field);

    traktor->updatePosition(47.972866, 13.949628);

#ifdef PRINT_INFO
    field->printEdgeLengths();
#endif // PRINT_INFO
}

void SFML_Navigation::OnUpdate()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y))
    {
        view->zoom(1.01f);
        std::cout << "Zoom out" << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
    {
        view->zoom(0.99f);
        std::cout << "Zoom in" << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        view->move(sf::Vector2f(-0.1f,0.0f));
        std::cout << "Move left" << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        view->move(sf::Vector2f(0.1f, 0.0f));
        std::cout << "Move right" << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        view->move(sf::Vector2f(0.0f, -0.1f));
        std::cout << "Move up" << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        view->move(sf::Vector2f(0.0f, 0.1f));
        std::cout << "Move down" << std::endl;
    }

    clear(sf::Color(150, 150, 150));
    setView(*view);
    draw(field->getShape());
    draw(traktor->getShape());
}
