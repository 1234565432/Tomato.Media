//
// Tomato Media
// ��̨ý�岥����������
// 
// ���ߣ�SunnyCase 
// �������� 2015-08-04
#pragma once
#include "common.h"
#include "BackgroundMediaPlayer.h"

DEFINE_NS_MEDIA

///<summary>��̨ý�岥����������</summary>
[Windows::Foundation::Metadata::WebHostHidden]
public interface class IBackgroundMediaPlayerHandler
{
	///<summary>����������ʱ������</summary>
	void OnActivated(BackgroundMediaPlayer^ mediaPlayer);
};

// {612D3DED-CD96-4A02-8449-11FC578CC289}
DEFINE_GUID(CLSID_BackgroundMediaPlyaerHanderGetter,
	0x612d3ded, 0xcd96, 0x4a02, 0x84, 0x49, 0x11, 0xfc, 0x57, 0x8c, 0xc2, 0x89);

public ref class BackgroundMediaPlyaerHanderGetter sealed
{
public:
	BackgroundMediaPlyaerHanderGetter()
	{

	}
};

END_NS_MEDIA