#ifndef __BACKGROUNDLAYER_H__
#define __BACKGROUNDLAYER_H__

class BackgroundLayer : public  cocos2d::Layer {
public:
	BackgroundLayer();
	void update(float dt);

	void add_pipe(int x, int y);
	void add_bird(int idx);
	void add_block(int x, int y);
	void add_edgebox();
	bool onContactBegin(const cocos2d::PhysicsContact& contact);

	cocos2d::Sprite* bird[4];
	int own;

	cocos2d::Sprite * ground;
	bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *event);
	bool isBegin;
	void begin(int own);
	void updateBird(int idx, float posX, float posY, float x);
	cocos2d::Sprite* makeRocket();
};

#endif