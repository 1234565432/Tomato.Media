//
// Tomato Media
// Media Engine Notify ʵ��
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-08-06
//
#pragma once
#include "common.h"
#include <Mfmediaengine.h>

DEFINE_NS_MEDIA

#if (WINVER >= _WIN32_WINNT_WIN8)

class MediaEngineNotify : public WRL::RuntimeClass<WRL::RuntimeClassFlags<WRL::RuntimeClassType::ClassicCom>, IMFMediaEngineNotify>
{
public:
	MediaEngineNotify(std::function<void(DWORD)>&& eventCallback);

	// ͨ�� RuntimeClass �̳�
	STDMETHODIMP EventNotify(DWORD event, DWORD_PTR param1, DWORD param2) override;
private:
	std::function<void(DWORD)> eventCallback;
};

#endif

END_NS_MEDIA