//
// Tomato Media
// ý����Ⱦ Sink
// 
// ���ߣ�SunnyCase 
// �������� 2015-08-07
#pragma once
#include "common.h"
#include "IVideoRender.h"
#include <mfidl.h>
#include <mutex>

DEFINE_NS_MEDIA

///<summary>ý����Ⱦ Sink</summary>
///<remarks>����һ����Ƶ��һ����Ƶ�� Sink</remarks>
class MediaRenderSink : public WRL::RuntimeClass<WRL::RuntimeClassFlags<WRL::ClassicCom>, IMFMediaSink, IMFGetService, IMFClockStateSink>
{
public:
	MediaRenderSink();

	// ͨ�� RuntimeClass �̳�
	STDMETHODIMP GetCharacteristics(DWORD * pdwCharacteristics) override;
	STDMETHODIMP AddStreamSink(DWORD dwStreamSinkIdentifier, IMFMediaType * pMediaType, IMFStreamSink ** ppStreamSink) override;
	STDMETHODIMP RemoveStreamSink(DWORD dwStreamSinkIdentifier) override;
	STDMETHODIMP GetStreamSinkCount(DWORD * pcStreamSinkCount) override;
	STDMETHODIMP GetStreamSinkByIndex(DWORD dwIndex, IMFStreamSink ** ppStreamSink) override;
	STDMETHODIMP GetStreamSinkById(DWORD dwStreamSinkIdentifier, IMFStreamSink ** ppStreamSink) override;
	STDMETHODIMP SetPresentationClock(IMFPresentationClock * pPresentationClock) override;
	STDMETHODIMP GetPresentationClock(IMFPresentationClock ** ppPresentationClock) override;
	STDMETHODIMP Shutdown(void) override;

	STDMETHODIMP OnClockStart(MFTIME hnsSystemTime, LONGLONG llClockStartOffset) override;
	STDMETHODIMP OnClockStop(MFTIME hnsSystemTime) override;
	STDMETHODIMP OnClockPause(MFTIME hnsSystemTime) override;
	STDMETHODIMP OnClockRestart(MFTIME hnsSystemTime) override;
	STDMETHODIMP OnClockSetRate(MFTIME hnsSystemTime, float flRate) override;

	STDMETHODIMP GetService(REFGUID guidService, REFIID riid, LPVOID * ppvObject) override;
private:
	///<remarks>����ǰ�����</remarks>
	WRL::ComPtr<IVideoRender>& GetVideoRender();
private:
	std::array<WRL::ComPtr<IMFStreamSink>, 2> streamSinks;
	WRL::ComPtr<IMFStreamSink> &audioSink, &videoSink;
	WRL::ComPtr<IVideoRender> videoRender;
	WRL::ComPtr<IMFPresentationClock> presentationClock;
	std::mutex stateMutex;
};

END_NS_MEDIA