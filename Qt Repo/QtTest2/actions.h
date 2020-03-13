#ifndef ACTIONS_H
#define ACTIONS_H

#include <QList>
#include <QColor>

class SceneObject;
class MainWindow;

class Action
{
public:

    Action(uint objectIndex): objectIndex(objectIndex)
    {}

    virtual ~Action() {}

    uint objectIndex;

    virtual void Do(SceneObject** object){};
    virtual void Undo(SceneObject** object){};
};

class CreateEntity : public Action
{
public:
    CreateEntity(uint objectIndex, QString type, MainWindow* main): Action(objectIndex), type(type), main(main)
    {}

    QString type;
    MainWindow* main;

    void Do(SceneObject** object) override;
    void Undo(SceneObject** object) override;
};

class DeleteEntity : public Action
{
public:
    DeleteEntity(uint objectIndex, MainWindow* main): Action(objectIndex), main(main)
    {}

    ~DeleteEntity() override;

    SceneObject* deletedObject;
    MainWindow* main;

    void Do(SceneObject** object) override;
    void Undo(SceneObject** object) override;
};

class SetActive: public Action
{
public:
    SetActive(uint objectIndex, bool state): Action(objectIndex), state(state)
    {}

    bool state;
    bool previousState;

    void Do(SceneObject** object) override;
    void Undo(SceneObject** object) override;

};

class ChangeName : public Action
{
public:
    ChangeName(uint objectIndex, QString name): Action(objectIndex), name(name)
    {}

    QString name;
    QString previousName;

    void Do(SceneObject** object) override;
    void Undo(SceneObject** object) override;
};

class ChangePositionX : public Action
{
public:
    ChangePositionX(uint objectIndex, int value): Action(objectIndex), value(value)
    {}

    int value;
    int previousValue;

    void Do(SceneObject** object) override;
    void Undo(SceneObject** object) override;
};

class ChangePositionY : public Action
{
public:
    ChangePositionY(uint objectIndex, int value): Action(objectIndex), value(value)
    {}

    int value;
    int previousValue;

    void Do(SceneObject** object) override;
    void Undo(SceneObject** object) override;
};

class ChangeScaleX : public Action
{
public:
    ChangeScaleX(uint objectIndex, float value): Action(objectIndex), value(value)
    {}

    float value;
    float previousValue;

    void Do(SceneObject** object) override;
    void Undo(SceneObject** object) override;
};

class ChangeScaleY : public Action
{
public:
    ChangeScaleY(uint objectIndex, float value): Action(objectIndex), value(value)
    {}

    float value;
    float previousValue;

    void Do(SceneObject** object) override;
    void Undo(SceneObject** object) override;
};

class ChangeShape : public Action
{
public:
    ChangeShape(uint objectIndex, int shapeType): Action(objectIndex), shapeType(shapeType)
    {}

    int shapeType;
    int previousShapeType;

    void Do(SceneObject** object) override;
    void Undo(SceneObject** object) override;
};

class ChangeSize : public Action
{
public:
    ChangeSize(uint objectIndex, float value): Action(objectIndex), value(value)
    {}

    float value;
    float previousValue;

    void Do(SceneObject** object) override;
    void Undo(SceneObject** object) override;
};

class ChangeFillColor : public Action
{
public:
    ChangeFillColor(uint objectIndex, QColor color): Action(objectIndex), color(color)
    {}

    QColor color;
    QColor previousColor;

    void Do(SceneObject** object) override;
    void Undo(SceneObject** object) override;
};

class ChangeOutlineColor : public Action
{
public:
    ChangeOutlineColor(uint objectIndex, QColor color): Action(objectIndex), color(color)
    {}

    QColor color;
    QColor previousColor;

    void Do(SceneObject** object) override;
    void Undo(SceneObject** object) override;
};

class ChangeOutlineThickness : public Action
{
public:
    ChangeOutlineThickness(uint objectIndex, float value): Action(objectIndex), value(value)
    {}

    float value;
    float previousValue;

    void Do(SceneObject** object) override;
    void Undo(SceneObject** object) override;
};

class ChangeOutlineStyle : public Action
{
public:
    ChangeOutlineStyle(uint objectIndex, int outlineStyle): Action(objectIndex), outlineStyle(outlineStyle)
    {}

    int outlineStyle;
    int previousOutlineStyle;

    void Do(SceneObject** object) override;
    void Undo(SceneObject** object) override;
};

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
