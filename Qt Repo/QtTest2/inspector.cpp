#include "mainwindow.h"
#include "sceneview.h"
#include "inspector.h"
#include "actions.h"
#include "ui_universals.h"
#include "ui_transform.h"
#include "ui_shaperenderer.h"

#include <QColorDialog>

#include "iostream"

Inspector::Inspector(MainWindow* main, QWidget* parent): QWidget(parent),
     uiUniversals(new Ui::Universals),
     uiTransform(new Ui::Transform),
     uiShapeRenderer(new Ui::ShapeRenderer),
     main(main),
     currentIndex(-1)
{

    universalsWidget = new QWidget;
    uiUniversals->setupUi(universalsWidget);

    transformWidget = new QWidget;
    uiTransform->setupUi(transformWidget);

    shapeRendererWidget = new QWidget;
    uiShapeRenderer->setupUi(shapeRendererWidget);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(universalsWidget);
    layout->addWidget(transformWidget);
    layout->addWidget(shapeRendererWidget);
    layout->addItem(new QSpacerItem(1,1,QSizePolicy::Expanding, QSizePolicy::Expanding));

    setLayout(layout);

    //Set up Slots

    connect(uiUniversals->nameInput, SIGNAL(editingFinished()), this, SLOT(onNameChanged()));
    connect(uiUniversals->activeCheckbox, SIGNAL(stateChanged(int)), this, SLOT(onActiveToggled(int)));

    connect(uiTransform->PositionX, SIGNAL(valueChanged(int)), this, SLOT(onTransformChangeX(int)));
    connect(uiTransform->PositionY, SIGNAL(valueChanged(int)), this, SLOT(onTransformChangeY(int)));
    connect(uiTransform->ScaleX, SIGNAL(valueChanged(double)), this, SLOT(onScaleChangeX(double)));
    connect(uiTransform->ScaleY, SIGNAL(valueChanged(double)), this, SLOT(onScaleChangeY(double)));

    connect(uiShapeRenderer->shapePicker, SIGNAL(currentIndexChanged(int)), this, SLOT(onShapeChanged(int)));
    connect(uiShapeRenderer->sizeValue, SIGNAL(valueChanged(double)), this, SLOT(onSizeChanged(double)));
    connect(uiShapeRenderer->fillColorButton, SIGNAL(clicked()), this, SLOT(onFillColorChanged()));
    connect(uiShapeRenderer->outlineColorButton, SIGNAL(clicked()), this, SLOT(onOutlineColorChanged()));
    connect(uiShapeRenderer->outlineThicknessValue, SIGNAL(valueChanged(double)), this, SLOT(onOutlineThicknessChanged(double)));
    connect(uiShapeRenderer->outlineStylePicker, SIGNAL(currentIndexChanged(int)), this, SLOT(onOutlineStyleChanged(int)));
}

Inspector::~Inspector()
{
    delete uiTransform;
    delete uiUniversals;
}

void Inspector::showInspector()
{
    hidden = false;

    universalsWidget->show();
    transformWidget->show();
    shapeRendererWidget->show();
}

void Inspector::hideInspector()
{
    hidden = true;

    universalsWidget->hide();
    transformWidget->hide();
    shapeRendererWidget->hide();
}

