#ifndef Setting_H
#define Setting_H

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
 * @class Setting
 * @brief A Setting class allows user to remove their account.
 * @author So Yoon Kim
 * 
 * The user must provide their password once again for verification purposes.
 * User data will be removed from the JSON file
 */

class Setting : public QObject {
	Q_OBJECT
public:
	/**
	 * @brief Setting Constructor
	 * @param userlist A list of current users
	 * @param username Current user's username
	 */
	Setting(std::vector<User>& userlist, std::string username);
	/**
	 * @brief Setting Destructor
	 */
	~Setting();

private:
	/**
	 * @brief Current user's username
	 */
	std::string username;
	/**
	 * @brief Click event for delete button. This removes user from the userlist and user information will be removed from json file
	 * @param username The entered username from the textbox
	 * @param password The entered password from the textbox
	 * @param userList A list of current users
	 * @return Void
	 */
	void deleteButtonClicked(QString username, QString password, std::vector<User> userlist);
	/**
	 * @brief Click event for cancel button. Once it is clicked, the user will be redirect to Login page
	 * @param userList A list of current users
	 * @return void
	 */
	void cancelButtonClicked(std::vector<User> userlist);
	//std::vector<User> users_;
};
#endif
