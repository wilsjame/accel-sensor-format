#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // *** G-Link ***
    void on_lineEdit_glink_file_path_textChanged();

    void on_pushButton_glink_file_path_clicked();

    void on_pushButton_glink_format_clicked();

private:
    Ui::MainWindow *ui;

    // *** G-Link ***
    QString glink_file;
    std::string glink_out_file;
};
#endif // MAINWINDOW_H
