#ifndef __BIRDSPRITE_H__
#define __BIRDSPRITE_H__

class BirdSprite : public cocos2d::Sprite {
public:
	BirdSprite(int color);
	bool init();
	void makeBird();

	bool isRun;
	float speed, delta;

	void move();
	void stop();
	void update(float dt);
	void changeSpeed(float de);

	bool checkLive();

	int color;

	void otherTouch(int Hei, int Speed);
};

#endif