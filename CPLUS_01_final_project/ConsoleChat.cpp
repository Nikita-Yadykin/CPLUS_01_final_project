#include"Console�hat.h"
#include<iostream>

bool ConsoleChat::�hatStarted() const
{
	return _�hatStarted;
}

void ConsoleChat::start()
{
	_�hatStarted = true;
}


void ConsoleChat::startMenu()
{
	short action;

	cout << "\t������������ � ����!" << endl << endl
		<< "��� ����������� �������� ��������: " << endl << endl
		<< "1-������������������" << endl
		<< "2-����� � ���" << endl
		<< "3-����� �� ����" << endl;
	cin >> action;
	switch (action)
	{
	case 1:
		signUp();
		break;
	case 2:
		logIn();
		break;
	case 3:
		_�hatStarted = false;
		break;
	default:
		cout << "����������, ��������� ������������ �������� ��������" << endl;
		break;
	}

}

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


	cout << "����������, ������� �����: ";
	cin >> login;
	cout << "������� ������: ";
	cin >> password;

	_onlineUser = getUserByLogin(login);

	if (_onlineUser == nullptr || password != _onlineUser->getPassword())
		_onlineUser = nullptr;
	cout << "�������� ����� ��� ������, ��������� �������" << endl; // ����������� � ����� ������




}

void ConsoleChat::signUp()
{
	string login;
	string password;
	string name;
	cout << "����������, ������� ���� �����: ";
	cin >> login;
	cout << "���������� �������� ������: ";
	cin >> password;
	cout << "������� ���� ���, ������� ����� ������ ������ ������������: ";
	cin >> name;

	User user = User(login, password, name);
	_user.push_back(user);
	_onlineUser = make_shared<User>(user);
	cout << endl << "�����������! �� ������� ����������������!" << endl;
}

void ConsoleChat::chatMenu()
{
	short operation;
	cout << "����� ���������� " << _onlineUser->getName() << endl;
	while (_onlineUser)
	{
		cout << "�������� ��������: " << endl
			<< "1-��������� ���" << endl
			<< "2-�������� ������ ���������" << endl
			<< "3-�����" << endl;
		cin >> operation;
		switch (operation)
		{
		case 1:

			break;

		case 2:

			break;

		case 3:
			_onlineUser = nullptr;
			break;

		default:
			cout << "����������, ��������� �������" << endl;
			break;
		}
	}
}

