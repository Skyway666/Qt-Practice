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

    void updateInspector();

public slots:

    void onEntityChanged(int row);
    void onEntityRemoved(int index);

    //Object properties
    void onActiveToggled(int state);
    void onNameChanged();
    void onTransformChangeX(int value);
    void onTransformChangeY(int value);
    void onScaleChangeX(double value);
    void onScaleChangeY(double value);

    //Shape properties
    void onShapeChanged(int index);
    void onSizeChanged(double value);
    void onFillColorChanged();
    void onOutlineColorChanged();
    void onOutlineThicknessChanged(double value);
    void onOutlineStyleChanged(int index);

private:    
    Ui::Universals*     uiUniversals;
    Ui::Transform*      uiTransform;
    Ui::ShapeRenderer*  uiShapeRenderer;

    int currentIndex;

public:
    MainWindow* main = nullptr;
};

#endif // INSPECTOR_H
