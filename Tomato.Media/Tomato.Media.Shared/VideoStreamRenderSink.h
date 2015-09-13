//
// Tomato Media
// ��Ƶ����Ⱦ Sink
// 
// ���ߣ�SunnyCase 
// �������� 2015-08-07
#pragma once
#include "IVideoRender.h"
#include "StreamRenderSinkBase.h"
#include "../../include/MFWorkerQueueProvider.h"
#include <atomic>
#include <chrono>
#include <queue>

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
		// ׼����ϣ�������ϣ�
		Ready,
		// ������
		Playing
	};

	struct FrameInfo : public Frame
	{
		MFTIME SampleTime;
		MFTIME Duration;

		FrameInfo() : SampleTime(0), Duration(0) {}

		FrameInfo(Frame frame, MFTIME sampleTime, MFTIME duration)
			:Frame(std::move(frame)), SampleTime(sampleTime), Duration(duration)
		{

		}
	};

	const MFTIME FrameCacheDuration = MFCLOCK_FREQUENCY_HNS * 3;
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

#if (WINVER >= _WIN32_WINNT_WIN8)
	STDMETHODIMP RegisterThreadsEx(DWORD * pdwTaskIndex, LPCWSTR wszClassName, LONG lBasePriority) override;
	STDMETHODIMP SetWorkQueueEx(DWORD dwMultithreadedWorkQueueId, LONG lWorkItemBasePriority) override;
#elif (WINVER >= _WIN32_WINNT_VISTA) && WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
	STDMETHODIMP RegisterThreads(DWORD dwTaskIndex, LPCWSTR wszClass) override;
	STDMETHODIMP SetWorkQueue(DWORD dwWorkQueueId) override;
#endif
	STDMETHODIMP UnregisterThreads(void) override;

	virtual void SetPresentationClock(IMFPresentationClock* presentationClock) override;
	virtual void NotifyPreroll(MFTIME hnsUpcomingStartTime) override;
	virtual void Play(MFTIME startTime) override;
private:
	void OnSetMediaType();
	///<param name="setInited">�Ƿ�����״̬Ϊ Initialized��</param>
	///<remarks>����ǰ���״̬����</remarks>
	void FlushCore(bool setInited = false);

	///<remarks>����ǰ���״̬����</remarks>
	void PostSampleRequest();

	///<remarks>����ǰ���״̬����</remarks>
	void PostSampleRequestIfNeeded();

	///<remarks>����ǰ�����״̬����</remarks>
	void OnProcessIncomingSamples(IMFSample* sample);

	///<remarks>����ǰ���״̬����</remarks>
	void RegisterWorkThreadIfNeeded();

	///<remarks>����ǰ�����״̬����</remarks>
	void RequestDecodeFrame();

	///<remarks>����ǰ�����״̬����</remarks>
	void RequestRenderFrame();

	///<summary>������Ĳ�������Ϊ֡</summary>
	///<remarks>
	/// ����ǰ���ܶ�״̬��������֤ͬʱֻ��һ���̵߳��á�
	/// �������쳣����֤ cachedFrameDuration ��Ч���޷�����Ĳ�������������
	///</remarks>
	void OnDecodeFrame();

	///<summary>��֡��Ⱦ����</summary>
	///<remarks>����ǰ���ܶ�״̬��������֤ͬʱֻ��һ���̵߳���</remarks>
	void OnRenderFrame();

	WRL::ComPtr<IMFSample> TryPopSample();
private:
	UINT32 frameWidth, frameHeight;
	WRL::ComPtr<IVideoRender> videoRender;
	WRL::ComPtr<IMFMediaType> mediaType;
	std::mutex stateMutex;
	VideoStreamRenderSinkState sinkState = NotInitialized;
	std::queue<WRL::ComPtr<IMFSample>> sampleCache;
	std::queue<FrameInfo> frameCache;
	std::mutex sampleCacheMutex;
	std::mutex frameCacheMutex;
	Core::MFWorkerQueueProviderRef workerQueue;
	bool workThreadRegistered = false;

	std::shared_ptr<Core::WorkerThread> decodeFrameWorker;
	std::atomic<bool> decodeFrameWorkerActived = false;
	std::atomic<MFTIME> cachedFrameDuration = 0;
	std::atomic<bool> streamEnded = false;

	std::shared_ptr<Core::WorkerThread> renderFrameWorker;
	std::atomic<bool> renderFrameWorkerActived = false;

	WRL::ComPtr<IMFPresentationClock> presentationClock;
};

END_NS_MEDIA