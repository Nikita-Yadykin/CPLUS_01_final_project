#include"Console—hat.h"
#include<iostream>
#include <windows.h>
using namespace std;
bool ConsoleChat::ÒhatStarted() const
{
	return _ÒhatStarted;
}

void ConsoleChat::start()
{
	_ÒhatStarted = true;
}


void ConsoleChat::startMenu()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);
	cout << "\tWelcome to chat!\n\n"
		<< "Choose an action to continue: \n\n"
		<< "1-Register\n"
		<< "2-Enter chat\n"
		<< "3-Leave the chat" << endl;
	string str;
	char action;
	
	cin >> str;
	
	if (!str.empty())
		action = '0';

    action = str[0];
		
	switch (action)
	{
	case '1':
		SetConsoleTextAttribute(hConsole, 10);
		signUp();
		break;
	case '2':
		SetConsoleTextAttribute(hConsole, 11);
		logIn();
		break;
	case '3':
		_ÒhatStarted = false;
		SetConsoleTextAttribute(hConsole, 15);
		break;
	default:
		SetConsoleTextAttribute(hConsole, 12);
		cout << "Please check that the characters you are entering are correct.\n";
		break;
	}

};



shared_ptr<User> ConsoleChat::getUserByLogin(const string login) const
{
	for (auto& user : _user)
	{
		if (login == user.getLogin())
			return make_shared<User>(user);
	}
	return nullptr;
}

shared_ptr<User>  ConsoleChat::getOnlineUser() const
{
	return _onlineUser;
}

void ConsoleChat::logIn()
{
	string login;
	string password;

	cout << "Please enter a login: ";
	cin >> login;
	cout << "Enter password: ";
	cin >> password;

	_onlineUser = getUserByLogin(login);

	if (_onlineUser == nullptr || password != _onlineUser->getPassword())
	{
		_onlineUser = nullptr;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 12);
		cout << "Invalid login or password, please try again\n"; // —‡·‡Ú˚‚‡ÂÚ ‚ Î˛·ÓÏ ÒÎÛ˜‡Â
		SetConsoleTextAttribute(hConsole, 11);
	}
}

void ConsoleChat::signUp()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);
	string login, password, name;

	cout << "Please enter your login: ";
	cin >> login;
	cout << "Choose security password: ";
	cin >> password;
	cout << "Enter your name: ";
	cin >> name;
	
	if (getUserByLogin(login) || login == "all")
	{
		throw LoginException();
	};
	
	User user = User(login, password, name);
	_user.push_back(user);
	_onlineUser = make_shared<User>(user);
	cout << endl << "Congratulations! You have successfully registered!\n";
}
void ConsoleChat::openChat() const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11);
	std::string sender, recipient;
	std::cout << " -----------chat-------  \n";
	for (auto& message : _message)
	{
		if (_onlineUser->getLogin() == message.getSender() || _onlineUser->getLogin() == message.getRecipient() || message.getRecipient() == "all")
		{
			sender = (_onlineUser->getLogin() == message.getSender()) ? _onlineUser->getLogin() : getUserByLogin(message.getSender())->getName();

			if (message.getRecipient() == "all")
			{
				recipient = "all";
			}
			else
			{
				recipient = (_onlineUser->getLogin() == message.getRecipient()) ? _onlineUser->getLogin() : getUserByLogin(message.getRecipient())->getName();
			}
			std::cout << "message from " << sender << ": to " << recipient << "\n";
			std::cout << " - " << message.getLetter() << " - \n";
		}
	}
	std::cout << "---------------------------\n";
	SetConsoleTextAttribute(hConsole, 15);
};
void ConsoleChat::sendMessage()
{
	std::string recipient, text;
	std::cout << "to (login or all) - ";
	std::cin >> recipient;
	std::cout << ">> ";
	std::cin.ignore();
	getline(cin, text);

	if (!(recipient == "all" || getUserByLogin(recipient))) {
		std::cout << "error no such user  -- " << recipient << "\n";
		return;
	}
	if (recipient == "all")
		_message.push_back(Message(_onlineUser->getLogin(), "all", text));
	else
		_message.push_back(Message(_onlineUser->getLogin(), getUserByLogin(recipient)->getLogin(), text));
	std::cout << "message send -  " << recipient << ":\n ";
}

void ConsoleChat::chatMenu()
{
	
	cout << "Welcome " << _onlineUser->getLogin() << "\n";
	while (_onlineUser)
	{
		cout << "Choose an action: \n"
			<< "1-Group chat \n"
			<< "2-Write a private message \n"
			<< "3-Exit \n" ;
		string str;
		char action;

		cin >> str;

		if (!str.empty())
			action = '0';

		action = str[0];

		switch (action)
		{
		case '1':
			openChat();
			break;
		case '2':
			sendMessage();
			break;
		case '3':
			_onlineUser = nullptr;
			break;
		default:
			cout << "Please try again" << endl;
			break;
		}
	}
}

