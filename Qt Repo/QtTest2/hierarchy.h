#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <QWidget>

namespace Ui {
class Hierarchy;
}

class Hierarchy : public QWidget
{
    Q_OBJECT

public:
    explicit Hierarchy(QWidget *parent = nullptr);
    ~Hierarchy();

public slots:
    void onAddEntity();
    void onRemoveEntity();

private:
    Ui::Hierarchy *ui;
};

#endif // HIERARCHY_H
