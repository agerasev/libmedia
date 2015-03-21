#pragma once

typedef struct Media_App Media_App;

typedef struct Media_Asset Media_Asset;

#ifdef __cplusplus
extern "C" {
#endif

Media_Asset *Media_openAsset(Media_App *app, const char *filename);
void Media_closeAsset(Media_Asset *asset);

long Media_getAssetLength(Media_Asset *asset);
void Media_readAsset(Media_Asset *asset, long size, void *buffer);

#ifdef __cplusplus
}
#endif
