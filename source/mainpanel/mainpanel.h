#include <QtWidgets/qwidget.h>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QSystemTrayIcon>

class MainPanel : public QMainWindow
{
    Q_OBJECT
public:
    MainPanel(QWidget* parent = nullptr);

private:
    void initUi();
    void initTrayIcon();
    void signalConnect();
    void showKeyCounter();

protected:
    void changeEvent(QEvent* event) override;

private:
    struct
    {
        QMenu* main_menu_ = nullptr;
        QSystemTrayIcon* tray_icon_ = nullptr;
        QMenu* tray_icon_menu_ = nullptr;
    } ui_;
};