/**
*@file history.h
*@brief This file contains the declaration of the history class, which is a widget for displaying the history of media recorded by the system.
*/

#ifndef HISTORY_H
#define HISTORY_H

#include <QWidget>
#include <QMediaPlayer>
#include <string>
namespace Ui {

/**
*@brief The history class is a widget for displaying the history of media recorded by the system.
*/

class history;
}

class history : public QWidget
{
    Q_OBJECT

public:
/**
* @brief Constructs a new history object.
* @param parent The parent widget.
*/

    explicit history(QWidget *parent = nullptr);
    /**
 * @brief Sets the current user name and email to be used for accessing the media files.
 * @param currentUserx The name of the current user.
 * @param userEmailx The email of the current user.
 */
    void setUserName(QString currentUserx, std::string userEmailx);

/**
 * @brief Destroys the history object.
 */
    ~history();

private slots:

void on_pushButton_clicked();
/**
 * @brief Loads and displays the images in the history directory.
 */
void loadImages();

void on_pushButton_2_clicked();
/**
 * @brief Handles events for the media player.
 * @param obj The object that generated the event.
 * @param event The event to handle.
 * @return Returns true if the event was handled successfully, false otherwise.
 */

bool eventFilter(QObject *obj, QEvent *event);
/**
 * @brief Creates a thumbnail image for the given video file.
 * @param filePath The path of the video file.
 * @return Returns the thumbnail image.
 */

QImage createVideoThumbnail(QString filePath);
/**
 * @brief Plays the video file with the given file path.
 * @param filePath The path of the video file.
 */
void play(QString filePath);

private:
    Ui::history *ui;
    QString currentUser; //< The name of the current user. */
    std::string userEmailtoPass; //< The email of the current user. */
};

#endif // HISTORY_H
