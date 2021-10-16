#ifndef VIDEO_STREAM_FFMPEG_H
#define VIDEO_STREAM_FFMPEG_H

#include "core/io/resource_loader.h"
#include "scene/resources/video_stream.h"

class WebMFrame;
class WebMDemuxer;
class VPXDecoder;
class OpusVorbisDecoder;


class VideoStreamFFMpeg : public VideoStream {
	GDCLASS(VideoStreamFFMpeg, VideoStream);

	String file;
	int audio_track = 0;

protected:
	static void _bind_methods();

public:
	VideoStreamFFMpeg();

	virtual Ref<VideoStreamPlayback> instance_playback() override;

	virtual void set_file(const String &p_file);
	String get_file();
	virtual void set_audio_track(int p_track) override;
};


#endif // VIDEO_STREAM_FFMPEG_H
