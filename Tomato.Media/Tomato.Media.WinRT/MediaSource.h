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

///<summary>ý��Դ</summary>
public ref class MediaSource sealed
{
public:
	static Windows::Foundation::IAsyncOperation<MediaSource^>^ CreateFromStream(Windows::Storage::Streams::IRandomAccessStream^ stream);
	static Windows::Foundation::IAsyncOperation<MediaSource^>^ CreateFromStream(Windows::Storage::Streams::IRandomAccessStream^ stream, Platform::String^ uriHint);

	///<summay>��������Ԫ����</summay>
	//Windows::Foundation::IAsyncAction^ InitializeFullMetadatas();

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
internal:
	property IMFMediaSource* MFMediaSource {IMFMediaSource* get() { return mediaSource.Get(); }}
private:
	MediaSource();
	concurrency::task<void> OpenAsync(Windows::Storage::Streams::IRandomAccessStream^ stream, Platform::String^ uriHint = nullptr);
private:
	MFMediaSourceWrapper mediaSource;
};

END_NS_MEDIA