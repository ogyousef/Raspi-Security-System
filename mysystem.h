/**

*@file MySystem.h
*@brief Header file for the MySystem class, which implements a security system with camera and sensor
*This header file defines the MySystem class, which consists of Camera and Sensor objects that work together
*to create a security system capable of taking photos and videos and detecting motion. The class also provides
*the functionality to arm and disarm the system, turn alarms on and off, and send alarms to a specified email address.
*@author [Osama Yousef]
*@date [2023-03-31]
*/

#ifndef MY_SYSTEM_H
#define MY_SYSTEM_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <pigpio.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>


using namespace std;



/**
*@class Camera
*@brief Class that implements a camera for the security system
*This class contains functions for taking photos and videos, turning the camera on and off, and accessing the current
*state of the camera.
*/

class Camera{
  private:
  bool isOn; //< Current state of the camera (on/off) */
  string picPath; //< Path to save pictures and videos */
  string waitDuration; //< Wait duration for camera capture */
   string time2x(); //< Helper function to generate timestamps */
  public:

/**
*@brief Function to take a photo with the camera
*@param path Path to save the photo
*/
  void takePhoto(string path);

  /**
*@brief Function to take a Video with the camera
*@param path Path to save the Video
*/
  void takeVideo(string path);

    /**
*@brief Function to take a Live video with the camera

*/
  void LiveView();

  void setOn();
  bool getisOn();


  ~Camera(){}
};


/**
*@class Sensor
*@brief Class that implements a motion sensor for the security system
*This class contains functions for initializing the sensor and getting the current output of the sensor.
**/

class Sensor{
  public:
  bool Initialize();

  /**
*@brief Function to get the current output of the sensor
*@return The current output of the sensor
*/

  int sensorOutput();
};


/**
*@class System
*@brief Class that implements the security system
*This class contains Camera and Sensor objects and functions for controlling the security system.
*/

class System{
  private:

  Camera camera;//< Camera object used by the security system */
  Sensor sensor;//< Sensor object used by the security system */
  bool alarm = false;//< Current state of the alarm (on/off) */
  bool armed;//< Current state of the security system (armed/disarmed) */
  int sensorCoolDown;//< Duration of sensor cooldown */
  int videoOn; //< Current state of video capture (on/off) */
  string userName;//< Username for sending email alarms */
  string path; //< Path to save pictures and videos */
  string userEmail; //< Email address for sending email alarms */



  public:
  void alarmsOn();
  void alarmsOff();
  void armSystem(int sensorLeng, string userNamex, string userEmailx);
  void disarmSystem();
  bool motionDetected();
  void sendAlarm(string path);
  void SystemOn();
  void LiveView();
  void MediaType(int Type);
  string mediaPath();
  void createDir(string dirname);
  void setUserName(string givinUser);
  string time2x();
  void snapShot();

  ~System(){}
};

#endif /* MY_SYSTEM_H */
