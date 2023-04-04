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
void ConsoleChat::openChat() const

{
	std::string sender, recipient;
	std::cout << " -----------chat-------  \n";
	for (auto& mess : _message)
	{
		if (_onlineUser->getLogin() == mess.getSender() || _onlineUser->getLogin() == mess.getRecipient() || mess.getRecipient() == "all")
		{
			sender = (_onlineUser->getLogin() == mess.getSender()) ? "me" : getUserByLogin(mess.getSender())->getName();

			if (mess.getRecipient() == "all")
			{
				recipient = "all";
			}
			else
			{
				recipient = (_onlineUser->getLogin() == mess.getRecipient()) ? "me" : getUserByLogin(mess.getRecipient())->getName();
			}
			std::cout << "message from " << sender << ": to " << recipient << "\n";
			std::cout << " - " << mess.getLetter() << " - \n";
		}
	}
	std::cout << "---------------------------\n";
};
void ConsoleChat::sendMessage()
{
	std::string recipient, text;
	std::cout << "to (name or all) - ";
	std::cin >> recipient;
	std::cout << "text - ";
	std::cin.ignore();
	getline(std::cin, text);

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
			openChat();
			break;

		case 2:
			sendMessage();
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

