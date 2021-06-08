#pragma once

#include <QtGui/QPainter>
#include <string>
#include"Resource.h"

class Plane
{
public:
    Plane(float x, float y, float xDir, float yDir, Resource* raster);
    void update(float deltaSeconds);
    void redraw(QPainter& painter);
private:
    float m_ballPositionX = 0;
    float m_ballPositionY = 0;
    int size = 5;
    float xDir;
    float yDir;
    int number;

    Resource* rec;
};
