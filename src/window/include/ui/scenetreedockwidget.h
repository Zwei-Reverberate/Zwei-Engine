#ifndef SCENETREEDOCKWIDGET_H
#define SCENETREEDOCKWIDGET_H

#include "ZwDockWidget.h"
#include <QListWidget>

class SceneTreeDockWidget : public ZwDockWidget
{
    Q_OBJECT

public:
    explicit SceneTreeDockWidget(const QString& title, QWidget* parent = nullptr);

protected:
    void setupUi() override;
};

#endif // SCENETREEDOCKWIDGET_H