#include "register_types.h"

#include "video_stream_ffmpeg.h"
#include "resource_format_loader_ffmpeg.h"

static Ref<ResourceFormatLoaderFFMpeg> resource_loader_ffmpeg;

void register_ffmpeg_types() {
	resource_loader_ffmpeg.instantiate();
	ResourceLoader::add_resource_format_loader(resource_loader_ffmpeg, true);

	GDREGISTER_CLASS(VideoStreamFFMpeg);
}

void unregister_ffmpeg_types() {
	ResourceLoader::remove_resource_format_loader(resource_loader_ffmpeg);
	resource_loader_ffmpeg.unref();
}
