//
// Tomato Media
// IMFMediaSource ��װ
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-08-05
//
#pragma once
#include "common.h"

DEFINE_NS_MEDIA

class MFMediaSourceWrapper : public WRL::ComPtr<IMFMediaSource>
{
public:
	MFMediaSourceWrapper();

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
	void Open(IStream* stream);
#endif

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
#if __cplusplus_winrt
	concurrency::task<void> OpenAsync(Windows::Storage::Streams::IRandomAccessStream^ stream);
#endif
#endif

	void Open(IMFByteStream* byteStream);
	concurrency::task<void> OpenAsync(IMFByteStream* byteStream);

	void Reset();

	DEFINE_PROPERTY_GET(Title, std::wstring);
	std::wstring get_Title() const;

	DEFINE_PROPERTY_GET(Album, std::wstring);
	std::wstring get_Album() const;
private:
	// ����Ԫ����
	void EnsureInitializeMetadata() const;
	void CheckOpened() const;
private:
	mutable WRL::ComPtr<IMFMetadata> metadata;
};

END_NS_MEDIA
