//
// Tomato Media
// Windows::Meida::Core::IMediaSource ʵ��
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-08-05
//
#pragma once
#include "common.h"
#include <windows.media.core.h>
#include <mfidl.h>
#include "MediaSource.h"

DEFINE_NS_MEDIA

class CoreMediaSource sealed : public WRL::RuntimeClass<WRL::RuntimeClassFlags<WRL::RuntimeClassType::WinRtClassicComMix>,
	ABI::Windows::Media::Core::IMediaSource, IMFGetService>
{
public:
	CoreMediaSource(MediaSource^ mediaSource);
	virtual ~CoreMediaSource();

	// ͨ�� RuntimeClass �̳�
	STDMETHODIMP GetService(REFGUID guidService, REFIID riid, LPVOID * ppvObject) override;
private:
	MediaSource^ mediaSource;
};

END_NS_MEDIA