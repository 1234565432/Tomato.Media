//
// Tomato Media Codec
// ���������ݵ� Media Stream ����
// 
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-09-09
#pragma once
#include "common.h"
#include "../../include/WeakReferenceBase.h"
#include <mfidl.h>
#include <queue>
#include <atomic>

DEFINE_NS_MEDIA_CODEC

class MediaSourceBase;

// ���������ݵ� Media Stream ����
class DeliverMediaStreamBase : public WRL::RuntimeClass<WRL::RuntimeClassFlags<WRL::ClassicCom>,
	IMFMediaEventGenerator,
	IMFMediaStream>
{
	enum : MFTIME
	{
		DesiredCacheDuration = 3 * size_t(1e7),
		DesiredCacheSamples = 3 * 24
	};

	enum StreamState
	{
		Stopped,
		Started,
		Paused,
		EndOfStream
	};
public:
	DeliverMediaStreamBase(Core::WeakRef<MediaSourceBase> mediaSource, IMFStreamDescriptor* streamDescriptor);
	virtual ~DeliverMediaStreamBase();

	// ͨ�� RuntimeClass �̳�
	STDMETHODIMP GetEvent(DWORD dwFlags, IMFMediaEvent ** ppEvent) override;
	STDMETHODIMP BeginGetEvent(IMFAsyncCallback * pCallback, IUnknown * punkState) override;
	STDMETHODIMP EndGetEvent(IMFAsyncResult * pResult, IMFMediaEvent ** ppEvent) override;
	STDMETHODIMP QueueEvent(MediaEventType met, REFGUID guidExtendedType, HRESULT hrStatus, const PROPVARIANT * pvValue) override;
	STDMETHODIMP GetMediaSource(IMFMediaSource ** ppMediaSource) override;
	STDMETHODIMP GetStreamDescriptor(IMFStreamDescriptor ** ppStreamDescriptor) override;
	STDMETHODIMP RequestSample(IUnknown * pToken) override;

	bool DoesNeedMoreData();
	bool IsActive() const noexcept { return isActive.load(std::memory_order_acquire); }
	void Start(const PROPVARIANT& position);
	void Pause();
	void Stop();
protected:
	void EnqueueSample(IMFSample* sample);
private:
	void DispatchSampleRequests();
	void OnEndOfStream();
	void RequestDataIfNeeded();
private:
	Core::WeakRef<MediaSourceBase> mediaSource;
	WRL::ComPtr<IMFStreamDescriptor> streamDescriptor;
	WRL::ComPtr<IMFMediaEventQueue> eventQueue;					// �¼�����

	std::queue<WRL::ComPtr<IMFSample>> samplesCache;		// ��������
	std::queue<WRL::ComPtr<IUnknown>> sampleRequests;		// ��������
	std::mutex sampleRequestsMutex, samplesCacheMutex;
	std::atomic<bool> endOfDeliver = false;
	std::atomic<MFTIME> cachedDuration = 0;
	std::atomic<bool> isActive = false;
	StreamState streamState = Stopped;
	std::mutex stateMutex;
};

END_NS_MEDIA_CODEC