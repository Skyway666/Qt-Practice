#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>

namespace Ui{   
    class Universals;
    class Transform;
    class ShapeRenderer;
}

class MainWindow;

class Inspector: public QWidget
{

    Q_OBJECT
public:
    explicit Inspector(MainWindow* main, QWidget* parent = nullptr);
    ~Inspector();

    void updateInspector(int index);

public slots:

    void onEntityChanged(int row);
    void onShapeChanged(int index);

private:    
    Ui::Universals*     uiUniversals;
    Ui::Transform*      uiTransform;
    Ui::ShapeRenderer*  uiShapeRenderer;

    int currentIndex;

public:
    MainWindow* main = nullptr;
};

#endif // INSPECTOR_H
