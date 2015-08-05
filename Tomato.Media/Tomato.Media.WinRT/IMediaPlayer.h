//
// Tomato Media
// ý�岥�����ӿ�
// 
// ���ߣ�SunnyCase 
// �������� 2015-08-05
#pragma once
#include "common.h"
#include "MediaSource.h"

DEFINE_NS_MEDIA

///<summary>ý�岥�����ӿ�</summary>
public interface class IMediaPlayer
{
	void SetMediaSource(MediaSource^ mediaSource);
	void Play();
	void Pause();

	event Windows::Foundation::TypedEventHandler<IMediaPlayer^, Platform::Object^>^ MediaOpened;
	event Windows::Foundation::TypedEventHandler<IMediaPlayer^, Platform::Object^>^ CurrentStateChanged;
};

END_NS_MEDIA