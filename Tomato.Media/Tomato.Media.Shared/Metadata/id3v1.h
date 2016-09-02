//
// Tomato Media
// ID3v1 ������Ϣ
// 
// ���ߣ�SunnyCase 
// ����ʱ�䣺2015-04-03
#pragma once
#include <Tomato.Media/MediaMetadata.h>
#include <ppltasks.h>
#include <mfidl.h>

DEFINE_NS_MEDIA

///<summary>ID3v1 ����</summary>
enum class ID3v1Genre
{
	Blues,
	ClassicRock,
	Country,
	Dance,
	Disco,
	Funk,
	COUNT,
	Unknown = 255
};

std::wstring to_string(ID3v1Genre value);

///<summary>ID3v1 ������Ϣ</summary>
class ID3V1Meta
{
public:
	ID3V1Meta();

	///<summary>�Ƿ��ȡ�ɹ�</summary>
	bool IsGood() const noexcept;
	///<summary>��ȡ������Ϣ</summary>
	///<return>�Ƿ��ȡ�ɹ�</return>
	concurrency::task<bool> Read(IMFByteStream* byteStream);
	///<summary>��ȡ������Ϣ</summary>
	static concurrency::task<bool> ReadMetadata(IMFByteStream* byteStream, MediaMetadataContainer& container);
private:
	bool valid;						// ��ȡ�ɹ�
	std::wstring title;				// ����
	std::wstring artist;			// ������
	std::wstring album;				// ר��
	uint32_t year;					// ���
	std::wstring comment;			// ע��
	byte track;						// ����
	ID3v1Genre genre;				// ����
};

END_NS_MEDIA