#pragma once

#include<vector>
#include<memory>
#include"Message.h"

class ConsoleChat
{
public:
	void start();
	bool ˝hatStarted() const;
	void startMenu();
	void signUp();
	void logIn();
	shared_ptr<User> getOnlineUser() const;
	void chatMenu();

private:

	vector<User> _user;
	shared_ptr<User> _onlineUser = nullptr;
	vector<Message> _message;
	bool _˝hatStarted = false;
	shared_ptr<User> getUserByLogin(const string login) const;
	void openChat() const;
};


