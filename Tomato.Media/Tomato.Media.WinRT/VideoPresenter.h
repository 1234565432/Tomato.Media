//
// Tomato Media
// ��Ƶ������
// 
// ���ߣ�SunnyCase 
// �������� 2015-08-05
#pragma once
#include "common.h"
#include "MediaSource.h"
#include "VideoEngine.h"
#include <windows.ui.xaml.media.dxinterop.h>

DEFINE_NS_MEDIA

///<summary>��Ƶ������</summary>
[Windows::Foundation::Metadata::WebHostHiddenAttribute]
public ref class VideoPresenter sealed
{
public:
	VideoPresenter();

	void SetMediaSource(MediaSource^ mediaSource);

	property Windows::UI::Xaml::Media::Imaging::SurfaceImageSource^ ImageSource
	{
		Windows::UI::Xaml::Media::Imaging::SurfaceImageSource^ get() { return imageSource; }
	}

	void Play();
private:
	void InitializeSurfaceImageSource();
private:
	Windows::UI::Xaml::Media::Imaging::SurfaceImageSource^ imageSource;
	WRL::ComPtr<ISurfaceImageSourceNativeWithD2D> imageSourceNative;
	VideoEngine videoEngine;
};

END_NS_MEDIA