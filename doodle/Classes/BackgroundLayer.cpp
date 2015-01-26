#include "Config.h"

int RandHei[] = {45, 101, 112, 87, 30, 199, 125, 30, 170, 
	138, 80, 92, 8, 147, 153, 70, 31, 119, 105, 130, 189, 177, 
	167, 57, 200, 74, 26, 127, 195, 71, 192, 176, 14, 163, 67, 147, 
	140, 156, 16, 66, 150, 85, 48, 24, 74, 157, 86, 57, 96, 126, 43, 
	96, 32, 166, 58, 7, 23, 65, 196, 82, 122, 50, 117, 71, 145, 166, 
	74, 41, 60, 183, 144, 118, 154, 90, 88, 19, 113, 155, 32, 109, 85, 
	106, 34, 12, 43, 11, 141, 76, 125, 101, 32, 130, 14, 39, 114, 0, 
	175, 3, 167, 127};

void BackgroundLayer::add_pipe(int x, int y) {
	auto tem = cocos2d::Sprite::create("DoodleJump.app/spike0@2x.png");
	tem->setPosition(cocos2d::Vec2(x, y));
	auto bound = cocos2d::PhysicsBody::createBox(cocos2d::Size(126, 536));
	bound->setCategoryBitmask(2);
	bound->setCollisionBitmask(1);
	bound->setContactTestBitmask(1);
	bound->setGravityEnable(false);
	bound->setDynamic(false);
	tem->setPhysicsBody(bound);
	this->addChild(tem, 10, -1);
}

void BackgroundLayer::add_block(int x, int y) {
	auto tem = cocos2d::Sprite::create();
	tem->setPosition(cocos2d::Vec2(x, y));
	auto bound = cocos2d::PhysicsBody::createBox(cocos2d::Size(126, 5));

	bound->setCategoryBitmask(2);
	bound->setCollisionBitmask(1);
	bound->setContactTestBitmask(1);
	bound->setGravityEnable(false);
	bound->setDynamic(false);
	tem->setPhysicsBody(bound);
	this->addChild(tem, 10, 100);
}

void BackgroundLayer::add_edgebox() {
	auto node=Node::create();
	/* 创建一个物体对象 EdgeBox是一个空心的矩形 相当于边框效果 */
	auto bound = cocos2d::PhysicsBody::createEdgeBox(cocos2d::Size(30000, 768));
	/* 设置刚体掩码 用于碰撞检测 */
	bound->setCategoryBitmask(2);
	bound->setCollisionBitmask(1);
	bound->setContactTestBitmask(1);
	/*   将物体与节点绑定  */
	node->setPhysicsBody(bound);
	node->setPosition(cocos2d::Point(15000, 384));
	this->addChild(node, 0, 100);
}

cocos2d::Sprite* BackgroundLayer::makeRocket() {
	auto texture = cocos2d::Director::getInstance()->getTextureCache()->addImage("DoodleJump.app/jetpack@2x.png");

	float width[10] = {0, 54.25, 108.5, 162.75, 0, 54.25, 108.5, 162.75, 0, 54.25};
	float height[10] = {0, 0, 0, 0, 108.68, 108.68, 108.68, 108.68, 217.36, 217.36};

	cocos2d::Vector<cocos2d::SpriteFrame *> frames;

	for(int i = 0 ;i < 10;i ++) {
		auto rect = cocos2d::Rect(width[i], height[i], 54.25, 108.68);
		auto frame = cocos2d::SpriteFrame::createWithTexture(texture, rect);
		frames.pushBack(frame);
	}

	auto animation = cocos2d::Animation::createWithSpriteFrames(frames, 0.07f);
	auto animate = cocos2d::Animate::create(animation);
	auto ttt = cocos2d::RepeatForever::create(animate);
	auto ret = cocos2d::Sprite::create();
	ret->runAction(ttt);
	return ret;
}

void BackgroundLayer::add_bird(int idx) {
	int bitmask[4] = {1, 2, 4, 8};
	char * birdname;
	if(0 == idx)
		birdname = "DoodleJump.app/playerblue@2x.png";
	else if(1 == idx)
		birdname = "DoodleJump.app/playergreen@2x.png";
	else if(2 == idx)
		birdname = "DoodleJump.app/playerred@2x.png";
	else if(3 == idx)
		birdname = "DoodleJump.app/playerwhite@2x.png";

	this->bird[idx] = cocos2d::Sprite::create(birdname);
	this->bird[idx]->setPosition(cocos2d::Vec2(300, 500 - idx * 70));
	auto bound = cocos2d::PhysicsBody::createBox(cocos2d::Size(88, 84), cocos2d::PhysicsMaterial(0, 1, 0));
	bound->setCategoryBitmask(1);
	bound->setCollisionBitmask(2);
	bound->setContactTestBitmask(2);
	bound->setGravityEnable(false);
	//bound->setContactTestBitmask(bitmask[idx]);

	bound->setRotationEnable(false);
	bound->setVelocityLimit(1000);
	this->bird[idx]->setPhysicsBody(bound);
	auto rocket = this->makeRocket();
	rocket->setPosition(cocos2d::Vec2(85, 15));
	this->bird[idx]->addChild(rocket);
	this->addChild(this->bird[idx], 20, idx);
}

