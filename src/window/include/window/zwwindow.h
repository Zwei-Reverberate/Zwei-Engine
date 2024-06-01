#ifndef ZWWINDOW_H
#define ZWWINDOW_H
#include <qwindow.h>

class ZwWindow : public QWindow
{
	Q_OBJECT
public:
	ZwWindow();
	bool getIsClosed() const { return m_isClosed; }

Q_SIGNALS:
	void windowClosed();

public slots:
	void onWindowClosed();

protected:
	void closeEvent(QCloseEvent* event) override;

private:
	bool m_isClosed = false;
};

#endif