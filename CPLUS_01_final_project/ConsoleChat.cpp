#include"ConsoleСhat.h"
#include<iostream>

bool ConsoleChat::сhatStarted() const
{
	return _сhatStarted;
}

void ConsoleChat::start()
{
	_сhatStarted = true;
}


void ConsoleChat::startMenu()
{
	short action;

	cout << "\tПриветствуем в чате!" << endl << endl
		<< "Для продолжения выберите действие: " << endl << endl
		<< "1-Зарегистрироваться" << endl
		<< "2-Войти в чат" << endl
		<< "3-Выйти из чата" << endl;
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
		_сhatStarted = false;
		break;
	default:
		cout << "Пожалуйста, проверьте правильность вводимых символов" << endl;
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


	cout << "Пожалуйста, укажите логин: ";
	cin >> login;
	cout << "Введите пароль: ";
	cin >> password;

	_onlineUser = getUserByLogin(login);

	if (_onlineUser == nullptr || password != _onlineUser->getPassword())
		_onlineUser = nullptr;
	cout << "Неверный логин или пароль, повторите попытку" << endl; // Срабатывает в любом случае




}

void ConsoleChat::signUp()
{
	string login;
	string password;
	string name;
	cout << "Пожалуйста, укажите свой логин: ";
	cin >> login;
	cout << "Придумайте надежный пароль: ";
	cin >> password;
	cout << "Укажите свое имя, которое будут видеть другие пользователи: ";
	cin >> name;

	User user = User(login, password, name);
	_user.push_back(user);
	_onlineUser = make_shared<User>(user);
	cout << endl << "Поздравляем! Вы успешно зарегистрированы!" << endl;
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
	cout << "Добро пожаловать " << _onlineUser->getName() << endl;
	while (_onlineUser)
	{
		cout << "Выберите действие: " << endl
			<< "1-Групповой чат" << endl
			<< "2-Написать личное сообщение" << endl
			<< "3-Выйти" << endl;
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
			cout << "Пожалуйста, повторите попытку" << endl;
			break;
		}
	}
}

