#include "User.h"
#include <ctime>

unsigned int User::countUsers_ = 0;
// User methods
// Constructors
User::User() : name_("\0"), login_("\0"), password_("\0"), countDialogs_(0)
{
	countUsers_++;
}
User::User(std::string& name, std::string& login, std::string& password) :
	name_(name), login_(login), password_(password), countDialogs_(0)
{
	countUsers_++;
}

// Getters
const std::string& User::getName() const
{
	return name_;
}
const std::string& User::getLogin() const
{
	return login_;
}
const std::string& User::getPassword() const
{
	return password_;
}
const int User::getCountDialogs() const																// ������� ���-�� �������� � �������� ������������
{
	return countDialogs_;
}
const int User::getCountUsers() const																// ������� ���-�� ������������������ �������������
{
	return countUsers_;
}

// Setters
void User::setName(const std::string& name)															// ������ ���
{
	name_ = name;
}
void User::setLogin(const std::string& login)														// ������ �����
{
	login_ = login;
}
void User::setPassword(const std::string& password)													// ������ ������
{
	password_ = password;
}

// Others
void User::showDialogs() const																		// ���������� �������, ������� ���� � �������� ������������ + ������ �����
{
	int i = 0;
	for (; i < countDialogs_; i++)
		std::cout << "- " << pDialogs_[i].getNameCompanion() << std::endl;
	std::cout << "- all\n";
}
void User::showMessages() const																		// ������� ��� ������� ��������� ������ ����
{
	if (pGeneralChat_ != nullptr)
		pGeneralChat_->showHistoryMessages();
}
void User::showMessages(const std::string tempName) const															// ������������� ������� ������� ��������� ������� � �������� i
{	
	for (int i(0); i < countDialogs_; i++)
		if(pDialogs_[i].getNameCompanion() == tempName)
			pDialogs_[i].showHistoryMessages();
}
void User::recieveMessage(Dialog::Message& message, std::string recipient)							// ������� ��������� ���������
{
	if (recipient == "all")																			// ���� ���������� �� ������, �� �� �� ��������� ����� All 
	{
		if (pGeneralChat_ == nullptr)																// ���� ������ ��� ������ ���� �������� ������������ �� ��������
			pGeneralChat_ = new Dialog(message, recipient);											// �������� ������ ��� ������� "����� ���" � �������������� � ���������� ����������
		else																					    // �����
			pGeneralChat_->addMessage(message);														// ��������� ��������� � "����� ���"
	}
	else																							// ����� ��������� ��������� ����������
	{
		if (pDialogs_ == nullptr)																	// ���� �������� ��� ���, ��
		{
			pDialogs_ = new Dialog[1];																// �������� ��� ���� ������
			pDialogs_[0].addMessage(message);														// ��������� � ��� ������ ���������
			pDialogs_[0].setNameCompanion(recipient);												// ����� ��������� ����������
			countDialogs_++;																		// ����������� ���-�� �������� �� 1
		}
		else																						// �����(���� ���� ���� ������)
		{
			for (int i(0); i < countDialogs_; i++)													// ���� ���� �� ������ � ��������� �����������
				if (pDialogs_[i].getNameCompanion() == recipient)									// ���� ����, ��
				{
					pDialogs_[i].addMessage(message);												// ��������� � ���� ���������
					break;
				}
				else if ((i + 1) == countDialogs_)													// ���� ������ ������ �� ��� ������, ������ �� ���� ��������, �� ������ ����� ������
				{
					Dialog* oldpDialogs_ = pDialogs_;												// ������ ��������� ���������� ��������� ��� ���������� ������ ��������
					pDialogs_ = new Dialog[countDialogs_ + 1];										// �������� ������ ��� �������� ������ �������� + 1 �����
					for (int i(0); i < countDialogs_; i++)											// ��������� � ����� ���������� ������ ��� ������ ������� �� ��������� ���������� 
						pDialogs_[i] = oldpDialogs_[i];
					delete[] oldpDialogs_;															// ������� ������ ������, �� ������� �������� ��������� ���������
					pDialogs_[countDialogs_].addMessage(message);									// ��������� ��������� � ���������(�����), ������ ��� ��������� ������
					pDialogs_[countDialogs_].setNameCompanion(recipient);							// ����� ��������� ����������
					countDialogs_++;																// ����������� ���-�� �������� �� 1
					break;
				}
		}
	}
}
void User::sendMessageTo(User* user, std::string& ttext, const bool all)
{
	time_t seconds = time(NULL);																	// ���������� ������� ������ �������(��������� ���-�� ������)
	tm* time = localtime(&seconds);																	// ����������� ���-�� ������ � ��������� ������� � ����
	Dialog::Message tempMessage{ ttext, this->getName(), *time };									// �������� ��������� ��������� ���������,�����������,����� ��������
	if (all)																						// ���� all == true, �� ���������� ��������� � ����� ���
		for (int i(0); i < countUsers_; i++)
			user[i].recieveMessage(tempMessage);													// ��������� �������� ������ ������������, ������������������ �� ������ �������� ���������
	else if (user == this)																			// ���� ���������� ��������� ������ ����
		this->recieveMessage(tempMessage, user->getName());
	else
	{
		user->recieveMessage(tempMessage, this->getName());											// ��������� �������� ������������, ������� ��� ������� � �������� ��������� � ����. sendMessageTo
		this->recieveMessage(tempMessage, user->getName());											// ����� ��������� ��������� � ������� ���� ������ ���������
	}

}
User::~User()
{
	countUsers_--;																					// ��������� ���-�� �������������
	delete pGeneralChat_;																			// �������� ������, ���������� ��� ������ ����, ��� �������� ������������ 
	delete[] pDialogs_;																				// �������� ������, ���������� ��� �������� �������� �������� ������������
}