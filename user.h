#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>

class User
{
public:
    /**
     * @brief Construct a new User object
     * 
     * @param uName The username which the user is being created with.
     * @param pWord The password which the user is being created with.
     */
    User(std::string uName, std::string pWord);
    
    /**
     * @brief Destroy the User object
     * 
     */
    ~User();

    /**
     * @brief Get the username.
     * 
     * @return std::string The username.
     */
    std::string getUsername();

    /**
     * @brief Set a new username.
     * 
     * @param newUsername The new username for the user.
     */
    void setUsername(std::string newUsername);
<<<<<<< HEAD
    // bool verifyUsername(std::string uName);
=======

    /**
     * @brief Verifies if the current user is an administrator.
     * 
     * @return true If the current user is an administrator.
     * @return false If the current user is not an administator.
     */
>>>>>>> 2f3706038c86741b1a1e51249f607e5bca5b9c41
    bool getIsAdmin();

    /**
     * @brief Sets the administrator status of the user.
     * 
     * @param newAdmin Whether or not the user should be an administator.
     */
    void setIsAdmin(bool newAdmin);

    /**
     * @brief Get's the user's password.
     * 
     * @return std::string The password.
     */
    std::string getPassword();

    /**
     * @brief Set a new password for the user.
     * 
     * @param newPassword The new password for the user.
     */
    void setPassword(std::string newPassword);

    /**
     * @brief Gets the email addresses associated with the user.
     * 
     * @return std::vector<std::string> The list of the user's email addresses.
     */
    std::vector<std::string> getEmail();

    /**
     * @brief Adds a new email address to the user's account.
     * 
     * @param newEmail The email address to add.
     */
    void addEmail(std::string newEmail);

    /**
     * @brief Removes an email address from a user's account.
     * 
     * @param remEmail The email address to remove.
     */
    void removeEmail(std::string remEmail);

    /**
     * @brief Gets the user's current camera sensitivity.
     * 
     * @return float The sensitivity.
     */
    float getSensitivity();

    /**
     * @brief Sets a new camera sensitivity for the user.
     * 
     * @param newSensitivity The new sensitivity.
     */
    void setSensitivity(float newSensitivity);

    /**
     * @brief Gets whether the user has email alerts on or not.
     * 
     * @return true If they have email alerts on.
     * @return false If they don't have email alerts on.
     */
    bool alertsOn();

    /**
     * @brief Sets if the user wants email alerts on or not.
     * 
     * @param newAlerts Whether they do or not.
     */
    void updateAlerts(bool newAlerts);

    /**
     * @brief Gets if the user's account is locked or not.
     * 
     * @return true If the user's account is locked.
     * @return false If the user's account is unlocked.
     */
    bool getIsLocked();

    /**
     * @brief Sets if the user's account should be locked or not.
     * 
     * @param newIsLocked The new locked status for the user.
     */
    void setIsLocked(bool newIsLocked);
<<<<<<< HEAD
    bool verifyUsername(std::string uName);
    /**
        * @brief Encrypts the user's password for security.
        *
        * @param pword The string password to encrypt.
        * @param key The key which is used for encryption.
        * @return std::string The encrypted passowrd.
        */
       std::string encryptPassword(std::string pword, std::string key);

       /**
        * @brief Since the encryption is its own inverse, the encrypt password method can be used to decrypt the password if the key is known.
        *
        * @param pword The encrypted password.
        * @param key The key which is used for decryption.
        * @return std::string The decrypted
        */
       std::string decryptPassword(std::string pword, std::string key);

=======

    /**
     * @brief Adds a photo taken by the camera to the user's account.
     * 
     * @param photoPath The path to access the photo.
     */
    void addPhoto(std::string photoPath);

    /**
     * @brief Deletes a photo on the user's account.
     * 
     * @param photoPath The path to access the photo for deletion.
     */
    void deletePhoto(std::string photoPath);

    /**
     * @brief Encrypts the user's password for security.
     * 
     * @param pword The string password to encrypt.
     * @param key The key which is used for encryption.
     * @return std::string The encrypted passowrd.
     */
    std::string encryptPassword(std::string pword, std::string key);

    /**
     * @brief Since the encryption is its own inverse, the encrypt password method can be used to decrypt the password if the key is known.
     * 
     * @param pword The encrypted password. 
     * @param key The key which is used for decryption.
     * @return std::string The decrypted
     */
    std::string decryptPassword(std::string pword, std::string key);
>>>>>>> 2f3706038c86741b1a1e51249f607e5bca5b9c41
private:
    /**
     * @brief The user's username.
     * 
     */
    std::string username;

    /**
     * @brief The user's password.
     * 
     */
    std::string password;

    /**
     * @brief The user's administator status.
     * 
     * True for administrators, false for other users.
     * 
     */
    bool isAdmin;

    /**
     * @brief A vector of the emails which the user has added to their account.
     * 
     */
    std::vector<std::string> emails;

    /**
     * @brief The user's camera sensitivity.
     * 
     */
    float sensitivity;

    /**
     * @brief Whether or not the user wants to receive email alerts.
     * 
     */
    bool sendAlert;

    /**
     * @brief Whether or not the user's account is locked.
     * 
     */
    bool isLocked;
<<<<<<< HEAD
=======

    /**
     * @brief A string of file paths to photos the user has stored to their account.
     * 
     */
    std::vector<std::string> photos;
>>>>>>> 2f3706038c86741b1a1e51249f607e5bca5b9c41
};

#endif
