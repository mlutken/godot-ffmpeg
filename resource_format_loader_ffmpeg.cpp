#include "resource_format_loader_ffmpeg.h"

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

#include "video_stream_ffmpeg.h"


RES ResourceFormatLoaderFFMpeg::load(const String &p_path, const String &p_original_path, Error *r_error, bool p_use_sub_threads, float *r_progress, CacheMode p_cache_mode) {
	FileAccess *f = FileAccess::open(p_path, FileAccess::READ);
	if (!f) {
		if (r_error) {
			*r_error = ERR_CANT_OPEN;
		}
		return RES();
	}

	VideoStreamFFMpeg *stream = memnew(VideoStreamFFMpeg);
	stream->set_file(p_path);

	Ref<VideoStreamFFMpeg> webm_stream = Ref<VideoStreamFFMpeg>(stream);

	if (r_error) {
		*r_error = OK;
	}

	f->close();
	memdelete(f);
	return webm_stream;
}

void ResourceFormatLoaderFFMpeg::get_recognized_extensions(List<String> *p_extensions) const {
	p_extensions->push_back("webx");
	p_extensions->push_back("mp4");
}

bool ResourceFormatLoaderFFMpeg::handles_type(const String &p_type) const {
	return ClassDB::is_parent_class(p_type, "VideoStream");
}

String ResourceFormatLoaderFFMpeg::get_resource_type(const String &p_path) const {
	String el = p_path.get_extension().to_lower();
	if (el == "webx" || el == "mp4") {
		return "VideoStreamFFMpeg";
	}
	return "";
}
