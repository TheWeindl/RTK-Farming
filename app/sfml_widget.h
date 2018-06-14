#ifndef SFML_WIDGET_H
#define SFML_WIDGET_H

#include <QWidget>
#include <QTimer>
#include <SFML/Graphics.hpp>

class SFML_Widget : public QWidget, public sf::RenderWindow
{
    Q_OBJECT
public:
    SFML_Widget(QWidget *parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime = 0);

    virtual ~SFML_Widget() {}

private:
    virtual void OnInit() {}

    virtual void OnUpdate() {}

    virtual QPaintEngine* paintEngine() const;

    virtual void showEvent(QShowEvent*);

    virtual void paintEvent(QPaintEvent*);

    virtual void resizeEvent(QResizeEvent* event);

    QTimer myTimer;
    bool   myInitialized;

signals:

public slots:
};

#endif // SFML_WIDGET_H
