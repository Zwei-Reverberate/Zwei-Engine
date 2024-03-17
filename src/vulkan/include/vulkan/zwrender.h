#ifndef ZWRENDER_H
#define	ZWRENDER_H

class ZwInstance;
class ZwValidation;
class ZwRender
{
public:
	void init();
	void destroy();

private:
	ZwInstance* m_pZwInstance = nullptr;
	ZwValidation* m_pValidation = nullptr;
};

#endif // !ZWRENDER_H
