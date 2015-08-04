//
// Tomato Media
// ƽ̨��� for Windows Runtime
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-08-04
//
#pragma once
#include <comdef.h>

inline void ThrowIfFailed(HRESULT hr)
{
	if (FAILED(hr)) throw Platform::Exception::CreateException(hr);
}

template<typename T>
inline Windows::Foundation::TimeSpan MSToTimeSpan(T ms)
{
	return Windows::Foundation::TimeSpan{ static_cast<long long>(ms * 10000) };
}