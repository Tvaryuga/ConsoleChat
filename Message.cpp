#include "Message.h"

// Message methods
Dialog::Dialog()
{
	countMessages_ = 0;
}
Dialog::Dialog(const Message message, const std::string nameCompanion) : countMessages_(0)
{
	messages_ = new Message[1];
	*messages_ = message;
	nameCompanion_ = nameCompanion;
	countMessages_++;
}
Dialog::Dialog(Dialog& dialog)
{
	countMessages_ = dialog.getCountMessages();
	delete[] messages_;
	messages_ = new Message[countMessages_];
	for (int i(0); i < countMessages_; i++)
		messages_[i] = dialog[i];
	nameCompanion_ = dialog.getNameCompanion();
}
Dialog& Dialog::operator=(const Dialog& dialog)
{
	if (this == &dialog)
		return *this;
	delete[] messages_;
	countMessages_ = dialog.getCountMessages();
	messages_ = new Message[countMessages_];
	for (int i(0); i < countMessages_; i++)
		messages_[i] = dialog[i];
	nameCompanion_ = dialog.getNameCompanion();
	return  *this;
}
const Dialog::Message& Dialog::operator[](int i) const
{
	return messages_[i];
}
// getter
const int Dialog::getCountMessages() const
{
	return countMessages_;
}
const std::string Dialog::getNameCompanion() const
{
	return nameCompanion_;
}
// setter
void Dialog::setNameCompanion(const std::string name)
{
	nameCompanion_ = name;
}
// other methods
void Dialog::addMessage(Message& message)
{
	if (messages_ == nullptr)
	{
		messages_ = new Message[1];
		*messages_ = message;
	}
	else
	{
		Message* oldmessages = messages_;
		messages_ = new Message[countMessages_ + 1];
		for (int i(0); i < countMessages_; i++)
			messages_[i] = oldmessages[i];
		delete[] oldmessages;
		messages_[countMessages_] = message;
	}
	countMessages_++;
}
void Dialog::showHistoryMessages() const
{
	for (int i(0); i < countMessages_; i++)
	{
		std::cout << asctime(&(messages_[i].timeinfo));
		std::cout << "From: " << messages_[i].from_ << std::endl;
		std::cout << messages_[i].text_ << std::endl << std::endl;
	}
}
Dialog::~Dialog()
{
	delete[] messages_;
}