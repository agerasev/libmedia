#include <media/desktop/platform.h>

#ifdef __MEDIA_DESKTOP

#include <media/desktop/desktop.h>

#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 0x100

typedef struct Media_Asset
{
	FILE *handle;
	long length;
}
Media_Asset;

Media_Asset *Media_openAsset(Media_App *app, const char *filename)
{
	char ffn[MAX_NAME_LENGTH] = {'\0'};
	strcat(ffn,"assets/");
	strcat(ffn,filename);
	
	FILE *file = fopen(ffn,"rb");
	if(!file)
	{
		return NULL;
	}
	
	Media_Asset *asset = (Media_Asset*)malloc(sizeof(Media_Asset));
	asset->handle = file;
	
	fseek(file, 0L, SEEK_END);
	asset->length = ftell(file);
	fseek(file, 0L, SEEK_SET);
	
	return asset;
}

void Media_closeAsset(Media_Asset *asset)
{
	fclose(asset->handle);
	free(asset);
}

long Media_getAssetLength(Media_Asset *asset)
{
	return asset->length;
}

void Media_readAsset(Media_Asset *asset, long size, void *buffer)
{
	fread(buffer,1,size,asset->handle);
}

#endif
