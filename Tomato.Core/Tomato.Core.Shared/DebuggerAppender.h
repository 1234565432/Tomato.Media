//
// Tomato Media Core
// ��������־��¼׷�����ӿ�
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-09-05
//
#pragma once
#include "IAppender.h"

DEFINE_NS_CORE_INTERN

// ��������־��¼׷�����ӿ�
class DebuggerAppender : public IAppender
{
	virtual void Information(const std::wstring& message) override;
};

END_NS_CORE_INTERN