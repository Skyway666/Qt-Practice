#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>

namespace Ui{
    class Transform;
    class Universals;
}
class Inspector: public QWidget
{

    Q_OBJECT
public:
    explicit Inspector(QWidget* parent = nullptr);
    ~Inspector();

public slots:

    void onEntityChanged(int row);

private:
    Ui::Transform* uiTransform;
    Ui::Universals* uiUniversals;
};

#endif // INSPECTOR_H
