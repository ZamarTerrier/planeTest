#include <QtGui/QGuiApplication>
#include "RasterWindow.h"

int main(int argc, char * argv[])
{
    QGuiApplication app(argc,argv);

    RasterWindow window;
    window.show();

    return app.exec();
}
