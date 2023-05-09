/**
*@file mainwindow.h
*@brief Header file for MainWindow class which is a Qt-based GUI for a security system using the System class.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mysystem.h>
#include <history.h>
#include <thread>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
*@class MainWindow
*@brief Class for the main window of the security system GUI.
*/

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:

/**
* @brief Constructor for the MainWindow class.
* @param parent Pointer to the parent QWidget.
*/
    MainWindow(QWidget *parent = nullptr);

    /**
 * @brief Setter function for the current user name.
 * @param currentUserx String representing the current user's name.
 */
    void setUserName(QString currentUserx);
    /**
 * @brief Setter function for the current user email.
 * @param email String representing the current user's email.
 */

    void setuserEmail(string email);
    QString currentUser; //**< QString representing the current user name. */

/**
 * @brief Destructor for the MainWindow class.
 */
    ~MainWindow();

private slots:
/**
 * @brief Slot for the "Snapshot" radio button press event.
 */
    void on_pushButton_pressed();

/**
 * @brief Slot for the "Disarm System" button press event.
 */
    void on_pushButton_2_pressed();
/**
 * @brief Slot for the "Snapshot" radio button press event.
 */
    void on_radioButton_pressed();
/**
 * @brief Slot for the "Video" radio button press event.
 */
    void on_radioButton_2_clicked();
/**
 * @brief Slot for the "Alarms On" radio button press event.
 */
    void on_radioButton_3_pressed();
/**
 * @brief Slot for the "Alarms Off" radio button press event.
 */
    void on_radioButton_4_clicked();
/**
 * @brief Slot for the "Live View" radio button press event.
 */
    void on_radioButton_5_pressed();
/**
 * @brief Slot for the "Create Directory" button press event.
 */
    void on_pushButton_3_pressed();
/**
 * @brief Slot for the "View History" button press event.
 */
    void on_pushButton_5_pressed();
/**
 * @brief Slot for the "Email" button press event.
 */
    void on_pushButton_4_pressed();
/**
 * @brief Slot for the "Live View" button press event.
 */
    void on_pushButton_6_clicked();



private:
    Ui::MainWindow *ui; ///< Pointer to the MainWindow UI object. */
    System CurrentSystem;//< Object representing the current security system. */
    int sensorSen;//< Integer representing the sensitivity of the sensor. */
    int mediaType;//< Integer representing the type of media (snapshot or video). */
    history *w;//< Pointer to the history window. */
    string currentUserEmail; //< String representing the current user's email. */
};
#endif // MAINWINDOW_H
