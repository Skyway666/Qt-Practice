#include "sceneview.h"

#include <QPainter>
#include <QBrush>
#include <QPen>

#include "iostream"

SceneView::SceneView(QWidget *parent) : QWidget(parent)
{
    for(int i = 0; i < 100; i++)
        sceneObjects[i] = nullptr;
}

void SceneView::paintEvent(QPaintEvent *event)
{

    QColor blue = QColor::fromRgb(127,190,220);
    QColor white = QColor::fromRgb(255,255,255);
    QColor black = QColor::fromRgb(0,0,0);

    QPainter painter(this);


    QBrush brush;
    QPen pen;

    brush.setColor(blue);
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    pen.setStyle(Qt::PenStyle::NoPen);
    painter.setBrush(brush);
    painter.setPen(pen);
    /*
    painter.drawRect(rect());


    brush.setColor(white);
    pen.setWidth(4);
    pen.setColor(black);
    pen.setStyle(Qt::PenStyle::DashLine);
    painter.setBrush(brush);
    painter.setPen(pen);

    int r = 64;
    int w = r*2;
    int h = r*2;
    int x = rect().width() / 2 - r;
    int y = rect().height() / 2 - r;

    QRect circleRect(x,y,w,h);
    painter.drawEllipse(circleRect);*/


   std::cout << "Paint event" << std::endl;

   for(int i = 0; i < 100 && sceneObjects[i] != nullptr; i++){
       // This should be done for every object in the "Draw()" function, but I'm just messing around

       Rectangle* myRect = (Rectangle*)sceneObjects[i];
       painter.drawRect(myRect->position.x, myRect->position.y, myRect->size.x,myRect->size.y);
   }



}


void SceneView::onEntityCreated(){
  Rectangle* newRectangle = new Rectangle();
  sceneObjects[objectIndex++] = newRectangle;

  newRectangle->size.x = 100;
  newRectangle->size.y = 200;
}
