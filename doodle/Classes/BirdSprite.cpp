#include "Config.h"

BirdSprite::BirdSprite(int color) {
	this->speed = 0;
	this->delta = -0.1;
	this->isRun = false;
	this->color = color;
	this->makeBird();
}

void BirdSprite::makeBird() {
	this->initWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("bird0_0"));

	cocos2d::Vector<cocos2d::SpriteFrame *> frames;

	char buff[255];
	for(int i = 0 ;i < 3;i ++) {
		sprintf(buff, "bird%d_%d", this->color, i);
		//CCLOG(buff);
		auto frame = AtlasLoader::getInstance()->getSpriteFrameByName(buff);
		frames.pushBack(frame);
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(frames, 0.2f);
	auto animate = cocos2d::Animate::create(animation);
	auto ttt = cocos2d::RepeatForever::create(animate);
	this->runAction(ttt);
	this->scheduleUpdate();
}

bool BirdSprite::init() {
	return true;
}

void BirdSprite::move() {
	this->isRun = true;
}

void BirdSprite::stop() {
	this->isRun = false;
}

void BirdSprite::update(float dt) {
	if(true == Socket::getInstance()->isUwin) {
		GameScene::getInstance()->end(true);
		cocos2d::Director::getInstance()->stopAnimation();
		return ;
	}
	if(false == this->isRun)
		return ;

	float nowY = this->getPositionY();

	this->setPositionY(nowY + this->speed);
	this->speed += this->delta;
}

void BirdSprite::changeSpeed(float de) {
	this->speed += de;
}

void BirdSprite::otherTouch(int Hei, int Speed) {
	this->speed = Speed;
	this->setPositionY(Hei);
}
