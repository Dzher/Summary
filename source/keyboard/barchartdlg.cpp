#include "barchartdlg.h"
#include <qboxlayout.h>
#include <qpair.h>
#include <qtabwidget.h>
#include "keycounter.h"
#include "keytype.h"

using namespace keyboard;

KeyBarChartDlg::KeyBarChartDlg(QWidget* parent) : QDialog(parent)
{
    initData();
    initUi();
}

void KeyBarChartDlg::initData()
{
    auto raw_data = KeyCounter::getData();
    for (auto it = raw_data.begin(); it != raw_data.end(); it++)
    {
        bar_data_[vkCodeType(it.key())] = qMakePair(it.key(), it.value());
    }
}

void KeyBarChartDlg::initUi()
{
    setWindowTitle("Keyboard BarChart");
    setMinimumSize(800, 600);

    QVBoxLayout* main_lyt = new QVBoxLayout;
    ui_.bar_tab_ = new QTabWidget();
    ui_.bar_tab_->addTab(new QWidget(), "All");
    ui_.bar_tab_->addTab(new QWidget(), "Alpha");
    ui_.bar_tab_->addTab(new QWidget(), "Numeric");
    ui_.bar_tab_->addTab(new QWidget(), "Function");
    ui_.bar_tab_->addTab(new QWidget(), "Navigation");
    ui_.bar_tab_->addTab(new QWidget(), "Symbol");
    ui_.bar_tab_->addTab(new QWidget(), "Control");
    ui_.bar_tab_->addTab(new QWidget(), "System");
    ui_.bar_tab_->addTab(new QWidget(), "Edit");
    ui_.bar_tab_->addTab(new QWidget(), "Other");

    main_lyt->addWidget(ui_.bar_tab_);
    setLayout(main_lyt);
}

void KeyBarChartDlg::signalConnect()
{
}

void KeyBarChartDlg::showBarChart(KeyZone key_type)
{
}
