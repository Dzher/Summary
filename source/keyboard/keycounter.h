#include <QMap>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

class KeyCounter : public QWidget
{
public:
    KeyCounter(QWidget* parent = nullptr);
    ~KeyCounter();

private:
    void initUi();
    void signalConnect();
    void showPieChart();
    void showBarChart();
    void filter();
    void exportFile();

private:
    QMap<Qt::Key, unsigned int> key_map_;
    struct
    {
        QPushButton* pie_btn = nullptr;
        QPushButton* bar_btn = nullptr;
        QPushButton* cloud_btn = nullptr;
        QPushButton* dot_btn = nullptr;
        QPushButton* line_btn = nullptr;
        QPushButton* percent_bar_btn = nullptr;
    } ui_;
};