# Raspi-Security-System
Raspi Security System that uses camera and motion sensors, that also supports email notifications and alerts
# #---------------------------------------------------------------------------------------------------------------------------#
The full project contains the following files:
camera.cpp, CMakeLists.txt, CMakeLists.txt.user, history.cpp, history.h
history.ui, json.hpp, Login.cpp, Login.h, main.cpp, main.h, mainwindow.cpp,
mainwindow.h, mainwindow.ui, mysystem.cpp, mysystem.h, Register.cpp, 
Register.h, Setting.cpp, Setting.h, user.cpp, user.h, users.json, send-email.sh

The project requires the following libraries:
Qt, nlohmann, libcurl, and pigpio (only available for Raspberry Pi)

The project can only be run fully while connected to a Raspberry Pi with a
motion sensor and camera.

The motion sensor: must be sit to GPIO 12: or You can change the PIN in the mysystem.cpp to your pin,
The camera has to be connected through the MIPI CSI Camera Pinout.
For the Motion and camera to work: the program must be run as root. (sudo ./prog)
For the sendAlert Function to work send-email.sh has to be in the same dir as the excutable / the program make.

the program must be contained in a file called: untitled for it to compile correctly if this have to be changed then
changes must be made the CMAKELists.txt replacing all "untitled" to the current containg file name.

make sure to install the pigpio library to the pi before runnning anything.

Suggested-debuging: create a new project called "untitled" in qtcreator and then copy the Files to it, proccesed from there to make changes.

Running the excutable: After ensuring that all mentioned libraries are installed on the pi, u can run the excutable as sudo, ensure that the send-email.sh is 
in the same directory as the excutable to ensure that the sendAlert function will work probarely.

In the absence of those classes, main, Login, Register, user, and Setting
can be run on their own with their respective header files and with the pigpio
library ommitted. Running the project in this condensed version will work on 
any machine with the correct libraries, but will only present the initial 
pages of Login, Register, and Settings.

When running the file, a user can log in with an existing account, or by
registering a new account.

When logged in, there are functions to arm the camera, switch between taking
photos or videos, checking to send an email alert to your account, and viewing
saved photos. When photos or videos are taken, a folder will be created under
your username that will store them.
# #---------------------------------------------------------------------------------------------------------------------------#
