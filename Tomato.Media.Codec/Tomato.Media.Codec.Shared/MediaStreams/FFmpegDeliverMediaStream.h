//
// Tomato Media Codec
// ���������ݵ� FFmpeg Media Stream
// 
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-12-30
#pragma once
#include "DeliverMediaStreamBase.h"
#ifdef __cplusplus
extern "C" {
#endif
#include <libavformat/avformat.h>
#ifdef __cplusplus
}
#endif
#include <mutex>

DEFINE_NS_MEDIA_CODEC

class FFmpegDeliverMediaStream : public DeliverMediaStreamBase
{
public:
	FFmpegDeliverMediaStream(AVStream* stream, Core::WeakRef<MediaSourceBase> mediaSource, IMFStreamDescriptor* streamDescriptor);

	void DeliverPacket(AVPacket& packet);
	int GetIndex() const noexcept { return _stream->index; }
	int GetId() const noexcept { return _stream->id; }
private:
	void QueuePacket(AVPacket& packet);
	virtual void OnResetStream() override;
private:
	AVStream* _stream;
	std::mutex streamStateMutex;
};

END_NS_MEDIA_CODEC