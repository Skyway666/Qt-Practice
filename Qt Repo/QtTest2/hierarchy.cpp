#include "hierarchy.h"
#include "ui_hierarchy.h"

Hierarchy::Hierarchy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hierarchy)
{
    ui->setupUi(this);

    connect(ui->Add, SIGNAL(clicked()), this, SLOT(onAddEntity()));
    connect(ui->Remove, SIGNAL(clicked()), this, SLOT(onRemoveEntity()));

    connect(ui->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(onEntitySelected(int)));
}

Hierarchy::~Hierarchy()
{
    delete ui;
}

void Hierarchy::onAddEntity(){
    ui->listWidget->addItem(ui->entityTypeSelector->currentText());
    emit entityCreated(ui->entityTypeSelector->currentText());
}
void Hierarchy::onRemoveEntity(){
    int row = ui->listWidget->currentRow();
    ui->listWidget->takeItem(row);
}

void Hierarchy::onEntitySelected(int row){
    emit entityChanged(row);

}
