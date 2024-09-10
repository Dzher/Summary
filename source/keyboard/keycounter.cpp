#include "keycounter.h"
#include <QDebug>
#include <QGridLayout>
#include <QKeyEvent>

KeyCounter::KeyCounter(QWidget* parent) : QWidget(parent)
{
    initUi();
    setKeyboardHook();
}

KeyCounter::~KeyCounter()
{
    qDebug() << "Keyboard Summary";
    for (auto it = key_map_.begin(); it != key_map_.end(); ++it)
    {
        qDebug() << it.key() << " " << it.value();
    }
    removeKeyboardHook();
}

void KeyCounter::initUi()
{
    setWindowTitle("Keyboard Counter");

    QGridLayout* main_lyt = new QGridLayout();
    ui_.bar_btn = new QPushButton();
    ui_.bar_btn->setText("Bar Chart");
    ui_.pie_btn = new QPushButton();
    ui_.pie_btn->setText("Pie Chart");
    ui_.cloud_btn = new QPushButton();
    ui_.cloud_btn->setText("Cloud Chart");
    ui_.dot_btn = new QPushButton();
    ui_.dot_btn->setText("Dot Chart");
    ui_.line_btn = new QPushButton();
    ui_.line_btn->setText("Line Chart");
    ui_.percent_bar_btn = new QPushButton();
    ui_.percent_bar_btn->setText("Percent Chart");

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

void KeyCounter::signalConnect()
{
}

void KeyCounter::showPieChart()
{
}

void KeyCounter::showBarChart()
{
}

void KeyCounter::filter()
{
}

void KeyCounter::exportFile()
{
}