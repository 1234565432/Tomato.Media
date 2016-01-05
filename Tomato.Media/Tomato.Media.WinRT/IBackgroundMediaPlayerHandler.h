//
// Tomato Media
// ��̨ý�岥����������
// 
// ���ߣ�SunnyCase 
// �������� 2015-08-04
#pragma once
#include "common.h"

DEFINE_NS_MEDIA

ref class BackgroundMediaPlayer;

///<summary>��̨ý�岥����������</summary>
[Windows::Foundation::Metadata::WebHostHidden]
public interface class IBackgroundMediaPlayerHandler
{
	///<summary>����������ʱ������</summary>
	void OnActivated(BackgroundMediaPlayer^ mediaPlayer);
	void OnReceiveMessage(Platform::String^ tag, Platform::String^ message);
	void OnCanceled();
};

END_NS_MEDIA