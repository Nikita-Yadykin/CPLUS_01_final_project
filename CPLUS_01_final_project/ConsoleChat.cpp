#include"Console—hat.h"
#include<iostream>

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
	
	cout << "\tœË‚ÂÚÒÚ‚ÛÂÏ ‚ ˜‡ÚÂ!" << endl<<endl
		<< "ƒÎˇ ÔÓ‰ÓÎÊÂÌËˇ ‚˚·ÂËÚÂ ‰ÂÈÒÚ‚ËÂ: " << endl<<endl
		<< "1-«‡Â„ÂÒÚËÓ‚‡Ú¸Òˇ" << endl
		<< "2-¬ÓÈÚË ‚ ˜‡Ú" << endl
		<< "3-¬˚ÈÚË ËÁ ˜‡Ú‡" << endl;
}