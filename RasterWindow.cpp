#include "RasterWindow.h"


RasterWindow::RasterWindow(QWindow *parent) : QWindow(parent),
    m_backingStore(new QBackingStore(this))
{

    rec.origX = 0;
    rec.origY = 0;
    rec.zoom = 1;

    setMinimumSize(QSize(600,600));
    m_updateTimer.start();

    image = new QImage(QSize(width(),height()), QImage::Format_RGB32);
    QRgb c;

    for(int x=0; x<width(); x++)
        for(int y=0; y < height(); y++)
        {
            float v = std::abs(perlin.ValueNoise_2D(x,y));
            c = qRgba(200,100,200,v);
            image->setPixel(x,y,c);
        }



    for(int i=0;i < 10;i++)
    {
        float x = (rand() %600);
        float y = (rand() %600);
        planes[i] = std::make_unique<Plane>( x, y, perlin.ValueNoise_2D(x,y), perlin.ValueNoise_2D(x,y), &rec);
    }

}

bool RasterWindow::event(QEvent *event)
{
    if(event->type() == QEvent::UpdateRequest)
    {
        renderNow();
        return true;
    }
    return QWindow::event(event);
}

void RasterWindow::exposeEvent(QExposeEvent *event)
{
    if(isExposed())
    {
        renderNow();
    }
}

void RasterWindow::mousePressEvent(QMouseEvent* event)
{
    switch(event->button())
    {
        case Qt::LeftButton:
        {
            rec.zoom+=0.01f;
            break;
        }
        case Qt::RightButton:
        {
            rec.zoom-=0.01f;
            break;
        }
        case Qt::MiddleButton:
        {
            std::cout << "Middle";
            break;
        }
        default:
        {
            std::cout << "Other button pressed";
            break;
        }
    }
}

void RasterWindow::resizeEvent(QResizeEvent *resizeEvent)
{
    m_backingStore->resize(resizeEvent->size());
    image = new QImage(QSize(width(),height()), QImage::Format_RGB32);
    QRgb c;

    for(int x=0; x<width(); x++)
        for(int y=0; y < height(); y++)
        {
            float v = std::abs(perlin.ValueNoise_2D(x,y)) * 1000;
            c = qRgb(200,100,v - 20);
            image->setPixel(x,y,c);
        }
    if(isExposed())
    {
        renderNow();
    }
}

void RasterWindow::renderLater()
{
    requestUpdate();
}

void RasterWindow::renderNow()
{
    if(!isExposed())
    {
        return;
    }

    updateScene();
    renderScene();

    renderLater();
}

void RasterWindow::updateScene()
{
    const float elapsedSeconds = float(m_updateTimer.elapsed()) / 1000.f;

    if(elapsedSeconds > 0)
    {
        m_updateTimer.restart();
        for(int i=0;i < 10; i++)
        {
            planes[i]->update(elapsedSeconds);
        }
    }
}

void RasterWindow::renderScene()
{
    QRect rect(0,0,width(), height());
    m_backingStore->beginPaint(rect);

    QPaintDevice * device = m_backingStore->paintDevice();
    QPainter painter(device);

    painter.fillRect(0,0, width(), height(), Qt::white);
    if(image != NULL)
    {
         QPixmap pixmap;
         pixmap.convertFromImage(image->scaled( QSize(600 * rec.zoom, 600 * rec.zoom), Qt::IgnoreAspectRatio), Qt::ColorOnly);
         painter.drawPixmap((0 + rec.origX) * rec.zoom,(0 + rec.origX) * rec.zoom, pixmap);
    }
    for(int i=0;i < 10; i++)
    {
        planes[i]->redraw(painter);
    }

    painter.end();

    m_backingStore->endPaint();
    m_backingStore->flush(rect);
}

