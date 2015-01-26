#include "Config.h"

SplashLayer::SplashLayer() {
	auto splash = cocos2d::Sprite::create("DoodleJump.app/Default-Landscape.png");

    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    splash->setPosition(cocos2d::Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	this->setTouchEnabled(true);
	this->setTouchMode(cocos2d::Touch::DispatchMode::ONE_BY_ONE);
    this->addChild(splash, 0);
}

bool SplashLayer::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *event) {
	if("" == this->name->getString())
		return true;

	CCLOG(this->name->getString().c_str());
	GameScene::getInstance()->username = name->getString();
	GameScene::getInstance()->enterRace();
	return true;
}

void SplashLayer::add_play() {
	auto play = cocos2d::Sprite::create("DoodleJump.app/play@2x_1.png");
    this->addChild(play, 1);
	play->setPosition(cocos2d::Vec2(710, 250));
	/*
	auto listen = cocos2d::EventListenerTouchOneByOne::create();
	listen->onTouchBegan = CC_CALLBACK_2(SplashLayer::onTouchBegan, this);
	*/
	/*listen->onTouchBegan = [play](cocos2d::Touch *touch, cocos2d::Event *event) {
		CCLOG("success");
		return true;
	};
	*/
	//listen->onTouchBegan = CC_CALLBACK_2(SplashLayer::onTouchBegan, this);
	this->name = cocos2d::TextFieldTTF::textFieldWithPlaceHolder("YOUR NAME : ", "DoodleJump.app/DoodleJumpBold_v2.ttf", 50);
	this->name->setColor(cocos2d::Color3B(0xff, 0x00, 0x00));
	this->name->setPosition(300, 300);
	this->name->attachWithIME();
	this->addChild(this->name);
}
