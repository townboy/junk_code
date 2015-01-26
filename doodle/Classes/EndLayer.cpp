#include "Config.h"

EndLayer::EndLayer(bool isWin) {
	cocos2d::Label* text ;
	if(false == isWin) {
		text = cocos2d::Label::createWithTTF("Game Over!", "fonts/Marker Felt.ttf", 50.0f);
		text->setColor(cocos2d::Color3B(0x68, 0x22, 0x8b) );
	}
	else {
		text = cocos2d::Label::createWithTTF("YOU WIN", "fonts/Marker Felt.ttf", 50.0f);
		text->setColor(cocos2d::Color3B(0xff, 0x00, 0x00) );
	}
	text->setPosition(150, 200);
	this->addChild(text);
}