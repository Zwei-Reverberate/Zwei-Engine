#ifndef PROPERTYDOCKWIDGET_H
#define PROPERTYDOCKWIDGET_H

#include "ZwDockWidget.h"
#include <QTableWidget>

class PropertyDockWidget : public ZwDockWidget
{
    Q_OBJECT

public:
    explicit PropertyDockWidget(const QString& title, QWidget* parent = nullptr);

protected:
    void setupUi() override;
};

#endif // PROPERTYDOCKWIDGET_H