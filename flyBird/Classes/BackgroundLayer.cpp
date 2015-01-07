#include "Config.h"

BackgroundLayer::BackgroundLayer() {
	auto bg = cocos2d::Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("bg_night"));

	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	bg->setPosition(cocos2d::Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	this->addChild(bg);

	this->ground = cocos2d::Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
	this->ground->setPosition(cocos2d::Vec2(visibleSize.width/2 + origin.x, 50));
	this->addChild(this->ground);

	this->stop();
	this->scheduleUpdate();
};

void BackgroundLayer::move() {
	this->isRun = true;
}

void BackgroundLayer::update(float dt) {
	if(true == this->isRun) {
		this->ground->setPositionX(this->ground->getPositionX() - 2);
		if(this->ground->getPositionX() < 116)
			this->ground->setPositionX(136);
	}
}

void BackgroundLayer::stop() {
	this->isRun = false;
}