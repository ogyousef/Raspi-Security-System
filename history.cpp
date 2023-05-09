/**
*@file history.cpp
*@brief  file for history class which is a Qt-based GUI for a security system using the history class.
*/

#include "history.h"
#include "ui_history.h"
#include <mainwindow.h>
#include "QDebug"
#include "QDir"
#include "QFileInfo"
#include "QImage"
#include "QScrollArea"
#include "QLabel"
#include "QPixmap"
#include "QHBoxLayout"
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDesktopWidget>

/**
 * @brief A class representing the history of the pictures and videos recprded before.
 */


/**
 * This the constructing function for the history class
 * @param parent: takes the parent of this widget
 * @return Returns The UI for the History class
 */
history::history(QWidget *parent) :
    QWidget(nullptr),
    ui(new Ui::history)
{
    qDebug() << "Creating history widget...";

    ui->setupUi(this);

}

//< destructor for history class
history::~history()
{

    delete ui;
    QVideoWidget ttt;
}



/**
 * @brief Slot function called when the push button is clicked.
 *
 * This function creates a new instance of MainWindow, sets its size and position,
 * passes some user data to it, and shows it. It also closes the current window.
 */

void history::on_pushButton_clicked()
{
    QDesktopWidget *desktop = QApplication::desktop();
     int screenWidth = desktop->width();
     int screenHeight = desktop->height();
        int width = 1200;
        int height = 600;
        int x = (screenWidth - width) / 2;
        int y = (screenHeight - height) / 2;

        MainWindow *w = new MainWindow();
        w->setFixedSize(QSize(1200,600));
        w->setWindowFlags(Qt::CustomizeWindowHint);
        w->setuserEmail(userEmailtoPass); ///< User email to pass to MainWindow.
        w->setUserName(currentUser);///< Current user name to pass to MainWindow.
        w->move(x,y);
        w->show();
        this->close();

}

/**
 * @brief Load images and videos from the user's directory and display them in a grid layout.
 * 
 * @details Searches for image and video files with the extensions .png, .jpg, .bmp, .mp4, .avi, .mov, and .h264
 * in the directory named after the current user. For each file found, a label is created with a thumbnail image
 * or the first frame of the video file and a label with the file name. The labels are arranged in a grid layout
 * with three columns. The layout is added to a scroll area and displayed on the UI.
 * 
 * @return void
 */
void history::loadImages() {

    char cwd[PATH_MAX];
    QString cwdtoString;

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        std::cout << "Current directory path: " << cwd << std::endl;
            cwdtoString = cwd;
                 std::cout << "CTESTTT: " << cwd << std::endl;
      } else {
        std::cerr << "Error: Could not get current directory path." << std::endl;
      }

    QString path = cwdtoString + "/" + currentUser;
    QDir dir(path);
    dir.setNameFilters(QStringList() << "*.png" << "*.jpg" << "*.bmp" << "*.mp4" << "*.avi" << "*.mov" << "*.h264");
    QFileInfoList files = dir.entryInfoList();

    QGridLayout *layout = new QGridLayout();

    int row = 0, col = 0;
    foreach (const QFileInfo &file, files) {

        if (file.suffix().toLower() == "mp4" || file.suffix().toLower() == "avi" || file.suffix().toLower() == "mov"|| file.suffix().toLower() == "h264") {
            QLabel *thumbnailLabel = new QLabel();
            QImage thumbnailImage = createVideoThumbnail(file.absoluteFilePath());
            thumbnailLabel->setPixmap(QPixmap::fromImage(thumbnailImage));
            thumbnailLabel->setAlignment(Qt::AlignCenter);
            thumbnailLabel->setFixedSize(200, 200);
            thumbnailLabel->setProperty("filePath", file.absoluteFilePath());
            thumbnailLabel->setProperty("isVideo", true);
            thumbnailLabel->installEventFilter(this);

            QLabel *nameLabel = new QLabel();
            nameLabel->setText(file.fileName());
            nameLabel->setAlignment(Qt::AlignCenter);
            nameLabel->setFixedSize(200, 20);

            QVBoxLayout *videoLayout = new QVBoxLayout();
            videoLayout->addWidget(thumbnailLabel);
            videoLayout->addWidget(nameLabel);

            QWidget *videoWidgetContainer = new QWidget();
            videoWidgetContainer->setLayout(videoLayout);

            layout->addWidget(videoWidgetContainer, row, col);
            col++;

            if (col == 3) {
                col = 0;
                row++;
            }
        } else {
            QImage image(file.absoluteFilePath());

            QLabel *imageLabel = new QLabel();
            imageLabel->setPixmap(QPixmap::fromImage(image.scaled(200, 200, Qt::KeepAspectRatio)));
            imageLabel->setAlignment(Qt::AlignCenter);
            imageLabel->setFixedSize(200, 200);
            imageLabel->installEventFilter(this);
            imageLabel->setProperty("filePath", file.absoluteFilePath());

            QLabel *nameLabel = new QLabel();
            nameLabel->setText(file.fileName());
            nameLabel->setAlignment(Qt::AlignCenter);
            nameLabel->setFixedSize(200, 20);

            QVBoxLayout *imageLayout = new QVBoxLayout();
            imageLayout->addWidget(imageLabel);
            imageLayout->addWidget(nameLabel);

            QWidget *widget = new QWidget();
            widget->setLayout(imageLayout);

            layout->addWidget(widget, row, col);
            col++;

            if (col == 3) {
                col = 0;
                row++;
            }
        }
    }

    QWidget *scrollWidget = new QWidget();
    scrollWidget->setLayout(layout);
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidget(scrollWidget);

    ui->gridLayout->addWidget(scrollArea);
}


