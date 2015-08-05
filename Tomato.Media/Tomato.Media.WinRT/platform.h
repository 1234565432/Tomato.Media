//
// Tomato Media
// ƽ̨��� for Windows Runtime
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-08-04
//
#pragma once
#include <comdef.h>
#include <wrl.h>

inline void ThrowIfFailed(HRESULT hr)
{
	if (FAILED(hr)) throw Platform::Exception::CreateException(hr);
}

inline void ThrowIfFailed(HRESULT hr, const wchar_t* message)
{
	throw Platform::Exception::CreateException(hr, ref new Platform::String(message));
}

template<typename T>
inline Windows::Foundation::TimeSpan MSToTimeSpan(T ms)
{
	return Windows::Foundation::TimeSpan{ static_cast<long long>(ms * 10000) };
}

namespace WRL = Microsoft::WRL;