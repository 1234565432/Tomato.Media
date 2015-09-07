//
// Tomato Media Codec
// Media Foundation Ogg MediaSource
// 
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-09-06
#pragma once
#include "MediaSourceBase.h"
#include "libogg/ogg.h"
#include "../../include/MFWorkerQueueProvider.h"
#include "../../include/MFAsyncCallback.h"
#include <map>

DEFINE_NS_MEDIA_CODEC

// Media Foundation Ogg MediaSource
class OggMediaSource : public MediaSourceBase
{
public:
	OggMediaSource();
	virtual ~OggMediaSource();

	// ͨ�� MediaSourceBase �̳�
	virtual DWORD OnGetCharacteristics() override;
	virtual void OnValidatePresentationDescriptor(IMFPresentationDescriptor * pPD) override;
	virtual concurrency::task<WRL::ComPtr<IMFPresentationDescriptor>> OnCreatePresentationDescriptor(IMFByteStream * stream) override;
	virtual concurrency::task<void> OnStreamsRequestData(TOperation & op) override;
	virtual void OnStartStream(DWORD streamId, bool selected, MFTIME position) override;
	virtual void OnPauseStream(DWORD streamId) override;
	virtual void OnStopStream(DWORD streamId) override;
private:
	void OnByteStreamReadCompleted(IMFAsyncResult* asyncResult);
	void OnByteStreamReadCompletedForBOS(IMFAsyncResult* asyncResult);
	concurrency::task<void> ReadAllBOSPackets();
	// �� ByteStream ��ȡһ���ڴ浽 SyncLayer
	void SyncBufferFromByteStream(IMFAsyncCallback* asyncCallback, IUnknown* state = nullptr);
	WRL::ComPtr<IMFPresentationDescriptor> BuildPresentationDescriptor();

	///<remarks>����ǰ���״̬����</remarks>
	void RegisterWorkThreadIfNeeded();

	void EndOfSource();
private:
	ogg_sync_state syncState;
	Core::MFWorkerQueueProviderRef workerQueue;
	bool workThreadRegistered = false;
	WRL::ComPtr<IMFAsyncCallback> byteStreamReadCompletedCallback;
	WRL::ComPtr<IMFByteStream> byteStream;
	std::map<int, ogg_stream_state> streamStates;
};

END_NS_MEDIA_CODEC