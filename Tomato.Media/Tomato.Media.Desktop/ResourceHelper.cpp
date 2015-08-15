//
// Tomato Media
// ��Դ����
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-08-15
//
#include "pch.h"
#include "ResourceHelper.h"
#include "resource.h"

using namespace NS_MEDIA;

namespace
{
	LPCTSTR ShaderResourceType = TEXT("SHADER");
}

const ResourceRef Resources::DefaultVideoVS = { MAKEINTRESOURCE(IDR_DEFAULTVIDEOVS), ShaderResourceType };
const ResourceRef Resources::DefaultVideoPS = { MAKEINTRESOURCE(IDR_DEFAULTVIDEOPS), ShaderResourceType };