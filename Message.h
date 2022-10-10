#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <ctime>

class Dialog
{
public:
	struct Message { std::string text_; std::string from_; tm timeinfo; };
private:
	std::string nameCompanion_;
	Message* messages_ = nullptr;
	unsigned int countMessages_;
public:
	Dialog();
	Dialog(const Message, const std::string nameCompanion = "all");
	Dialog(Dialog&);
	const std::string getNameCompanion() const;
	void setNameCompanion(const std::string);
	const Message& operator[](int) const;
	const int getCountMessages() const;
	void addMessage(Message&);
	void showHistoryMessages() const;

	Dialog& operator=(const Dialog&);
	~Dialog();
};