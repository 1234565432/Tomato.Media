//
// Tomato Media
// ý��Ԫ�����ṩ����
// 
// ���ߣ�SunnyCase 
// �������� 2016-01-02
#pragma once
#include "common.h"
#include "Metadata/MediaMetadata.h"

DEFINE_NS_MEDIA

public ref class MediaMetadataProvider sealed
{
public:
	static Windows::Foundation::IAsyncOperation<MediaMetadataProvider^>^ CreateFromStream(Windows::Storage::Streams::IRandomAccessStream^ stream, bool brief);

	///<summary>����</summary>
	property Platform::String^ Title {Platform::String^ get(); }
	///<summary>ר��</summary>
	property Platform::String^ Album {Platform::String^ get(); }
	///<summary>ר��������</summary>
	property Platform::String^ AlbumArtist {Platform::String^ get(); }
	///<summary>������</summary>
	property Platform::String^ Artist {Platform::String^ get(); }
	///<summary>����</summary>
	property Platform::IBox<Windows::Foundation::TimeSpan>^ Duration {Platform::IBox<Windows::Foundation::TimeSpan>^ get(); }
	///<summary>���</summary>
	property Platform::String^ Lyrics {Platform::String^ get(); }

	virtual ~MediaMetadataProvider();
private:
	MediaMetadataProvider();
	concurrency::task<void> LoadAsync(Windows::Storage::Streams::IRandomAccessStream^ stream, bool brief);
private:
	std::shared_ptr<Internal::MediaMetadataContainer> _container;
};

END_NS_MEDIA