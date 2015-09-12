//
// Tomato Media Codec
// Media Foundation Ogg MediaSource
// 
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-09-06
#pragma once
#include "MediaSourceBase.h"
#include "MediaStreams/OggDeliverMediaStream.h"
#include "libogg/ogg.h"
#include "../../include/MFWorkerQueueProvider.h"
#include "../../include/MFAsyncCallback.h"
#include <map>
#include <condition_variable>

DEFINE_NS_MEDIA_CODEC

// Media Foundation Ogg MediaSource
class OggMediaSource : public MediaSourceBase
{
public:
	OggMediaSource();
	virtual ~OggMediaSource();

	// IMFGetService
	IFACEMETHOD(GetService) (_In_ REFGUID guidService, _In_ REFIID riid, _Out_opt_ LPVOID *ppvObject);

	// ͨ�� MediaSourceBase �̳�
	virtual DWORD OnGetCharacteristics() override;
	virtual void OnValidatePresentationDescriptor(IMFPresentationDescriptor * pPD) override;
	virtual concurrency::task<WRL::ComPtr<IMFPresentationDescriptor>> OnCreatePresentationDescriptor(IMFByteStream * stream) override;
	virtual concurrency::task<void> OnStreamsRequestData(IMFMediaStream* mediaStream) override;
	virtual void OnSeekSource(MFTIME position) override;
	virtual void OnStartStream(DWORD streamId, bool selected, const PROPVARIANT& position) override;
	virtual void OnPauseStream(DWORD streamId) override;
	virtual void OnStopStream(DWORD streamId) override;
private:
	// ��֤ͬʱֻ��һ���̵߳���
	void OnByteStreamReadCompleted(IMFAsyncResult* asyncResult);
	// ��֤ͬʱֻ��һ���̵߳���
	void OnByteStreamReadCompletedForBOS(IMFAsyncResult* asyncResult);
	// �� ByteStream ��ȡһ���ڴ浽 SyncLayer
	void SyncBufferFromByteStream(IMFAsyncCallback* asyncCallback, IUnknown* state = nullptr);
	concurrency::task<WRL::ComPtr<IMFPresentationDescriptor>> BuildPresentationDescriptor();

	///<remarks>����ǰ���״̬����</remarks>
	void RegisterWorkThreadIfNeeded();

	void EndOfSource();
	void AddStream(ogg_stream_state&& streamState, IMFStreamDescriptor* streamDescriptor);
private:
	ogg_sync_state syncState;
	Core::MFWorkerQueueProviderRef workerQueue;
	bool workThreadRegistered = false;
	WRL::ComPtr<IMFByteStream> byteStream;
	std::map<int, WRL::ComPtr<OggDeliverMediaStream>> mediaStreams;
};

END_NS_MEDIA_CODEC