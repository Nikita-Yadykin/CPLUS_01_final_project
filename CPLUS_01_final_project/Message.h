#pragma once
#include"User.h"

class Message
{
public:

	Message(const string sender, const string recipient, const string message);
	~Message() = default;

	string getSender() const;
	string getRecipient() const;
	string getMessage() const;

private:

	const string _sender;
	const string _recipient;
	const string _message;

};
