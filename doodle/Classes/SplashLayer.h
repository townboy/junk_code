#ifndef __SPLASHLAYER_H__
#define __SPLASHLAYER_H__

class SplashLayer : public cocos2d::Layer {
public:
	SplashLayer();
	void add_play();
	bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *event);
	cocos2d::TextFieldTTF * name;
};

#endif 