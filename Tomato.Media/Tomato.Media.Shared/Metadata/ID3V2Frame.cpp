//
// Tomato Media
// ID3v2 ������Ϣ
// 
// ���ߣ�SunnyCase 
// ����ʱ�䣺2015-04-03
#include "pch.h"
#include "ID3V2Frame.h"
#include "../../include/encoding.h"

using namespace NS_CORE;
using namespace NS_MEDIA;
using namespace NS_MEDIA_INTERN;
using namespace concurrency;

const ID3V2FrameKind ID3V2FrameKinds::Padding = { 0, 0, 0, 0 };
const ID3V2FrameKind ID3V2FrameKinds::Unknown = { 0, 0, 0, 0 };
const ID3V2FrameKind ID3V2FrameKinds::COMM = { 'C', 'O', 'M', 'M' };
const ID3V2FrameKind ID3V2FrameKinds::TIT2 = { 'T', 'I', 'T', '2' };
const ID3V2FrameKind ID3V2FrameKinds::TALB = { 'T', 'A', 'L', 'B' };
const ID3V2FrameKind ID3V2FrameKinds::TCON = { 'T', 'C', 'O', 'N' };
const ID3V2FrameKind ID3V2FrameKinds::TPOS = { 'T', 'P', 'O', 'S' };
const ID3V2FrameKind ID3V2FrameKinds::TXXX = { 'T', 'X', 'X', 'X' };
const ID3V2FrameKind ID3V2FrameKinds::TPE1 = { 'T', 'P', 'E', '1' };
const ID3V2FrameKind ID3V2FrameKinds::TPE2 = { 'T', 'P', 'E', '2' };
const ID3V2FrameKind ID3V2FrameKinds::PRIV = { 'P', 'R', 'I', 'V' };
const ID3V2FrameKind ID3V2FrameKinds::TPUB = { 'T', 'P', 'U', 'B' };
const ID3V2FrameKind ID3V2FrameKinds::TRCK = { 'T', 'R', 'C', 'K' };
const ID3V2FrameKind ID3V2FrameKinds::TYER = { 'T', 'Y', 'E', 'R' };
const ID3V2FrameKind ID3V2FrameKinds::APIC = { 'A', 'P', 'I', 'C' };

constexpr static const uint16_t UTF_16_BOM = 0xFEFF;

namespace
{
#define DEFINE_FRAME_ACRIVATOR(name) { ID3V2FrameKinds::##name, [] {return std::make_unique<ID3V2Frame##name>(); } }

	static const FrameFactory frameFactory =
	{
		DEFINE_FRAME_ACRIVATOR(COMM),
		DEFINE_FRAME_ACRIVATOR(TALB),
		DEFINE_FRAME_ACRIVATOR(TCON),
		DEFINE_FRAME_ACRIVATOR(TIT2),
		DEFINE_FRAME_ACRIVATOR(TPE1),
		DEFINE_FRAME_ACRIVATOR(TPE2),
		DEFINE_FRAME_ACRIVATOR(TPUB),
		DEFINE_FRAME_ACRIVATOR(TRCK),
		DEFINE_FRAME_ACRIVATOR(TYER),
		DEFINE_FRAME_ACRIVATOR(PRIV),
		DEFINE_FRAME_ACRIVATOR(TXXX),
		DEFINE_FRAME_ACRIVATOR(APIC),
	};

	enum
	{
		// Id
		ID_LEN = 4,
		// ���ݴ�С
		CONTENT_LEN_LEN = 4,
		// ��־
		FLAG_LEN = 2,
		// ͷ������
		HEADER_LEN = ID_LEN + CONTENT_LEN_LEN + FLAG_LEN
	};

#pragma pack(push, 1)

	struct ID3V2FrameHeader
	{
		std::array<byte, ID_LEN> Id;
		uint32_t Size;
		ID3V2FrameFlags Flags;

		void Fix()
		{
			Size = to_be(Size);
		}
	};
	static_assert(sizeof(ID3V2FrameHeader) == HEADER_LEN, "sizeof ID3V2FrameHeader must equal to HEADER_LEN.");

#pragma pack(pop)

	static std::unique_ptr<ID3V2Frame> CreateFrame(const ID3V2FrameKind& kind)
	{
		auto it = frameFactory.find(kind);
		// ��֪֡���
		if (it != frameFactory.end())
			return it->second();
		// δ֪
		return std::make_unique<ID3V2FrameUnknown>();
	}

	// ID3v2 �ı�
	class ID3V2Text
	{
	public:
		ID3V2Text(ID3V2TextEncoding encoding, bool hasNullTerm)
			:encoding(encoding), hasNullTerm(hasNullTerm)
		{

		}

		void SetHasNullTerm(bool value)
		{
			hasNullTerm = value;
		}

		void SetEncoding(ID3V2TextEncoding encoding)
		{
			this->encoding = encoding;
		}

		enum : size_t
		{
			UnknownCount = SIZE_MAX
		};

