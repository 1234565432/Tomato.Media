//
// Tomato Media
// WIC ����
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-08-16
//
#pragma once
#include "common.h"
#include <wincodec.h>

DEFINE_NS_MEDIA

///<summary>WIC ����</summary>
class WICHelper
{
public:
	WICHelper();

	void SaveTexture(ID3D11DeviceContext* d3dDeviceContext, ID3D11Texture2D* texture);
private:
	void CreateWICComponent();
private:
	WRL::ComPtr<IWICImagingFactory> wicFactory;
};

END_NS_MEDIA