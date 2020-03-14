#include "mainwindow.h"
#include "hierarchy.h"
#include "inspector.h"
#include "sceneview.h"
#include "actions.h"

#include "ui_mainwindow.h"

#include "iostream"

#include <QMessageBox>
#include <QFileDialog>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    uiMainWindow(new Ui::MainWindow)
{
    uiMainWindow->setupUi(this);

    connect(uiMainWindow->actionOpen_Project, SIGNAL(triggered()), this, SLOT(openProject()));
    connect(uiMainWindow->actionSave_Project, SIGNAL(triggered()), this, SLOT(saveProject()));
    connect(uiMainWindow->actionNew_Project, SIGNAL(triggered()), this, SLOT(newProject()));
    connect(uiMainWindow->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));

    hierarchy = new Hierarchy();
    uiMainWindow->Hierarchy->setWidget(hierarchy);

    inspector = new Inspector(this);
    uiMainWindow->Inspector->setWidget(inspector);

    scene = new SceneView();
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(scene);
    uiMainWindow->centralWidget->setLayout(layout);

    actions = new Actions(this);

    connect(hierarchy, SIGNAL(entityChanged(int)), inspector, SLOT(onEntityChanged(int)));
    connect(hierarchy, SIGNAL(entityCreated(QString, uint)), this, SLOT(newEntity(QString, uint)));
    connect(hierarchy, SIGNAL(entityRemoved(int)), this, SLOT(deletedEntity(int)));

    connect(uiMainWindow->actionUndo, SIGNAL(triggered()), this, SLOT(Undo()));
    connect(uiMainWindow->actionRedo, SIGNAL(triggered()), this, SLOT(Redo()));

    connect(uiMainWindow->actionNew_Rectangle, SIGNAL(triggered()), this, SLOT(NewRectangle()));
    connect(uiMainWindow->actionNew_Elipse, SIGNAL(triggered()), this, SLOT(NewElipse()));

    connect(inspector, SIGNAL(doAction(Action*)), this, SLOT(Do(Action*)));
}

MainWindow::~MainWindow()
{
    delete uiMainWindow;
}

SceneObject** MainWindow::getSceneObject(int index)
{
    return &scene->sceneObjects[index];
}

void MainWindow::updateInspector()
{
    inspector->updateInspector();
}

void MainWindow::forceRepaint()
{
    scene->repaint();
    scene->updateHierarchy(hierarchy);
}

void MainWindow::updateHierarchy(){

}

int MainWindow::getSelectionIndex()
{
    return hierarchy->currentSelected();
}

void MainWindow::createObject(QString type, uint objectIndex)
{
    scene->addObject(type);
    hierarchy->insertEntity("Entity", objectIndex);
}

void MainWindow::insertObject(SceneObject def, uint objectIndex)
{
    scene->insertObject(objectIndex, def);
    hierarchy->insertEntity(def.name, objectIndex);
}

void MainWindow::removeObject(uint objectIndex)
{
    scene->removeObject(objectIndex);
    hierarchy->deleteEntity(objectIndex);
    inspector->hideInspector();
}

void MainWindow::DoAction(Action *action)
{
    actions->Do(action);
}

void MainWindow::Undo()
{
    actions->Undo();
}

void MainWindow::Redo()
{
    actions->ReDo();
}

void MainWindow::NewRectangle(){
    hierarchy->addEntity("Rectangle");
}
void MainWindow::NewElipse(){
    hierarchy->addEntity("Elipsis");
}

// SLOTS

void MainWindow::newProject(){
    QString filepath = QFileDialog::getSaveFileName(this, "New file");

    workingFile = filepath;
    scene->clearScene(hierarchy);
}

void MainWindow::newEntity(QString type, uint index)
{
    Action* action = new CreateEntity(index, type, this);
    Do(action);
}

void MainWindow::deletedEntity(int index)
{
    Action* action = new DeleteEntity(index, this);
    Do(action);
}

void MainWindow::Do(Action *action)
{
    actions->Do(action);
}

void MainWindow::openProject(){
    QString filepath = QFileDialog::getOpenFileName(this, "Load file");

    scene->loadScene(filepath, hierarchy);

    if(!filepath.isEmpty()){
        QMessageBox::information(this, "Working on:", filepath);
    }
    workingFile = filepath;

}

void MainWindow::saveProject(){
    QString filepath = "";
    if(workingFile == ""){
        filepath = QFileDialog::getSaveFileName(this, "Save project as...");
        if(!filepath.isEmpty()){
            QMessageBox::information(this, "New File:", filepath);
        }
        workingFile = filepath;
    }
    else
        filepath = workingFile;

    scene->saveScene(filepath);
}
