#include "Config.h"

mDelegate::mDelegate() {
}
	
void mDelegate::onOpen(cocos2d::network::WebSocket* ws) {
	GameScene::getInstance()->clientFd->send("wait play");
	CCLOG("Connect Succcess");
}
void mDelegate::onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data) {
	std::string recv = data.bytes;
	if("start" == recv.substr(0, 5) ) {
		const char * str = recv.c_str();
		int own;
		sscanf(str, "start game %d", &own);
		
		char ans[100];
		sprintf(ans, "%d\n", own);
		dynamic_cast<BackgroundLayer *>(GameScene::getInstance()->back) -> begin(own);
		CCLOG("confirm start");

		dynamic_cast<StatusLayer *>(GameScene::getInstance()->status) -> needUpdate = true;
	}
	else if("sendMsg" == recv.substr(0, 7)) {
		const char * str = recv.c_str();
		int idx;
		float posX, posY, x;
		sscanf(str, "sendMsg %d %f %f %f\n", &idx, &posX, &posY, &x);
		dynamic_cast<BackgroundLayer *>(GameScene::getInstance()->back) -> updateBird(idx, posX, posY, x);
	}
	else {
		CCLOG(data.bytes);
		dynamic_cast<StatusLayer *>(GameScene::getInstance()->status)->addfinish(recv.substr(6));
	}
}

void mDelegate::onClose(cocos2d::network::WebSocket* ws) {
	CCLOG("onClose");
}

void mDelegate::onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error) {
	CCLOG("onError");
}