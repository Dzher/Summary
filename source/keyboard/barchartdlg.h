#ifndef _SUMMARY_KEY_COUNTER_BARCHART_DLG_H_
#define _SUMMARY_KEY_COUNTER_BARCHART_DLG_H_

#include <QMap>
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

private:
    void initUi();
    void initData();
    void signalConnect();
    // TODO: support previous date later
    void showBarChart(KeyZone key_type);

private:
    struct
    {
        QTabWidget* bar_tab_ = nullptr;
    } ui_;
    QMap<KeyZone, QPair<DWORD, unsigned int>> bar_data_;
};
} // namespace keyboard

#endif