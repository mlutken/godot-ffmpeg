#ifndef VIDEO_STREAM_PLAYBACK_FFMPEG_H
#define VIDEO_STREAM_PLAYBACK_FFMPEG_H

#include "core/io/resource_loader.h"
#include "scene/resources/video_stream.h"

class WebMFrame;
class WebMDemuxer;
class VPXDecoder;
class OpusVorbisDecoder;

class VideoStreamPlaybackFFMpeg : public VideoStreamPlayback {
	GDCLASS(VideoStreamPlaybackFFMpeg, VideoStreamPlayback);

	String file_name;
	int audio_track = 0;

	WebMDemuxer *webm = nullptr;
	VPXDecoder *video = nullptr;
	OpusVorbisDecoder *audio = nullptr;

	WebMFrame **video_frames = nullptr, *audio_frame = nullptr;
	int video_frames_pos = 0, video_frames_capacity = 0;

	int num_decoded_samples = 0, samples_offset = -1;
	AudioMixCallback mix_callback = nullptr;
	void *mix_udata = nullptr;

	bool playing = false, paused = false;
	double delay_compensation = 0.0;
	double time = 0.0, video_frame_delay = 0.0, video_pos = 0.0;

	Vector<uint8_t> frame_data;
	Ref<ImageTexture> texture;

	float *pcm = nullptr;

public:
	VideoStreamPlaybackFFMpeg();
	~VideoStreamPlaybackFFMpeg();

	bool open_file(const String &p_file);

	virtual void stop() override;
	virtual void play() override;

	virtual bool is_playing() const override;

	virtual void set_paused(bool p_paused) override;
	virtual bool is_paused() const override;

	virtual void set_loop(bool p_enable) override;
	virtual bool has_loop() const override;

	virtual float get_length() const override;

	virtual float get_playback_position() const override;
	virtual void seek(float p_time) override;

	virtual void set_audio_track(int p_idx) override;

	virtual Ref<Texture2D> get_texture() const override;
	virtual void update(float p_delta) override;

	virtual void set_mix_callback(AudioMixCallback p_callback, void *p_userdata) override;
	virtual int get_channels() const override;
	virtual int get_mix_rate() const override;

private:
	inline bool has_enough_video_frames() const;
	bool should_process(WebMFrame &video_frame);

	void delete_pointers();
};


#endif // VIDEO_STREAM_PLAYBACK_FFMPEG_H
