//
// Tomato Media
// ����ͷ�ļ�
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-08-04
//
#pragma once

#define DEFINE_NS_MEDIA namespace Tomato { namespace Media {
#define END_NS_MEDIA }}
#define NS_MEDIA Tomato::Media

#include "platform.h"

#define DEFINE_PROPERTY_GET(name, type) __declspec(property(get = get_##name)) type name