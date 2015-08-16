//
// Tomato Media
// ��Ƶ����Ⱦ Sink
// 
// ���ߣ�SunnyCase 
// �������� 2015-08-07
#pragma once
#include "IVideoRender.h"
#include "StreamRenderSinkBase.h"
#include <atomic>

DEFINE_NS_MEDIA

///<summary>��Ƶ�� Sink</summary>
class VideoStreamRenderSink : public StreamRenderSinkBase
{
	// Sink ״̬
	enum VideoStreamRenderSinkState
	{
		// δ���أ�δ����ý�����ͣ�
		NotInitialized,
		// �Ѽ��أ�������ý�����ͣ��� Flush ��
		Initialized,
		// ������
		Prerolling,
	};
public:
	VideoStreamRenderSink(DWORD identifier, MediaRenderSink* mediaSink, IVideoRender* videoRender);

	STDMETHODIMP GetMediaTypeHandler(IMFMediaTypeHandler ** ppHandler) override;
	STDMETHODIMP ProcessSample(IMFSample * pSample) override;
	STDMETHODIMP PlaceMarker(MFSTREAMSINK_MARKER_TYPE eMarkerType, const PROPVARIANT * pvarMarkerValue, const PROPVARIANT * pvarContextValue) override;
	STDMETHODIMP Flush(void) override;

	STDMETHODIMP IsMediaTypeSupported(IMFMediaType * pMediaType, IMFMediaType ** ppMediaType) override;
	STDMETHODIMP GetMediaTypeCount(DWORD * pdwTypeCount) override;
	STDMETHODIMP GetMediaTypeByIndex(DWORD dwIndex, IMFMediaType ** ppType) override;
	STDMETHODIMP SetCurrentMediaType(IMFMediaType * pMediaType) override;
	STDMETHODIMP GetCurrentMediaType(IMFMediaType ** ppMediaType) override;
	STDMETHODIMP GetMajorType(GUID * pguidMajorType) override;

	virtual void NotifyPreroll(MFTIME hnsUpcomingStartTime) override;
private:
	void OnSetMediaType();
	///<param name="setInited">�Ƿ�����״̬Ϊ Initialized��</param>
	///<remarks>����ǰ���״̬����</remarks>
	void FlushCore(bool setInited = false);
	void PostSampleRequest();
	void PostSampleRequestIfNeeded();
private:
	UINT32 frameWidth, frameHeight;
	WRL::ComPtr<IVideoRender> videoRender;
	WRL::ComPtr<IMFMediaType> mediaType;
	std::mutex stateMutex;
	VideoStreamRenderSinkState sinkState = NotInitialized;
};

END_NS_MEDIA