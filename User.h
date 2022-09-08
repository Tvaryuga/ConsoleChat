#pragma once
#include <iostream>
#include "Message.h"

class User
{
	std::string name_;
	std::string password_;
	std::string login_;
	std::string* contacts_;
	Messages* messages_;
public:
	User();
	User(std::string name, std::string password, std::string email);
	const std::string& getName() const;
	const std::string& getLogin() const;
	const std::string& getPassword() const;
	void showChats() const;
	const int chooseDialog() const;
	void showMessages(const int i) const;
	void setName();
	void setLogin();
	void setPassword();
	void addMessage(const Messages& message);
	void sendMessage(User& user);
	Messages editMessage();
	friend std::ostream& operator<<(std::ostream& os, const User& user);
	~User();
};