//
// Tomato Media
// ��̨ý�岥����
// 
// ���ߣ�SunnyCase 
// �������� 2015-08-04
#pragma once
#include "common.h"
#include "IMediaPlayer.h"

DEFINE_NS_MEDIA

///<summary>��̨ý�岥����</summary>
[Windows::Foundation::Metadata::WebHostHidden]
public ref class BackgroundMediaPlayer sealed : public Windows::ApplicationModel::Background::IBackgroundTask, public IMediaPlayer
{
public:
	BackgroundMediaPlayer();

	///<summary>��ȡ������״̬��</summary>
	property Windows::Media::Playback::MediaPlayerState State
	{
		Windows::Media::Playback::MediaPlayerState get() { return playerState; }
	}

	// ͨ�� IBackgroundTask �̳�
	virtual void Run(Windows::ApplicationModel::Background::IBackgroundTaskInstance ^taskInstance);

	// ͨ�� IMediaPlayer �̳�
	virtual void SetMediaSource(MediaSource^ mediaSource);
	virtual void Play();
	virtual void Pause();

	virtual event Windows::Foundation::TypedEventHandler<IMediaPlayer^, Platform::Object^>^ MediaOpened;
	virtual event Windows::Foundation::TypedEventHandler<IMediaPlayer^, Platform::Object^>^ CurrentStateChanged;
private:
	void ActivateHandler();
	void AttachMessageHandlers();
	void ConfigureMediaPlayer();

	void OnMessageReceivedFromForeground(Platform::Object ^sender, Windows::Media::Playback::MediaPlayerDataReceivedEventArgs ^args);
	void OnMediaOpened(Windows::Media::Playback::MediaPlayer ^sender, Platform::Object ^args);
private:
	Platform::Agile<Windows::ApplicationModel::Background::BackgroundTaskDeferral> deferral;
	Windows::Media::Playback::MediaPlayerState playerState = Windows::Media::Playback::MediaPlayerState::Closed;
	Windows::Media::Playback::MediaPlayer^ mediaPlayer;
	void OnCurrentStateChanged(Windows::Media::Playback::MediaPlayer ^sender, Platform::Object ^args);
};

END_NS_MEDIA