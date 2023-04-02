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
		<< "1-Зарегестрироваться" << endl
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

			break;

		case 2:

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

