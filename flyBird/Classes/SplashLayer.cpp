#include "Config.h"

SplashLayer::SplashLayer() {
	auto splash = cocos2d::Sprite::create("image/splash.png");

    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    splash->setPosition(cocos2d::Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    this->addChild(splash, 0);
}