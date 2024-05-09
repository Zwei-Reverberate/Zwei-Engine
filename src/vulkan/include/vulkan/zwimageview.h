#ifndef ZWIMAGEVIEW_H
#define ZWIMAGEVIEW_H
#include <include/vulkan/zwlogicaldevice.h>
#include <vector>

class ZwSwapChain;
class ZwImageView
{
public:
	void init(ZwSwapChain* pSwapChain, ZwLogicalDevice* pLogicalDevice);
	void destroy(ZwLogicalDevice* pLogicalDevice);
	const std::vector<VkImageView>& getSwapChainImageViews() const { return m_swapChainImageViews; }

private:
	std::vector<VkImageView> m_swapChainImageViews;
};

#endif // !ZWIMAGEVIEW_H
