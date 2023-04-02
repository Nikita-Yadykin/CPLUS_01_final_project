#pragma once

#include<vector>
#include<memory>
#include"Message.h"

class ConsoleChat
{
public:
	void start();
	bool ñhatStarted() const;
	void startMenu();

private:

	vector<User> _user;
	shared_ptr<User> _onlineUser = nullptr;
	vector<Message> _message;

	bool _ñhatStarted = false;


};


