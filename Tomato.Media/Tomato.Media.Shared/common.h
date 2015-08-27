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
#define ARGUMENT_NOTNULL_HR(pointer) if(!(pointer)) return E_POINTER

#include <functional>

///<summary>�ս���</summary>
class finalizer final
{
public:
	finalizer(std::function<void()> action)
		:action(std::move(action))
	{

	}

	~finalizer()
	{
		if (action)
			action();
	}
private:
	std::function<void()> action;
};

#include <chrono>
typedef std::ratio<1, 10000000> hn;
typedef std::chrono::duration<long long, hn> hnseconds;