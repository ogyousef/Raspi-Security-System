#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <pigpio.h>
#include <chrono>
#include <thread>
#include "mysystem.h"
#include <filesystem>
#include "history.h"
#include <QApplication>
#include <QDesktopWidget>

using namespace std;

/**
*@brief Take a photo using the Raspberry Pi camera and save it to a file.
*This function takes a photo using the Raspberry Pi camera and saves it to the specified file path.
*@param path The file path where the photo will be saved.
**/

void Camera::takePhoto(string path) {
  picPath = path;
  string command = "raspistill -n -t 3 -o ";
  string finalC = command + path;
  const char* toPass = finalC.c_str();
  system(toPass);
}

/**
 * @brief Get the current system time and format it as a string.
 * 
 * @return A string representing the current system time in the format "YYYY-MM-DD-HH:MM:SS".
 */

string Camera::time2x(){
    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);
    string sss;
    char buffer[80];
    std::strftime(buffer, 80, "%Y-%m-%d-%H:%M:%S", std::localtime(&time));
    std::string time_string = buffer;
    sss = time_string;
    return sss;
}
/**
 * @brief Take a video and save it to the specified path.
 * 
 * @param path The path where the video should be saved.
 */
void Camera::takeVideo(string path) {
  picPath = path;
  string command = "raspivid -n -t 8000 -o ";
  string finalC = command + path;
  const char* toPass = finalC.c_str();
  system(toPass);
}

void Camera::LiveView(){
    QDesktopWidget *desktop = QApplication::desktop();
     int screenWidth = desktop->width();
     int screenHeight = desktop->height();
        int width = 750;
        int height = 500;
        int x = (screenWidth - width)  / 2 ;
        int y = (screenHeight - height) / 2;
        cout << x << y;
//  system("raspistill -p 900,300,750,500 -t 9000 -o /dev/null");
  string commad = "raspistill -p "+ to_string(x) + "," + to_string(y) + "," +to_string(width) + "," +to_string(height) + " -t 9000 -o /dev/null";
  system(commad.c_str());

}



/**
*@brief Initializes the sensor by calling gpioInitialise()
*@return True if initialization is successful, false otherwise
*/
bool Sensor::Initialize(){
  if( gpioInitialise() < 0 ){
    return false;
  }
  else return true;
}

/**
*@brief This function reads the output of the sensor.
*It initializes the sensor and reads the output pin 12. If initialization fails, it prints an error message and returns 0.
**/

int Sensor::sensorOutput(){
  if (Initialize() == true) {
    return gpioRead(12);
  }
  else{
    cout << "Sensor is Off" << endl;
    return 0;
  }
}


/**
*@brief This function turns alarm to On;
**/
void System::alarmsOn(){
  alarm = true;
}
/**
*@brief This function turns alarm to Off;
**/
void System::alarmsOff(){
  alarm = false;

}

/**
*@brief Arms the system with the specified sensor length, username and user email.
*@param sensorLeng The sensor length to arm the system with.
*@param userNamex The username of the user arming the system.
*@param userEmailx The email of the user arming the system.
*/

void System::armSystem(int sensorLeng, string userNamex, string userEmailx){
  createDir(userNamex);
  sensorCoolDown = sensorLeng;
  armed = true;
  userName = userNamex;
  userEmail = userEmailx;
  mediaPath();

}

/**
*@brief Sets the media type for the system.
*@param Type Integer representing the type of media to be used (0 for picture, 1 for video).
*@return void
*/

void System::MediaType(int Type){
    if (Type == 0){
        videoOn = 0;
    }
    else{
        videoOn =1;
    }
}


/**
*Takes a snapshot using the camera and saves it to the media path with the extension .jpg.
*@return void
*/

void System::snapShot(){
 camera.takePhoto(mediaPath().append(".jpg"));
}

/**
 * @brief Disarms the system
 */

void System::disarmSystem(){
  armed = false;
    printf("SYSTEM off");
}

/**
 * @brief Checks if motion is detected by the sensor
 * 
 * @return true if motion is detected, false otherwise
 */

bool System::motionDetected(){
  if(sensor.sensorOutput() > 0){
    return true;
  }
  else{
    return false;
  }
}

