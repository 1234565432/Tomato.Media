//
// Tomato Media
// ��Ƶ������
// 
// ���ߣ�SunnyCase 
// �������� 2015-08-05
#pragma once
#include "common.h"
#include "MediaSource.h"

DEFINE_NS_MEDIA

///<summary>��Ƶ������</summary>
public ref class VideoPresenter sealed
{
public:
	VideoPresenter();

	void SetMediaSource(MediaSource^ mediaSource);
private:
	Windows::UI::Xaml::Media::Imaging::SurfaceImageSource^ imageSource;
};

END_NS_MEDIA