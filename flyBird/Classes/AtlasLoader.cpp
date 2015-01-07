#include "Config.h"

AtlasLoader* AtlasLoader::sharedAtlasLoader = nullptr;

AtlasLoader* AtlasLoader::getInstance() {
	if(sharedAtlasLoader == NULL)
		sharedAtlasLoader = new AtlasLoader();
	return sharedAtlasLoader;
}

void AtlasLoader::destoyInstance() {
	CC_SAFE_DELETE(sharedAtlasLoader);
}

void AtlasLoader::loadAtlas(std::string filename) {
	auto textureAtlas = cocos2d::Director::getInstance()->getTextureCache()->addImage("image/atlas.png");
	this->loadAtlas(filename, textureAtlas);
}

void AtlasLoader::loadAtlas(std::string filename, cocos2d::Texture2D *texture) {
	std::string data = cocos2d::FileUtils::getInstance()->getStringFromFile(filename);
	unsigned pos;
	Atlas atlas;
	pos = data.find_first_of("\n");
	
	std::string line = data.substr(0, pos);
	data = data.substr(pos + 1);
	while(line != "") {
		sscanf(line.c_str(), "%s %d %d %f %f %f %f", 
			atlas.name, &atlas.width, &atlas.height, &atlas.start.x, 
			&atlas.start.y, &atlas.end.x, &atlas.end.y);

		atlas.start.x *= 1024;
		atlas.start.y *= 1024;
		atlas.end.x *= 1024;
		atlas.end.y *= 1024;
		pos = data.find_first_of("\n"); 
		line = data.substr(0, pos);
		data = data.substr(pos + 1);
		if(atlas.name == std::string("land")) 
			atlas.start.x += 1;

		auto rect = cocos2d::Rect(atlas.start.x, atlas.start.y, atlas.width, atlas.height);
		auto frame = cocos2d::SpriteFrame::createWithTexture(texture, rect);
		this->_spriteFrames.insert(std::string(atlas.name), frame); 
	}
}

AtlasLoader::AtlasLoader() {
}

cocos2d::SpriteFrame* AtlasLoader::getSpriteFrameByName(std::string name) {
	return this->_spriteFrames.at(name);
}