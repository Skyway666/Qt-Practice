#include "hierarchy.h"
#include "ui_hierarchy.h"

Hierarchy::Hierarchy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hierarchy)
{
    ui->setupUi(this);

    connect(ui->Add, SIGNAL(clicked()), this, SLOT(onAddEntity()));
    connect(ui->Remove, SIGNAL(clicked()), this, SLOT(onRemoveEntity()));
}

Hierarchy::~Hierarchy()
{
    delete ui;
}

void Hierarchy::onAddEntity(){
    ui->listWidget->addItem("Entity");
}
void Hierarchy::onRemoveEntity(){
    int row = ui->listWidget->currentRow();
    ui->listWidget->takeItem(row);
}
