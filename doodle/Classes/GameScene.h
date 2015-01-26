#ifndef __GAMESCENESCENE_H__
#define __GAMESCENESCENE_H__
#include "network\WebSocket.h"

class GameScene : public cocos2d::Scene {
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

	void enterGame(float dt);
	void enterRace();

	GameScene();

	void end(bool isWin);
	void connect_server();

	void startSplash();

	static GameScene* getInstance();
	static GameScene* shared;

	cocos2d::Layer * splash;

	cocos2d::Layer * back;
	
	cocos2d::Sprite* bird;
	cocos2d::Sprite* other;

	cocos2d::Layer * win;
	cocos2d::Layer * lose;
	cocos2d::Layer * status;

	cocos2d::network::WebSocket * clientFd;
	std::string username;
};

#endif // __HELLOWORLD_SCENE_H__