#include "sceneview.h"
#include "hierarchy.h"

#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QColor>

#include <QMessageBox>

#include<QFile>
#include<QJsonObject>
#include<QJsonArray>
#include<QJsonDocument>
#include<QByteArray>

#include <QListWidget>


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

    painter->setBrush(brush);

    // Set Stroke
    if (strokeThickness > 0)
    {
        pen.setWidth(strokeThickness);
        pen.setColor(strokeColor);
        pen.setStyle(strokeStyle);

        painter->setPen(pen);
    }
    else
        painter->setPen(Qt::NoPen);
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
       if(sceneObjects[i]->active)
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

void SceneView::insertObject(uint index, SceneObject def){
    // TODO(Lucas): Handle more than 100 objects
    // Make room for the new object
    for (int i = objectIndex; i > index; i--)
        sceneObjects[i] = sceneObjects[i - 1];

    sceneObjects[index] = new SceneObject();
    *sceneObjects[index] = def;
    objectIndex++;
}

void SceneView::clearScene(Hierarchy *hierarchy){
    hierarchy->list->clear();

    for(int i = 0; i < objectIndex; i++){
        delete sceneObjects[i];
        sceneObjects[i] = nullptr;
    }

    objectIndex = 0;

}

void SceneView::addObject(QString type)
{
    SceneObject* newObject = nullptr;

    if(type == "Elipsis")
     newObject = new SceneObject(ELIPSIS);
    else if(type == "Rectangle")
     newObject = new SceneObject(RECTANGLE);

   sceneObjects[objectIndex++] = newObject;
   repaint();
}

void SceneView::removeObject(uint index)
{
    delete sceneObjects[index];
    sceneObjects[index] = nullptr;

    for(int i = index; i < objectIndex; i++)
        sceneObjects[i] = sceneObjects[i + 1];

    objectIndex--;
    repaint();
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
    json["shape"] = shape;
    json["position_x"] = position.x;
    json["position_y"] = position.y;
    json["scale_x"] = scale.x;
    json["scale_y"] = scale.y;
    json["size"] = size;

    json["fillColor_r"] = fillColor.red();
    json["fillColor_g"] = fillColor.green();
    json["fillColor_b"] = fillColor.blue();

    json["strokeColor_r"] = strokeColor.red();
    json["strokeColor_g"] = strokeColor.green();
    json["strokeColor_b"] = strokeColor.blue();

    json["strokeThickness"] = strokeThickness;

    json["strokeStyle"] = strokeStyle;
}

void SceneObject::read(QJsonObject &json){
    name = json["name"].toString();
    active = json["active"].toBool();
    shape = Shape(json["shape"].toInt());
    position.x = json["position_x"].toDouble();
    position.y = json["position_y"].toDouble();
    scale.x = json["scale_x"].toDouble();
    scale.y = json["scale_y"].toDouble();
    size = json["size"].toDouble();

    fillColor = QColor::fromRgb(json["fillColor_r"].toInt(),json["fillColor_g"].toInt(),json["fillColor_b"].toInt());
    strokeColor = QColor::fromRgb(json["strokeColor_r"].toInt(),json["strokeColor_g"].toInt(),json["strokeColor_b"].toInt());

    strokeThickness = json["strokeThickness"].toInt();

    strokeStyle =   Qt::PenStyle(json["strokeStyle"].toInt());
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
          return;
      }
    saveFile.write(doc.toJson());
}

void SceneView::loadScene(QString path, Hierarchy* hierarchy){

    QFile loadFile(path);
    if (!loadFile.open(QIODevice::ReadOnly)) {
          qWarning("Couldn't open save file.");
          return;
    }
    // Clear scene
    clearScene(hierarchy);

    QByteArray savedScene = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(savedScene));
    QJsonArray array = loadDoc.array();

    for(int i = 0; i < array.size(); i++){
        QJsonObject json_sceneObject = array[i].toObject();
        sceneObjects[i] = new SceneObject;
        sceneObjects[i]->read(json_sceneObject);
        hierarchy->list->addItem(sceneObjects[i]->name);
    }

    objectIndex = array.size();
    repaint();
}

void SceneView::updateHierarchy(Hierarchy *hierarchy){
    for(int i = 0; i < objectIndex; i++)
        hierarchy->list->item(i)->setText(sceneObjects[i]->name);
}
