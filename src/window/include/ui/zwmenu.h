#ifndef ZWMENU_H
#define ZWMENU_H
#include <QMenu>

class ZwMenu : public QMenu
{
	Q_OBJECT
public:
	explicit ZwMenu(const QString& title, QWidget* parent = nullptr);
};


#endif // !ZWMENU_H
