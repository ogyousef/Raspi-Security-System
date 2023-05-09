#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPainter>
#include <QMessageBox>
#include <iostream>
#include "Register.h"
#include "user.h"
#include "Setting.h"

/**
 * @class Login
 * @brief Provides functionality for the login screen.
 *
 * The Login class provides a graphical user interface for entering a username and password
 * to access the security system.The class handles user authentication by checking the entered
 * username and password against a list of registered users.
 */
class Login : public QObject {
	Q_OBJECT
public:
    /**
	 * @brief Constructs a Login object with the given parameters.
	 * @param argc The number of command-line arguments.
	 * @param argv The array of command-line arguments.
	 * @param users A vector of User objects representing the registered users.
	 */
    Login(int argc, char* argv[], std::vector<User>& users);

    /**
	 * @brief Destructs the Login object.
	 */
	~Login();

private:
    /**
	 * @brief Handles the event when the Enter button is clicked.
	 * @param username The entered username.
	 * @param password The entered password.
	 * @param userList A vector of User objects representing the registered users.
	 */
	void enterButtonClicked(QString username, QString password, std::vector<User> userList);

    /**
	 * @brief Handles the event when the Register button is clicked.
	 * @param userList A vector of User objects representing the registered users.
	 */
	void registerButtonClicked(std::vector<User> userlist);

    /**
     * @brief Handles the event when the Settings button is clicks
     * @param username The entered username
     * @param password The entered password
     * @param userList A vector of User objects representing the registered users.
     */
    void settingButtonClicked(QString username, QString password, std::vector<User> userList);

    /**
	 * @brief A vector of User objects representing the registered users.
	 */
    std::vector<User> users_;

    /**
	 * @brief A vector of User objects representing the registered users.
	 */
    int argc_;

    /**
	 * @brief An array of command-line arguments.
	 */
    char* argv_[];
};
#endif
