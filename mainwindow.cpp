#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <sstream>

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

// trim out file extenstion and display path preview
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

// use file explorer to find file to format
void MainWindow::on_pushButton_glink_file_path_clicked()
{
    ui->lineEdit_glink_file_path->setText(QFileDialog::getOpenFileName(this, "Select G-Link file to format", QDir::homePath()));
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