/**
 * @brief Initiates the live view feature of the camera
 * 
 */

void System::LiveView(){
  camera.LiveView();
}


/**
*@brief Sends an email notification to the user with the given path to the media file.
*The function retrieves the current working directory path and appends the filename to it.
*Then, it calls a shell script to send an email with the media file as an attachment to the user's email.
*@param path The path to the media file.
*@return void
*/

void System::sendAlarm(string path){
    char cwd[PATH_MAX];
    string cwdtoString;

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        std::cout << "Current directory path: " << cwd << std::endl;
            cwdtoString = cwd;
                 std::cout << "CTESTTT: " << cwd << std::endl;
      } else {
        //std::cerr << "Error: Could not get current directory path." << std::endl;
      }
    cout << userEmail;
    string command = cwdtoString + "/send-email.sh "+ path + " TESt " + userEmail ;
    system(command.c_str());
}


/**
*@brief Sets the username of the system.
*@param givingUser The username to be set.
*/

void System::setUserName(string givingUser){
    userName = givingUser;

}



/**
*@brief This function generates the path for the media to be stored in.
*@return string
*/

string System::mediaPath(){
    char cwd[PATH_MAX];
    string cwdtoString;

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        std::cout << "Current directory path: " << cwd << std::endl;
            cwdtoString = cwd;
                 std::cout << "CTESTTT: " << cwd << std::endl;
      } else {
        std::cerr << "Error: Could not get current directory path." << std::endl;
      }

    string stringg = time2x();
    string dash = "/";
    //string pathPlus = cwdtoString.append(dash.append(userName.append(sss)));
    string testPath = cwdtoString + dash + userName + stringg;
    return testPath;
}
/**
 * @brief Get the current system time and format it as a string.
 * @return A string representing the current system time in the format "YYYY-MM-DD-HH:MM:SS".
 */

string System::time2x(){
    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);
    string sss;
    char buffer[80];
    std::strftime(buffer, 80, "/%Y-%m-%d-%H:%M:%S", std::localtime(&time));
    std::string time_string = buffer;
    sss = time_string;
    return sss;
}


/**
*@brief Creates a directory with the given name if it doesn't exist already.
*@param dirname Name of the directory to be created.
*This function checks if a directory with the given name exists, and if not,
*it creates a new directory with the given name using mkdir system call.
*The permission flags S_IRWXU, S_IRWXG, S_IROTH, S_IXOTH are used to set the
*permissions for the new directory.
*Upon successful creation of the directory, the function updates the path member
*variable with the name of the directory.
*/

void System::createDir(string dirname){

    struct stat sb;
        if (stat(dirname.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)) {
            std::cout << "Directory already exists.:" << dirname << std::endl;
            path = dirname;
        } else {
            int status = mkdir(dirname.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            if (status == 0) {
                std::cout << "Directory created successfully!" << dirname << std::endl;
                path = dirname;
            } else {
                std::cout << "Error creating directory." << std::endl;
            }
        }


}

/**
*@brief This function starts the system and keeps it running as long as it is armed.
*The function continuously checks for motion detected by the sensor, and based on the media type set by the user, it takes a photo or a video when motion is detected.
*If the alarm is on, it sends an email with the media file as an attachment.
*The function also sets the sensor cool down time and media type to use while taking the media files.
*@return void
*/

void System::SystemOn(){
 while(armed == true){ // while(armed == true)
    bool movement = motionDetected();
    if(movement == true){
      if(videoOn == 1){
          string path = mediaPath();
          camera.takeVideo(path.append(".h264"));
      //printf("VIDEO\n");mediaPath();
          if(alarm == true){
            sendAlarm(path);
          }
      }
      if(videoOn ==0){
          string path = mediaPath();
          camera.takePhoto(path.append(".jpg"));
          if(alarm == true){
            sendAlarm(path);
          }
      }

        this_thread::sleep_for(chrono::seconds(sensorCoolDown));
    }
  }

    printf("SYSTEM INSTIALIZSED sensor cool down %d, media Type %d\n",sensorCoolDown, videoOn);
}


