#include"Message.h"

Message::Message(const string sender, const string recipient, const string message) : _sender(sender), _recipient(recipient), _message(message)
{
}

string Message::getSender() const
{
	return _sender;
}
string  Message::getRecipient() const
{
	return _recipient;
}
string  Message::getMessage() const
{
	return _message;
}