#include "Config.h"

void StatusLayer::add_bird() {
	this->bird[0] = cocos2d::Sprite::create("DoodleJump.app/hudplayerblue@2x.png");
	this->bird[0]->setPosition(cocos2d::Vec2(150, 745));
	
	this->bird[1] = cocos2d::Sprite::create("DoodleJump.app/hudplayergreen@2x.png");
	this->bird[1]->setPosition(cocos2d::Vec2(150, 745));

	this->bird[2] = cocos2d::Sprite::create("DoodleJump.app/hudplayerred@2x.png");
	this->bird[2]->setPosition(cocos2d::Vec2(150, 745));

	this->bird[3] = cocos2d::Sprite::create("DoodleJump.app/hudplayerwhite@2x.png");
	this->bird[3]->setPosition(cocos2d::Vec2(150, 745));

	for(int i = 0 ;i < 4; i++)
		this->addChild(this->bird[i]);
}

StatusLayer::StatusLayer() {
	auto tem = cocos2d::Sprite::create("DoodleJump.app/hudbckgleft@2x.png");
	tem->setPosition(cocos2d::Vec2(474, 745));
	this->addChild(tem);

	tem = cocos2d::Sprite::create("DoodleJump.app/hudbckgright@2x.png");
	tem->setPosition(cocos2d::Vec2(928, 745));
	this->addChild(tem);

	this->scheduleUpdate();

	this->add_bird();
	this->finnum = 0;
	this->needUpdate = false;
}

void StatusLayer::update(float dt) {
	if(false == this->needUpdate)
		return;

	for(int i = 0 ; i < 4; i++) {
		float x = dynamic_cast<BackgroundLayer *>(GameScene::getInstance()->back) ->bird[i]->getPosition().x;
		float per = (x - 300) / (21100 - 300);
		float turnx = 150 + per * (890 - 150);
		this->bird[i]->setPosition(cocos2d::Vec2(turnx, 745));
	}
}

void StatusLayer::finish(int own) {
	char str[100];
	sprintf(str, "finish %s", GameScene::getInstance()->username.c_str());
	GameScene::getInstance()->clientFd->send(str);
	
	auto rank = cocos2d::Sprite::create("DoodleJump.app/leaderboardbackground@2x.png");
	rank->setPosition(cocos2d::Vec2(500, 500));
	this->addChild(rank);

	int size = this->name.size();
	for(int i = 0 ;i < size; i++) {
		this->finnum ++;
		auto text = cocos2d::Label::createWithTTF(name[i].c_str(), "DoodleJump.app/DoodleJumpBold_v2.ttf", 40.0f);
		text->setColor(cocos2d::Color3B(0xff, 0x00, 0x00) );
		text->setPosition(460, 670 - 50 * this->finnum);
		this->addChild(text);
	}
}

void StatusLayer::addfinish(std::string fname) {
	if(false == dynamic_cast<BackgroundLayer* >( GameScene::getInstance()->back)->isBegin) {
		this->finnum ++;
		auto text = cocos2d::Label::createWithTTF(fname.c_str(), "DoodleJump.app/DoodleJumpBold_v2.ttf", 40.0f);
		text->setColor(cocos2d::Color3B(0xff, 0x00, 0x00) );
		text->setPosition(460, 670 - 50 * this->finnum);
		this->addChild(text);
	}
	else
		this->name.push_back(fname);
}