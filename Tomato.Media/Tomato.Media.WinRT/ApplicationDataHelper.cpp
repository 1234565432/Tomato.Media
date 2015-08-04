//
// Tomato Media
// Ӧ�ó������ݸ���
// 
// ���ߣ�SunnyCase 
// �������� 2015-08-04
#include "pch.h"
#include "ApplicationDataHelper.h"

using namespace Platform;
using namespace Windows::Storage;
using namespace Tomato::Media;

String^ details::settings::BackgroundMediaPlayerHandlerFullNameSetting::Key = L"BackgroundMediaPlayerHandlerFullName";

ApplicationDataContainer ^ details::GetSettingContainer()
{
	static auto container = ApplicationData::Current->LocalSettings->CreateContainer(
		L"_TomatoMediaSetting", ApplicationDataCreateDisposition::Always);
	return container;
}
