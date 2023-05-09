#include "Register.h"

/// Class: Registration Class
/// Description: User can either register or cancel

QWidget* widgetRegister;

//Registeration method
Register::Register(std::vector<User>& userlist) {
    users_ = userlist;

    widgetRegister = new QWidget(); //initialize this window
    widgetRegister->setWindowTitle("Register New User");
    widgetRegister->setFixedSize(500, 500);

    QVBoxLayout* layout = new QVBoxLayout(widgetRegister); //create a layout that all widgets call align with
    layout->setAlignment(Qt::AlignCenter);
    //Due to alignment, objects are created in how they appear in descending order

    //Email Label
    QLabel* emailLabel = new QLabel("Email:", widgetRegister);
    emailLabel->setAlignment(Qt::AlignLeft);
    layout->addWidget(emailLabel);
    emailLabel->show();

    //Email input
    QLineEdit* emailTextBox = new QLineEdit(widgetRegister);
    emailTextBox->setFixedSize(300, 20);
    emailTextBox->setAlignment(Qt::AlignLeft);
    layout->addWidget(emailTextBox);

    //username label
    QLabel* usernameLabel = new QLabel("Username:", widgetRegister);
    usernameLabel->setAlignment(Qt::AlignLeft);
    layout->addWidget(usernameLabel);
    usernameLabel->show();

    //username input
    QLineEdit* usernameTextBox = new QLineEdit(widgetRegister);
    usernameTextBox->setFixedSize(300, 20);
    usernameTextBox->setAlignment(Qt::AlignLeft);
    layout->addWidget(usernameTextBox);

    //password label
    QLabel* passwordLabel = new QLabel("Password (minimum 6 characters):", widgetRegister);
    passwordLabel->setAlignment(Qt::AlignLeft);
    layout->addWidget(passwordLabel);

    //password input
    QLineEdit* passwordTextBox = new QLineEdit(widgetRegister);
    passwordTextBox->setFixedSize(300, 20);
    passwordTextBox->setAlignment(Qt::AlignLeft);
    passwordTextBox->setEchoMode(QLineEdit::Password); //show all characters as bullet points
    layout->addWidget(passwordTextBox);

    //Register
    QPushButton* registerButton = new QPushButton("Register", widgetRegister);
    registerButton->setGeometry(150, 400, 80, 20);
    //QPushButton doesn't recognize alignment
    //for connect() to work, Login class must be of type QObject, which is declared in the header
    QObject::connect(registerButton, &QPushButton::clicked, [this, emailTextBox, usernameTextBox, passwordTextBox, userlist]() {
                         registerButtonClicked(emailTextBox->text(), usernameTextBox->text(), passwordTextBox->text(), userlist);
                     }
    );

    //Cancel
    QPushButton* cancelButton = new QPushButton("Cancel", widgetRegister);
    cancelButton->setGeometry(275, 400, 110, 20);
    QObject::connect(cancelButton, &QPushButton::clicked, [this, userlist]() {
        cancelButtonClicked(userlist);
    });

    widgetRegister->setLayout(layout);
    widgetRegister->show();
}

//Dtor
Register::~Register() {}

//register button click event
void Register::registerButtonClicked(QString email, QString username, QString password, std::vector<User> userlist) {
    bool valid = true;
    QString emailError = "";
    QString usernameError = "";
    QString passwordError = "";

    //Verification process
    for (int i = 0; i < userlist.size(); i++) {
        User tempUser = userlist[i];
        for (int j = 0; j < tempUser.getEmail().size(); j++) {
            if (tempUser.getEmail()[j] == email.toStdString()) {
                emailError = "\nThis email is taken. Please enter different email.";
                valid = false;
                break;
            }
        }
        if (username.toStdString() == tempUser.getUsername()) {
            usernameError = "\nThis username is taken. Please enter different username.";
            valid = false;
        }
        if (password.toStdString().length() < 6) {
            passwordError = "\nPassword must be at least 6 characters";
            valid = false;
        }
    }

    //Display message
    QMessageBox* registerBox = new QMessageBox(widgetRegister);
    registerBox->setWindowTitle("Registration Result");
    registerBox->setDefaultButton(QMessageBox::Ok);

    if (!valid) {
        registerBox->setText("Registration Failed." + emailError + usernameError + passwordError);
        int ret = registerBox->exec();
    }
    else {
        registerBox->setText("Registration Successful");

        //Add to list
        std::string encrypted = password.toStdString();
        std::string key = "key";
        for (size_t i = 0; i < password.toStdString().size(); ++i) {
            encrypted[i] = password.toStdString()[i] ^ key[i % key.size()];
        }

        User newUser = User(username.toStdString(), encrypted);
        newUser.addEmail(email.toStdString());
        userlist.push_back(newUser);

        //File Location
        std::string current_file = __FILE__;
        std::string current_dir = current_file.substr(0, current_file.find_last_of("/\\") + 1);

        //open users.json
        std::ifstream infile(current_dir + "users.json");
        if (!infile.is_open()) {
            std::cerr << "Error opening file" << std::endl;
        }
        //Add new user
        nlohmann::json data = nlohmann::json::parse(infile);
        nlohmann::json nUser = {
                {"username", username.toStdString()},
            {"password", newUser.encryptPassword(password.toStdString(), "key")},
                {"emails", {email.toStdString()}},
                {"admin", false},
                {"sensitivity", 2},
                {"sendAlerts", true},
                {"photos", {""}}
        };
        data["users"].push_back(nUser);
        data["totalItems"] = data["users"].size();
        std::ofstream output_file(current_dir + "users.json");
        output_file << data.dump(4);

        char* argv[1] = { "\0" };
        Login loginPage(0, argv, userlist);
        widgetRegister->hide();
    }
}

//Cancellation event.
void Register::cancelButtonClicked(std::vector<User> userlist) {
    std::cout << "Cancel button clicked" << std::endl;
    char* argv[1] = { "\0" };
    Login loginPage(0, argv, userlist);
    widgetRegister->hide(); //close this window so new window can be opened
}