void Inspector::updateInspector()
{
    currentIndex = main->getSelectionIndex();

    if (currentIndex == -1 || hidden)
        return;

    SceneObject* object = *main->getSceneObject(currentIndex);

    //Block signals during value changes
    uiUniversals->nameInput->blockSignals(true);
    uiUniversals->activeCheckbox->blockSignals(true);

    uiTransform->PositionX->blockSignals(true);
    uiTransform->PositionY->blockSignals(true);
    uiTransform->ScaleX->blockSignals(true);
    uiTransform->ScaleY->blockSignals(true);

    uiShapeRenderer->shapePicker->blockSignals(true);
    uiShapeRenderer->sizeValue->blockSignals(true);
    uiShapeRenderer->outlineThicknessValue->blockSignals(true);
    uiShapeRenderer->outlineStylePicker->blockSignals(true);

    //Update values
    uiUniversals->nameInput->setText(object->name);
    uiUniversals->activeCheckbox->setChecked(object->active);

    uiTransform->PositionX->setValue(object->position.x);
    uiTransform->PositionY->setValue(object->position.y);
    uiTransform->ScaleX->setValue(object->scale.x);
    uiTransform->ScaleY->setValue(object->scale.y);

    uiShapeRenderer->shapePicker->setCurrentIndex(object->shape);
    uiShapeRenderer->sizeValue->setValue(object->size);
    QString qss = QString("background-color: %1").arg(object->fillColor.name());
    uiShapeRenderer->fillColorButton->setStyleSheet(qss);
    qss = QString("background-color: %1").arg(object->strokeColor.name());
    uiShapeRenderer->outlineColorButton->setStyleSheet(qss);
    uiShapeRenderer->outlineThicknessValue->setValue(object->strokeThickness);
    uiShapeRenderer->outlineStylePicker->setCurrentIndex(object->strokeStyle-1);

    //Unblock signals after value changes
    uiUniversals->nameInput->blockSignals(false);
    uiUniversals->activeCheckbox->blockSignals(false);

    uiTransform->PositionX->blockSignals(false);
    uiTransform->PositionY->blockSignals(false);
    uiTransform->ScaleX->blockSignals(false);
    uiTransform->ScaleY->blockSignals(false);

    uiShapeRenderer->shapePicker->blockSignals(false);
    uiShapeRenderer->sizeValue->blockSignals(false);
    uiShapeRenderer->outlineThicknessValue->blockSignals(false);
    uiShapeRenderer->outlineStylePicker->blockSignals(false);
}



void Inspector::onEntityChanged(int row)
{
    currentIndex = row;
    showInspector();
    updateInspector();
}

void Inspector::onActiveToggled(int state)
{
    Action* action = new SetActive(currentIndex, state == 2);
    emit doAction(action);
}

void Inspector::onNameChanged()
{
    if(currentIndex == -1) return;

    QString name = uiUniversals->nameInput->text();

    SceneObject* object = *main->getSceneObject(currentIndex);

    if (object != nullptr && object->name != name)
    {
        Action* action = new ChangeName(currentIndex, name);
        emit doAction(action);
    }
}

void Inspector::onTransformChangeX(int value)
{
    Action* action = new ChangePositionX(currentIndex, value);
    emit doAction(action);
}

void Inspector::onTransformChangeY(int value)
{
    Action* action = new ChangePositionY(currentIndex, value);
    emit doAction(action);
}

void Inspector::onScaleChangeX(double value)
{
    Action* action = new ChangeScaleX(currentIndex, value);
    emit doAction(action);
}

void Inspector::onScaleChangeY(double value)
{
    Action* action = new ChangeScaleY(currentIndex, value);
    emit doAction(action);
}

void Inspector::onShapeChanged(int index)
{
    Action* action = new ChangeShape(currentIndex, index);
    emit doAction(action);
}

void Inspector::onSizeChanged(double value)
{
    Action* action = new ChangeSize(currentIndex, value);
    emit doAction(action);
}

void Inspector::onFillColorChanged()
{
    SceneObject** object = main->getSceneObject(currentIndex);

    QColor color = QColorDialog::getColor((*object)->fillColor , this);
    if(color.isValid())
    {
        QString qss = QString("background-color: %1").arg(color.name());
        uiShapeRenderer->fillColorButton->setStyleSheet(qss);

        Action* action = new ChangeFillColor(currentIndex, color);
        emit doAction(action);
    }
}

void Inspector::onOutlineColorChanged()
{
    SceneObject** object = main->getSceneObject(currentIndex);

    QColor color = QColorDialog::getColor((*object)->strokeColor , this);
    if(color.isValid())
    {
        QString qss = QString("background-color: %1").arg(color.name());
        uiShapeRenderer->outlineColorButton->setStyleSheet(qss);

        Action* action = new ChangeOutlineColor(currentIndex, color);
        emit doAction(action);
    }
}

void Inspector::onOutlineThicknessChanged(double value)
{
    Action* action = new ChangeOutlineThickness(currentIndex, value);
    emit doAction(action);
}

void Inspector::onOutlineStyleChanged(int index)
{
    Action* action = new ChangeOutlineStyle(currentIndex, index);
    emit doAction(action);
}
