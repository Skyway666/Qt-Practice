#include "inspector.h"
#include "ui_transform.h"
#include "ui_universals.h"

#include "iostream"

Inspector::Inspector(QWidget* parent): QWidget(parent),
    uiTransform(new Ui::Transform),
    uiUniversals(new Ui::Universals)
{

    QWidget* universalsWidget = new QWidget;
    uiUniversals->setupUi(universalsWidget);

    QWidget* transformWidget = new QWidget;
    uiTransform->setupUi(transformWidget);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(universalsWidget);
    layout->addWidget(transformWidget);

    setLayout(layout);
}

Inspector::~Inspector()
{
    delete uiTransform;
    delete uiUniversals;
}

void Inspector::onEntityChanged(int row){
    std::cout << "Row Changed" << std::endl;
}
