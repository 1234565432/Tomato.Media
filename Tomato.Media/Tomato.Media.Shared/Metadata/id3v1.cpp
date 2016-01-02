//
// Tomato Media
// ID3v1 ������Ϣ
// 
// ���ߣ�SunnyCase 
// ����ʱ�䣺2015-04-03
#include "pch.h"
#include "id3v1.h"
#include "../../include/BinaryReader.h"
#include "../../include/encoding.h"

using namespace NS_CORE;
using namespace NS_MEDIA;
using namespace NS_MEDIA_INTERN;
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

std::wstring NS_MEDIA_INTERN::to_string(ID3v1Genre value)
{
	static constexpr const wchar_t* texts[(size_t)ID3v1Genre::COUNT] =
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

task<bool> ID3V1Meta::ReadMetadata(IMFByteStream* byteStream, std::shared_ptr<MediaMetadataContainer> container)
{
	auto meta = std::make_shared<ID3V1Meta>();

	return meta->Read(byteStream).then([=](bool good)
	{
		if (good)
		{
			auto pmeta = meta.get();
			auto cntner = container.get();
			cntner->Add<DefaultMediaMetadatas::Title>(pmeta->title);
			cntner->Add<DefaultMediaMetadatas::Album>(pmeta->album);
			cntner->Add<DefaultMediaMetadatas::Artist>(pmeta->artist);
			cntner->Add<DefaultMediaMetadatas::Year>(pmeta->year);
			cntner->Add<DefaultMediaMetadatas::TrackNumber>(std::to_wstring(pmeta->track));
			cntner->Add<DefaultMediaMetadatas::Genre>(to_string(pmeta->genre));
		}
		return good;
	});
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