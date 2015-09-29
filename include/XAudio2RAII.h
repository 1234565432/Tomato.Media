//
// Tomato Music
// XAudio2 RAII ����
// 
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-09-16
#pragma once
#include "common.h"
#include <xaudio2.h>

DEFINE_NS_CORE

struct xaudio2_voice_deleter
{
	void operator()(IXAudio2Voice* voice) const noexcept
	{
		if (voice)
			voice->DestroyVoice();
	}
};

END_NS_CORE