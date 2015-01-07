#ifndef __BACKGROUNDLAYER_H__
#define __BACKGROUNDLAYER_H__

class BackgroundLayer : public  cocos2d::Layer {
public:
	BackgroundLayer();
	void move();
	void stop();
	void update(float dt);

	bool isRun;

	cocos2d::Sprite * ground;
};

#endif