//
// Tomato Media
// ��̨ý�岥����
// 
// ���ߣ�SunnyCase 
// �������� 2015-08-04
#pragma once
#include "common.h"

DEFINE_NS_MEDIA

///<summary>��̨ý�岥����</summary>
[Windows::Foundation::Metadata::WebHostHidden]
public ref class BackgroundMediaPlayer sealed : public Windows::ApplicationModel::Background::IBackgroundTask
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
private:
	void ActivateHandler();
	void AttachEventHandlers();

	void OnMessageReceivedFromForeground(Platform::Object ^sender, Windows::Media::Playback::MediaPlayerDataReceivedEventArgs ^args);
private:
	Platform::Agile<Windows::ApplicationModel::Background::BackgroundTaskDeferral> deferral;
	Windows::Media::Playback::MediaPlayerState playerState = Windows::Media::Playback::MediaPlayerState::Closed;
	Windows::Media::Playback::MediaPlayer^ mediaPlayer;
};

END_NS_MEDIA