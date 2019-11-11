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
    void on_lineEdit_glink_file_path_textChanged();

private:
    Ui::MainWindow *ui;

    // G-Link-200
    QString glink_file;
    std::string glink_out_file;

    // nPoint
};
#endif // MAINWINDOW_H
