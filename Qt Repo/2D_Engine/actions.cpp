#include "actions.h"
#include "mainwindow.h"
#include "sceneview.h"

Actions::Actions(MainWindow* main): main(main)
{

}

void Actions::Do(Action* action)
{
    doneActions.push_back(action);
    SceneObject** object = main->getSceneObject(action->objectIndex);

    if (object != nullptr)
    {
        action->Do(object);
        main->updateInspector();
        main->forceRepaint();

        for(int i = 0; i < undoneActions.size(); ++i)
        {
            delete undoneActions[i];
        }
        undoneActions.clear();
    }
}

void Actions::Undo()
{
    if (!doneActions.isEmpty())
    {
        Action* action = doneActions.back();
        doneActions.pop_back();
        SceneObject** object = main->getSceneObject(action->objectIndex);

        if (object != nullptr)
        {
            action->Undo(object);
            main->updateInspector();
            main->forceRepaint();

            undoneActions.push_back(action);
        }
    }
}

void Actions::ReDo()
{
    if (!undoneActions.isEmpty())
    {
        Action* action = undoneActions.back();
        undoneActions.pop_back();
        SceneObject** object = main->getSceneObject(action->objectIndex);

        if (object != nullptr)
        {
            action->Do(object);
            main->updateInspector();
            main->forceRepaint();

            doneActions.push_back(action);
        }
    }
}

void ChangeShape::Do(SceneObject** object)
{
     previousShapeType = (*object)->shape;
     (*object)->shape = (Shape)shapeType;
}

void ChangeShape::Undo(SceneObject** object)
{
    (*object)->shape = (Shape)previousShapeType;
}

void ChangePositionX::Do(SceneObject** object)
{
    previousValue = (*object)->position.x;
    (*object)->position.x = value;
}

void ChangePositionX::Undo(SceneObject** object)
{
    (*object)->position.x = previousValue;
}

void ChangePositionY::Do(SceneObject** object)
{
    previousValue = (*object)->position.y;
    (*object)->position.y = value;
}

void ChangePositionY::Undo(SceneObject** object)
{
    (*object)->position.y = previousValue;
}

void ChangeSize::Do(SceneObject** object)
{
    previousValue = (*object)->size;
    (*object)->size = value;
}

void ChangeSize::Undo(SceneObject** object)
{
    (*object)->size = previousValue;
}

void ChangeScaleX::Do(SceneObject** object)
{
    previousValue = (*object)->scale.x;
    (*object)->scale.x = value;
}

void ChangeScaleX::Undo(SceneObject** object)
{
    (*object)->scale.x = previousValue;
}

void ChangeScaleY::Do(SceneObject** object)
{
    previousValue = (*object)->scale.y;
    (*object)->scale.y = value;
}

void ChangeScaleY::Undo(SceneObject** object)
{
    (*object)->scale.y = previousValue;
}

void ChangeOutlineThickness::Do(SceneObject** object)
{
    previousValue = (*object)->strokeThickness;
    (*object)->strokeThickness = value;
}

void ChangeOutlineThickness::Undo(SceneObject** object)
{
    (*object)->strokeThickness = previousValue;
}

void ChangeOutlineStyle::Do(SceneObject** object)
{
    previousOutlineStyle = (*object)->strokeStyle-1;
    (*object)->strokeStyle = (Qt::PenStyle)(outlineStyle+1);
}

void ChangeOutlineStyle::Undo(SceneObject** object)
{
    (*object)->strokeStyle = (Qt::PenStyle)(previousOutlineStyle+1);
}

void ChangeFillColor::Do(SceneObject** object)
{
    previousColor = (*object)->fillColor;
    (*object)->fillColor = color;
}

void ChangeFillColor::Undo(SceneObject** object)
{
    (*object)->fillColor = previousColor;
}

void ChangeOutlineColor::Do(SceneObject** object)
{
    previousColor = (*object)->strokeColor;
    (*object)->strokeColor = color;
}

void ChangeOutlineColor::Undo(SceneObject** object)
{
    (*object)->strokeColor = previousColor;
}

void SetActive::Do(SceneObject** object)
{
    previousState = (*object)->active;
    (*object)->active = state;
}
void SetActive::Undo(SceneObject** object)
{
    (*object)->active = previousState;
}

void ChangeName::Do(SceneObject** object)
{
    previousName = (*object)->name;
    (*object)->name = name;
}

void ChangeName::Undo(SceneObject** object)
{
    (*object)->name = previousName;
}

DeleteEntity::~DeleteEntity()
{
    delete deletedObject;
}

void DeleteEntity::Do(SceneObject** object)
{
    deletedObject = new SceneObject();
    *deletedObject = **object;

    main->removeObject(objectIndex);
}

void DeleteEntity::Undo(SceneObject** object)
{
    main->insertObject(*deletedObject, objectIndex);
}

void CreateEntity::Do(SceneObject **object)
{
    main->createObject(type, objectIndex);
}

void CreateEntity::Undo(SceneObject **object)
{
    main->removeObject(objectIndex);
}
