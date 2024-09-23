#include "mainpanel.h"
#include <qaction.h>
#include <qmenu.h>
#include <qmenubar.h>
#include <qmessagebox.h>

#include <QtCore/QEvent>
#include <QtCore/QTimer>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QStyle>

#include "../keyboard/keycounter.h"
#include "../tools/confighelper.h"

MainPanel::MainPanel(QWidget* parent) : QMainWindow(parent)
{
    initUi();
    if (!tools::ConfigHelper::existConfigFile())
    {
        tools::ConfigHelper::initConfigFile();
    }
    runBackground();
}

MainPanel::~MainPanel()
{
}

void MainPanel::initUi()
{
    setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_ComputerIcon));
    setWindowTitle("Summary");
    setMinimumSize(480, 360);

    initMenus();
    initTrayIcon();
}

void MainPanel::initMenus()
{
    QMenuBar* menu_bar = new QMenuBar();

    QMenu* file_menu = new QMenu("File");
    QAction* quit_action = new QAction("Quit");
    file_menu->addAction(quit_action);

    QMenu* start_menu = new QMenu("Start");
    QAction* keyboard_action = new QAction("KeyCounter");
    start_menu->addAction(keyboard_action);

    QMenu* setting_menu = new QMenu("Setting");
    QAction* setting_edit_action = new QAction("Edit");
    setting_menu->addAction(setting_edit_action);

    menu_bar->addMenu(file_menu);
    menu_bar->addMenu(start_menu);
    menu_bar->addMenu(setting_menu);

    this->setMenuBar(menu_bar);

    connect(quit_action, &QAction::triggered, this, &MainPanel::close);
    connect(keyboard_action, &QAction::triggered, this, &MainPanel::showKeyCounter);
}

void MainPanel::initTrayIcon()
{
    ui_.tray_icon_ = new QSystemTrayIcon(this);
    QIcon icon = QApplication::style()->standardIcon(QStyle::SP_ComputerIcon);
    ui_.tray_icon_->setIcon(icon);

    ui_.tray_icon_menu_ = new QMenu();
    QAction* restore_action = new QAction("Restore");
    QAction* quit_action = new QAction("Quit");
    QMenu* statistics_menu = new QMenu("Statistics");
    QAction* keyboard_action = new QAction("KeyCounter");
    statistics_menu->addAction(keyboard_action);

    connect(restore_action, &QAction::triggered, this, &MainPanel::showNormal);
    connect(keyboard_action, &QAction::triggered, this, &MainPanel::showKeyCounter);
    connect(quit_action, &QAction::triggered, this, &MainPanel::close);

    ui_.tray_icon_menu_->addAction(restore_action);
    ui_.tray_icon_menu_->addSeparator();
    ui_.tray_icon_menu_->addMenu(statistics_menu);
    ui_.tray_icon_menu_->addSeparator();
    ui_.tray_icon_menu_->addAction(quit_action);

    ui_.tray_icon_->setContextMenu(ui_.tray_icon_menu_);
    ui_.tray_icon_->setToolTip("Summary");
    ui_.tray_icon_->show();
}

void MainPanel::signalConnect()
{
}

void MainPanel::runBackground()
{
    key_counter_ = new keyboard::KeyCounter(this);
    key_counter_->hide();
}

void MainPanel::showKeyCounter()
{
    key_counter_->show();
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

void MainPanel::closeEvent(QCloseEvent* event)
{
    QMessageBox::StandardButton result =
        QMessageBox::question(this, "Warning", "Are you sure you want out?\nClick 'Yes' to exit and 'No' to hide.");
    if (QMessageBox::StandardButton::No == result)
    {
        hide();
        event->ignore();
    }
    else
    {
        QMainWindow::closeEvent(event);
    }
}