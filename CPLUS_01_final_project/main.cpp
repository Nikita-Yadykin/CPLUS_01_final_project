#include <iostream>
#include"Console�hat.h"
using namespace std;

int main() {

	setlocale(LC_ALL, "");

	ConsoleChat ConsoleChat;

	ConsoleChat.start();
	
	while (ConsoleChat.�hatStarted())
	{
		ConsoleChat.startMenu();
		
			while (ConsoleChat.getOnlineUser())
			{
				ConsoleChat.chatMenu();
			}
	}

	return 0;

}