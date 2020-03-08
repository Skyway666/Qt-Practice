#include "mainwindow.h"
#include "sceneview.h"
#include "inspector.h"
#include "actions.h"
#include "ui_universals.h"
#include "ui_transform.h"
#include "ui_shaperenderer.h"

#include "iostream"

Inspector::Inspector(MainWindow* main, QWidget* parent): QWidget(parent),
     uiUniversals(new Ui::Universals),
     uiTransform(new Ui::Transform),
     uiShapeRenderer(new Ui::ShapeRenderer),
     main(main)
{

    QWidget* universalsWidget = new QWidget;
    uiUniversals->setupUi(universalsWidget);

    QWidget* transformWidget = new QWidget;
    uiTransform->setupUi(transformWidget);

    QWidget* shapeRendererWidget = new QWidget;
    uiShapeRenderer->setupUi(shapeRendererWidget);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(universalsWidget);
    layout->addWidget(transformWidget);
    layout->addWidget(shapeRendererWidget);
    layout->addItem(new QSpacerItem(1,1,QSizePolicy::Expanding, QSizePolicy::Expanding));

    setLayout(layout);

    //Set up Slots
    connect(uiTransform->PositionX, SIGNAL(valueChanged(int)), this, SLOT(onTransformChangeX(int)));
    connect(uiTransform->PositionY, SIGNAL(valueChanged(int)), this, SLOT(onTransformChangeY(int)));
    connect(uiTransform->ScaleX, SIGNAL(valueChanged(double)), this, SLOT(onScaleChangeX(double)));
    connect(uiTransform->ScaleY, SIGNAL(valueChanged(double)), this, SLOT(onScaleChangeY(double)));

    connect(uiShapeRenderer->shapePicker, SIGNAL(currentIndexChanged(int)), this, SLOT(onShapeChanged(int)));
    connect(uiShapeRenderer->sizeValue, SIGNAL(valueChanged(double)), this, SLOT(onSizeChanged(double)));
    connect(uiShapeRenderer->outlineThicknessValue, SIGNAL(valueChanged(double)), this, SLOT(onOutlineThicknessChanged(double)));
    connect(uiShapeRenderer->outlineStylePicker, SIGNAL(currentIndexChanged(int)), this, SLOT(onOutlineStyleChanged(int)));
}

Inspector::~Inspector()
{
    delete uiTransform;
    delete uiUniversals;
}

void Inspector::updateInspector()
{
    SceneObject* object = *main->getSceneObject(currentIndex);

    //Block signals during value changes
    uiTransform->PositionX->blockSignals(true);
    uiTransform->PositionY->blockSignals(true);
    uiTransform->ScaleX->blockSignals(true);
    uiTransform->ScaleY->blockSignals(true);

    uiShapeRenderer->shapePicker->blockSignals(true);
    uiShapeRenderer->sizeValue->blockSignals(true);
    uiShapeRenderer->outlineThicknessValue->blockSignals(true);
    uiShapeRenderer->outlineStylePicker->blockSignals(true);

    //Update values
    uiTransform->PositionX->setValue(object->position.x);
    uiTransform->PositionY->setValue(object->position.y);
    uiTransform->ScaleX->setValue(object->scale.x);
    uiTransform->ScaleY->setValue(object->scale.y);

    uiShapeRenderer->shapePicker->setCurrentIndex(object->shape);
    uiShapeRenderer->sizeValue->setValue(object->size);
    //Fill color
    //Outline color
    uiShapeRenderer->outlineThicknessValue->setValue(object->strokeThickness);
    uiShapeRenderer->outlineStylePicker->setCurrentIndex(object->strokeStyle-1);

    //Unblock signals after value changes
    uiTransform->PositionX->blockSignals(false);
    uiTransform->PositionY->blockSignals(false);
    uiTransform->ScaleX->blockSignals(false);
    uiTransform->ScaleY->blockSignals(false);

    uiShapeRenderer->shapePicker->blockSignals(false);
    uiShapeRenderer->sizeValue->blockSignals(false);
    uiShapeRenderer->outlineThicknessValue->blockSignals(false);
    uiShapeRenderer->outlineStylePicker->blockSignals(false);
}

void Inspector::onEntityChanged(int row){
    std::cout << "Row Changed" << std::endl;
    std::cout << row << std::endl;

    currentIndex = row;
    updateInspector();
}

void Inspector::onTransformChangeX(int value)
{
    SceneObject** object = main->getSceneObject(currentIndex);

    Action* action = new ChangePositionX(object, value);
    main->DoAction(action);
}

void Inspector::onTransformChangeY(int value)
{
    SceneObject** object = main->getSceneObject(currentIndex);

    Action* action = new ChangePositionY(object, value);
    main->DoAction(action);
}

void Inspector::onScaleChangeX(double value)
{
    SceneObject** object = main->getSceneObject(currentIndex);

    Action* action = new ChangeScaleX(object, value);
    main->DoAction(action);
}

void Inspector::onScaleChangeY(double value)
{
    SceneObject** object = main->getSceneObject(currentIndex);

    Action* action = new ChangeScaleY(object, value);
    main->DoAction(action);
}

void Inspector::onShapeChanged(int index)
{
    SceneObject** object = main->getSceneObject(currentIndex);

    Action* action = new ChangeShape(object, index);
    main->DoAction(action);
}

void Inspector::onSizeChanged(double value)
{
    SceneObject** object = main->getSceneObject(currentIndex);

    Action* action = new ChangeSize(object, value);
    main->DoAction(action);
}

void Inspector::onOutlineThicknessChanged(double value)
{
    SceneObject** object = main->getSceneObject(currentIndex);

    Action* action = new ChangeOutlineThickness(object, value);
    main->DoAction(action);
}

void Inspector::onOutlineStyleChanged(int index)
{
    SceneObject** object = main->getSceneObject(currentIndex);

    Action* action = new ChangeOutlineStyle(object, index);
    main->DoAction(action);
}
