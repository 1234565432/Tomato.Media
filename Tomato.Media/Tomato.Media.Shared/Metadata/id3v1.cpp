//
// Tomato Media
// ID3v1 ������Ϣ
// 
// ���ߣ�SunnyCase 
// ����ʱ�䣺2015-04-03
#include "pch.h"
#include "id3v1.h"
#include <Tomato.Core/BinaryReader.h>
#include <Tomato.Core/encoding.h>
#include <array>

using namespace NS_CORE;
using namespace NS_MEDIA;
using namespace concurrency;

enum
{
	// �ܳ���
	TOTAL_LEN = 128,
	// ͷ������
	HEADER_LEN = 3,
	// ���ⳤ��
	TITLE_LEN = 30,
	// �����ҳ���
	ARTIST_LEN = 30,
	// ר������
	ALBUM_LEN = 30,
	// ע�ͣ������죩����
	COMMENT_AND_TRACK_LEN = 30,
	// ����ǰ�� Padding λ��
	TRACK_PAD_OFFSET = 28,
	// �����λ��
	TRACK_OFFSET = 29,
	// ���ɳ���
	GENRE_LEN = 1
};

static const std::array<byte, HEADER_LEN> GoodHeader = { 'T', 'A', 'G' };

std::wstring NS_MEDIA::to_string(ID3v1Genre value)
{
	static const wchar_t* texts[(size_t)ID3v1Genre::COUNT] =
	{
		L"Blues",
		L"ClassicRock",
		L"Country",
		L"Dance",
		L"Disco",
		L"Funk"
	};
	auto iValue = (size_t)value;
	if (iValue >= 0 && iValue < (size_t)ID3v1Genre::COUNT)
		return texts[iValue];
	return L"Unknown";
}

#pragma pack(push, 1)
struct ID3V1Tag
{
	std::array<byte, HEADER_LEN> Header;
	char Title[30];
	char Artist[30];
	char Album[30];
	uint32_t Year;
	union
	{
		char Comment[30];
		struct
		{
			char LessComment[28];
			bool NoTrackNumber;
			byte TrackNumber;
		};
	};
	byte Genre;
};
#pragma pack(pop)

ID3V1Meta::ID3V1Meta()
	:valid(false)
{

}

bool ID3V1Meta::IsGood() const noexcept
{
	return valid;
}

task<bool> ID3V1Meta::ReadMetadata(IMFByteStream* byteStream, MediaMetadataContainer& container)
{
	ID3V1Meta meta;
	auto good = await meta.Read(byteStream);
	if (good)
	{
		container.Add<DefaultMediaMetadatas::Title>(meta.title);
		container.Add<DefaultMediaMetadatas::Album>(meta.album);
		container.Add<DefaultMediaMetadatas::Artist>(meta.artist);
		container.Add<DefaultMediaMetadatas::Year>(meta.year);
		container.Add<DefaultMediaMetadatas::TrackNumber>(std::to_wstring(meta.track));
		container.Add<DefaultMediaMetadatas::Genre>(to_string(meta.genre));
	}
	return good;
}

task<bool> ID3V1Meta::Read(IMFByteStream* byteStream)
{
	this->valid = false;
	BinaryReader<IMFByteStream> streamReader(byteStream);
	auto ret = [&]
	{
		if (streamReader.GetLength() < TOTAL_LEN)
			return false;
		// ת��β������ȡ�ܳ�����ô���ֽ�
		streamReader.Seek(-TOTAL_LEN, SeekOrigin::End);
		if (streamReader.Load(TOTAL_LEN) != TOTAL_LEN)
			return false;

		auto tag = streamReader.Read<ID3V1Tag>();
		// ���ͷ��
		if (tag.Header != GoodHeader)
			return false;
		this->title = s2ws(tag.Title);
		this->artist = s2ws(tag.Artist);
		this->album = s2ws(tag.Album);
		this->year = tag.Year;

		if (tag.NoTrackNumber)
		{
			this->comment = s2ws(tag.Comment);
			this->track = 0;
		}
		else
		{
			this->comment = s2ws(tag.LessComment);
			this->track = tag.TrackNumber;
		}
		this->genre = static_cast<ID3v1Genre>(
			tag.Genre < (byte)ID3v1Genre::COUNT ? tag.Genre : (byte)ID3v1Genre::Unknown);

		this->valid = true;
		return true;
	}();
	return task_from_result(ret);
}