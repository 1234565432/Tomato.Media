//
// Tomato Media
// ��̨��Ƶ�������ͻ���
// 
// (c) SunnyCase 
// �������� 2015-05-11
#include "pch.h"
#include "BackgroundAudioPlayerClient.h"
#include "BackgroundAudioIPC.h"

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::Media::Playback;
using namespace Tomato::Media;
using namespace Tomato::Media::details;

BackgroundAudioPlayerClient::BackgroundAudioPlayerClient(String^ audioHandlerTypeName)
{
	// ���ô��������Ͳ���ʼ����̨��Ƶ����
	SetSetting<settings::HandlerFullNameSetting>(audioHandlerTypeName);
	AttachMessageListener();
}

void BackgroundAudioPlayerClient::SendMessageToBackground(ValueSet^ valueSet)
{
	BackgroundMediaPlayer::SendMessageToBackground(valueSet);
}

void BackgroundAudioPlayerClient::SendMessageToForeground(ValueSet^ valueSet)
{
	BackgroundMediaPlayer::SendMessageToForeground(valueSet);
}

void BackgroundAudioPlayerClient::AttachMessageListener()
{
	messageListenerToken = BackgroundMediaPlayer::MessageReceivedFromBackground +=
		ref new EventHandler<MediaPlayerDataReceivedEventArgs ^>(this,
			&BackgroundAudioPlayerClient::OnMessageReceivedFromBackground);
}

void BackgroundAudioPlayerClient::DetachMessageListener()
{
	BackgroundMediaPlayer::MessageReceivedFromBackground -= messageListenerToken;
}

void BackgroundAudioPlayerClient::OnMessageReceivedFromBackground(Object ^ sender, MediaPlayerDataReceivedEventArgs ^ e)
{
	MessageReceivedFromBackground(sender, e->Data);
}

TimeSpan BackgroundAudioPlayerClient::Position::get()
{
	return BackgroundMediaPlayer::Current->Position;
}

TimeSpan BackgroundAudioPlayerClient::Duration::get()
{
	return BackgroundMediaPlayer::Current->NaturalDuration;
}