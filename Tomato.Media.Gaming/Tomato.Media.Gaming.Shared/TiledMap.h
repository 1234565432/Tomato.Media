//
// Tomato Media Gaming
// Tiled ��ͼ
// 
// ���ߣ�SunnyCase 
// �������� 2015-10-03
#pragma once
#include "common.h"
#include <ppltasks.h>
#include <unordered_map>

DEFINE_NS_MEDIA_GAMING_INTERN
namespace TiledMap
{
	struct TiledMapReaderHandler
	{
		virtual concurrency::task<std::wstring> OnReadTileSet(const std::wstring& name) const = 0;
	};
}
END_NS_MEDIA_GAMING_INTERN