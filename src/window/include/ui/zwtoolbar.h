#ifndef ZWTOOLBAR_H
#define ZWTOOLBAR_H
#include <qtoolbar.h>
#include <include/ui/zwmenu.h>

class ZwToolBar : public QToolBar
{
	Q_OBJECT
public:
	explicit ZwToolBar(QWidget* parent = nullptr);

private:
	void setupActions();
	void setupFile();
	void setupSetting();

private:
	ZwMenu* m_pFileMenu = nullptr;
	ZwMenu* m_pSettingMenu = nullptr;
};

#endif // !ZWTOOLBAR_H
