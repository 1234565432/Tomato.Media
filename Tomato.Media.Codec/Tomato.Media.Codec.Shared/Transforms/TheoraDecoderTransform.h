//
// Tomato Media Codec
// Media Foundation Theora ���� Transform
// 
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-09-08
#pragma once
#include "DecoderTransformBase.h"
#if (NTDDI_VERSION >= NTDDI_WIN8)
#include "Tomato.Media.Codec_i.h"
#endif
#include "libtheora/theoradec.h"
#include "libtheora/theora_raii.h"

DEFINE_NS_MEDIA_CODEC

// Media Foundation Theora ���� Transform
class TheoraDecoderTransform : public DecoderTransformBase
{
	enum class TheoraState
	{
		Header,
		Body
	};
#if (NTDDI_VERSION >= NTDDI_WIN8)
	InspectableClass(RuntimeClass_Tomato_Media_Codec_TheoraDecoderTransform, BaseTrust)
#endif
public:
	static const DecoderTransformRegisterInfo RegisterInfos[1];

	TheoraDecoderTransform();

private:
	virtual void OnValidateInputType(IMFMediaType* type) override;
	virtual void OnValidateOutputType(IMFMediaType* type) override;
	// ��ȡ���֡��С
	virtual DWORD OnGetOutputFrameSize() const noexcept override;
	// ������������
	virtual WRL::ComPtr<IMFMediaType> OnSetInputType(IMFMediaType* type) override;
	// �����������
	virtual WRL::ComPtr<IMFMediaType> OnSetOutputType(IMFMediaType* type) override;
	// ��������
	virtual bool OnReceiveInput(IMFSample* sample) override;
	virtual void OnProduceOutput(MFT_OUTPUT_DATA_BUFFER& output) override;
	virtual WRL::ComPtr<IMFMediaType> OnGetOutputAvailableType(DWORD index) noexcept override;

	void InitializeAvailableOutputTypes(IMFMediaType* inputType);
	void InitializeDecoder();
	bool FeedBodyPacket(ogg_packet& packet);
	DWORD FillYV12Frame(IMFMediaBuffer* buffer, BYTE* data, DWORD maxLength);
private:
	std::vector<WRL::ComPtr<IMFMediaType>> availableOutputTypes;
	TheoraState theoraState = TheoraState::Header;

	th_info_raii theoraInfo;
	th_comment_raii theoraComment;
	std::unique_ptr<th_setup_info, th_setup_info_deleter> theoraSetup;
	std::unique_ptr<th_dec_ctx, th_dec_ctx_deleter> theoraContext;
	th_ycbcr_buffer decodedBuffer = { 0 };
	ogg_int64_t granpos = 0;
};

END_NS_MEDIA_CODEC