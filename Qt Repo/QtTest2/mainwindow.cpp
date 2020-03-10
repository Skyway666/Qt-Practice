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
    connect(hierarchy, SIGNAL(entityCreated(QString)), scene, SLOT(onEntityCreated(QString)));
    connect(hierarchy, SIGNAL(entityRemoved(int)), scene, SLOT(onEntityRemoved(int)));
    connect(hierarchy, SIGNAL(entityRemoved(int)), inspector, SLOT(onEntityRemoved(int)));

    connect(uiMainWindow->actionUndo, SIGNAL(triggered()), this, SLOT(Undo()));
    connect(uiMainWindow->actionRedo, SIGNAL(triggered()), this, SLOT(Redo()));
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
    scene->update();
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

void MainWindow::openProject(){
    /*QMessageBox::StandardButton button = QMessageBox::question(this, "Pregunta importante", "Eres tonto?");

    if(button == QMessageBox::Yes)
        std::cout <<"Ya lo sabia" << std::endl;
    else if(button == QMessageBox::No){
        std::cout <<"Que mentiroso..." << std::endl;
        return;
    }*/


    QString filepath = QFileDialog::getOpenFileName(this, "Load file");

    scene->loadScene(filepath, hierarchy);

    if(!filepath.isEmpty()){
        QMessageBox::information(this, "Path", filepath);
    }

}

void MainWindow::saveProject(){
    QString filepath = QFileDialog::getSaveFileName(this, "Save project as...");

    scene->saveScene(filepath);

    if(!filepath.isEmpty()){
        QMessageBox::information(this, "Path", filepath);
    }
}
