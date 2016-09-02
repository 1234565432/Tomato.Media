//
// Tomato Media Codec
// Media Foundation ���� Transform ����
// 
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-09-08
#pragma once
#include <Tomato.Media/Tomato.Media.h>
#include <mutex>
#include <windows.media.h>
#include <mfidl.h>

DEFINE_NS_MEDIA_CODEC

struct DecoderTransformRegisterInfo
{
	const GUID InputSubType;
	const GUID OutputSubType;
};

// Media Foundation ���� Transform ����
class __declspec(novtable) DecoderTransformBase : public WRL::RuntimeClass<WRL::RuntimeClassFlags<
#if (NTDDI_VERSION >= NTDDI_WIN8)
	WRL::WinRtClassicComMix>,
	ABI::Windows::Media::IMediaExtension,
#else
	WRL::ClassicCom>,
#endif
	IMFTransform>
{
public:
	enum TransformState
	{
		Initializing,
		Ready,
		WaitingInput,
		PendingOutput
	};

	DecoderTransformBase();
	virtual ~DecoderTransformBase();

#if (NTDDI_VERSION >= NTDDI_WIN8)
	// IMediaExtension
	IFACEMETHOD(SetProperties) (ABI::Windows::Foundation::Collections::IPropertySet *pConfiguration) override;
#endif
	// IMFTransform methods
	STDMETHODIMP GetStreamLimits(
		DWORD   *pdwInputMinimum,
		DWORD   *pdwInputMaximum,
		DWORD   *pdwOutputMinimum,
		DWORD   *pdwOutputMaximum
		);

	STDMETHODIMP GetStreamCount(
		DWORD   *pcInputStreams,
		DWORD   *pcOutputStreams
		);

	STDMETHODIMP GetStreamIDs(
		DWORD   dwInputIDArraySize,
		DWORD   *pdwInputIDs,
		DWORD   dwOutputIDArraySize,
		DWORD   *pdwOutputIDs
		);

	STDMETHODIMP GetInputStreamInfo(
		DWORD                     dwInputStreamID,
		MFT_INPUT_STREAM_INFO *   pStreamInfo
		);

	STDMETHODIMP GetOutputStreamInfo(
		DWORD                     dwOutputStreamID,
		MFT_OUTPUT_STREAM_INFO *  pStreamInfo
		);

	STDMETHODIMP GetAttributes(IMFAttributes** pAttributes);

	STDMETHODIMP GetInputStreamAttributes(
		DWORD           dwInputStreamID,
		IMFAttributes   **ppAttributes
		);

	STDMETHODIMP GetOutputStreamAttributes(
		DWORD           dwOutputStreamID,
		IMFAttributes   **ppAttributes
		);

	STDMETHODIMP DeleteInputStream(DWORD dwStreamID);

	STDMETHODIMP AddInputStreams(
		DWORD   cStreams,
		DWORD   *adwStreamIDs
		);

	STDMETHODIMP GetInputAvailableType(
		DWORD           dwInputStreamID,
		DWORD           dwTypeIndex, // 0-based
		IMFMediaType    **ppType
		);

	STDMETHODIMP GetOutputAvailableType(
		DWORD           dwOutputStreamID,
		DWORD           dwTypeIndex, // 0-based
		IMFMediaType    **ppType
		);

	STDMETHODIMP SetInputType(
		DWORD           dwInputStreamID,
		IMFMediaType    *pType,
		DWORD           dwFlags
		);

	STDMETHODIMP SetOutputType(
		DWORD           dwOutputStreamID,
		IMFMediaType    *pType,
		DWORD           dwFlags
		);

	STDMETHODIMP GetInputCurrentType(
		DWORD           dwInputStreamID,
		IMFMediaType    **ppType
		);

	STDMETHODIMP GetOutputCurrentType(
		DWORD           dwOutputStreamID,
		IMFMediaType    **ppType
		);

	STDMETHODIMP GetInputStatus(
		DWORD           dwInputStreamID,
		DWORD           *pdwFlags
		);

	STDMETHODIMP GetOutputStatus(DWORD *pdwFlags);

	STDMETHODIMP SetOutputBounds(
		LONGLONG        hnsLowerBound,
		LONGLONG        hnsUpperBound
		);

	STDMETHODIMP ProcessEvent(
		DWORD              dwInputStreamID,
		IMFMediaEvent      *pEvent
		);

	STDMETHODIMP ProcessMessage(
		MFT_MESSAGE_TYPE    eMessage,
		ULONG_PTR           ulParam
		);

	STDMETHODIMP ProcessInput(
		DWORD               dwInputStreamID,
		IMFSample           *pSample,
		DWORD               dwFlags
		);

	STDMETHODIMP ProcessOutput(
		DWORD                   dwFlags,
		DWORD                   cOutputBufferCount,
		MFT_OUTPUT_DATA_BUFFER  *pOutputSamples, // one per stream
		DWORD                   *pdwStatus
		);
protected:
	// ���δ�ر���ִ�в���
	//HRESULT IfNotShutdown(std::function<HRESULT(MFTState)> aliveHandler) noexcept;

	// ��֤��������
	virtual void OnValidateInputType(IMFMediaType* type) = 0;
	// ��֤�������
	virtual void OnValidateOutputType(IMFMediaType* type) = 0;
	virtual DWORD OnGetOutputStreamFlags() const noexcept;
	// ��ȡ���֡��С
	virtual DWORD OnGetOutputFrameSize() const noexcept = 0;
	// ������������
	virtual WRL::ComPtr<IMFMediaType> OnSetInputType(IMFMediaType* type) = 0;
	// �����������
	virtual WRL::ComPtr<IMFMediaType> OnSetOutputType(IMFMediaType* type) = 0;
	// ��������
	// ����ֵ���Ƿ�����������
	virtual bool OnReceiveInput(IMFSample* sample) = 0;
	virtual void OnProduceOutput(MFT_OUTPUT_DATA_BUFFER& output) = 0;
	virtual WRL::ComPtr<IMFMediaType> OnGetOutputAvailableType(DWORD index) noexcept = 0;
	// ��ʼ��ˮ
	virtual void BeginStreaming();
	// ֹͣ��ˮ
	virtual void EndStreaming();
private:
	// ��֤�Ƿ���Ч�������� Id
	bool IsValidInputStream(DWORD inputStreamId) const noexcept;
	// ��֤�Ƿ���Ч������� Id
	bool IsValidOutputStream(DWORD outputStreamId) const noexcept;
	// ��֤�������
	void ValidateOutputType(IMFMediaType* type);
	// ��֤��������
	void ValidateInputType(IMFMediaType* type);
protected:
	TransformState state = Ready;						// ״̬
	std::mutex stateMutex;
	WRL::ComPtr<IMFMediaType> inputMediaType;	// ����ý������
	WRL::ComPtr<IMFMediaType> outputMediaType;	// ���ý������
private:
};

END_NS_MEDIA_CODEC