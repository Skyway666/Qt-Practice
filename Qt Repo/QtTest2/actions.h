#ifndef ACTIONS_H
#define ACTIONS_H

#include <QList>
#include <QColor>

class SceneObject;

class Action
{
public:

    Action(SceneObject** object): object(object)
    {}

    SceneObject** object;

    virtual void Do(){};
    virtual void Undo(){};
};

class DeleteEntity : public Action
{
public:
    DeleteEntity(SceneObject** object, int index): Action(object), index(index)
    {}

    SceneObject* object;
    int index;

    void Do() override;
    void Undo() override;
};

class ChangeName : public Action
{
public:
    ChangeName(SceneObject** object, QString name): Action(object), name(name)
    {}

    QString name;
    QString previousName;

    void Do() override;
    void Undo() override;
};

class ChangePositionX : public Action
{
public:
    ChangePositionX(SceneObject** object, int value): Action(object), value(value)
    {}

    int value;
    int previousValue;

    void Do() override;
    void Undo() override;
};

class ChangePositionY : public Action
{
public:
    ChangePositionY(SceneObject** object, int value): Action(object), value(value)
    {}

    int value;
    int previousValue;

    void Do() override;
    void Undo() override;
};

class ChangeScaleX : public Action
{
public:
    ChangeScaleX(SceneObject** object, float value): Action(object), value(value)
    {}

    float value;
    float previousValue;

    void Do() override;
    void Undo() override;
};

class ChangeScaleY : public Action
{
public:
    ChangeScaleY(SceneObject** object, float value): Action(object), value(value)
    {}

    float value;
    float previousValue;

    void Do() override;
    void Undo() override;
};

class ChangeShape : public Action
{
public:
    ChangeShape(SceneObject** object, int shapeType): Action(object), shapeType(shapeType)
    {}

    int shapeType;
    int previousShapeType;

    void Do() override;
    void Undo() override;
};

class ChangeSize : public Action
{
public:
    ChangeSize(SceneObject** object, float value): Action(object), value(value)
    {}

    float value;
    float previousValue;

    void Do() override;
    void Undo() override;
};

class ChangeFillColor : public Action
{
public:
    ChangeFillColor(SceneObject** object, QColor color): Action(object), color(color)
    {}

    QColor color;
    QColor previousColor;

    void Do() override;
    void Undo() override;
};

class ChangeOutlineColor : public Action
{
public:
    ChangeOutlineColor(SceneObject** object, QColor color): Action(object), color(color)
    {}

    QColor color;
    QColor previousColor;

    void Do() override;
    void Undo() override;
};

class ChangeOutlineThickness : public Action
{
public:
    ChangeOutlineThickness(SceneObject** object, float value): Action(object), value(value)
    {}

    float value;
    float previousValue;

    void Do() override;
    void Undo() override;
};

class ChangeOutlineStyle : public Action
{
public:
    ChangeOutlineStyle(SceneObject** object, int outlineStyle): Action(object), outlineStyle(outlineStyle)
    {}

    int outlineStyle;
    int previousOutlineStyle;

    void Do() override;
    void Undo() override;
};

class MainWindow;

class Actions
{
public:
    Actions(MainWindow* main);

    void Do(Action* action);
    void Undo();
    void ReDo();

private:

    QList<Action*> doneActions;
    QList<Action*> undoneActions;

public:
    MainWindow* main = nullptr;
};

#endif // ACTIONS_H
