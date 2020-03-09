#include "actions.h"
#include "mainwindow.h"
#include "sceneview.h"

Actions::Actions(MainWindow* main): main(main)
{

}

void Actions::Do(Action* action)
{
    doneActions.push_back(action);
    action->Do();
    main->forceRepaint();

    for(int i = 0; i < undoneActions.size(); ++i)
    {
        delete undoneActions[i];
    }
    undoneActions.clear();
}

void Actions::Undo()
{
    if (!doneActions.isEmpty())
    {
        Action* action = doneActions.back();
        doneActions.pop_back();
        action->Undo();
        main->updateInspector();
        main->forceRepaint();

        undoneActions.push_back(action);
    }
}

void Actions::ReDo()
{
    if (!undoneActions.isEmpty())
    {
        Action* action = undoneActions.back();
        undoneActions.pop_back();
        action->Do();
        main->updateInspector();
        main->forceRepaint();

        doneActions.push_back(action);
    }
}

void ChangeShape::Do()
{
    if (*object != nullptr) //TODO
    {
        previousShapeType = (*object)->shape;
        (*object)->shape = (Shape)shapeType;
    }
}

void ChangeShape::Undo()
{
    if (*object != nullptr) //TODO
    {
        (*object)->shape = (Shape)previousShapeType;
    }
}

void ChangePositionX::Do()
{
    if (*object != nullptr) //TODO
    {
        previousValue = (*object)->position.x;
        (*object)->position.x = value;
    }
}

void ChangePositionX::Undo()
{
    if (*object != nullptr) //TODO
    {
        (*object)->position.x = previousValue;
    }
}

void ChangePositionY::Do()
{
    if (*object != nullptr) //TODO
    {
        previousValue = (*object)->position.y;
        (*object)->position.y = value;
    }
}

void ChangePositionY::Undo()
{
    if (*object != nullptr) //TODO
    {
        (*object)->position.y = previousValue;
    }
}

void ChangeSize::Do()
{
    if (*object != nullptr) //TODO
    {
        previousValue = (*object)->size;
        (*object)->size = value;
    }
}

void ChangeSize::Undo()
{
    if (*object != nullptr) //TODO
    {
        (*object)->size = previousValue;
    }
}

void ChangeScaleX::Do()
{
    if (*object != nullptr) //TODO
    {
        previousValue = (*object)->scale.x;
        (*object)->scale.x = value;
    }
}

void ChangeScaleX::Undo()
{
    if (*object != nullptr) //TODO
    {
        (*object)->scale.x = previousValue;
    }
}

void ChangeScaleY::Do()
{
    if (*object != nullptr) //TODO
    {
        previousValue = (*object)->scale.y;
        (*object)->scale.y = value;
    }
}

void ChangeScaleY::Undo()
{
    if (*object != nullptr) //TODO
    {
        (*object)->scale.y = previousValue;
    }
}

void ChangeOutlineThickness::Do()
{
    if (*object != nullptr) //TODO
    {
        previousValue = (*object)->strokeThickness;
        (*object)->strokeThickness = value;
    }
}

void ChangeOutlineThickness::Undo()
{
    if (*object != nullptr) //TODO
    {
        (*object)->strokeThickness = previousValue;
    }
}

void ChangeOutlineStyle::Do()
{
    if (*object != nullptr) //TODO
    {
        previousOutlineStyle = (*object)->strokeStyle-1;
        (*object)->strokeStyle = (Qt::PenStyle)(outlineStyle+1);
    }
}

void ChangeOutlineStyle::Undo()
{
    if (*object != nullptr) //TODO
    {
        (*object)->strokeStyle = (Qt::PenStyle)(previousOutlineStyle+1);
    }
}

void ChangeFillColor::Do()
{
    if (*object != nullptr) //TODO
    {
        previousColor = (*object)->fillColor;
        (*object)->fillColor = color;
    }
}

void ChangeFillColor::Undo()
{
    if (*object != nullptr) //TODO
    {
        (*object)->fillColor = previousColor;
    }
}

void ChangeOutlineColor::Do()
{
    if (*object != nullptr) //TODO
    {
        previousColor = (*object)->strokeColor;
        (*object)->strokeColor = color;
    }
}

void ChangeOutlineColor::Undo()
{
    if (*object != nullptr) //TODO
    {
        (*object)->strokeColor = previousColor;
    }
}
