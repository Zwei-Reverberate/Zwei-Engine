#include <include/ui/scenetreedockwidget.h>

SceneTreeDockWidget::SceneTreeDockWidget(const QString& title, QWidget* parent)
    : ZwDockWidget(title, parent)
{
    setupUi();
}

void SceneTreeDockWidget::setupUi()
{
    QListWidget* listWidget = new QListWidget(this);
    listWidget->addItem("Scene");
    listWidget->addItem("  └─ Node1");
    listWidget->addItem("      └─ Node1.1");
    listWidget->addItem("  └─ Node2");

    setWidget(listWidget);
}