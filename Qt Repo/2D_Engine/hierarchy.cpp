#include "hierarchy.h"
#include "ui_hierarchy.h"

#include "QMessageBox"
Hierarchy::Hierarchy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hierarchy)
{
    ui->setupUi(this);

    connect(ui->Add, SIGNAL(clicked()), this, SLOT(onAddEntity()));
    connect(ui->Remove, SIGNAL(clicked()), this, SLOT(onRemoveEntity()));

    connect(ui->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(onEntitySelected(int)));

    list = ui->listWidget;
}

Hierarchy::~Hierarchy()
{
    delete ui;
}

int Hierarchy::currentSelected()
{
    return ui->listWidget->currentRow();
}

void Hierarchy::createEntity(QString name)
{
    ui->listWidget->addItem(name);
}

void Hierarchy::insertEntity(QString name, uint index)
{
    ui->listWidget->insertItem(index, name);
}

void Hierarchy::deleteEntity(uint index)
{
    ui->listWidget->blockSignals(true);

    ui->listWidget->takeItem(index);

    ui->listWidget->blockSignals(false);
}

void Hierarchy::addEntity(QString type){
    emit entityCreated(type, ui->listWidget->count());
}

void Hierarchy::onAddEntity(){
    emit entityCreated(ui->entityTypeSelector->currentText(), ui->listWidget->count());
}
void Hierarchy::onRemoveEntity(){
    int index = ui->listWidget->currentRow();
    if (index != -1)
        emit entityRemoved(index);
    else
        QMessageBox::information(this, "Warning", "Select an item to delete");
}

void Hierarchy::onEntitySelected(int row){
    if (row != -1)
    {
        ui->listWidget->item(row)->setSelected(true);
    }
    emit entityChanged(row);
}
