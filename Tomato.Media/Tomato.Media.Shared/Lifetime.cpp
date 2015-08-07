//
// Tomato Media
// ��������
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-08-04
//
#include "pch.h"
#include "common.h"

namespace
{
	struct LifeTime
	{
		LifeTime()
		{
			auto hr = MFStartup(MF_SDK_VERSION);
			if (FAILED(hr))
				_com_issue_error(hr);
		}

		~LifeTime()
		{
			MFShutdown();
		}
	} lifeTime;
}