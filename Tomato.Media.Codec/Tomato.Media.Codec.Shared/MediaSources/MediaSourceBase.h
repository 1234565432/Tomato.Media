//
// Tomato Media Codec
// Media Foundation MediaSource ����
// 
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-03-17
#pragma once
#include "common.h"
#include "../../include/MFOperationQueue.h"
#include "MediaSourceOperation.h"
#include "../../include/WeakReferenceBase.h"
#include <mfidl.h>
#include <ppltasks.h>
#include <atomic>

DEFINE_NS_MEDIA_CODEC

enum class MFMediaSourceState
{
	NotInitialized,
	Initializing,
	Starting,
	Started,
	Paused,
	Stopping,
	Stopped
};

class MediaSourceBase : public Core::WeakReferenceBase<MediaSourceBase,
	WRL::RuntimeClassFlags<WRL::ClassicCom>,
	IMFMediaEventGenerator,
	IMFMediaSource,
	IMFGetService>
{
public:
	using TOperation = std::shared_ptr<MediaSourceOperation>;

	virtual ~MediaSourceBase();

	// IMFMediaEventGenerator
	STDMETHODIMP BeginGetEvent(IMFAsyncCallback *pCallback, IUnknown *punkState) final;
	STDMETHODIMP EndGetEvent(IMFAsyncResult *pResult, IMFMediaEvent **ppEvent);
	STDMETHODIMP GetEvent(DWORD dwFlags, IMFMediaEvent **ppEvent);
	STDMETHODIMP QueueEvent(MediaEventType met, REFGUID guidExtendedType, HRESULT hrStatus, const PROPVARIANT *pvValue);

	// IMFMediaSource
	STDMETHODIMP CreatePresentationDescriptor(IMFPresentationDescriptor **ppPresentationDescriptor);
	STDMETHODIMP GetCharacteristics(DWORD *pdwCharacteristics);
	STDMETHODIMP Pause();
	STDMETHODIMP Shutdown();
	STDMETHODIMP Start(
		IMFPresentationDescriptor *pPresentationDescriptor,
		const GUID *pguidTimeFormat,
		const PROPVARIANT *pvarStartPosition
		);
	STDMETHODIMP Stop();

	// IMFGetService
	IFACEMETHOD(GetService) (_In_ REFGUID guidService, _In_ REFIID riid, _Out_opt_ LPVOID *ppvObject);

	// ���ֽ���
	concurrency::task<void> OpenAsync(IMFByteStream* byteStream);
	// ���������
	void QueueAsyncOperation(TOperation&& operation);
	void QueueAsyncOperation(MediaSourceOperationKind operation);
protected:
	MediaSourceBase();

	HRESULT QueueEventUnk(MediaEventType met, REFGUID guidExtendedType,
		HRESULT hrStatus, IUnknown *unk);

	// ��ȡ��Դ����
	virtual DWORD OnGetCharacteristics() = 0;
	// �ر�
	virtual void OnShutdown();
	// ��֤ Presentation Descriptor ��Ч
	virtual void OnValidatePresentationDescriptor(IMFPresentationDescriptor *pPD) = 0;
	// ��֤��ʼ����
	virtual void ValidateStartOperation(MFMediaSourceState state, MFTIME position);
	// ���� Presentation Descriptor
	virtual concurrency::task<WRL::ComPtr<IMFPresentationDescriptor>>
		OnCreatePresentationDescriptor(IMFByteStream* stream) = 0;
	// ����������
	virtual concurrency::task<void> OnStreamsRequestData(IMFMediaStream* mediaStream) = 0;
	virtual void OnSeekSource(MFTIME position) = 0;
	// ��ʼ��
	virtual void OnStartStream(DWORD streamId, bool selected, const PROPVARIANT& position) = 0;
	virtual void OnPauseStream(DWORD streamId) = 0;
	virtual void OnStopStream(DWORD streamId) = 0;
private:
	bool HasShutdown() const;
	// ��֤ Presentation Descriptor ��Ч
	void ValidatePresentationDescriptor(IMFPresentationDescriptor *pPD);
	// ���� Presentation Descriptor
	concurrency::task<void> CreatePresentationDescriptor(IMFByteStream* stream);
	void OnDispatchOperation(TOperation& op);
	// ������Դ
	concurrency::task<void> InitializeAudioSource(IMFByteStream* stream);

	// ��ʼ
	void DoStart(MediaSourceStartOperation* operation);
	void StartStreams(IMFPresentationDescriptor* pd, const PROPVARIANT& position);

	void DoPause();
	void PauseStreams();

	void DoStop();
	void StopStreams();

	// ��ֹͣ
	void OnEndOfStream();
protected:
	MFMediaSourceState state = MFMediaSourceState::NotInitialized;	// ״̬
	WRL::ComPtr<IMFMediaEventQueue> eventQueue;					// �¼�����
	std::mutex stateMutex;
private:
	std::shared_ptr<Core::MFOperationQueue<TOperation>> operationQueue;
	WRL::ComPtr<IMFPresentationDescriptor> presentDescriptor;	// PresentationDescriptor
	std::atomic<uint32_t> pendingEOSCount = 0;					// ��Ҫ������������
};

END_NS_MEDIA_CODEC