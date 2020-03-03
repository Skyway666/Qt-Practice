#ifndef SCENEVIEW_H
#define SCENEVIEW_H

#include <QWidget>


struct vec2{
    float x = 0;
    float y = 0;
};

class SceneObject{
    public:
        vec2 position;

        void Draw(){}
};


class Rectangle: public SceneObject {
    public:
        vec2 size;
        QColor color = QColor(QColor::fromRgb(0,0,0));
};

class SceneView : public QWidget
{
    Q_OBJECT
public:
    explicit SceneView(QWidget *parent = nullptr);
    int objectIndex = 0;
    SceneObject* sceneObjects[100];

signals:

public slots:

    void onEntityCreated();

private:

    void paintEvent(QPaintEvent* event) override;
};

#endif // SCENEVIEW_H
