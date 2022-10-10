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
const int User::getCountDialogs() const																// вернуть кол-во диалогов у текущего пользователя
{
	return countDialogs_;
}
const int User::getCountUsers() const																// вернуть кол-во зарегестрированных пользователей
{
	return countUsers_;
}

// Setters
void User::setName(const std::string& name)															// задать имя
{
	name_ = name;
}
void User::setLogin(const std::string& login)														// задать логин
{
	login_ = login;
}
void User::setPassword(const std::string& password)													// задать пароль
{
	password_ = password;
}

// Others
void User::showDialogs() const																		// Показывает диалоги, которые есть у текущего пользователя + кнопка назад
{
	int i = 0;
	for (; i < countDialogs_; i++)
		std::cout << "- " << pDialogs_[i].getNameCompanion() << std::endl;
	std::cout << "- all\n";
}
void User::showMessages() const																		// Функция все выводит сообщения общего чата
{
	if (pGeneralChat_ != nullptr)
		pGeneralChat_->showHistoryMessages();
}
void User::showMessages(const std::string tempName) const															// Перегруженная функция выводит сообщения диалога с индексом i
{	
	for (int i(0); i < countDialogs_; i++)
		if(pDialogs_[i].getNameCompanion() == tempName)
			pDialogs_[i].showHistoryMessages();
}
void User::recieveMessage(Dialog::Message& message, std::string recipient)							// Функция получения сообщения
{
	if (recipient == "all")																			// Если получатель не указан, то он по умолчанию равен All 
	{
		if (pGeneralChat_ == nullptr)																// Если память для общего чата текущего пользователя не выделена
			pGeneralChat_ = new Dialog(message, recipient);											// Выделяем память для диалога "общий чат" и инициализируем её переданным сообщением
		else																					    // Иначе
			pGeneralChat_->addMessage(message);														// добавляем сообщение в "общий чат"
	}
	else																							// Иначе добавляем сообщение получателю
	{
		if (pDialogs_ == nullptr)																	// Если диалогов ещё нет, то
		{
			pDialogs_ = new Dialog[1];																// выделяем под него память
			pDialogs_[0].addMessage(message);														// добавляем в наш диалог сообщение
			pDialogs_[0].setNameCompanion(recipient);												// затем добавляем получателя
			countDialogs_++;																		// Увеличиваем кол-во диалогов на 1
		}
		else																						// Иначе(есть хоть один диалог)
		{
			for (int i(0); i < countDialogs_; i++)													// Ищем есть ли диалог с указанным получателем
				if (pDialogs_[i].getNameCompanion() == recipient)									// Если есть, то
				{
					pDialogs_[i].addMessage(message);												// добавляем в него сообщение
					break;
				}
				else if ((i + 1) == countDialogs_)													// Если нужный диалог не был найден, пройдя по всем диалогам, то создаём новый диалог
				{
					Dialog* oldpDialogs_ = pDialogs_;												// Создаём временную переменную указатель для сохранения старых диалогов
					pDialogs_ = new Dialog[countDialogs_ + 1];										// Выделяем память для хранения старых диалогов + 1 новый
					for (int i(0); i < countDialogs_; i++)											// Сохраняем в новую выделенную память все старые деалоги из временной переменной 
						pDialogs_[i] = oldpDialogs_[i];
					delete[] oldpDialogs_;															// Удаляем старую память, на которую указывал временный указатель
					pDialogs_[countDialogs_].addMessage(message);									// Добавляем сообщение в последний(новый), только что созданный диалог
					pDialogs_[countDialogs_].setNameCompanion(recipient);							// Также добавляем получателя
					countDialogs_++;																// Увеличиваем кол-во диалогов на 1
					break;
				}
		}
	}
}
void User::sendMessageTo(User* user, std::string& ttext, const bool all)
{
	time_t seconds = time(NULL);																	// Встроенная функция замера времени(получение кол-ва секунд)
	tm* time = localtime(&seconds);																	// преобразуем кол-во секунд в структуру времени и даты
	Dialog::Message tempMessage{ ttext, this->getName(), *time };									// Создание временной структуры сообщение,отправителя,время отправки
	if (all)																						// Если all == true, то отправляем сообщение в общий чат
		for (int i(0); i < countUsers_; i++)
			user[i].recieveMessage(tempMessage);													// сообщение получает каждый пользователь, зарегестрированный на момент отправки сообщения
	else if (user == this)																			// Если отправляем сообщение самому себе
		this->recieveMessage(tempMessage, user->getName());
	else
	{
		user->recieveMessage(tempMessage, this->getName());											// сообщение получает пользователь, который был передан в качестве параметра в функ. sendMessageTo
		this->recieveMessage(tempMessage, user->getName());											// также сохраняем сообщение в историю чата автора сообщения
	}

}
User::~User()
{
	countUsers_--;																					// уменьшаем кол-во пользователей
	delete pGeneralChat_;																			// удаление памяти, выделенной для общего чата, для текущего пользователя 
	delete[] pDialogs_;																				// удаление памяти, выделенной для хранения диалогов текущего пользователя
}