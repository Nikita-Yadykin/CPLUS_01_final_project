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
	
	cout << "\t������������ � ����!" << endl<<endl
		<< "��� ����������� �������� ��������: " << endl<<endl
		<< "1-������������������" << endl
		<< "2-����� � ���" << endl
		<< "3-����� �� ����" << endl;
}