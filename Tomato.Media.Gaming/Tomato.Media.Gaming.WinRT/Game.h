//
// Tomato Media Gaming
// ��Ϸ����
// 
// ���ߣ�SunnyCase 
// �������� 2015-09-05
#pragma once
#include "common.h"
#include "DeviceManager.h"

DEFINE_NS_MEDIA_GAMING

///<summary>��Ϸ����</summary>
[Windows::Foundation::Metadata::WebHostHiddenAttribute]
public ref class Game sealed
{
public:
	Game();

	void SetPresenter(Windows::UI::Xaml::Controls::SwapChainPanel^ swapChainPanel, uint32 width, uint32 height);
private:
	std::unique_ptr<DeviceManager> deviceManager;
};

END_NS_MEDIA_GAMING