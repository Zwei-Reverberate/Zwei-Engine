#include <include/ui/zwdockwidget.h>

ZwDockWidget::ZwDockWidget(const QString& title, QWidget* parent)
    : QDockWidget(title, parent)
{
    setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
    setFeatures(QDockWidget::DockWidgetMovable);
}