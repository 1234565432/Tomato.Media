//
// Tomato Media Toolkit
// Media Environment
// 
// ���ߣ�SunnyCase
// ����ʱ�䣺2016-09-02
#include "pch.h"
#include "MediaEnvironment.h"

using namespace NS_MEDIA_TOOLKIT;
using namespace NS_MEDIA_CODEC;

MediaEnvironment::MediaEnvironment()
{

}

void MediaEnvironment::RegisterDefaultCodecs()
{
	_codecManager.RegisterDefaultCodecs();
}
