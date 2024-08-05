#include "mainwindow.h"

#include <QApplication>

/**
 * @brief The main function of the application.
 *
 * This function initializes the QApplication object, creates the main window,
 * and starts the application's event loop. It also sets the application style
 * to "Fusion".
 *
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 * @return The exit status of the application.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv); ///< QApplication object to manage application-wide resources.

    MainWindow w; ///< Main window of the application.

    w.show(); ///< Displays the main window.

    QApplication::setStyle("Fusion"); ///< Sets the application's style to "Fusion".

    return a.exec(); ///< Enters the application's event loop and returns the exit status.
}
