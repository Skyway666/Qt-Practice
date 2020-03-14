#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>

namespace Ui{   
    class Universals;
    class Transform;
    class ShapeRenderer;
}

class MainWindow;
class Action;

class Inspector: public QWidget
{

    Q_OBJECT
public:
    explicit Inspector(MainWindow* main, QWidget* parent = nullptr);
    ~Inspector();

    void showInspector();
    void hideInspector();
    void updateInspector();

signals:

    void doAction(Action*);

public slots:

    void onEntityChanged(int row);

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

    QWidget* universalsWidget;
    QWidget* transformWidget;
    QWidget* shapeRendererWidget;
    bool hidden = false;

    int currentIndex;

public:
    MainWindow* main = nullptr;
};

#endif // INSPECTOR_H
