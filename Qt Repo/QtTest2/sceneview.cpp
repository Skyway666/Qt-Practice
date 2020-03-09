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

void SceneObject::Draw(QPainter *painter)
{
    setDrawingTools(painter);
    QRect rect(position.x,position.y,size*scale.x,size*scale.y);

    switch(shape)
    {
    case RECTANGLE:
        painter->drawRect(rect);
        break;
    case ELIPSIS:
        painter->drawEllipse(rect);
        break;
    };
}

void SceneView::paintEvent(QPaintEvent *event)
{
   QPainter painter(this);

   for(int i = 0; i < objectIndex && sceneObjects[i] != nullptr; i++)
       sceneObjects[i]->Draw(&painter);
}


void SceneView::onEntityCreated(QString type){
   SceneObject* newObject = nullptr;

   if(type == "Elipsis")
    newObject = new SceneObject(ELIPSIS);
   else if(type == "Rectangle")
    newObject = new SceneObject(RECTANGLE);

  sceneObjects[objectIndex++] = newObject;

  static int x = 0;
  newObject->position.x = 100 + x;
  x += 100;
  newObject->position.y = 200;
  repaint();
}

void SceneView::onEntityRemoved(int index){
   // TODO(Lucas): Display a message in the editor
   if(index == -1){
    std::cout << "Select an entity first" << std::endl;
   } else{
    delete sceneObjects[index];
    sceneObjects[index] = nullptr;

    for(int i = index; i < objectIndex; i++){
        sceneObjects[i] = sceneObjects[i + 1];
    }
    objectIndex--;
    repaint();
   }
}
