#include <include/ui/resourcebrowserdockwidget.h>

ResourceBrowserDockWidget::ResourceBrowserDockWidget(const QString& title, QWidget* parent)
    : ZwDockWidget(title, parent)
{
    setupUi();
}

void ResourceBrowserDockWidget::setupUi()
{
    QTreeWidget* treeWidget = new QTreeWidget(this);
    treeWidget->setHeaderLabels({ "Resource", "Type" });

    QTreeWidgetItem* rootItem = new QTreeWidgetItem(treeWidget);
    rootItem->setText(0, "Assets");

    QTreeWidgetItem* textureItem = new QTreeWidgetItem(rootItem);
    textureItem->setText(0, "Textures");
    textureItem->setText(1, "Folder");

    QTreeWidgetItem* textureFileItem = new QTreeWidgetItem(textureItem);
    textureFileItem->setText(0, "wood.png");
    textureFileItem->setText(1, "Image");

    QTreeWidgetItem* modelItem = new QTreeWidgetItem(rootItem);
    modelItem->setText(0, "Models");
    modelItem->setText(1, "Folder");

    QTreeWidgetItem* modelFileItem = new QTreeWidgetItem(modelItem);
    modelFileItem->setText(0, "chair.obj");
    modelFileItem->setText(1, "Model");

    treeWidget->expandAll();
    setWidget(treeWidget);
}