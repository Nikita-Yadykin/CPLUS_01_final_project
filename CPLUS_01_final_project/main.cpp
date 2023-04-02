#include <iostream>
#include"Console—hat.h"
using namespace std;

int main() {

	setlocale(LC_ALL, "");

	ConsoleChat ConsoleChat;

	ConsoleChat.start();

	while (ConsoleChat.ÒhatStarted())
	{
		ConsoleChat.startMenu();
		return 0;
	}

	return 0;

}