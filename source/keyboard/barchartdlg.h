#ifndef _SUMMARY_KEY_COUNTER_BARCHART_DLG_H_
#define _SUMMARY_KEY_COUNTER_BARCHART_DLG_H_

#include <QMap>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

#include "keytype.h"

namespace keyboard
{
class KeyBarChartDlg : public QDialog
{
    Q_OBJECT
public:
    explicit KeyBarChartDlg(QWidget* parent = nullptr);
    void showDetailData(QChart* chart, QBarSeries* series, bool show);

private:
    void initUi();
    // void initChartSet(int index);
    void initAllChartSet();
    void initAlphaChartSet();
    void initNumericChartSet();
    void initFuncChartSet();
    void initNavigationChartSet();
    void initSymbolChartSet();
    void initControlChartSet();
    void initSystemChartSet();
    void initEditChartSet();
    void initOtherChartSet();
    void signalConnect();

    // TODO: support previous date later
    void showBarChart(int index);
    void showAllChart();
    void showAlphaChart();
    void showNumericChart();
    void showFuncChart();
    void showNavigationChart();
    void showSymbolChart();
    void showControlChart();
    void showSystemChart();
    void showEditChart();
    void showOtherChart();

private:
    QTabWidget* bar_tab_ = nullptr;
    // TODO: maybe enhence this
    QMap<KeyZone, QBarSet*> AllBarData_;
    QMap<QString, QBarSet*> AlphaBarData_;
    QMap<QString, QBarSet*> NumericBarData_;
    QMap<QString, QBarSet*> FuncBarData_;
    QMap<QString, QBarSet*> NavigationBarData_;
    QMap<QString, QBarSet*> SymbolBarData_;
    QMap<QString, QBarSet*> ControlBarData_;
    QMap<QString, QBarSet*> SystemBarData_;
    QMap<QString, QBarSet*> EditBarData_;
    QMap<QString, QBarSet*> OtherBarData_;

    static constexpr int kAWeek = 7;
    int maximize_;
};
} // namespace keyboard

#endif