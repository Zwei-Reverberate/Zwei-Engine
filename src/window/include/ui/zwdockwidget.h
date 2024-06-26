#ifndef ZWDOCKWIDGET_H
#define ZWDOCKWIDGET_H

#include <QDockWidget>

class ZwDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit ZwDockWidget(const QString& title, QWidget* parent = nullptr);

protected:
    virtual void setupUi() = 0; // 纯虚函数，用于子类实现具体的UI
};

#endif // ZWDOCKWIDGET_H