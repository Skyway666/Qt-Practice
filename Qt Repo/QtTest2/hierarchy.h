#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <QWidget>

class QListWidget;

namespace Ui {
class Hierarchy;
}

class Hierarchy : public QWidget
{
    Q_OBJECT

public:
    explicit Hierarchy(QWidget *parent = nullptr);
    ~Hierarchy();

    int currentSelected();

    void createEntity(QString name);
    void insertEntity(QString name, uint index);
    void deleteEntity(uint index);

    void addEntity(QString name);

    QListWidget* list = nullptr;

signals:
    void entityChanged(int selectedRow);
    void entityCreated(QString type, uint index);
    void entityRemoved(int index);

public slots:

    void onAddEntity();
    void onRemoveEntity();
    void onEntitySelected(int index);


private:
    Ui::Hierarchy *ui;
};

#endif // HIERARCHY_H
