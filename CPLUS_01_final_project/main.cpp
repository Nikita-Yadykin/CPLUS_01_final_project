#include"Console—hat.h"


int main() {

	

	ConsoleChat ConsoleChat;

	ConsoleChat.start();
	
	while (ConsoleChat.ÒhatStarted())
	{
		ConsoleChat.startMenu();
		
			while (ConsoleChat.getOnlineUser())
			{
				ConsoleChat.chatMenu();
			}
	}

	return 0;

}