		// ��ȡ
		size_t Read(const byte* data, size_t count = UnknownCount)
		{
			if (count == UnknownCount) count = GuessCount(data);
			switch (encoding)
			{
			case ID3V2TextEncoding::ISO_8859_1:
				return ReadISO_8859_1Text(data, count);
			case ID3V2TextEncoding::UCS_2:
				return ReadUCS_2Text(data, count);
			default:
				ThrowAlways(L"Unknown Text Encoding.");
				break;
			}
		}
		// ��ȡ�ı�
		const std::wstring& GetText() const noexcept { return text; }
		std::wstring& GetText() noexcept { return text; }
	private:
		size_t GuessCount(const byte* data)
		{
			switch (encoding)
			{
			case ID3V2TextEncoding::ISO_8859_1:
				return GuessISO_8859_1Count(data);
			case ID3V2TextEncoding::UCS_2:
				return GuessUCS_2Count(data);
			default:
				ThrowAlways(L"Unknown Text Encoding.");
				break;
			}
		}

		size_t GuessISO_8859_1Count(const byte* data)
		{
			size_t count = 0;
			while (*data++)count++;
			return count;
		}

		size_t GuessUCS_2Count(const byte* data)
		{
			auto ptr = reinterpret_cast<const uint16_t*>(data);
			size_t count = 0;
			while (*ptr++)count++;
			return count * 2;
		}

		size_t ReadISO_8859_1Text(const byte* data, size_t count)
		{
			std::string tmp_str(data, data + count);
			text = s2ws(tmp_str);
			return count + (hasNullTerm ? 1 : 0);
		}

		size_t ReadUCS_2Text(const byte* data, size_t count)
		{
			auto rest = count / 2;
			auto ptr = (const wchar_t*)data;
			// BOM
			if (*ptr == UTF_16_BOM)
			{
				ptr++;
				rest--;
			}
			text = std::wstring(ptr, rest);
			return count + (hasNullTerm ? 2 : 0);
		}
	private:
		ID3V2TextEncoding encoding;
		bool hasNullTerm;
		std::wstring text;
	};
}

ID3V2FrameKind ID3V2Frame::ReadFrame(BinaryReader<byte*> & reader, const std::function<bool(const ID3V2FrameKind&)>& framePredicate, std::unique_ptr<ID3V2Frame>& frame)
{
	// ��ȡͷ��
	auto header = reader.Read<ID3V2FrameHeader>();
	header.Fix();
	// ��������Ҫ��֡
	if (!framePredicate(header.Id) || header.Id == ID3V2FrameKinds::Padding)
		reader.Seek(header.Size, SeekOrigin::Current);
	else
	{
		frame = CreateFrame(header.Id);
		frame->contentLength = header.Size;
		frame->flags = header.Flags;

		auto content = reader.Read(header.Size);
		frame->ReadContent({ content.get(), header.Size });
	}
	return header.Id;
}

void ID3V2FrameUnknown::ReadContent(BinaryReader<byte*> && reader)
{
}

void ID3V2FrameCOMM::ReadContent(BinaryReader<byte*> && reader)
{
	encoding = reader.Read<ID3V2TextEncoding>();
	language = reader.Read<3>();

	ID3V2Text textReader(encoding, true);
	reader.Seek(textReader.Read(reader.GetCurrentPointer()), SeekOrigin::Current);
	description = textReader.GetText();
	textReader.SetHasNullTerm(false);
	textReader.Read(reader.GetCurrentPointer(), reader.GetAvailable());
	text = textReader.GetText();
}

void ID3V2FrameSingleText::ReadContent(BinaryReader<byte*> && reader)
{
	encoding = reader.Read<ID3V2TextEncoding>();
	ID3V2Text textReader(encoding, false);
	textReader.Read(reader.GetCurrentPointer(), reader.GetAvailable());
	text = textReader.GetText();
}

void ID3V2FramePRIV::ReadContent(BinaryReader<byte*> && reader)
{
	ID3V2Text textReader(ID3V2TextEncoding::ISO_8859_1, true);
	reader.Seek(textReader.Read(reader.GetCurrentPointer()), SeekOrigin::Current);
	identifier = textReader.GetText();
	data.resize(reader.GetAvailable());
	reader.Read(data.data(), data.size());
}

void ID3V2FrameTXXX::ReadContent(BinaryReader<byte*> && reader)
{
	encoding = reader.Read<ID3V2TextEncoding>();
	ID3V2Text textReader(encoding, true);
	reader.Seek(textReader.Read(reader.GetCurrentPointer()), SeekOrigin::Current);
	description = textReader.GetText();
	textReader.SetHasNullTerm(false);
	textReader.Read(reader.GetCurrentPointer(), reader.GetAvailable());
	value = textReader.GetText();
}

void ID3V2FrameAPIC::ReadContent(BinaryReader<byte*>&& reader)
{
	encoding = reader.Read<ID3V2TextEncoding>();
	ID3V2Text textReader(ID3V2TextEncoding::ISO_8859_1, true);
	reader.Seek(textReader.Read(reader.GetCurrentPointer()), SeekOrigin::Current);
	mimeType = std::move(textReader.GetText());
	pictureType = reader.Read<ID3V2PictureType>();
	textReader.SetEncoding(encoding);
	reader.Seek(textReader.Read(reader.GetCurrentPointer()), SeekOrigin::Current);
	description = std::move(textReader.GetText());
	auto begin = reader.GetCurrentPointer();
	data.assign(begin, begin + reader.GetAvailable());
}
