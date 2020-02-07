#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <sstream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // start up
    // G-Link
    connect(ui->lineEdit_glink_file_path, SIGNAL(textChange(QString)), this, SLOT(on_lineEdit_glink_file_path_textChanged()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// *** G-Link ***
// use file explorer to find file to format
void MainWindow::on_pushButton_glink_file_path_clicked()
{
    ui->lineEdit_glink_file_path->setText(QFileDialog::getOpenFileName(this, "Select G-Link file to format", QDir::homePath()));
}

// trim out file extension and display path preview
void MainWindow::on_lineEdit_glink_file_path_textChanged()
{
    glink_file = ui->lineEdit_glink_file_path->text();

    // change file extension to .txt
    size_t lastIndex = glink_file.toStdString().find_last_of(".");
    std::string rawName = glink_file.toStdString().substr(0, lastIndex);
    glink_out_file = rawName.append("_FORMATTED.txt");

    // display out file preview
    ui->label_glink_format_file_path->setText(QString::fromStdString(glink_out_file));
}

// format glink data into tab delimited acceleration data
void MainWindow::on_pushButton_glink_format_clicked()
{
    std::ofstream outFile(glink_out_file);
    std::ifstream inFile(glink_file.toStdString());
    std::string line, value, temp;
    std::vector<std::string> row;

    // parse header
    while (line != "DATA_START")
    {
        std::getline(inFile, line);
    }

    std::getline(inFile, line); // additional line before data

    // parse data
    std::stringstream ss;

    //TODO verify tabs
    while (std::getline(inFile, line))
    {
        row.clear();
        std::stringstream ss(line);

        while (std::getline(ss, value, ','))
        {
            row.push_back(value);
        }

        row.erase(row.begin() + 0); // erase time stamp

        for (auto i = row.begin(); i != row.end(); ++i)
        {

            if (next(i) != row.end())
            {
                //std::cout << *i << '\t';
                outFile << *i << '\t' << std::flush;
            }
            else
            {
                //std::cout << *i;
                outFile << *i << std::flush;
            }

        }

        //std::cout << std::endl;
        outFile << std::endl;
    }

}

// *** BioStamp ***

// use file explorer to find files to format and combine
void MainWindow::on_pushButton_biostamp_left_arm_file_path_clicked()
{
    ui->lineEdit_biostamp_left_arm_file_path->setText(QFileDialog::getOpenFileName(this, "Select BioStamp left arm accel.csv", QDir::homePath()));
}

void MainWindow::on_pushButton_biostamp_right_arm_file_path_clicked()
{
    ui->lineEdit_biostamp_right_arm_file_path->setText(QFileDialog::getOpenFileName(this, "Select BioStamp right arm accel.csv", QDir::homePath()));
}

void MainWindow::on_pushButton_biostamp_torso_file_path_clicked()
{
    ui->lineEdit_biostamp_torso_file_path->setText(QFileDialog::getOpenFileName(this, "Select BioStamp torso accel.csv", QDir::homePath()));
}

// get the file names for left arm, right arm, and torso data sets
void MainWindow::on_lineEdit_biostamp_left_arm_file_path_textChanged(const QString &arg1)
{
    biostamp_file_left_arm = arg1;
}

void MainWindow::on_lineEdit_biostamp_right_arm_file_path_textChanged(const QString &arg1)
{
    biostamp_file_right_arm = arg1;
}

void MainWindow::on_lineEdit_biostamp_torso_file_path_textChanged(const QString &arg1)
{
    biostamp_file_torso = arg1;
}

// format
void MainWindow::on_pushButton_biostamp_format_clicked()
{

    //TODO check left arm, right arm, and torso file paths are populated

    Samples samples;

}
