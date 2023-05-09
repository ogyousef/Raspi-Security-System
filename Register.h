#ifndef REGISTER_H
#define REGISTER_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPainter>
#include <QMessageBox>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "user.h"
#include "Login.h"
#include "json.hpp"

/**
 * @class Register
 * @author So Yoon Kim
 * @brief A Register class allows new user to register.
 *
 * This Register class has a feature for new users to register by providing their personal details,
 * including a unique username, a unique email, and a password of at least 6 characters.
 * New registered user data will be saved to JSON file.
 */

class Register : public QObject {
Q_OBJECT
public:
    /**
	 * @brief Constructs a Register object with the given parameters.
	 * 
	 * 
	 * @param userlist A vector of users
	 */
    Register(std::vector<User>& userlist);

    /**
	 * @brief Destructs the Register object.
	 */
    ~Register();

private:
    /**
	 * @brief Click event for register button. Allows user to register and save user information to json file
	 * 
	 * 
	 * @param email The email text value which is entered by user
	 * @param password The password text value which is entered by user
	 * @param userList A list of current users
	 * 
	 * 
	 * @return void
	 */
    void registerButtonClicked(QString email, QString username, QString password, std::vector<User> userlist);
    /**
	 * @brief Click event for cancel button
	 * @param userList A list of current users
	 * @return void
	 */
    void cancelButtonClicked(std::vector<User> userlist);
    /**
    * @brief A list of current users
    */
    std::vector<User> users_;
};
#endif