/**
 * @brief Create a thubmnail for videos but since it could be resource consuming 
 * we set the deafault to a black image
 * 
 * @return void
 */
QImage history::createVideoThumbnail(QString filePath)
{
    QImage image(100,100, QImage::Format_RGB32);
    image.fill(Qt::black);
    return image;
}
/**
 * @brief Plays the video at the specified file path.
 * 
 * @param filePath The path to the video file.
 */

void history::play(QString filePath)
{
    QMediaPlayer player;  ///< The media player used to play the video.
    QVideoWidget videoWidget;  ///< The widget used to display the video.
    player.setVideoOutput(&videoWidget);
    player.setMedia(QUrl::fromLocalFile(filePath));
    videoWidget.show();
    videoWidget.resize(200, 200);
    QEventLoop loop;
    QObject::connect(&player, SIGNAL(metaDataChanged()), &loop, SLOT(quit()));
    player.play();


}


/**
* @brief Event filter to handle mouse button press events on a label object.
* @param watched The object that triggered the event.
* @param event The event to handle.
* @return bool Returns true if the event is handled, false otherwise.
*/

bool history::eventFilter(QObject *watched, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress) {
        QLabel *label = qobject_cast<QLabel*>(watched);
        //QVideoWidget *videoWidget = qobject_cast<QVideoWidget*>(watched);
        if (label && label->property("isVideo").toBool()) {
            QString filePath = label->property("filePath").toString();
            QMediaPlayer player;
            QVideoWidget videoWidget;
            videoWidget.setObjectName(filePath);
            player.setObjectName(filePath);
            player.setVideoOutput(&videoWidget);
            player.setMedia(QUrl::fromLocalFile(filePath));
            player.setMuted(true);
            videoWidget.show();
            videoWidget.resize(800, 800);
            player.play();
            QEventLoop loop;
            QObject::connect(&player, &QMediaPlayer::mediaStatusChanged, [&](QMediaPlayer::MediaStatus status) {
                if (status == QMediaPlayer::LoadedMedia) {
;
                }

            });
            player.play();
            loop.exec();
            return true;


        } else if (label && !label->property("isVideo").toBool()) {
            QLabel *maxLabel = new QLabel();
            maxLabel->setPixmap(label->pixmap()->scaled(800, 800, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            maxLabel->setAttribute(Qt::WA_DeleteOnClose);
            maxLabel->setWindowFlags(Qt::Window);
            maxLabel->show();
            return true;
        }
    }
    return QObject::eventFilter(watched, event);
}




/**

*@brief Sets the current user name and user email for the history object.
*@param currentUserx The current user name.
*@param userEmailx The current user email.
*/
void history::setUserName(QString currentUserx, string userEmailx){
    currentUser = currentUserx;
    userEmailtoPass = userEmailx;
}

/**
*@brief This slot is called when the "Load Images" button is clicked.
*@return void history::on_pushButton_2_clicked()
**/
{
    loadImages();
    ui->pushButton_2->hide();
}
