#include"ConsoleÑhat.h"


auto main() -> int
{
	ConsoleChat ConsoleChat;

	ConsoleChat.start();

	while (ConsoleChat.ñhatStarted())
	{
		ConsoleChat.startMenu();

		while (ConsoleChat.getOnlineUser())
		{
			ConsoleChat.chatMenu();
		}
	}

	return 0;

}