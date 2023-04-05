#pragma once
#include<vector>
#include<memory>
#include"Message.h"
class LoginException :public exception
{
public:
	const char *what() const noexcept override
	{
		return "error: user login already exists ";
	}
};

class ConsoleChat
{
public:
	void start();
	bool ñhatStarted() const;
	void startMenu();
	void signUp();
	void logIn();
	shared_ptr<User> getOnlineUser() const;
	void chatMenu();
	void sendMessage();
	
	
private:

	vector<User> _user;
	shared_ptr<User> _onlineUser = nullptr;
	vector<Message> _message;
	bool _ñhatStarted = false;
	shared_ptr<User> getUserByLogin(const string login) const;
	void openChat() const;
};


