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

    void on_pushButton_glink_file_path_clicked();

    void on_pushButton_glink_format_clicked();

    void on_pushButton_biostamp_right_arm_file_path_clicked();

    void on_pushButton_biostamp_left_arm_file_path_clicked();

    void on_pushButton_biostamp_torso_file_path_clicked();

    void on_pushButton_biostamp_format_clicked();

    void on_lineEdit_biostamp_left_arm_file_path_textChanged(const QString &arg1);

    void on_lineEdit_biostamp_right_arm_file_path_textChanged(const QString &arg1);

    void on_lineEdit_biostamp_torso_file_path_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

    // G-Link
    QString glink_file;
    std::string glink_out_file;

    // BioStamp
    QString biostamp_file_left_arm;
    QString biostamp_file_right_arm;
    QString biostamp_file_torso;
    std::string biostamp_out_file;

    struct Sample
    {
        float left_x;
        float left_y;
        float left_z;
        float right_x;
        float right_y;
        float right_z;
        float torso_x;
        float torso_y;
        float torso_z;
    };

    typedef std::vector<Sample> Samples;

};
#endif // MAINWINDOW_H
