#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Hierarchy;
class Inspector;
class SceneView;
class Actions;

class SceneObject;
class Action;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    SceneObject** getSceneObject(int index);
    void updateInspector();
    void forceRepaint();
    void updateHierarchy();

    int getSelectionIndex();

    void createObject(QString type, uint objectIndex);
    void insertObject(SceneObject def, uint objectIndex);
    void removeObject(uint objectIndex);

    void DoAction(Action* action);

public slots:
    void openProject();
    void saveProject();
    void newProject();

    void newEntity(QString type, uint index);
    void deletedEntity(int index);

    void Do(Action* action);
    void Undo();
    void Redo();
    void NewRectangle();
    void NewElipse();

private:
    Ui::MainWindow *uiMainWindow;
    Hierarchy * hierarchy;
    Inspector* inspector;
    SceneView* scene;
    Actions* actions;

    QString workingFile = "";
};

#endif // MAINWINDOW_H
