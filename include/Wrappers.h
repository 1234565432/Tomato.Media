//
// Tomato Media Core
// Wrappers
// ���ߣ�SunnyCase
// ����ʱ�䣺2016-01-15
//
#pragma once
#include "common.h"
#include <windows.storage.streams.h>
#include <mfidl.h>

DEFINE_NS_CORE

void TOMATO_CORE_API CreateBufferOnMFMediaBuffer(IMFMediaBuffer* sourceBuffer, ABI::Windows::Storage::Streams::IBuffer** wrappedBuffer);

END_NS_CORE