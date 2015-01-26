#ifndef __STATUSLAYER_H__
#define __STATUSLAYER_H__

class StatusLayer : public cocos2d::Layer {
public:
	StatusLayer();
	void StatusLayer::update(float dt);
	void add_bird();
	cocos2d::Sprite * bird[4];
	void finish(int own);
	void addfinish(std::string fname);
	std::vector<std::string>name;
	int finnum;
	bool needUpdate;
};

#endif