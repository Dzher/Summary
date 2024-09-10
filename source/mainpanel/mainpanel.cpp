#include "mainpanel.h"
#include <qstyle.h>
#include <qwindowdefs.h>
#include <QtCore/QEvent>
#include <QtCore/QTimer>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStyle>

MainPanel::MainPanel(QWidget* parent) : QMainWindow(parent)
{
    initUi();
    initTrayIcon();
}

void MainPanel::initUi()
{
    setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_ComputerIcon));
    setWindowTitle("Summary");
    setMinimumSize(480, 360);
}

void MainPanel::initTrayIcon()
{
    ui_.tray_icon_ = new QSystemTrayIcon(this);
    QIcon icon = QApplication::style()->standardIcon(QStyle::SP_ComputerIcon);
    ui_.tray_icon_->setIcon(icon);

    ui_.tray_icon_menu_ = new QMenu();
    QAction* restore_action = new QAction("Restore");
    QAction* quit_action = new QAction("Quit");

    connect(restore_action, &QAction::triggered, this, &MainPanel::showNormal);
    connect(quit_action, &QAction::triggered, this, &MainPanel::close);

    ui_.tray_icon_menu_->addAction(restore_action);
    ui_.tray_icon_menu_->addAction(quit_action);

    ui_.tray_icon_->setContextMenu(ui_.tray_icon_menu_);
    ui_.tray_icon_->setToolTip("Summary");
    ui_.tray_icon_->show();
}

void MainPanel::signalConnect()
{
}

void MainPanel::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::WindowStateChange)
    {
        if (isMinimized())
        {
            QTimer::singleShot(0, this, &MainPanel::hide);
            ui_.tray_icon_->showMessage("Minimized", "The application is now minimized to tray.",
                                        QSystemTrayIcon::Information, 500);
        }
    }
    QMainWindow::changeEvent(event);
}