#include "Config.h"

Socket * Socket::shared = nullptr;

Socket* Socket::getInstance() {
	if(nullptr == shared)
		shared = new Socket();
	return shared;
}

Socket::Socket() {
	this->isUwin = false;
	WORD wVersionRequestd;
	WSADATA wsaData;
	int err;

	this->msg_len = 20;

	wVersionRequestd = MAKEWORD(1, 1);

	err = WSAStartup(wVersionRequestd, &wsaData);

	if(0 != err)
		return ;
	if(1 != LOBYTE(wsaData.wVersion) || 1 != HIBYTE(wsaData.wVersion) ) {
		WSACleanup();
		return ;
	}

	this->sockClient = socket(AF_INET, SOCK_STREAM, 0);

	addrSrv.sin_family = AF_INET;
	
	this->addButton();
	this->addText();
}

void Socket::addText() {
	this->ip = cocos2d::TextFieldTTF::textFieldWithPlaceHolder("INPUT HOST IP:PORT", "Arial", 20);
	this->ip->setColor(cocos2d::Color3B(0xff, 0x00, 0x00));
	this->ip->setPosition(-10, -50);
	this->ip->attachWithIME();
	this->addChild(this->ip);
}

void Socket::addButton() {

	this->bt_connect = cocos2d::ui::Button::create();
	this->bt_wait = cocos2d::ui::Button::create();

	this->bt_connect->setTitleText("ClIENT");
	this->bt_wait->setTitleText("HOST");

	this->bt_connect->setTitleFontSize(30.0f);
	this->bt_wait->setTitleFontSize(30.0f);

	this->bt_wait->setPositionY(50);

	this->bt_wait->addClickEventListener(CC_CALLBACK_1(Socket::HostInit, this));
	this->bt_connect->addClickEventListener(CC_CALLBACK_1(Socket::ClientInit, this));

	this->addChild(this->bt_connect);
	this->addChild(this->bt_wait);
}

void Socket::ClientInit(cocos2d::Ref * pSender) {
	this->Parser();
	CCLOG("CONNECT");
	isHost = false;

	this->removeChild(this->bt_wait);
	this->removeChild(this->ip);

	addrSrv.sin_port = htons(this->port);
	addrSrv.sin_addr.S_un.S_addr = inet_addr(this->str_ip);
	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	std::thread run(std::mem_fn(&Socket::Client_recv_msg), this);
	run.detach();
}

void Socket::Parser() {
	/*
	int pos = this->ip->getString().find_first_of(':');
	this->str_ip = this->ip->getString().substr(0, pos).c_str();
	sscanf(this->ip->getString().substr(pos + 1).c_str(), "%d", &this->ip);
	CCLOG(this->str_ip);
	*/
	this->str_ip = "127.0.0.1";
	this->port = 10086;
}

void Socket::HostInit(cocos2d::Ref * pSender) {
	this->Parser();
	CCLOG("WAIT");
	isHost = true;

	this->removeChild(this->bt_connect);
	this->removeChild(this->ip);

	addrSrv.sin_port = htons(this->port);
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	bind(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	listen(sockClient, 5);

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);

	sockConn = accept(sockClient, (SOCKADDR*) &addrClient, &len);

	if(sockConn == INVALID_SOCKET) {
		CCLOG("CONNECT FAILED");
		closesocket(sockClient);
		WSACleanup();
		return ;
	}

	std::thread run(std::mem_fn(&Socket::Host_recv_msg), this);
	run.detach();
}

void Socket::Client_recv_msg() {
	char recvBuf[20];
	while(true) {
		recv(sockClient, recvBuf, msg_len, 0);
		BirdLayer::getInstance()->otherTouch(recvBuf);
		CCLOG(recvBuf);
	}
}

void Socket::Host_recv_msg() {
	char recvBuf[20];
	while(true) {
		recv(sockConn, recvBuf, msg_len, 0);
		BirdLayer::getInstance()->otherTouch(recvBuf);
		CCLOG(recvBuf);
	}
}

bool Socket::getisHost() {
	return this->isHost;
}

void Socket::send_msg(char *msg) {
	if(true == this->getisHost())
		this->Host_send(msg);
	else
		this->Client_send(msg);
}

void Socket::Host_send(char *msg) {
	send(sockConn, msg, msg_len, 0);
}

void Socket::Client_send(char *msg) {
	send(sockClient, msg, msg_len, 0);
}