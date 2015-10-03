//
// Tomato Media Gaming
// Tile ͼ���ȡ��
// 
// ���ߣ�SunnyCase 
// �������� 2015-10-03
#pragma once
#include "common.h"
#include "tiledmap.h"
#include <rapidjson/document.h>

DEFINE_NS_MEDIA_GAMING_INTERN
namespace TiledMap
{
	// Tile ͼ��
	class TileSet
	{
	public:
		TileSet();
		void Reset();

		uint32_t FirstGlobalId;
		std::wstring Source;
		std::wstring Name;
		size_t TileWidth;
		size_t TileHeight;
		size_t Spacing;
		size_t Margin;
		size_t TileCount;
		std::wstring ImageSource;

		bool _Loaded;
	};

	// Tile ͼ���ȡ��
	// ����˳�� Parse -> InitializeTileSet
	class TileSetReader : public std::enable_shared_from_this<TileSetReader>
	{
	public:
		TileSetReader(std::shared_ptr<TiledMapReaderHandler> handler);
		void Parse(const std::wstring& source);
		void Parse(const rapidjson::GenericValue<rapidjson::UTF16<>>& value);

		concurrency::task<TileSet> InitializeTileSet();
	private:
		void ParseTileSet(const rapidjson::GenericValue<rapidjson::UTF16<>>& value);
	private:
		std::shared_ptr<TiledMapReaderHandler> _handler;
		TileSet _tileSet;
	};
}
END_NS_MEDIA_GAMING_INTERN