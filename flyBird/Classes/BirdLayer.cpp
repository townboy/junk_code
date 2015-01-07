#include "Config.h"

BirdLayer * BirdLayer::shared = nullptr;

BirdLayer* BirdLayer::getInstance() {
	if(nullptr == shared)
		shared = new BirdLayer();
	return shared;
}

BirdLayer::BirdLayer() {
	this->init();
}

bool BirdLayer::init() {
	this->bird = new BirdSprite(0);
	this->other = new BirdSprite(1);
	GameScene::getInstance()->bird = this->bird;
	GameScene::getInstance()->other = this->other;

	this->addChild(this->bird, 10);
	this->addChild(this->other, 5);

	this->bird->setPosition(cocos2d::Vec2(50, 300));
	this->other->setPosition(cocos2d::Vec2(50, 300));

	this->addPip();
	
	this->setTouchEnabled(true);
	this->setTouchMode(cocos2d::Touch::DispatchMode::ONE_BY_ONE);

	cocos2d::EventListenerTouchOneByOne::create()->onTouchBegan = CC_CALLBACK_2(BirdLayer::onTouchBegan, this);
	return true;
}

void BirdLayer::addPip() {
	this->addChild(new PipSprite(700, this->bird));
	this->addChild(new PipSprite(400, this->bird));
}

bool BirdLayer::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *event) {
	int changeDelta = 3;
	PipSprite::move();
	dynamic_cast<BirdSprite *>(bird)->move();
	dynamic_cast<BirdSprite *>(bird)->changeSpeed(changeDelta);

	dynamic_cast<BirdSprite *>(other)->move();

	dynamic_cast<BackgroundLayer *>(GameScene::getInstance()->back )->move();

	int Hei = dynamic_cast<BirdSprite *>(bird)->getPositionY();
	int Speed = dynamic_cast<BirdSprite *>(bird)->speed;
	char msg[20];
	sprintf(msg, "%d %d\n", Hei, Speed);
	Socket::getInstance()->send_msg(msg);

	return true;
}

void BirdLayer::otherTouch(char *msg) {
	if('U' == msg[0]) {
		CCLOG("enter Uwin");
		Socket::getInstance()->isUwin = true;
		return ;
	}

	PipSprite::move();

	int Hei, Speed;
	sscanf(msg, "%d %d\n", &Hei, &Speed);

	dynamic_cast<BirdSprite *>(bird)->move();
	dynamic_cast<BirdSprite *>(other)->move();

	dynamic_cast<BirdSprite *>(other)->otherTouch(Hei, Speed);

	dynamic_cast<BackgroundLayer *>(GameScene::getInstance()->back )->move();
}