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

END_NS_MEDIA