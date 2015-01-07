#ifndef __PIPLAYER_H__
#define __PIPLAYER_H__

class PipSprite : public cocos2d::Sprite {
public:
	PipSprite(int PosX, cocos2d::Sprite * bird);

	static int idx;
	static int RandHei[100];

	void randPos();

	static bool isMoved;
	static void move();

	static void stop();
	void update(float dt);
	cocos2d::Sprite * bird;

	bool checkLive();
	float diffHeight;
	float baseHeight;

	cocos2d::Sprite * upSprite;
	cocos2d::Sprite * downSprite;
};

#endif