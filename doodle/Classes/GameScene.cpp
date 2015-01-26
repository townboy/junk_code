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

void GameScene::enterGame(float dt) {
	dynamic_cast<SplashLayer *> (this->splash)->add_play();
	/*
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
	*/
}

void GameScene::connect_server() {
	auto client = new mDelegate();
	this->clientFd = new cocos2d::network::WebSocket();
	this->clientFd->init(*client, "ws://recwert.eicp.net:25104");
}

void GameScene::enterRace() {
	this->removeChildByTag(0);
	AtlasLoader::getInstance()->loadAtlas();
	this->back = new BackgroundLayer();
	this->addChild(this->back, 0, 1);

	this->status = new StatusLayer();

	this->addChild(this->status);
	
	this->getPhysicsWorld()->setGravity(cocos2d::Vect(700, -980));
	//this->getPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_ALL);

	this->connect_server();
}


void GameScene:: startSplash() {
	this->splash = new SplashLayer();
	this->addChild(this->splash, 0, 0);
	this->scheduleOnce(schedule_selector(GameScene::enterGame), 1.0f);
}

GameScene::GameScene() {
	this->initWithPhysics();
	//Scene::init();
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