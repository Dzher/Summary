#ifndef _SUMMARY_KEY_COUNTER_H_
#define _SUMMARY_KEY_COUNTER_H_

#include <qevent.h>
#include <windows.h>
#include <QMap>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

namespace keyboard
{
using KeyboardData = QMap<DWORD, unsigned int>;
class KeyCounter : public QWidget
{
public:
    KeyCounter(QWidget* parent = nullptr);
    ~KeyCounter();

    static KeyboardData getData();

private:
    void initUi();
    void signalConnect();
    void showPieChart();
    void showBarChart();
    void showCloudChart();
    void showDotChart();
    void showLineChart();
    void showPercentChart();
    void filter();
    void exportFile();
    void startLog(int minutes);
    void writeLog(const std::string& filename);

    static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
    void setKeyboardHook();
    void removeKeyboardHook();

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    inline static KeyboardData key_map_;
    struct
    {
        QPushButton* pie_btn = nullptr;
        QPushButton* bar_btn = nullptr;
        QPushButton* cloud_btn = nullptr;
        QPushButton* dot_btn = nullptr;
        QPushButton* line_btn = nullptr;
        QPushButton* percent_bar_btn = nullptr;
    } ui_;

    inline static HHOOK keyboardHook = nullptr;
};
} // namespace keyboard

#endif