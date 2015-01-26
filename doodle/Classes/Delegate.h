#ifndef __DELEGATE_H__
#define __DELEGATE_H__

class mDelegate : public  cocos2d::network::WebSocket::Delegate{
public:
	mDelegate();
	void onOpen(cocos2d::network::WebSocket* ws);
	void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);
	void onClose(cocos2d::network::WebSocket* ws);
	void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error);;
};

#endif