//
// Tomato Media Core
// ��־��¼׷�����ӿ�
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-09-05
//
#pragma once
#include "common.h"

DEFINE_NS_CORE_INTERN

// ��־��¼׷�����ӿ�
struct IAppender
{
	virtual void Information(const std::wstring& message) = 0;
};

END_NS_CORE_INTERN