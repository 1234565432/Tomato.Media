//
// Tomato Media
// ƽ̨��� for Windows Desktop
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-08-05
//
#pragma once
#include <comdef.h>
#include <wrl.h>
#include <stdexcept>

inline void ThrowIfFailed(HRESULT hr)
{
	if (FAILED(hr)) _com_raise_error(hr);
}

struct tomato_error
{
	HRESULT hr;
	const wchar_t* message;
};

inline void ThrowIfFailed(HRESULT hr, const wchar_t* message)
{
	throw tomato_error{ hr,message };
}

template<typename T>
void ThrowWin32IfNot(T value)
{
	if(!value) _com_raise_error(HRESULT_FROM_WIN32(GetLastError()));
}

#define CATCH_ALL() catch(tomato_error& ex){ return ex.hr;}catch(_com_error& ex){return ex.Error();}catch(...){return E_FAIL;}

namespace WRL = Microsoft::WRL;

// ��ģ����
extern HMODULE ModuleHandle;