/**
*@file mainwindow.cpp
*@brief  file for MainWindow class which is a Qt-based GUI for a security system using the System class.
*/
#include "mainwindow.h"
#include "mysystem.h"
#include "history.h"
#include <thread>
#include "./ui_mainwindow.h"
#include <QtDebug>
#include <QDesktopWidget>


/**
*@brief Constructs the MainWindow object and sets up the user interface.
*@param parent The parent widget.
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

}
/**
*@brief Destroys the MainWindow object and deletes the user interface.
*/
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief Called when the push button is pressed
 * @details then shows the live view
 */
void MainWindow::on_pushButton_pressed()
{
    CurrentSystem.LiveView();
    printf("LIVE VIEW");
}

/**
*@brief This slot function is called when the user presses the "Arm System" button.
*It sets the text of the "Status" label to indicate that the system is currently armed.
*It checks the state of the "Motion Detection" checkbox to determine whether to turn alarms on or off.
*It sets the media type and sensitivity of the current system to the values specified by the user.
*It arms the system with the specified sensor sensitivity, current user name and email.
*It creates a new thread to run the SystemOn function of the current system object.
*It sets the "Arm System" button to be disabled, and sets the background color to orange.
*It enables the "Disarm System" button.
*/

void MainWindow::on_pushButton_2_pressed()
{
    ui->label_3->setText("System Is Currently Armed ");
    if(ui->checkBox->isChecked()){
        CurrentSystem.alarmsOn();
    }
    else{
        CurrentSystem.alarmsOff();
    }
    CurrentSystem.MediaType(mediaType);
    CurrentSystem.armSystem(sensorSen, currentUser.toStdString(), currentUserEmail);
    std::thread systemThread(&System::SystemOn,&CurrentSystem);
    systemThread.detach();
    //CurrentSystem.SystemOn();
    printf("ARM SYSTEM");

    ui->pushButton_2->setEnabled(false);

    // Set the background color to orange
    QPalette pal = ui->pushButton_2->palette();
    pal.setColor(QPalette::Button, QColor(255, 165, 0));
    ui->pushButton_2->setAutoFillBackground(true);
    ui->pushButton_3->setEnabled(true);
}

/**
*@brief Sets the sensitivity of the system to 5.
*/
void MainWindow::on_radioButton_pressed()
{
    sensorSen = 5;
}
/**
*@brief Sets the sensitivity of the system to 10.
*/
void MainWindow::on_radioButton_2_clicked()
{
     sensorSen = 10;
}
/**
*@brief Sets the sensitivity of the system to 20.
*/
void MainWindow::on_radioButton_3_pressed()
{
    sensorSen = 20;
}
/**
*@brief Sets the media type to 0, indicating Image Capturing.
*/
void MainWindow::on_radioButton_4_clicked()
{
    mediaType =0;
}
/**
*@brief Sets the media type to 0, indicating Video Capturing.
*/

void MainWindow::on_radioButton_5_pressed()
{
    mediaType =1;
}

/**
@brief This slot function is called when the user clicks the "Disarm System" button.
*It sets the label text to "System Is Currently DiArmed", disarms the system by calling
*the disarmSystem function of the CurrentSystem object, enables the "Arm System"
*button, disables the "Disarm System" button, and resets the background color of the
*"Arm System" button.
*/

void MainWindow::on_pushButton_3_pressed()
{
    ui->label_3->setText("System Is Currently DiArmed ");
    CurrentSystem.disarmSystem();
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_2->setStyleSheet("");
    ui->pushButton_3->setEnabled(false);
}

/**
*@brief This slot function is called when the user clicks the "Exit" button.
*It closes the application window and prints "CLOSE" to the console.
*/
void MainWindow::on_pushButton_5_pressed()
{
    this->close();
    printf("CLOSE");
}
/**
*@brief This function sets the current user name.
*@param currentUserx The current user name as a QString.
*/

void MainWindow::setUserName(QString currentUserx){
    currentUser = currentUserx;
};

/**
*@brief Opens the history window and hides the current window.
*Creates an instance of the history window and sets its title, fixed size, and position on the screen.
*Sets the current user's name and email in the history window.
*Shows the history window and hides the current window.
*/

void MainWindow::on_pushButton_4_pressed()
{
    QDesktopWidget *desktop = QApplication::desktop();
     int screenWidth = desktop->width();
     int screenHeight = desktop->height();
        int width = 800;
        int height = 600;
        int x = (screenWidth - width) / 2;
        int y = (screenHeight - height) / 2;
    history *z = new history(this);
    z->setUserName(currentUser, currentUserEmail);
    z->setWindowTitle("History");
    z->setFixedSize(QSize(800,600));
    z->move(x,y);
    z->show();

    this->hide();
}

/**
*@brief This function sets the current user email.
*@param email The current email name as a string.
*/

void MainWindow::setuserEmail(string email){
    currentUserEmail = email;
}

/**
*@brief Handles the "Snapshot" button click event by arming and disarming the system and taking a snapshot.
*/

void MainWindow::on_pushButton_6_clicked()
{
     CurrentSystem.armSystem(0, currentUser.toStdString(), currentUserEmail);
     CurrentSystem.disarmSystem();
    CurrentSystem.snapShot();
}



