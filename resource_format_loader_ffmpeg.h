
#ifndef RESOURCE_FORMAT_LOADER_FFMPEG_H
#define RESOURCE_FORMAT_LOADER_FFMPEG_H

#include "core/io/resource_loader.h"
// #include "scene/resources/video_stream.h"
//
// class WebMFrame;
// class WebMDemuxer;
// class VPXDecoder;
// class OpusVorbisDecoder;

class ResourceFormatLoaderFFMpeg : public ResourceFormatLoader {
public:
	virtual RES load(const String &p_path, const String &p_original_path = "", Error *r_error = nullptr, bool p_use_sub_threads = false, float *r_progress = nullptr, CacheMode p_cache_mode = CACHE_MODE_REUSE);
	virtual void get_recognized_extensions(List<String> *p_extensions) const;
	virtual bool handles_type(const String &p_type) const;
	virtual String get_resource_type(const String &p_path) const;
};

#endif // RESOURCE_FORMAT_LOADER_FFMPEG_H
