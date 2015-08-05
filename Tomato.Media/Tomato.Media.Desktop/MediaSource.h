//
// Tomato Media
// ý��Դ
// 
// ���ߣ�SunnyCase 
// �������� 2015-08-05
#pragma once
#include "common.h"
#include "Utility/MFMediaSourceWrapper.h"

DEFINE_NS_MEDIA

#include "Tomato.Media_i.h"

///<summary>ý��Դ</summary>
class MediaSource : public WRL::RuntimeClass<WRL::RuntimeClassFlags<WRL::RuntimeClassType::ClassicCom>,
	IMediaSource>
{
public:
	MediaSource();

	// ͨ�� RuntimeClass �̳�
	STDMETHODIMP get_Title(BSTR * title) override;
	STDMETHODIMP get_Album(BSTR * album) override;
	STDMETHODIMP Open(IStream * pStream) override;
private:
	MFMediaSourceWrapper mediaSource;
};

CoCreatableClass(MediaSource);

END_NS_MEDIA
