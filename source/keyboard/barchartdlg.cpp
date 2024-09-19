#include "barchartdlg.h"

#include <qglobal.h>
#include <qpoint.h>
#include <winsock.h>
#include <QVBoxLayout>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSet>
#include <QtWidgets/QGraphicsSimpleTextItem>

#include "../utils/logger.h"
#include "keycounter.h"
#include "keytype.h"

using namespace keyboard;

KeyBarChartDlg::KeyBarChartDlg(QWidget* parent) : QDialog(parent), maximize_(0)
{
    initUi();
    signalConnect();

    showAllChart();
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

void KeyBarChartDlg::showDetailData(QChart* chart, QBarSeries* series, bool show)
{
    if (!chart || !series)
    {
        return;
    }

    if (not show)
    {
        return;
    }

    for (auto& barset : series->barSets())
    {
        for (int index = 0; index < barset->count(); ++index)
        {
            qreal value = barset->at(index);
            // QPointF labelPosition = series->barRect(barset, index).topRight();
            QPointF point = chart->mapToPosition(QPointF(index, value), series);

            QGraphicsSimpleTextItem* label = new QGraphicsSimpleTextItem(QString::number(value));
            label->setPos(point.x() - label->boundingRect().width() / 2, point.y() - label->boundingRect().height());

            chart->scene()->addItem(label);
        }
    }
}

void KeyBarChartDlg::showAllChart()
{
    initAllChartSet();

    delete bar_tab_->widget(0)->layout();

    QBarSeries* series = new QBarSeries();
    for (auto it = AllBarData_.begin(); it != AllBarData_.end(); it++)
    {
        series->append(it.value());
    }

    QChart* chart = new QChart();
    chart->setTitle("Keyboard Barchart in a Week");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->addSeries(series);

    QBarCategoryAxis* axis_x = new QBarCategoryAxis();
    QStringList categories;
    for (auto& each_x : utils::Timmer::getLastNDates(kAWeek))
    {
        categories.append(QString::fromStdString(each_x));
    }
    axis_x->append(categories);
    chart->addAxis(axis_x, Qt::AlignBottom);
    series->attachAxis(axis_x);

    QValueAxis* axis_y = new QValueAxis();
    axis_y->setRange(0, maximize_);
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
    // init the data each time reopened
    for (int zone = KeyZone::AlphaZone; zone <= KeyZone::Other; ++zone)
    {
        auto key = static_cast<KeyZone>(zone);
        if (AllBarData_[key])
        {
            delete AllBarData_[key];
        }
        AllBarData_[key] = new QBarSet(KeyboardUtils::keyZone2String(key));
    }
    maximize_ = 0;

    std::vector<std::string> week_list = utils::Timmer::getLastNDates(kAWeek);
    for (int day_index = 0; day_index < week_list.size(); ++day_index)
    {
        KeyZone bar_key;
        for (int zone = KeyZone::AlphaZone; zone <= KeyZone::Other; ++zone)
        {
            // the date's data is empty, or no exist the date's file
            bar_key = static_cast<KeyZone>(zone);
            AllBarData_[bar_key]->append(0);
        }

        KeyboardData day_data = KeyCounter::getKeyData(week_list[day_index]);
        for (auto it = day_data.begin(); it != day_data.end(); it++)
        {
            bar_key = KeyboardUtils::vkCodeType(it.key());
            QBarSet* barset = AllBarData_[bar_key];
            barset->replace(day_index, barset->at(day_index) + it.value());
            if (maximize_ < barset->at(day_index))
            {
                maximize_ = barset->at(day_index);
            }
        }
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
