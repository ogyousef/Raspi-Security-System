#include "Setting.h"

/// <summary>
/// Author: SoYoon Kim
/// Class: Setting
/// Description: User can change the setting
/// </summary>

QWidget* widgetSetting;

Setting::Setting(std::vector<User>& userlist, std::string username) {

	widgetSetting = new QWidget(); //initialize this window
	widgetSetting->setWindowTitle("Setting");
	widgetSetting->setFixedSize(500, 500);

	QVBoxLayout* layout = new QVBoxLayout(widgetSetting); //create a layout that all widgets call align with
	layout->setAlignment(Qt::AlignCenter);

	//password label v
	QLabel* passwordLabel = new QLabel("To remove your account, please enter your password", widgetSetting);
	passwordLabel->setAlignment(Qt::AlignLeft);
	layout->addWidget(passwordLabel);

	//password input
	QLineEdit* passwordTextBox = new QLineEdit(widgetSetting);
	passwordTextBox->setFixedSize(300, 20);
	passwordTextBox->setAlignment(Qt::AlignLeft);
	passwordTextBox->setEchoMode(QLineEdit::Password); //show all characters as bullet points
	layout->addWidget(passwordTextBox);

	//Register
	QPushButton* deleteAccountButton = new QPushButton("DELETE", widgetSetting);
	deleteAccountButton->setGeometry(150, 400, 80, 20);
	//QPushButton doesn't recognize alignment
	//for connect() to work, Login class must be of type QObject, which is declared in the header
	QObject::connect(deleteAccountButton, &QPushButton::clicked, [this, username, passwordTextBox, userlist]() {
		deleteButtonClicked(QString::fromStdString(username), passwordTextBox->text(), userlist);
		}
	);

	//Cancel 
	QPushButton* cancelButton = new QPushButton("Cancel", widgetSetting);
	cancelButton->setGeometry(275, 400, 110, 20);
	QObject::connect(cancelButton, &QPushButton::clicked, [this, userlist]() {
		cancelButtonClicked(userlist);
		});

	widgetSetting->setLayout(layout);
	widgetSetting->show();
}

Setting::~Setting() {}

void Setting::deleteButtonClicked(QString username, QString password, std::vector<User> userlist) {
	bool valid = false;
	QString emailError = "";
	QString usernameError = "";
	QString passwordError = "";

	int index = 0;

	//Verification process
	for (int i = 0; i < userlist.size(); i++) {
		User tempUser = userlist[i];

		if (tempUser.getUsername() == username.toStdString() && tempUser.getPassword() == password.toStdString()) {
			valid = true;
			break;
		}
		index++;
	}

	//Display message
	QMessageBox* messageBox = new QMessageBox(widgetSetting);
	messageBox->setWindowTitle("Deletion Result");
	messageBox->setDefaultButton(QMessageBox::Ok);

	if (!valid) {
		messageBox->setText("Account Deletion Failed. Please verify your password");
		int ret = messageBox->exec();
	}
	else {
		//File Location
		std::string current_file = __FILE__;
		std::string current_dir = current_file.substr(0, current_file.find_last_of("/\\") + 1);

		std::ifstream infile(current_dir + "users.json");
		if (!infile.is_open()) {
			std::cerr << "Error opening file" << std::endl;
		}
		nlohmann::json data = nlohmann::json::parse(infile);

		// Find the index of the user to delete
		int jsonIndex = -1;
		for (int i = 0; i < data["users"].size(); i++) {
			if (data["users"][i]["username"] == username.toStdString()) {
				jsonIndex = i;
				break;
			}
		}

		// Delete the user if found
		if (jsonIndex >= 0) {
			data["users"].erase(data["users"].begin() + jsonIndex);
		}

		// Update the "totalItems" count
		data["totalItems"] = data["users"].size();

		// Save the modified JSON data back to the file
		std::ofstream output_file(current_dir + "users.json");
		output_file << data.dump(4);

		//Remove from the userlist vector
		userlist.erase(userlist.begin() + index);

		//Show message
		messageBox->setText("Your account is successfully removed.\nYou will be redirected to the Login page");
		messageBox->exec();

        char* argv[1] = { "\0" };
		Login loginPage(0, argv, userlist);
        widgetSetting->hide();
	}
}

//Cancellation event.
void Setting::cancelButtonClicked(std::vector<User> userlist) {
	std::cout << "Cancel button clicked" << std::endl;
    char* argv[1] = { "\0" };
	Login loginPage(0, argv, userlist);
	widgetSetting->hide(); //close this window so new window can be opened
}

