#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "ui/UIButton.h"

class Socket : public cocos2d::Layer{
public:
	Socket();
	static Socket * getInstance();
	static Socket * shared;
	
	void ClientInit(cocos2d::Ref * pSender);
	void HostInit(cocos2d::Ref * pSender);

	void addButton();
	cocos2d::ui::Button* bt_wait;
	cocos2d::ui::Button* bt_connect;

	bool isUwin;
	bool isHost;
	SOCKET sockClient;
	SOCKADDR_IN addrSrv;
	SOCKET sockConn;

	void Host_recv_msg();
	void Client_recv_msg();
	bool getisHost();

	void send_msg(char *msg);
	int msg_len;
	void Host_send(char *msg);
	void addText();
	void Client_send(char *msg);

	void Parser();
	int port;
	const char *str_ip;

	cocos2d::TextFieldTTF* ip;
};

#endif