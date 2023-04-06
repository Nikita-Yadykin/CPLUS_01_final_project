#include"Console�hat.h"
#include<iostream>
#include <windows.h>
using namespace std;

bool ConsoleChat::�hatStarted() const
{
	return _�hatStarted;
}

void ConsoleChat::start()
{
	_�hatStarted = true;
}

void ConsoleChat::startMenu() // ��������� ����, ������������ ��� �������
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);
	cout << "\tWelcome to chat!\n\n"
		<< "Choose an action to continue: \n\n"
		<< "1-Register\n"
		<< "2-Enter chat\n"
		<< "3-Leave the chat\n";
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
		signUp(); // ������������������
		break;
	case '2':
		
		logIn(); // �����
		break;
	case '3':
		_�hatStarted = false; // ����� �� ����
		SetConsoleTextAttribute(hConsole, 15);
		break;
	default:
		SetConsoleTextAttribute(hConsole, 12);
		cout << "Please check that the characters you are entering are correct.\n";
		SetConsoleTextAttribute(hConsole, 11);
		break;
	}

};

shared_ptr<User> ConsoleChat::getUserByLogin(const string login) const
{
	for (auto& user : _user) // ���������� vector ������������
	{
		if (login == user.getLogin()) // ���� ��������� ����� ������ � ������� ������ �� �������������
			return make_shared<User>(user); // ���������� ��������� �� ����� ������������
	}
	return nullptr;
}

shared_ptr<User>  ConsoleChat::getOnlineUser() const
{
	return _onlineUser;
}

void ConsoleChat::logIn() // ���� � ���
{
	string login;
	string password;

	cout << "Please enter a login: ";
	cin >> login;
	cout << "Enter password: ";
	cin >> password;

	_onlineUser = getUserByLogin(login); // ��������� �� ������ ������������ �������� ��������� �� ������������ � ��������� �������

	if (_onlineUser == nullptr || password != _onlineUser->getPassword()) // ���� ��� ������ ������������ ��� ��������� ������ �� ����� ������ ������ ������������
	{
		_onlineUser = nullptr; // ��������, ��� ������ ������������ ����������
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 12);
		cout << "Invalid login or password, please try again\n";
		SetConsoleTextAttribute(hConsole, 11);
	}
}

void ConsoleChat::signUp() // �����������
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);
	string login, password, name;

	cout << "Please enter your login: ";
	cin >> login;
	cout << "Choose security password: ";
	cin >> password;
	cout << "Enter your name: ";
	cin >> name;

	try
	{
		if (getUserByLogin(login) || login == "all") // ���� ������������ � ����� ������� ���������� ��� ����� = all
		{
			throw LoginException("error: "); // ������������ ������
		};
	}

	catch (const LoginException& ex) // ����� ����������� ����������
	{
		SetConsoleTextAttribute(hConsole, 12);
		cerr << "\n\n (" << ex.what() << ") \n\n"; // �������� ����� what()
		SetConsoleTextAttribute(hConsole, 15);
		return;
	}

	User user = User(login, password, name); // ������� ������ ������������
	_user.push_back(user); // ��������� ������ ������������ � vector �������������
	_onlineUser = make_shared<User>(user); // ����� ������������ ���������� ������ �������������
	cout << "\nCongratulations! You have successfully registered!\n";
}

void ConsoleChat::openChat() const // �������� ���� � ������ �������������
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11);
	string sender, recipient;

	cout << "-------users chatting online-----\n";
	cout << "login  \t\t  name  \n";
	cout << "\n---------------------------------\n";
	for (auto& user : _user) // ���������� �������������
		cout << user.getLogin() << "\t  --- \t " << user.getName() << "\n"; // ������� ����� � ��� ������������
	cout << "\n--------messages-----------------\n\n";
	cout << " -----------chat-------  \n";

	for (auto& message : _message) // ���������� vector ���������
	{
		if (_onlineUser->getLogin() == message.getSender() || _onlineUser->getLogin() == message.getRecipient() || message.getRecipient() == "all") // ���� ����� ������ ������������ ����� ������ ����������� ��� ������ ���������� ��� ����� "all"
		{
			sender = (_onlineUser->getLogin() == message.getSender()) ? _onlineUser->getLogin() : getUserByLogin(message.getSender())->getName(); // ������������� �����������

			if (message.getRecipient() == "all") // ���� ��������� ������������� ��� ����
			{
				recipient = "all";
			}
			else // ���� ��������� ��� ����������� ������������
			{
				recipient = (_onlineUser->getLogin() == message.getRecipient()) ? _onlineUser->getLogin() : getUserByLogin(message.getRecipient())->getName(); // ������������� ����������
			}
			cout << "message from " << sender << ": to " << recipient << "\n";
			cout << " - " << message.getLetter() << " - \n";
		}
	}
	cout << "---------------------------\n";
	
}

void ConsoleChat::sendMessage() // �������� ���������
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	string recipient, text;
	cout << "to (login or all) - ";
	cin >> recipient; // ������� ����� ���������� ��� all
	cout << ">> ";
	cin.ignore();
	getline(cin, text);

	if (!(recipient == "all" || getUserByLogin(recipient))) {  // ���� ���������� �� ����� all ��� �� ������ ����� ������������
		
		SetConsoleTextAttribute(hConsole, 12);
		cout << "error no such user  -- " << recipient << "\n";
		SetConsoleTextAttribute(hConsole, 11);
		return;
	}
	if (recipient == "all") // ���� ��������� ��� ����
		_message.push_back(Message(_onlineUser->getLogin(), "all", text)); // ������� ��������� ��� ����
	else
		_message.push_back(Message(_onlineUser->getLogin(), getUserByLogin(recipient)->getLogin(), text)); // ������� ��������� ��� ����������� ������������
	cout << "message send -  " << recipient << ":\n ";
}

void ConsoleChat::chatMenu() // ���� ����
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11);
	cout << "Welcome " << _onlineUser->getName() << "\n";
	while (_onlineUser) // ���� ���� ������ ������������
	{
		cout << "Choose an action: \n"
			<< "1-Group chat \n"
			<< "2-Write a message \n"
			<< "3-Exit \n";
		string str;
		char action;

		cin >> str;

		if (!str.empty())
			action = '0';

		action = str[0];

		switch (action)
		{
		case '1':
			openChat(); // ������� ���
			break;
		case '2':
			sendMessage(); // �������� ���������
			break;
		case '3':
			_onlineUser = nullptr; // �����
			break;
		default:
			cout << "Please try again\n";
			break;
		}
	}
}