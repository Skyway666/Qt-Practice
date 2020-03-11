#ifndef SCENEVIEW_H
#define SCENEVIEW_H

#include <QWidget>

class Hierarchy;

enum Shape{
    RECTANGLE,
    ELIPSIS
};

struct vec2{
    vec2() {}
    vec2(int _x, int _y): x(_x), y(_y){}
    int x = 0;
    int y = 0;
};

class SceneObject{
    public:
        SceneObject(){}
        SceneObject(Shape _shape): shape(_shape){}
        virtual ~SceneObject() {}
        QString name = "Entity";
        bool active = true;
        Shape shape = Shape::ELIPSIS;
        vec2 position = vec2();
        vec2 scale = vec2(1, 2);
        float size = 100.0;

        QColor fillColor = QColor::fromRgb(255,0,0); // Red
        QColor strokeColor = QColor::fromRgb(0,0,0); // Black
        int strokeThickness = 4;
        Qt::PenStyle strokeStyle = Qt::PenStyle::SolidLine;

        void setDrawingTools(QPainter* painter);
        void Draw(QPainter* painter);


        // Serialization
        void write(QJsonObject& json);
        void read(QJsonObject& json);
};

class SceneView : public QWidget
{
    Q_OBJECT
public:
    explicit SceneView(QWidget *parent = nullptr);
    int objectIndex = 0;
    SceneObject* sceneObjects[100];

    void saveScene(QString path);
    void loadScene(QString path, Hierarchy* hierarchy);
    void updateHierarchy(Hierarchy* hierarchy);

    void clearScene(Hierarchy* hierarchy);
    void insertObject(int index, SceneObject def);

signals:

public slots:

    void onEntityCreated(QString type);
    void onEntityRemoved(int index);

private:

    void paintEvent(QPaintEvent* event) override;
};

#endif // SCENEVIEW_H
