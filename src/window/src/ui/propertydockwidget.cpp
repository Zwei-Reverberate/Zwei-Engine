#include <include/ui/propertydockwidget.h>

PropertyDockWidget::PropertyDockWidget(const QString& title, QWidget* parent)
    : ZwDockWidget(title, parent)
{
    setupUi();
}

void PropertyDockWidget::setupUi()
{
    QTableWidget* tableWidget = new QTableWidget(5, 2, this);
    tableWidget->setHorizontalHeaderLabels({ "Property", "Value" });
    tableWidget->setItem(0, 0, new QTableWidgetItem("Name"));
    tableWidget->setItem(0, 1, new QTableWidgetItem("Node1"));
    tableWidget->setItem(1, 0, new QTableWidgetItem("Position"));
    tableWidget->setItem(1, 1, new QTableWidgetItem("0,0,0"));
    tableWidget->setItem(2, 0, new QTableWidgetItem("Rotation"));
    tableWidget->setItem(2, 1, new QTableWidgetItem("0,0,0"));
    tableWidget->setItem(3, 0, new QTableWidgetItem("Scale"));
    tableWidget->setItem(3, 1, new QTableWidgetItem("1,1,1"));

    setWidget(tableWidget);
}