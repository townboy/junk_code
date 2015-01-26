#ifndef __BIRDLAYER_H__
#define __BIRDLAYER_H__

class BirdLayer : public  cocos2d::Layer {
public:
	static BirdLayer * getInstance();
	static BirdLayer * shared;

	BirdLayer();

	bool init();

	void addPip();

	bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *event);

	void otherTouch(char *msg);

	cocos2d::Sprite* bird;
	cocos2d::Sprite* other;
};

#endif