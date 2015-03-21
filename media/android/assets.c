#include "platform.h"

#ifdef __MEDIA_ANDROID

#include "android.h"
#include <android/asset_manager.h>

typedef struct Media_Asset
{
	AAsset *aasset;
}
Media_Asset;

Media_Asset *Media_openAsset(Media_App *app, const char *filename)
{
	AAssetManager *manager = app->platform_context->app->activity->assetManager;
	AAsset *aasset = AAssetManager_open(manager,filename,AASSET_MODE_UNKNOWN);
	if(!aasset)
	{
		return NULL;
	}
	Media_Asset *asset = (Media_Asset*)malloc(sizeof(Media_Asset));
	asset->aasset = aasset;
	
	return asset;
}

void Media_closeAsset(Media_Asset *asset)
{
	AAsset_close(asset->aasset);
}

long Media_getAssetLength(Media_Asset *asset)
{
	return AAsset_getLength(asset->aasset);
}

void Media_readAsset(Media_Asset *asset, long size, void *buffer)
{
	AAsset_read(asset->aasset,buffer,size);
}

#endif
