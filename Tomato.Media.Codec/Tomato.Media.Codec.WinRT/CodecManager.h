//
// Tomato Media Codec
// Codec ������
// 
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-09-06
#pragma once
#include "common.h"
#include "Tomato.Media.Codec_i.h"
#include <windows.media.core.h>

DEFINE_NS_MEDIA_CODEC

class CodecManager : public WRL::RuntimeClass<WRL::RuntimeClassFlags<WRL::WinRt>, WRL::FtmBase,
	ABI::NS_MEDIA_CODEC::ICodecManager>
{
	InspectableClass(RuntimeClass_Tomato_Media_Codec_CodecManager, BaseTrust);
public:
	HRESULT RuntimeClassInitialize();
	// ͨ�� RuntimeClass �̳�
	STDMETHODIMP RegisterDefaultCodecs(void) override;
private:
	WRL::ComPtr<ABI::Windows::Media::IMediaExtensionManager> mediaExtensionManager;
};

END_NS_MEDIA_CODEC