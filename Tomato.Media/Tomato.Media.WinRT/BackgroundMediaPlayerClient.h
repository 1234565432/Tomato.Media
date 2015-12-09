//
// Tomato Media
// ��̨ý�岥�����ͻ���
// 
// ���ߣ�SunnyCase 
// �������� 2015-08-04
#pragma once
#include "common.h"

DEFINE_NS_MEDIA

///<summary>��̨��Ƶ������</summary>
public ref class BackgroundMediaPlayerClient sealed
{
public:
	///<summary>���� <see cref="BackgroundMediaPlayerClient"/> ����ʵ����</summary>
	///<param name="mediaPlayerHandlerTypeName">ʵ���� <see cref="IBackgroundMediaHandler"/> �����͡�</param>
	BackgroundMediaPlayerClient(Platform::String^ mediaPlayerHandlerTypeName);

	event Windows::Foundation::EventHandler<Platform::Object^>^ PlayerActivated;
	event Windows::Foundation::EventHandler<Platform::String^>^ MessageReceived;

	void SendMessage(Platform::String^ message);
private:
	void AttachMessageListener();
	void DetachMessageListener();

	void OnMessageReceivedFromBackground(Platform::Object^ sender, Windows::Media::Playback::MediaPlayerDataReceivedEventArgs^ e);
private:
	Windows::Foundation::EventRegistrationToken messageListenerToken;
};

END_NS_MEDIA