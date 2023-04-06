#pragma once
#include<vector>
#include<memory>
#include"Message.h"

class LoginException :public exception // Класс исключения наследник от класса exception
{
public:
	LoginException(const std::string& msg) :_msg(msg) {}
	virtual const char* what() const noexcept override // Виртуальный метод what() выводит предупреждение, если логин не уникален
	{
		return "error: user login already exists ";
	}
private:
	std::string _msg;
};

class ConsoleChat
{
public:
	void start();
	bool сhatStarted() const;
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
	bool _сhatStarted = false;
	shared_ptr<User> getUserByLogin(const string login) const;
	void openChat() const;
	
};


