//
// Tomato Media Core
// ��������־��¼׷�����ӿ�
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-09-05
//
#include "pch.h"
#include "DebuggerAppender.h"

using namespace NS_CORE_INTERN;

void DebuggerAppender::Information(const std::wstring & message)
{
	OutputDebugString(message.c_str());
}
