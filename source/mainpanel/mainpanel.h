#ifndef _SUMMARY_MAIN_PANEL_H_
#define _SUMMARY_MAIN_PANEL_H_

#include <QtWidgets/qwidget.h>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QSystemTrayIcon>

namespace keyboard
{
class KeyCounter;
}

class MainPanel : public QMainWindow
{
    Q_OBJECT
public:
    MainPanel(QWidget* parent = nullptr);
    ~MainPanel();

private:
    void initUi();
    void initMenus();
    void initTrayIcon();
    void signalConnect();
    void showKeyCounter();
    void runBackground();

protected:
    void changeEvent(QEvent* event) override;
    void closeEvent(QCloseEvent* event) override;

private:
    struct
    {
        QSystemTrayIcon* tray_icon_ = nullptr;
        QMenu* tray_icon_menu_ = nullptr;
    } ui_;
    keyboard::KeyCounter* key_counter_ = nullptr;
};

#endif