
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <pigpio.h>

using namespace std;


class Camera{
  private: 
  bool isOn;
  string picPath;
  string waitDuration;

  public:

  void takePhoto(string path) {
    picPath = path;
    string command = "raspistill -t 3 -o ";
    string finalC = command + path;
    const char* = finalC.c_str();
    system(toPass);

  }
    void takeVideo(string path, string duration) {
    picPath = path;
    string command = "raspivid -t " + duration + " -o ";
    string finalC = command + path;
    const char* = finalC.c_str();
    system(toPass);

  }

  void LiveView(){
    system("raspistill -t 0");
  }



  void setOn() {
      isOn = true;
  }
  bool getisOn() {
    return isOn;
  }


  ~camera(){}

}

class Sensor{

  public:

  bool Initialize(){

    if( gpioInitialise() < 0 ){
      return false;
    }
    else return true;
  }

  int sensorOutput(){
    if (Initialize() == true) {
      return gpioRead(12);
    }
    else{cout << "Sensor is Off";}
  }

}

class System{
  private:
  Camera camera;
  Sensor sensor;
  bool alarm = false;
  bool armed;

  public:
  void alarmsOn(){alarm = true;}
  void alarmsOff(){alarm = false;}
  void armSystem(){
    armed = true;
  }
  void disarmSystem(){
    armed = false;
  }
  bool motionDetected(){
    if(sensor.sensorOutput() > 0){
      return true;
    }
    else{return 0;}
  }
  void sendAlarm(){}

  void SystemOn(){
    while(armed == true){
      bool movement = motionDetected();
      if(movement == true){
        camera.takePhoto();
        if(alarm = true){
          sendAlarm();
        }
      }
    }
  }

  ~System(){}
}


int main()
{
  System testSystem = new System;
  testSystem.armSystem();
  testSystem.SystemOn();
}