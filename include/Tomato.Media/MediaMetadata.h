//
// Tomato Media
// ý��Ԫ����
// 
// ���ߣ�SunnyCase 
// ����ʱ�䣺2015-03-18
#pragma once
#include <Tomato.Media/Tomato.Media.h>
#include <Tomato.Core/any.h>
#include <unordered_map>
#include <string>

DEFINE_NS_MEDIA

#define DECLARE_MEDIAMETA_TYPE(name, valuetype) struct name { \
TOMATO_MEDIA_API static const std::wstring Name; \
using value_type = valuetype;};

struct Picture
{
	std::wstring MimeType;
	std::wstring Description;
	std::wstring Type;
	std::vector<byte> Data;
};

class DefaultMediaMetadatas
{
public:
	// ����
	DECLARE_MEDIAMETA_TYPE(Title, std::wstring);
	// ר��
	DECLARE_MEDIAMETA_TYPE(Album, std::wstring);
	// ר��������
	DECLARE_MEDIAMETA_TYPE(AlbumArtist, std::wstring);
	// ������
	DECLARE_MEDIAMETA_TYPE(Artist, std::wstring);
	// ���
	DECLARE_MEDIAMETA_TYPE(Year, uint32_t);
	// ������
	DECLARE_MEDIAMETA_TYPE(TrackNumber, std::wstring);
	// ����
	DECLARE_MEDIAMETA_TYPE(Genre, std::wstring);
	// ���
	DECLARE_MEDIAMETA_TYPE(Lyrics, std::wstring);
	// ͼƬ
	DECLARE_MEDIAMETA_TYPE(Picture, NS_MEDIA::Picture);
};

// ý��Ԫ��������
class MediaMetadataContainer
{
public:
	MediaMetadataContainer()
	{

	}

	// ���Ԫ����
	template<typename TMeta>
	void Add(typename TMeta::value_type value)
	{
		metadatas.emplace(TMeta::Name, Core::any(value));
	}

	template<typename TMeta>
	// ��ȡԪ����
	typename const TMeta::value_type& Get() const
	{
		return any_cast<typename TMeta::value_type>(metadatas.find(TMeta::Name)->second);
	}

	template<typename TMeta>
	// Ԫ�����Ƿ����
	bool Exists() const
	{
		return metadatas.find(TMeta::Name) != metadatas.end();
	}

	template<typename TMeta>
	// ��ȡԪ����
	typename const TMeta::value_type& GetOrDefault(typename TMeta::value_type& defaultValue = typename TMeta::value_type()) const
	{
		if (Exists<TMeta>())
			return Get<TMeta>();
		return defaultValue;
	}

	template<typename TMeta, typename TCallback>
	// ��ȡԪ����
	void ForEach(TCallback&& callback) const
	{
		auto range = metadatas.equal_range(TMeta::Name);
		for (auto it = range.first;it != range.second;++it)
			if (callback(any_cast<typename TMeta::value_type>(it->second)))
				break;
	}

	size_t GetSize() const noexcept
	{
		return metadatas.size();
	}
private:
	std::unordered_multimap<std::wstring, Core::any> metadatas;
};

TOMATO_MEDIA_API concurrency::task<void> TryGetMediaMetadata(MediaMetadataContainer& container, IMFByteStream* byteStream, const std::wstring& uriHint, bool brief = true);

END_NS_MEDIA