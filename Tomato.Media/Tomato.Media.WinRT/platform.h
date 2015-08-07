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

#define CATCH_ALL() catch(Platform::Exception^ ex){ return ex->HResult;}catch(_com_error& ex){return ex.Error();}catch(...){return E_FAIL;}

namespace WRL = Microsoft::WRL;