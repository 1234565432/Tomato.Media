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

	property Windows::Media::SystemMediaTransportControls^ SystemMediaTransportControls
	{
		Windows::Media::SystemMediaTransportControls^ get();
	}

	property Windows::Foundation::TimeSpan Position
	{
		Windows::Foundation::TimeSpan get();
		void set(Windows::Foundation::TimeSpan value);
	}

	property bool IsMuted
	{
		bool get();
		void set(bool value);
	}

	property double Volume
	{
		double get();
		void set(double value);
	}

	event Windows::Foundation::TypedEventHandler<IMediaPlayer^, Platform::Object^>^ MediaOpened;
	event Windows::Foundation::TypedEventHandler<IMediaPlayer^, Platform::Object^>^ MediaEnded;
	event Windows::Foundation::TypedEventHandler<IMediaPlayer^, Windows::Media::Playback::MediaPlayerFailedEventArgs^>^ MediaFailed;
	event Windows::Foundation::TypedEventHandler<IMediaPlayer^, Platform::Object^>^ CurrentStateChanged;
	event Windows::Foundation::TypedEventHandler<IMediaPlayer^, Platform::Object^>^ SeekCompleted;
};

END_NS_MEDIA