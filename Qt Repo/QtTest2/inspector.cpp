#include "mainwindow.h"
#include "sceneview.h"
#include "inspector.h"
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
    connect(uiShapeRenderer->shapePicker, SIGNAL(currentIndexChanged(int)), this, SLOT(onShapeChanged(int)));
}

Inspector::~Inspector()
{
    delete uiTransform;
    delete uiUniversals;
}

void Inspector::updateInspector(int index)
{
    SceneObject* object = *main->getSceneObject(index);

    //Block signals during value changes
    uiShapeRenderer->shapePicker->blockSignals(true);
    uiShapeRenderer->sizeValue->blockSignals(true);
    uiShapeRenderer->outlineThicknessValue->blockSignals(true);
    uiShapeRenderer->outlineStylePicker->blockSignals(true);

    uiShapeRenderer->shapePicker->setCurrentIndex(object->shape);
    uiShapeRenderer->sizeValue->setValue(object->size);
    //Fill color
    //Outline color
    uiShapeRenderer->outlineThicknessValue->setValue(object->strokeThickness);
    uiShapeRenderer->outlineStylePicker->setCurrentIndex(object->strokeStyle-1);

    //Unblock signals after value changes
    uiShapeRenderer->shapePicker->blockSignals(false);
    uiShapeRenderer->sizeValue->blockSignals(false);
    uiShapeRenderer->outlineThicknessValue->blockSignals(false);
    uiShapeRenderer->outlineStylePicker->blockSignals(false);
}

void Inspector::onEntityChanged(int row){
    std::cout << "Row Changed" << std::endl;
    std::cout << row << std::endl;

    updateInspector(row);
    currentIndex = row;
}

void Inspector::onShapeChanged(int index)
{
    SceneObject** object = main->getSceneObject(currentIndex);
    (*object)->shape = (Shape)index;

    main->forceRepaint();
}
