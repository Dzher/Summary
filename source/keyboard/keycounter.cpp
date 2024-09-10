#include "keycounter.h"

#include <QGridLayout>

KeyCounter::KeyCounter(QWidget* parent) : QWidget(parent)
{
    initUi();
}

KeyCounter::~KeyCounter()
{
}

void KeyCounter::initUi()
{
    setWindowTitle("Keyboard Counting");

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