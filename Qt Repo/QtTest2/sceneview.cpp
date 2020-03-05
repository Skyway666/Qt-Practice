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

void SceneObject::setDrawingTools(QPainter* painter){

    QBrush brush;
    QPen pen;

    // Set fill
    brush.setColor(fillColor);
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    // Set Stroke
    pen.setWidth(strokeThickness);
    pen.setColor(strokeColor);
    pen.setStyle(strokeStyle);

    painter->setBrush(brush);
    painter->setPen(pen);
}

void Rectangle::Draw(QPainter* painter){
    setDrawingTools(painter);
    painter->drawRect(position.x,position.y, size.x, size.y);
}

void Elipsis::Draw(QPainter* painter){
    setDrawingTools(painter);
    QRect circleRect(position.x,position.y,size.x,size.y);
    painter->drawEllipse(circleRect);
}

void SceneView::paintEvent(QPaintEvent *event)
{
   std::cout << "Paint event" << std::endl;

   QPainter painter(this);

   for(int i = 0; i < 100 && sceneObjects[i] != nullptr; i++)
       sceneObjects[i]->Draw(&painter);
}


void SceneView::onEntityCreated(QString type){
   SceneObject* newObject = nullptr;

   if(type == "Elipsis")
    newObject = new Elipsis();
   else if(type == "Rectangle")
    newObject = new Rectangle();

  sceneObjects[objectIndex++] = newObject;

  static int x = 0;
  newObject->position.x = 100 + x;
  x += 100;
  newObject->position.y = 200;
  repaint();
}
