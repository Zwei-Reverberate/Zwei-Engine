#include <include/window/zwwindow.h>

ZwWindow::ZwWindow()
{
	connect(this, &ZwWindow::windowClosed, this, &ZwWindow::onWindowClosed);
}

void ZwWindow::closeEvent(QCloseEvent* event)
{
	emit windowClosed();
}

void ZwWindow::onWindowClosed()
{
	m_isClosed = true;
}