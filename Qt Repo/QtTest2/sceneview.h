#ifndef SCENEVIEW_H
#define SCENEVIEW_H

#include <QWidget>

enum Shape{
    RECTANGLE,
    ELIPSIS
};

struct vec2{
    vec2() {};
    vec2(int _x, int _y): x(_x), y(_y){}
    int x = 0;
    int y = 0;
};

class SceneObject{
    public:
        SceneObject(Shape _shape): shape(_shape){}
        virtual ~SceneObject() {}
        Shape shape;
        vec2 position = vec2();
        vec2 size = vec2(100, 200);

        QColor fillColor = QColor(QColor::fromRgb(255,0,0)); // Red
        QColor strokeColor = QColor(QColor::fromRgb(0,0,0)); // Black
        int strokeThickness = 4;
        Qt::PenStyle strokeStyle = Qt::PenStyle::SolidLine;

        void setDrawingTools(QPainter* painter);
        virtual void Draw(QPainter* painter){}
};


class Rectangle: public SceneObject {
    public:
        Rectangle(): SceneObject(Shape::RECTANGLE){}
        void Draw(QPainter* painter) override;
};

// For the moment just a circle
class Elipsis: public SceneObject {
    public:
        Elipsis(): SceneObject(Shape::ELIPSIS){}
        void Draw(QPainter* painter) override;

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

    void onEntityCreated(QString type);

private:

    void paintEvent(QPaintEvent* event) override;
};

#endif // SCENEVIEW_H
