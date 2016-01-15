//
// Tomato Media
// IMFSourceReaderCallback ʵ��
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-08-07
//
#pragma once
#include "common.h"
#include <functional>
#include <mfreadwrite.h>

DEFINE_NS_MEDIA

///<summary>IMFSourceReaderCallback ʵ��</summary>
class MFSourceReaderCallback : public WRL::RuntimeClass<WRL::RuntimeClassFlags<WRL::ClassicCom>, IMFSourceReaderCallback>
{
public:
	MFSourceReaderCallback(std::function<void(HRESULT, DWORD, DWORD, LONGLONG, IMFSample*)>&& sampleCallback,
		std::function<void(DWORD)>&& flushCallback);

	// ͨ�� RuntimeClass �̳�
	STDMETHODIMP OnReadSample(HRESULT hrStatus, DWORD dwStreamIndex, DWORD dwStreamFlags, LONGLONG llTimestamp, IMFSample * pSample) override;
	STDMETHODIMP OnFlush(DWORD dwStreamIndex) override;
	STDMETHODIMP OnEvent(DWORD dwStreamIndex, IMFMediaEvent * pEvent) override;
private:
	std::function<void(HRESULT, DWORD, DWORD, LONGLONG, IMFSample*)> sampleCallback;
	std::function<void(DWORD)> flushCallback;
};

END_NS_MEDIA