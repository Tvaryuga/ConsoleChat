#pragma once
#include <iostream>

class Messages
{
public:
	struct TextTime { std::string text_; int hours_; int min_; };
private:
	std::string from_;
	TextTime* pdialog_ = nullptr;
public:
	Messages() = default;
	Messages(const TextTime dialog, const std::string& from);
	const std::string& getFrom() const;
	void showDialog() const;
	void editText();
	void deleteMessage();
	~Messages();
};