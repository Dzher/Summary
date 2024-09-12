#include "barchartdlg.h"
#include <qbarset.h>
#include <qboxlayout.h>
#include <qpair.h>
#include <qtabwidget.h>
#include <winsock.h>
#include "keycounter.h"
#include "keytype.h"

using namespace keyboard;

KeyBarChartDlg::KeyBarChartDlg(QWidget* parent) : QDialog(parent)
{
    initUi();
    signalConnect();

    bar_tab_->setCurrentIndex(0);
}

void KeyBarChartDlg::initUi()
{
    setWindowTitle("Keyboard BarChart");
    setMinimumSize(800, 600);

    QVBoxLayout* main_lyt = new QVBoxLayout;
    bar_tab_ = new QTabWidget();
    bar_tab_->addTab(new QWidget(), "All");
    bar_tab_->addTab(new QWidget(), "Alpha");
    bar_tab_->addTab(new QWidget(), "Numeric");
    bar_tab_->addTab(new QWidget(), "Function");
    bar_tab_->addTab(new QWidget(), "Navigation");
    bar_tab_->addTab(new QWidget(), "Symbol");
    bar_tab_->addTab(new QWidget(), "Control");
    bar_tab_->addTab(new QWidget(), "System");
    bar_tab_->addTab(new QWidget(), "Edit");
    bar_tab_->addTab(new QWidget(), "Other");

    main_lyt->addWidget(bar_tab_);
    setLayout(main_lyt);
}

void KeyBarChartDlg::signalConnect()
{
    connect(bar_tab_, &QTabWidget::currentChanged, this, [this](int index) { showBarChart(index); });
}

void KeyBarChartDlg::showAllChart()
{
    initAllChartSet();

    QBarSeries* series = new QBarSeries();
    QStringList categories;
    for (auto it = AllBarData_.begin(); it != AllBarData_.end(); it++)
    {
        series->append(it.value());
        categories.append(it.value()->label());
    }

    QChart* chart = new QChart();
    chart->setTitle("Today's Keyboard Barchart");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->addSeries(series);

    QBarCategoryAxis* axis_x = new QBarCategoryAxis();
    axis_x->append(categories);
    chart->addAxis(axis_x, Qt::AlignBottom);
    series->attachAxis(axis_x);

    QValueAxis* axis_y = new QValueAxis();
    chart->addAxis(axis_y, Qt::AlignLeft);
    series->attachAxis(axis_y);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView* chart_view = new QChartView();
    chart_view->setChart(chart);
    chart_view->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout* main_lyt = new QVBoxLayout;
    main_lyt->addWidget(chart_view);
    bar_tab_->widget(0)->setLayout(main_lyt);
}

void KeyBarChartDlg::showBarChart(int index)
{
    QString tab_title = bar_tab_->tabText(index);
    if (tab_title == "All")
    {
        showAllChart();
    }
    else if (tab_title == "Alpha")
    {
        initAlphaChartSet();
    }
    else if (tab_title == "Numeric")
    {
        initNumericChartSet();
    }
    else if (tab_title == "Function")
    {
        initFuncChartSet();
    }
    else if (tab_title == "Navigation")
    {
        initNavigationChartSet();
    }
    else if (tab_title == "Symbol")
    {
        initSymbolChartSet();
    }
    else if (tab_title == "Control")
    {
        initControlChartSet();
    }
    else if (tab_title == "System")
    {
        initSystemChartSet();
    }
    else if (tab_title == "Edit")
    {
        initEditChartSet();
    }
    else if (tab_title == "Other")
    {
        initOtherChartSet();
    }
}

void KeyBarChartDlg::initAllChartSet()
{
    auto raw_data = KeyCounter::getData();
    for (auto it = raw_data.begin(); it != raw_data.end(); it++)
    {
        KeyZone bar_key = KeyboardUtils::vkCodeType(it.key());
        if (!AllBarData_.contains(bar_key))
        {
            QBarSet* each_set = new QBarSet(KeyboardUtils::keyZone2String(bar_key));
            AllBarData_[bar_key] = each_set;
        }
        AllBarData_[bar_key]->replace(0, AllBarData_[bar_key]->at(0) + it.value());
    }
}

void KeyBarChartDlg::initAlphaChartSet()
{
}

void KeyBarChartDlg::initNumericChartSet()
{
}

void KeyBarChartDlg::initFuncChartSet()
{
}

void KeyBarChartDlg::initNavigationChartSet()
{
}

void KeyBarChartDlg::initSymbolChartSet()
{
}

void KeyBarChartDlg::initControlChartSet()
{
}

void KeyBarChartDlg::initSystemChartSet()
{
}

void KeyBarChartDlg::initEditChartSet()
{
}

void KeyBarChartDlg::initOtherChartSet()
{
}

void KeyBarChartDlg::showAlphaChart()
{
    initAlphaChartSet();
}

void KeyBarChartDlg::showNumericChart()
{
    initNumericChartSet();
}

void KeyBarChartDlg::showFuncChart()
{
    initFuncChartSet();
}

void KeyBarChartDlg::showNavigationChart()
{
    initNavigationChartSet();
}

void KeyBarChartDlg::showSymbolChart()
{
    initSymbolChartSet();
}

void KeyBarChartDlg::showControlChart()
{
    initControlChartSet();
}

void KeyBarChartDlg::showSystemChart()
{
    initSystemChartSet();
}

void KeyBarChartDlg::showEditChart()
{
    initEditChartSet();
}

void KeyBarChartDlg::showOtherChart()
{
    initOtherChartSet();
}
