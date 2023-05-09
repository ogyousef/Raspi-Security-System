#include "main.h"
/**
*@file main.h
*@brief Main program file for the security system application.
*/

/**
*
*@brief Main function of the security system application.
*@param argc Argument count.
*@param argv Argument vector.
*@return Exit code of the application.
*/

int main(int argc, char *argv[])
{
    User *currentUser = new User("noUser", "noPass");
    std::vector<User> users;
    QString currentUserx;

    std::string current_file = __FILE__;
    std::string current_dir = current_file.substr(0, current_file.find_last_of("/\\") + 1);

    //open users.json
    std::ifstream infile(current_dir+"users.json");
        if (!infile.is_open()) {
            std::cerr << "Error opening file" << std::endl;
            return 1;
        }

        std::string file_contents((std::istreambuf_iterator<char>(infile)),
                                  (std::istreambuf_iterator<char>()));
        nlohmann::json json_object = nlohmann::json::parse(file_contents); //json object to hold the json file

        //read users.json and fill vector of users
        for (int i = 0; i < json_object["totalItems"]; i++) {
            std::string username = json_object["users"][i]["username"];
            std::string password = json_object["users"][i]["password"];

            bool isAdmin = json_object["users"][i]["admin"];
            int sensitivity = json_object["users"][i]["sensitivity"];
            bool sendAlerts = json_object["users"][i]["sendAlerts"];
            User *newUser = new User(username, password);
            newUser->setIsAdmin(isAdmin);
            newUser->setSensitivity(sensitivity);
            newUser->addEmail(json_object["users"][i]["emails"][0]);
            users.push_back(*newUser);
        }
;
    QApplication a(argc, argv);
    Login loginPage(argc, argv, users);
    return a.exec();
}
