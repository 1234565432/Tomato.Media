//
// Tomato Media
// ��̨ý�岥�����ͻ���
// 
// ���ߣ�SunnyCase 
// �������� 2015-08-04
#pragma once
#include "common.h"

DEFINE_NS_MEDIA

public ref class MessageReceivedEventArgs sealed
{
public:
	MessageReceivedEventArgs(Platform::String^ tag, Platform::String^ message)
		:tag(tag), message(message)
	{

	}

	property Platform::String^ Tag
	{
		Platform::String^ get() { return tag; }
	}

	property Platform::String^ Message
	{
		Platform::String^ get() { return message; }
	}
private:
	Platform::String^ tag;
	Platform::String^ message;
};

///<summary>��̨��Ƶ������</summary>
[Windows::Foundation::Metadata::WebHostHidden]
public ref class BackgroundMediaPlayerClient sealed
{
public:
	///<summary>���� <see cref="BackgroundMediaPlayerClient"/> ����ʵ����</summary>
	///<param name="mediaPlayerHandlerTypeName">ʵ���� <see cref="IBackgroundMediaHandler"/> �����͡�</param>
	BackgroundMediaPlayerClient(Windows::UI::Xaml::Interop::TypeName mediaPlayerHandlerTypeName);

	event Windows::Foundation::EventHandler<Platform::Object^>^ PlayerActivated;
	event Windows::Foundation::EventHandler<MessageReceivedEventArgs^>^ MessageReceived;

	void SendMessage(Platform::String^ tag, Platform::String^ message);
private:
	void AttachMessageListener();
	void DetachMessageListener();

	void OnMessageReceivedFromBackground(Platform::Object^ sender, Windows::Media::Playback::MediaPlayerDataReceivedEventArgs^ e);
private:
	Windows::Foundation::EventRegistrationToken messageListenerToken;
};

END_NS_MEDIA