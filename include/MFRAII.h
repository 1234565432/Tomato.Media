//
// Tomato Music
// Media Foundation RAII ����
// 
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-09-12
#pragma once
#include "common.h"
#include <mfidl.h>
#include <sal.h>

DEFINE_NS_CORE

class MFBufferLocker
{
public:
	MFBufferLocker(IMFMediaBuffer* buffer)
		:buffer(buffer)
	{

	}

	~MFBufferLocker()
	{
		if (buffer)
			buffer->Unlock();
	}

	void Lock(_Outref_result_bytebuffer_to_(*maxLength, *currentLength) BYTE*& data,
		_Outptr_opt_ DWORD* maxLength, _Outptr_opt_ DWORD* currentLength)
	{
		ThrowIfFailed(buffer->Lock(&data, maxLength, currentLength));
	}
private:
	IMFMediaBuffer* buffer;
};

END_NS_CORE