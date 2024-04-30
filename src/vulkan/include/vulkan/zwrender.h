#ifndef ZWRENDER_H
#define	ZWRENDER_H

class ZwInstance;
class ZwValidation;
class ZwPhysicalDevice;
class ZwLogicalDevice;
class ZwRender
{
public:
	void init();
	void destroy();

private:
	ZwInstance* m_pZwInstance = nullptr;
	ZwValidation* m_pValidation = nullptr; 
	ZwPhysicalDevice* m_pPhysicalDevice = nullptr;
	ZwLogicalDevice* m_pLogicalDevice = nullptr;
};

#endif // !ZWRENDER_H
