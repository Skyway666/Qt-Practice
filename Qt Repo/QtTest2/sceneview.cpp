#include "sceneview.h"

#include <QPainter>
#include <QBrush>
#include <QPen>

#include <QMessageBox>

#include<QFile>
#include<QJsonObject>
#include<QJsonArray>
#include<QJsonDocument>


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

void SceneView::insertObject(int index, SceneObject def){
    // TODO(Lucas): Handle more than 100 objects
    // Make room for the new object
    for (int i = objectIndex; i > index; i--)
        sceneObjects[i] = sceneObjects[i - 1];

    sceneObjects[index] = new SceneObject;
    *sceneObjects[index] = def;
}

void SceneView::onEntityRemoved(int index){
   // TODO(Lucas): Handle more than 100 objects
   if(index == -1)
     QMessageBox::information(this, "Warning", "Select an item to delete");
   else{
    delete sceneObjects[index];
    sceneObjects[index] = nullptr;

    for(int i = index; i < objectIndex; i++)
        sceneObjects[i] = sceneObjects[i + 1];

    objectIndex--;
    repaint();
   }
}


void SceneObject::write(QJsonObject &json){
    json["name"] = name;
    json["active"] = active;
    json["position_x"] = position.x;
    json["position_y"] = position.y;


}
void SceneView::saveScene(QString path){
    // Create jsonArray
    QJsonArray json_sceneObjects;
    // Fill it with objects
    for(int i = 0; i < objectIndex && sceneObjects[i] != nullptr; i++){
        QJsonObject json_sceneObject;
        sceneObjects[i]->write(json_sceneObject);
        json_sceneObjects.append(json_sceneObject);
    }

    // Create document
    QJsonDocument doc(json_sceneObjects);

    // Create file
    QFile saveFile(path);
    if (!saveFile.open(QIODevice::WriteOnly)) {
          qWarning("Couldn't open save file.");
      }
    saveFile.write(doc.toJson());

}
