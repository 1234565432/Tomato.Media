//
// Tomato Media Core
// ��־��¼��
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-09-05
//
#pragma once
#include "common.h"
#include <string>

DEFINE_NS_CORE_INTERN

// ��־��¼��ʵ��
class Logger
{
public:
	Logger(std::wstring typeName);

	void Information(const std::wstring& message);
private:
	const std::wstring typeName;
};

END_NS_CORE_INTERN