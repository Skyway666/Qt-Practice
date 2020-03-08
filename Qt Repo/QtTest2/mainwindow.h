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

    void DoAction(Action* action);

public slots:
    void openProject();
    void saveProject();

    void Undo();
    void Redo();

private:
    Ui::MainWindow *uiMainWindow;
    Hierarchy * hierarchy;
    Inspector* inspector;
    SceneView* scene;
    Actions* actions;
};

#endif // MAINWINDOW_H
