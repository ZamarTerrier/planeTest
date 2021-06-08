#include "plane.h"

Plane::Plane(float x, float y, float xDir, float yDir, Resource* rec)
{
    this->xDir = xDir;
    this->yDir = yDir;
    m_ballPositionX = x;
    m_ballPositionY = y;
    number = rand()%1000;

    this->rec = rec;
}

void Plane::update(float deltaSeconds)
{
    m_ballPositionX += xDir * 100 * deltaSeconds;
    m_ballPositionY += yDir * 100 * deltaSeconds;

    if(m_ballPositionX > 600 || m_ballPositionX < 0 ||
            m_ballPositionY > 600 || m_ballPositionY < 0)
    {
        m_ballPositionX = rand()%600;
        m_ballPositionY = rand()%600;
    }
}

void Plane::redraw(QPainter &painter)
{
    std::string text = std::to_string(number);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawText(QRect((rec->origX + m_ballPositionX) * rec->zoom - 30,(rec->origX + m_ballPositionY) * rec->zoom - 30, 100,50), QString(text.c_str()));
    painter.setBrush(QBrush(QColor(0xFA, 0xFE, 0x78)));
    painter.drawEllipse(QRectF((rec->origX + m_ballPositionX) * rec->zoom,(rec->origY + m_ballPositionY) * rec->zoom, size*(rec->zoom * 10), size*(rec->zoom * 10)));
}
