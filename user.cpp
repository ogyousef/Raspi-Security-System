#include "user.h"

/**
 * @brief Construct a new User:: User object
 *
 * @param uName The username which the user is being created with.
 * @param pWord The password which the user is being created with.
 */
User::User(std::string uName, std::string pWord) {
    username = uName;
    password = pWord;
    isAdmin = false;
    sensitivity = 1;
    sendAlert = false;
    isLocked = false;
}

/**
 * @brief Destroy the User:: User object
 *
 */
User::~User() {}

std::string User::getUsername() {
    return username;
}

/**
 * @brief setter for the username variable
 *
 * @param newUsername The new username for the user.
 */
void User::setUsername(std::string newUsername) {
    username = newUsername;
}

/**
 * @brief Verifies if the current user is an administrator.
 *
 * @return true If the current user is an administator.
 * @return false If the current user is not an administrator.
 */
bool User::getIsAdmin() {
    return isAdmin;
}

/**
 * @brief Sets the administrator status of the user.
 *
 * @param newAdmin Whether or not the user should be an administator.
 */
void User::setIsAdmin(bool newAdmin) {
    isAdmin = newAdmin;
}

/**
 * @brief Gets the user's password.
 *
 * @return std::string The password.
 */
std::string User::getPassword() {
    return password;
}

/**
 * @brief Sets the user's password.
 *
 * @param newPassword Sets the user's new password.
 */
void User::setPassword(std::string newPassword) {
    password = newPassword;
}

/**
 * @brief Gets the email addresses associated with the user.
 *
 * @return std::vector<std::string> The list of the user's email addresses.
 */
std::vector<std::string> User::getEmail() {
    return emails;
}

/**
 * @brief Adds a new email address to the user's account.
 *
 * @param newEmail The email address to add.
 */
void User::addEmail(std::string newEmail) {
    emails.push_back(newEmail);
}

/**
 * @brief Gets the user's current camera sensitivity.
 *
 * @return float The sensitivity.
 */
float User::getSensitivity() {
    return sensitivity;
}

/**
 * @brief Sets a new camera sensitivity for the user.
 *
 * @param newSensitivity The new sensitivity.
 */
void User::setSensitivity(float newSensitivity) {
    sensitivity = newSensitivity;
}

/**
 * @brief Gets whether the user has email alerts on or not.
 *
 * @return true If they have email alerts on.
 * @return false If they don't have email alerts on.
 */
bool User::alertsOn() {
    return sendAlert;
}

/**
 * @brief Sets if the user wants email alerts on or not.
 *
 * @param newAlerts Whether they do or not.
 */
void User::updateAlerts(bool newAlerts) {
    sendAlert = newAlerts;
}

/**
 * @brief Gets if the user's account is locked or not.
 *
 * @return true If the user's account is locked.
 * @return false If the user's account is unlocked.
 */
bool User::getIsLocked() {
    return isLocked;
}

/**
 * @brief Sets if the user's account should be locked or not.
 *
 * @param newIsLocked The new locked status for the user.
 */
void User::setIsLocked(bool newIsLocked) {
    isLocked = newIsLocked;
}

/**
 * @brief Adds a photo taken by the camera to the user's account.
 *
 * @param photoPath The path to access the photo.
 */
void User::addPhoto(std::string photoPath) {
    photos.push_back(photoPath);
}

/**
 * @brief Deletes a photo on the user's account.
 *
 * @param photoPath The path to access the photo for deletion.
 */
void User::deletePhoto(std::string photoPath) {
    for (std::vector<std::string>::iterator i = photos.begin(); i != photos.end(); ++i) {
        if (*i == photoPath) {
            photos.erase(i);
            break;
        }
    }
}

/**
 * @brief Encrypts the user's password for security.
 *
 * @param pword The string password to encrypt.
 * @param key The key which is used for encryption.
 * @return std::string The encrypted passowrd.
 */
std::string User::encryptPassword(std::string pword, std::string key) {
    std::string encrypted = pword;
    for (size_t i = 0; i < pword.size(); ++i) {
        encrypted[i] = pword[i] ^ key[i % key.size()];
    }
    return encrypted;
}

/**
 * @brief Since the encryption is its own inverse, the encrypt password method can be used to decrypt the password if the key is known.
 *
 * @param pword The encrypted password.
 * @param key The key which is used for decryption.
 * @return std::string The decrypted password.
 */
std::string User::decryptPassword(std::string pword, std::string key) {
    return encryptPassword(pword, key);
}