#pragma once

#include <QtGui/QWindow>
#include <QtGui/QPainter>
#include <QtGui/QResizeEvent>
#include <QtGui/QExposeEvent>
#include <QtGui/QBackingStore>
#include <QtCore/QElapsedTimer>
#include <QDebug>
#include "plane.h"
#include "perlin2d.h"
#include "Resource.h"
#include <memory>
#include <vector>
#include <iostream>

class RasterWindow : public QWindow
{
    Q_OBJECT

   public:

    RasterWindow(QWindow *parent = 0);

   protected:

    bool event(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void exposeEvent(QExposeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

   private :

    void renderLater();
    void renderNow();
    void updateScene();
    void renderScene();


    QBackingStore *m_backingStore = nullptr;
    std::unique_ptr<Plane> planes[10];
    QElapsedTimer m_updateTimer;

    PerlinNoise perlin = PerlinNoise();

    QImage* image;
    Resource rec;
};
