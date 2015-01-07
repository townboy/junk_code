#include "Config.h"

GameScene* GameScene::shared = nullptr;
// on "init" you need to initialize your instance
GameScene* GameScene::getInstance() {
	if(nullptr == shared)
		shared = new GameScene();
	return shared;
}

bool GameScene::init() {
	this->startSplash();
    return true;
}

void GameScene::start(float dt) {
	this->removeChildByTag(0);

	AtlasLoader::getInstance()->loadAtlas();
	this->back = new BackgroundLayer();
	this->addChild(this->back, 0, 1);
	auto bird = BirdLayer::getInstance();

	this->addChild(bird, 10);
	auto sock =  Socket::getInstance();

	sock->setPosition(150, 300);
	this->addChild(sock, 20);

	this->win = new EndLayer(true);
	this->lose = new EndLayer(false);
	this->win->setVisible(false);
	this->lose->setVisible(false);

	this->addChild(this->win);
	this->addChild(this->lose);
}

void GameScene:: startSplash() {
	auto splash = new SplashLayer();
	this->addChild(splash, 0, 0);
	this->scheduleOnce(schedule_selector(GameScene::start), 1.0f);
}

GameScene::GameScene() {
	this->init();
}

cocos2d::Scene* GameScene::createScene() {
	auto scene = new GameScene();
	scene->init();
	return scene;
}

void GameScene::end(bool isWin) {
	if(true == isWin) {
		this->win->setVisible(true);
		this->lose->setVisible(false);
	}
	else {
		this->lose->setVisible(true);
		this->win->setVisible(false);
	}
}