#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include "Message.h"

class User
{
	std::string name_;
	std::string login_;
	std::string password_;
	Dialog* pDialogs_ = nullptr;
	Dialog* pGeneralChat_ = nullptr;
	static unsigned int countUsers_;
	unsigned int countDialogs_;
public:
	User();
	User(std::string&, std::string&, std::string&);
	const std::string& getName() const;
	const std::string& getLogin() const;
	const std::string& getPassword() const;
	const int getCountDialogs() const;
	const int getCountUsers() const;
	void showDialogs() const;
	void showMessages() const;
	void showMessages(const std::string tempName) const;
	void setName(const std::string&);
	void setLogin(const std::string&);
	void setPassword(const std::string&);
	void recieveMessage(Dialog::Message&, std::string recipient = "all");
	void sendMessageTo(User*, std::string&, const bool all = false);
	~User();
};