BackgroundLayer::BackgroundLayer() {
	this->isBegin = false;

	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	this->setTouchEnabled(true);
	this->setTouchMode(cocos2d::Touch::DispatchMode::ONE_BY_ONE);

	for(int i = 0;i < 30;i ++) {
		auto tem = cocos2d::Sprite::create("DoodleJump.app/bck@2x.png");
		tem->setPosition(cocos2d::Vec2(512 + i * 1024, 320));
		this->addChild(tem);
		tem = cocos2d::Sprite::create("DoodleJump.app/bck@2x.png");
		tem->setPosition(cocos2d::Vec2(512 + i * 1024, 320 + 640));
		this->addChild(tem);
	}

	auto tem = cocos2d::Sprite::create("DoodleJump.app/matchingboard-1@2x.png");
    tem->setPosition(cocos2d::Vec2(visibleSize.width/2 + origin.x + 200, visibleSize.height/2 + origin.y));
	this->addChild(tem, 0, 2);

	tem = cocos2d::Sprite::create("DoodleJump.app/startline@2x.png");
	tem->setScaleY(1.4);
    tem->setPosition(cocos2d::Vec2(234, 320));
	this->addChild(tem);

	tem = cocos2d::Sprite::create("DoodleJump.app/finishline@2x.png");
	tem->setScaleY(1.4);
    tem->setPosition(cocos2d::Vec2(21100, 320));
	this->addChild(tem);

	tem = cocos2d::Sprite::create("DoodleJump.app/signalred@2x.png");
    tem->setPosition(cocos2d::Vec2(250, 58));
	this->addChild(tem);

	this->scheduleUpdate();

	for(int i = 0;i < 30;i ++) {
		this->add_pipe(700 + i * 700, RandHei[i] - 50);
		this->add_block(700 + i * 700, RandHei[i] + 224);
		this->add_pipe(700 + i * 700, RandHei[i] + 700);
		this->add_block(700 + i * 700, RandHei[i] + 425);
	}

	this->add_bird(0);
	this->add_edgebox();

	/* 创建监听器对象 */
	auto contactListener = cocos2d::EventListenerPhysicsContact::create();
	/* 设置onContactBegin回调函数为onContactBegin 开始碰撞调用 */
	contactListener->onContactBegin = CC_CALLBACK_1(BackgroundLayer::onContactBegin, this);
	/* 设置监听 最后在释放函数中不要忘记取消注册 */
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	//this->begin(0);
};

bool BackgroundLayer::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *event) {
	if(false == isBegin)
		return true;

	float posX = this->bird[this->own]->getPosition().x;
	float posY = this->bird[this->own]->getPhysicsBody()->getPosition().y;
	float x = this->bird[this->own]->getPhysicsBody()->getVelocity().x;

	char str[1000];
	sprintf(str, "sendMsg %d %f %f %f\n", this->own, posX, posY, x);

	GameScene::getInstance()->clientFd->send(str);

	this->bird[this->own]->getPhysicsBody()->setVelocity(cocos2d::Vec2(x, 600));
	return true;
}

bool BackgroundLayer::onContactBegin(const cocos2d::PhysicsContact& contact) {
	auto NodeA=(cocos2d::Sprite*)contact.getShapeA()->getBody()->getNode(); 
	auto NodeB=(cocos2d::Sprite*)contact.getShapeB()->getBody()->getNode(); 
	int tagA=NodeA->getTag();
	int tagB=NodeB->getTag();

	if(tagA + tagB > 50)
		return true;

	int aim;
	if(-1 == tagA)
		aim = tagB;
	else
		aim = tagA;

	char ans[100];
	sprintf(ans, "%d\n", tagA, tagB, aim);
		
	float yV = this->bird[aim]->getPhysicsBody()->getVelocity().y;
	this->bird[aim]->getPhysicsBody()->setVelocity(cocos2d::Vec2( -400, yV));

	return true;
}

void BackgroundLayer::begin(int belong) {
	char str[100];

	sprintf(str, "%d\n", belong);
	for(int i = 1;i < 4;i ++)
		this->add_bird(i);
	this->removeChildByTag(2);
	for(int i = 0 ;i < 4;i ++)
		this->bird[i]->getPhysicsBody()->setGravityEnable(true);

	this->own = belong;
	isBegin = true;
	sprintf(str, "%d\n", this->own);
}

void BackgroundLayer::updateBird(int idx, float posX, float posY, float x) {
	if(idx == this->own)
		return ;
	this->bird[idx]->setPosition(posX, posY);
	this->bird[idx]->getPhysicsBody()->setVelocity(cocos2d::Vec2(x, 600));
}

void BackgroundLayer::update(float dt) {
	if(false == isBegin)
		return ;
	char str[100];
	sprintf(str, "%d\n", this->own);
	float x = this->bird[this->own]->getPositionX();
	float add = 0.0f;
	if(x > 21100) {
		dynamic_cast<StatusLayer *> ( GameScene::getInstance()->status) -> finish(this->own);
		this->isBegin = false;

		this->bird[this->own]->getPhysicsBody()->setGravityEnable(false);
		float xV = this->bird[this->own]->getPhysicsBody()->getVelocity().x;
		this->bird[this->own]->getPhysicsBody()->setVelocity(cocos2d::Vec2(std::max(0.0f, xV - 12), 0));
		add = this->bird[this->own]->getPositionX() - 21100;
	}
	this->setPosition(cocos2d::Vec2(add + 150 - x ,0));
}