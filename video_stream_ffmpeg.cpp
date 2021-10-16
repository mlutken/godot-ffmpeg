#include "video_stream_ffmpeg.h"

#include "core/config/project_settings.h"
#include "core/io/file_access.h"
#include "core/os/os.h"
#include "servers/audio_server.h"

#include "thirdparty/misc/yuv2rgb.h"

// libsimplewebm
#include <OpusVorbisDecoder.hpp>
#include <VPXDecoder.hpp>

// libvpx
#include <vpx/vpx_image.h>

// libwebm
#include <mkvparser/mkvparser.h>

#include "video_stream_playback_ffmpeg.h"

VideoStreamFFMpeg::VideoStreamFFMpeg() {}

Ref<VideoStreamPlayback> VideoStreamFFMpeg::instance_playback() {
	Ref<VideoStreamPlaybackFFMpeg> pb = memnew(VideoStreamPlaybackFFMpeg);
	pb->set_audio_track(audio_track);
	if (pb->open_file(file)) {
		return pb;
	}
	return nullptr;
}

void VideoStreamFFMpeg::set_file(const String &p_file) {
	file = p_file;
}

String VideoStreamFFMpeg::get_file() {
	return file;
}

void VideoStreamFFMpeg::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_file", "file"), &VideoStreamFFMpeg::set_file);
	ClassDB::bind_method(D_METHOD("get_file"), &VideoStreamFFMpeg::get_file);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "file", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR | PROPERTY_USAGE_INTERNAL), "set_file", "get_file");
}

void VideoStreamFFMpeg::set_audio_track(int p_track) {
	audio_track = p_track;
}

