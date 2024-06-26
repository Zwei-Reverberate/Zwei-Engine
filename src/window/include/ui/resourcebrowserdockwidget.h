#ifndef RESOURCEBROWSERDOCKWIDGET_H
#define RESOURCEBROWSERDOCKWIDGET_H

#include "ZwDockWidget.h"
#include <QTreeWidget>

class ResourceBrowserDockWidget : public ZwDockWidget
{
    Q_OBJECT

public:
    explicit ResourceBrowserDockWidget(const QString& title, QWidget* parent = nullptr);

protected:
    void setupUi() override;
};

#endif // RESOURCEBROWSERDOCKWIDGET_H
