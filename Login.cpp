/**
 * @file Login.cpp
 * @author Jacob Smith
 * @brief GUI file for the Login page where users enter usernames and passwords
 * @brief This is the first page seen when starting the program
 */

#include "Login.h"
#include <Register.h>
#include <mainwindow.h>
#include <QDesktopWidget>
#include <QApplication>

QWidget *widget;

/**
 * @brief Constructor for the Login class.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @param userlist Reference to the vector of User objects defined in main.cpp
 */
Login::Login(int argc, char *argv[], std::vector<User> &userlist) {
    argc = argc_;
    argv = argv_;
    widget = new QWidget(); //initialize this window
    widget->setWindowTitle("Security System");
    widget->setFixedSize(500, 500);
    std::cout << userlist.size() << std::endl;

    QVBoxLayout *layout = new QVBoxLayout(widget); //create a layout that all widgets call align with
    layout->setAlignment(Qt::AlignCenter);
    //Due to alignment, objects are created in how they appear in descending order

    QLabel *userNameLabel = new QLabel("Username:", widget); //Username label
    userNameLabel->setAlignment(Qt::AlignCenter); //align label with the center
    layout->addWidget(userNameLabel); //add label to the alignment layout
    userNameLabel->show(); //when done, show it

    QLineEdit *userNameTextBox = new QLineEdit(widget);
    userNameTextBox->setFixedSize(300, 20);
    userNameTextBox->setAlignment(Qt::AlignCenter);
    layout->addWidget(userNameTextBox);

    QLabel *passwordLabel = new QLabel("Password:", widget);
    passwordLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(passwordLabel);

    QLineEdit *passwordTextBox = new QLineEdit(widget);
    passwordTextBox->setFixedSize(300, 20);
    passwordTextBox->setAlignment(Qt::AlignCenter);
    passwordTextBox->setEchoMode(QLineEdit::Password); //show all characters as bullet points
    layout->addWidget(passwordTextBox);

    QPushButton *enterButton = new QPushButton("Log in", widget);
    enterButton->setGeometry(150, 400, 80, 20); //QPushButton doesn't recognize alignment
    //for connect() to work, Login class must be of type QObject, which is declared in the header
    //connect(enterButton, &QPushButton::pressed, this, &Login::enterButtonClicked);
    connect(enterButton, &QPushButton::clicked, [this, userlist, userNameTextBox, passwordTextBox]() {
        enterButtonClicked(userNameTextBox->text(), passwordTextBox->text(), userlist);
    });

    QPushButton *registerButton = new QPushButton("Create an account", widget);
    registerButton->setGeometry(275, 400, 110, 20);
    connect(registerButton, &QPushButton::clicked, [this, userlist]() {
        registerButtonClicked(userlist);
		});

    QPushButton* settingButton = new QPushButton("Setting", widget);
    settingButton->setGeometry(410, 10, 70, 25);
    connect(settingButton, &QPushButton::clicked, [this, userNameTextBox, passwordTextBox, userlist]() {
        settingButtonClicked(userNameTextBox->text(), passwordTextBox->text(), userlist);
    });

    widget->setLayout(layout);
    widget->show();

}

/**
 * @brief Destructor for the Login class.
 */
Login::~Login() {}

/**
 * @brief Method that is called when the enterButton is clicked.
 * @brief This will check if entered information is valid and either prompt an error or move to main menu
 * @param username The entered username from the texfield.
 * @param password The entered password from the textfield.
 * @param userList The vector of User objects.
 */
void Login::enterButtonClicked(QString username, QString password, std::vector<User> userList) {
    bool valid = false;
    string userEmail;

    QString userEmailToPass;
    for (int i = 0; i < userList.size(); i++) {
        std::string userString = username.toStdString(); //convert from QString to std::string
        std::string passString = password.toStdString();
        std::string checkPassword = userList[i].decryptPassword(userList[i].getPassword(), "key");
        if (userList[i].getUsername() == userString && checkPassword == passString) {
            valid = true;
            userEmail = userList[i].getEmail()[0];
        }
    }

    if (valid) {
        MainWindow *w = new MainWindow();
        QDesktopWidget *desktop = QApplication::desktop();
        int screenWidth = desktop->width();
        int screenHeight = desktop->height();
        int width = 1200;
        int height = 600;
        int x = (screenWidth - width) / 2;
        int y = (screenHeight - height) / 2;

        w->setFixedSize(QSize(1200,600));
        w->setWindowFlags(Qt::CustomizeWindowHint);
        w->setUserName(username);
        w->setuserEmail(userEmail);
        w->move(x,y);
        w->show();
        widget->close();
    }
    else {
        QMessageBox *invalidBox = new QMessageBox(widget);
        invalidBox->setText("Invalid login credentials");
        invalidBox->setDefaultButton(QMessageBox::Ok);
        invalidBox->setWindowTitle("Error");
        invalidBox->exec();
    }
}

/**
 * @bried Method that is called when the register button is clicked.
 * @brief This will close the current window and open the register window from Register.cpp.
 * @param userlist The vector of User objects.
 */
void Login::registerButtonClicked(std::vector<User> userlist) {
    std::cout << "Register" << std::endl;
    Register registerPage(userlist);
    widget->close();
}

/**
 * @bried Method that is called when the settings button is clicked.
 * @brief This will open the settings window, but keep this window open.
 * @param username The username typed into the text field
 * @param password The password typed into the text field
 * @param userList The vector of User objects.
 */
void Login::settingButtonClicked(QString username, QString password, std::vector<User> userList) {
    bool valid = false;
    for (int i = 0; i < userList.size(); i++) {
        std::string userString = username.toStdString(); //convert from QString to std::string
        std::string passString = password.toStdString();
        std::string checkPassword = userList[i].decryptPassword(userList[i].getPassword(), "key");
        if (userList[i].getUsername() == userString && checkPassword == passString) {
            valid = true;
        }
    }
    QDesktopWidget *desktop = QApplication::desktop();
    int screenWidth = desktop->width();
    int screenHeight = desktop->height();
    int width = 800;
    int height = 600;
    int x = (screenWidth - width) / 2;
    int y = (screenHeight - height) / 2;
    if (valid) {
        Setting settingPage(userList, username.toStdString());
        widget->close();
    } else {
        QMessageBox *invalidBox = new QMessageBox(widget);
        invalidBox->setText("Invalid login credentials");
        invalidBox->setDefaultButton(QMessageBox::Ok);
        invalidBox->setWindowTitle("Error");
        invalidBox->exec();
    }
}
