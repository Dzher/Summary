#include "barchartdlg.h"

#include <qchar.h>
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

void KeyBarChartDlg::showBarChart(int index)
{
    QString tab_title = bar_tab_->tabText(index);

    delete bar_tab_->currentWidget()->layout();

    if (tab_title == "All")
    {
        showAllChart();
    }
    else if (tab_title == "Alpha")
    {
        showAlphaChart();
    }
    else if (tab_title == "Numeric")
    {
        showNumericChart();
    }
    else if (tab_title == "Function")
    {
        showFuncChart();
    }
    else if (tab_title == "Navigation")
    {
        showNavigationChart();
    }
    else if (tab_title == "Symbol")
    {
        showSymbolChart();
    }
    else if (tab_title == "Control")
    {
        showControlChart();
    }
    else if (tab_title == "System")
    {
        showSystemChart();
    }
    else if (tab_title == "Edit")
    {
        showEditChart();
    }
    else if (tab_title == "Other")
    {
        showOtherChart();
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
    // case insensitivity
    // init the data each time reopened
    for (char alpha = 0x41; alpha <= 0x5A; ++alpha)
    {
        auto key = QString::fromLatin1(&alpha, 1);
        if (AlphaBarData_[key])
        {
            delete AlphaBarData_[key];
        }
        AlphaBarData_[key] = new QBarSet(key);
    }
    maximize_ = 0;

    std::vector<std::string> week_list = utils::Timmer::getLastNDates(kAWeek);
    for (int day_index = 0; day_index < week_list.size(); ++day_index)
    {
        for (char alpha = 0x41; alpha <= 0x5A; ++alpha)
        {
            // the date's data is empty, or no exist the date's file
            auto key = QString::fromLatin1(&alpha, 1);
            AlphaBarData_[key]->append(0);
        }

        KeyboardData day_data = KeyCounter::getKeyData(week_list[day_index]);
        for (auto it = day_data.begin(); it != day_data.end(); it++)
        {
            char alpha = it.key();
            if (KeyboardUtils::vkCodeType(alpha) != KeyZone::AlphaZone)
            {
                continue;
            }
            if (alpha >= 0x61 && alpha <= 0x7A)
            {
                alpha -= 32;
            }
            auto key = QString::fromLatin1(&alpha, 1);
            QBarSet* barset = AlphaBarData_[key];
            barset->replace(day_index, barset->at(day_index) + it.value());
            if (maximize_ < barset->at(day_index))
            {
                maximize_ = barset->at(day_index);
            }
        }
    }
}

void KeyBarChartDlg::initNumericChartSet()
{
    // init the data each time reopened
    for (char numeric = 0x30; numeric <= 0x39; ++numeric)
    {
        auto key = QString::fromLatin1(&numeric, 1);
        if (NumericBarData_[key])
        {
            delete NumericBarData_[key];
        }
        NumericBarData_[key] = new QBarSet(key);
    }
    maximize_ = 0;

    std::vector<std::string> week_list = utils::Timmer::getLastNDates(kAWeek);
    for (int day_index = 0; day_index < week_list.size(); ++day_index)
    {
        for (char numeric = 0x30; numeric <= 0x39; ++numeric)
        {
            // the date's data is empty, or no exist the date's file
            auto key = QString::fromLatin1(&numeric, 1);
            NumericBarData_[key]->append(0);
        }

        KeyboardData day_data = KeyCounter::getKeyData(week_list[day_index]);
        for (auto it = day_data.begin(); it != day_data.end(); it++)
        {
            if (KeyboardUtils::vkCodeType(it.key()) != KeyZone::NumericZone)
            {
                continue;
            }
            char numeric = it.key();
            auto key = QString::fromLatin1(&numeric, 1);
            QBarSet* barset = NumericBarData_[key];
            barset->replace(day_index, barset->at(day_index) + it.value());
            if (maximize_ < barset->at(day_index))
            {
                maximize_ = barset->at(day_index);
            }
        }
    }
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

void KeyBarChartDlg::showAllChart()
{
    initAllChartSet();
    initBarChart(AllBarData_, bar_tab_->tabText(bar_tab_->currentIndex()));
}

void KeyBarChartDlg::showAlphaChart()
{
    initAlphaChartSet();
    initBarChart(AlphaBarData_, bar_tab_->tabText(bar_tab_->currentIndex()));
}

void KeyBarChartDlg::showNumericChart()
{
    initNumericChartSet();
    initBarChart(NumericBarData_, bar_tab_->tabText(bar_tab_->currentIndex()));
}

void KeyBarChartDlg::showFuncChart()
{
    initFuncChartSet();
    initBarChart(FuncBarData_, bar_tab_->tabText(bar_tab_->currentIndex()));
}

void KeyBarChartDlg::showNavigationChart()
{
    initNavigationChartSet();
    initBarChart(NavigationBarData_, bar_tab_->tabText(bar_tab_->currentIndex()));
}

void KeyBarChartDlg::showSymbolChart()
{
    initSymbolChartSet();
    initBarChart(SymbolBarData_, bar_tab_->tabText(bar_tab_->currentIndex()));
}

void KeyBarChartDlg::showControlChart()
{
    initControlChartSet();
    initBarChart(ControlBarData_, bar_tab_->tabText(bar_tab_->currentIndex()));
}

void KeyBarChartDlg::showSystemChart()
{
    initSystemChartSet();
    initBarChart(SystemBarData_, bar_tab_->tabText(bar_tab_->currentIndex()));
}

void KeyBarChartDlg::showEditChart()
{
    initEditChartSet();
    initBarChart(EditBarData_, bar_tab_->tabText(bar_tab_->currentIndex()));
}

void KeyBarChartDlg::showOtherChart()
{
    initOtherChartSet();
    initBarChart(OtherBarData_, bar_tab_->tabText(bar_tab_->currentIndex()));
}

void KeyBarChartDlg::initBarChart(const auto& data, const QString& title)
{
    QBarSeries* series = new QBarSeries();
    for (auto it = data.begin(); it != data.end(); it++)
    {
        series->append(it.value());
    }

    QChart* chart = new QChart();
    chart->setTitle(QString("Keyboard %1 Barchart in a Week").arg(title));
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
    bar_tab_->currentWidget()->setLayout(main_lyt);
}