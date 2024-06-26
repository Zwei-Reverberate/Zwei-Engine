#include <include/ui/zwtoolbar.h>
#include <QAction>
#include <QHoverEvent>
#include <QToolButton>


ZwToolBar::ZwToolBar(QWidget* parent)
	: QToolBar(parent)
{
    setupActions();
}

void ZwToolBar::setupActions()
{
    setMovable(false);
    setupFile();
    setupSetting();
}


void ZwToolBar::setupFile()
{
    m_pFileMenu = new ZwMenu("File", this);

    QAction* fileAction = new QAction("File", this);
    m_pFileMenu->addAction("Open");
    m_pFileMenu->addAction("Save");

    QToolButton* fileButton = new QToolButton(this);
    fileButton->setMenu(m_pFileMenu);
    fileButton->setPopupMode(QToolButton::InstantPopup);
    fileButton->setText("File");
    addWidget(fileButton);
}

void ZwToolBar::setupSetting()
{
    m_pSettingMenu = new ZwMenu("Setting", this);

    QAction* settingsAction = new QAction("Settings", this);
    m_pSettingMenu->addAction("Preferences");
    m_pSettingMenu->addAction("Options");

    QToolButton* settingsButton = new QToolButton(this);
    settingsButton->setMenu(m_pSettingMenu);
    settingsButton->setPopupMode(QToolButton::InstantPopup);
    settingsButton->setText("Settings");

    addWidget(settingsButton);
}