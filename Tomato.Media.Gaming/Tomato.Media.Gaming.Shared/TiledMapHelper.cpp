//
// Tomato Media Gaming
// Tiled ��ͼ����
// 
// ���ߣ�SunnyCase 
// �������� 2015-10-03
#include "pch.h"
#include "TiledMapHelper.h"

using namespace NS_MEDIA;
using namespace NS_MEDIA_GAMING_INTERN;
using namespace WRL;
using namespace rapidjson;
using namespace concurrency;

void TiledMap::ParseProperties(const GenericValue<UTF16<>>& value, std::unordered_map<std::wstring, std::wstring>& properties)
{
	if (!value.ObjectEmpty())
	{
		ThrowIfNot(value.IsArray(), L"Invalid Properties.");
		properties.clear();
		properties.reserve(value.Size());
		for (auto it = value.Begin(); it != value.End(); ++it)
			properties.emplace(AsString(value[L"name"]), AsString(value[L"value"]));
	}
}
