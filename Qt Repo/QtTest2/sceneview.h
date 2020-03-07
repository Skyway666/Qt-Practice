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
        vec2 scale = vec2(1, 2);
        float size = 100.0;

        QColor fillColor = QColor(QColor::fromRgb(255,0,0)); // Red
        QColor strokeColor = QColor(QColor::fromRgb(0,0,0)); // Black
        int strokeThickness = 4;
        Qt::PenStyle strokeStyle = Qt::PenStyle::SolidLine;

        void setDrawingTools(QPainter* painter);
        void Draw(QPainter* painter);
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
    void onEntityRemoved(int index);

private:

    void paintEvent(QPaintEvent* event) override;
};

#endif // SCENEVIEW_H
