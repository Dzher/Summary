#include "keycounter.h"
#include <qpushbutton.h>
#include <winsock.h>
#include <QDebug>
#include <QGridLayout>
#include <QKeyEvent>
#include <chrono>
#include <cstring>
#include <sstream>
#include <thread>

#include "../utils/logger.h"
#include "barchartdlg.h"

using namespace keyboard;

KeyCounter::KeyCounter(QWidget* parent) : QWidget(parent)
{
    initUi();
    setKeyboardHook();
    signalConnect();
    
    // TODO: ues config replace the magic number 10.
    std::thread timerThread([this]() { startLog(10); });
    timerThread.detach();
}

KeyCounter::~KeyCounter()
{
    std::string filename = utils::Logger::getCurrentDate() + ".txt";
    writeLog(filename);
    removeKeyboardHook();
}

KeyboardData KeyCounter::getData()
{
    return key_map_;
}

void KeyCounter::closeEvent(QCloseEvent* event)
{
    hide();
    event->ignore();
}

void KeyCounter::initUi()
{
    setWindowTitle("Keyboard Counter");
    setMinimumSize(800, 600);

    QGridLayout* main_lyt = new QGridLayout();
    ui_.bar_btn = new QPushButton();
    ui_.bar_btn->setText("Bar Chart");
    ui_.bar_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui_.pie_btn = new QPushButton();
    ui_.pie_btn->setText("Pie Chart");
    ui_.pie_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui_.cloud_btn = new QPushButton();
    ui_.cloud_btn->setText("Cloud Chart");
    ui_.cloud_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui_.dot_btn = new QPushButton();
    ui_.dot_btn->setText("Dot Chart");
    ui_.dot_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui_.line_btn = new QPushButton();
    ui_.line_btn->setText("Line Chart");
    ui_.line_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui_.percent_bar_btn = new QPushButton();
    ui_.percent_bar_btn->setText("Percent Chart");
    ui_.percent_bar_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    main_lyt->addWidget(ui_.bar_btn, 0, 0);
    main_lyt->addWidget(ui_.pie_btn, 0, 1);
    main_lyt->addWidget(ui_.cloud_btn, 0, 2);
    main_lyt->addWidget(ui_.dot_btn, 1, 0);
    main_lyt->addWidget(ui_.line_btn, 1, 1);
    main_lyt->addWidget(ui_.percent_bar_btn, 1, 2);

    setLayout(main_lyt);
}

LRESULT CALLBACK KeyCounter::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0 && wParam == WM_KEYDOWN)
    {
        KBDLLHOOKSTRUCT* kbdStruct = (KBDLLHOOKSTRUCT*)lParam;
        DWORD key = kbdStruct->vkCode;
        key_map_[key]++;
    }
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

void KeyCounter::setKeyboardHook()
{
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
}

void KeyCounter::removeKeyboardHook()
{
    if (keyboardHook)
    {
        UnhookWindowsHookEx(keyboardHook);
        keyboardHook = nullptr;
    }
}

QString KeyCounter::vkCode2String(DWORD key, bool remove_prefix)
{
    LONG lParam = MapVirtualKeyA(key, MAPVK_VK_TO_VSC) << 16;
    char key_name[128];
    int result = GetKeyNameTextA(lParam, key_name, sizeof(key_name));

    if (!result)
    {
        return {};
    }

    QString key_str{key_name};
    if (remove_prefix)
    {
        key_str.remove(0, 3);
    }
    return key_str;
}

void KeyCounter::signalConnect()
{
    connect(ui_.bar_btn, &QPushButton::clicked, this, &KeyCounter::showBarChart);
    connect(ui_.pie_btn, &QPushButton::clicked, this, &KeyCounter::showPieChart);
    connect(ui_.cloud_btn, &QPushButton::clicked, this, &KeyCounter::showCloudChart);
    connect(ui_.dot_btn, &QPushButton::clicked, this, &KeyCounter::showDotChart);
    connect(ui_.line_btn, &QPushButton::clicked, this, &KeyCounter::showLineChart);
    connect(ui_.percent_bar_btn, &QPushButton::clicked, this, &KeyCounter::showPercentChart);
}

void KeyCounter::showBarChart()
{
    auto bar_dlg = new KeyBarChartDlg(this);
    bar_dlg->show();
}

void KeyCounter::showPieChart()
{
}

void KeyCounter::showCloudChart()
{
}

void KeyCounter::showDotChart()
{
}

void KeyCounter::showLineChart()
{
}

void KeyCounter::showPercentChart()
{
}

void KeyCounter::filter()
{
}

void KeyCounter::exportFile()
{
}

void KeyCounter::writeLog(const std::string& filename)
{
    std::ostringstream key_count_lines{};
    for (auto it = key_map_.begin(); it != key_map_.end(); ++it)
    {
        key_count_lines << it.key() << "," << it.value() << std::endl;
    }
    utils::Logger::log(filename, key_count_lines.str(), utils::LogMethod::Replace);
}

void KeyCounter::startLog(int minutes)
{
    std::string filename = utils::Logger::getCurrentDate() + ".txt";
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::minutes(minutes));
        writeLog(filename);
    }
}