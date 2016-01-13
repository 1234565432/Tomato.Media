//
// Tomato Media
// ֧�� Effect �� MediaStreamSource
// ���ߣ�SunnyCase
// ����ʱ�䣺2016-01-13
//
#pragma once
#include "common.h"
#include "MediaSource.h"

DEFINE_NS_MEDIA

class EffectMediaStreamSource : public WRL::RuntimeClass<WRL::RuntimeClassFlags<WRL::ClassicCom>, IMFSourceReaderCallback>
{
public:
	EffectMediaStreamSource(MediaSource^ mediaSource);

	// ͨ�� RuntimeClass �̳�
	STDMETHODIMP OnReadSample(HRESULT hrStatus, DWORD dwStreamIndex, DWORD dwStreamFlags, LONGLONG llTimestamp, IMFSample * pSample) override;
	STDMETHODIMP OnFlush(DWORD dwStreamIndex) override;
	STDMETHODIMP OnEvent(DWORD dwStreamIndex, IMFMediaEvent * pEvent) override;
private:
	void ConfigureSourceReader(IMFMediaSource* mediaSource);
	void InstallEffects();
	void ConfigureMSS();
private:
	Windows::Media::Core::MediaStreamSource^ _mss;
	WRL::ComPtr<IMFSourceReaderEx> _sourceReader;
	WRL::ComPtr<IMFMediaType> _outputMT;
};

END_NS_MEDIA