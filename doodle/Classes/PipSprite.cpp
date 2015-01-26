#include "Config.h"

bool PipSprite::isMoved = false;
int PipSprite::idx = 0;

int PipSprite::RandHei[] = {45, 101, 112, 87, 30, 199, 125, 30, 170, 
	138, 80, 92, 8, 147, 153, 70, 31, 119, 105, 130, 189, 177, 
	167, 57, 200, 74, 26, 127, 195, 71, 192, 176, 14, 163, 67, 147, 
	140, 156, 16, 66, 150, 85, 48, 24, 74, 157, 86, 57, 96, 126, 43, 
	96, 32, 166, 58, 7, 23, 65, 196, 82, 122, 50, 117, 71, 145, 166, 
	74, 41, 60, 183, 144, 118, 154, 90, 88, 19, 113, 155, 32, 109, 85, 
	106, 34, 12, 43, 11, 141, 76, 125, 101, 32, 130, 14, 39, 114, 0, 
	175, 3, 167, 127};


PipSprite::PipSprite(int PosX, cocos2d::Sprite* bird) {
	this->diffHeight = 400.0f;
	this->baseHeight = 0.0f;
	this->bird = bird;

	auto pipUp = AtlasLoader::getInstance()->getSpriteFrameByName("pipe_up");
	auto pipDown = AtlasLoader::getInstance()->getSpriteFrameByName("pipe_down");
	this->upSprite = cocos2d::Sprite::createWithSpriteFrame(pipUp);
	this->downSprite = cocos2d::Sprite::createWithSpriteFrame(pipDown);

	this->downSprite->setPositionY(this->diffHeight);

	this->addChild(this->upSprite);
	this->addChild(this->downSprite);

	this->stop();
	this->scheduleUpdate();
	this->setPositionX(PosX);
}

void PipSprite::randPos() {
	this->baseHeight = PipSprite::RandHei[PipSprite::idx];
	PipSprite::idx += 1;

	this->downSprite->setPositionY(this->baseHeight + this->diffHeight);
	this->upSprite->setPositionY(this->baseHeight);
}

void PipSprite::move() {
	PipSprite::isMoved = true;
}

void PipSprite::stop() {
	PipSprite::isMoved = false;
}

bool PipSprite::checkLive() {
	int width = 70;
	int start = 30;
	int X = this->getPositionX();

	char abc[100];
	sprintf(abc, "%f", this->bird->getPositionY());

	static int idx = 0;
	if(X < width + start && X > start) {
		idx ++;
		char str_idx[100];
		sprintf(str_idx, "%d", idx);

		int birdY = this->bird->getPositionY();
		int Y = this->baseHeight;
		int down = 170;
		int up = 230;
		if(birdY < Y + up && birdY > Y + down)
			return true;
		return false;
	}
	return true;
}

void PipSprite::update(float dt) {
	if(false == PipSprite::isMoved)
		return ;

	if(false == checkLive()) {
		GameScene::getInstance()->end(false);
		Socket::getInstance()->send_msg("Uwin");
		cocos2d::Director::getInstance()->stopAnimation();
	}

	this->setPositionX(this->getPositionX() - 1);
	if(this->getPositionX() < -30) {
		this->randPos();
		this->setPositionX(500);
	}
}