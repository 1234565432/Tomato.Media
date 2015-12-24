//
// Tomato Media
// Ӧ�ó������ݸ���
// 
// ���ߣ�SunnyCase 
// �������� 2015-08-04
#pragma once
#include "common.h"

DEFINE_NS_MEDIA

namespace details
{
	Windows::Storage::ApplicationDataContainer^ GetSettingContainer();

	template<typename TSetting>
	// ��������
	void SetSetting(typename TSetting::TValue value)
	{
		GetSettingContainer()->Values->Insert(TSetting::Key, value);
	}

	template<typename TSetting>
	// ��ȡ���������
	typename TSetting::TValue GetResetSetting()
	{
		auto values = GetSettingContainer()->Values;
		auto value = static_cast<TSetting::TValue>(values->Lookup(TSetting::Key));
		values->Remove(TSetting::Key);
		return value;
	}

	namespace settings
	{
		struct BackgroundMediaPlayerHandlerFullNameSetting
		{
			static Platform::String^ Key;
			using TValue = Platform::String^;
		};
	}
}

END_NS_MEDIA