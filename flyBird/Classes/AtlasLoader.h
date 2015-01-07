#pragma once
#include "cocos2d.h"

typedef struct _atlas {
	char name[255];
	int width;
	int height;
	cocos2d::Point start;
	cocos2d::Point end;
} Atlas;

class AtlasLoader {
public:
	static AtlasLoader* getInstance();

	static void destoyInstance();

	void loadAtlas(std::string filename = "image/atlas.txt");

	void loadAtlas(std::string filename, cocos2d::Texture2D *texture);

	cocos2d::SpriteFrame* getSpriteFrameByName(std::string name);

protected:
	AtlasLoader();
	static AtlasLoader* sharedAtlasLoader;

	cocos2d::Map<std::string, cocos2d::SpriteFrame*> _spriteFrames;
};