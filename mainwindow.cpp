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

    // *** G-Link ***
    // start up
    connect(ui->lineEdit_glink_file_path, SIGNAL(textChange(QString)), this, SLOT(on_lineEdit_glink_file_path_textChanged()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// *** G-Link ***
//
// Use file explorer to find in file to format. Default directory is user's home path.
//
void MainWindow::on_pushButton_glink_file_path_clicked()
{
    ui->lineEdit_glink_file_path->setText(QFileDialog::getOpenFileName(this, "Select G-Link file to format", QDir::homePath()));
}

//
// Trim in file extension and display out file path preview.
//
void MainWindow::on_lineEdit_glink_file_path_textChanged()
{
    glink_file = ui->lineEdit_glink_file_path->text();

    // change file extension to .txt
    size_t lastIndex = glink_file.toStdString().find_last_of(".");
    std::string rawName = glink_file.toStdString().substr(0, lastIndex);
    glink_out_file = rawName.append("_FORMATTED.csv");

    // display out file preview
    ui->label_glink_format_file_path->setText(QString::fromStdString(glink_out_file));
}


// The older glink sensor output had one time header.
// glinkcombine.vi checks the first 4 characters of each header
// and expects only one header to start with "Time".
// The newer glink sensor output has multitple headers that
// begin with "Time" before the data actually starts.
// This trims all the headers before the true time header
// so glinkcombine.vi can take the file as input as if it
// was an older glink sensor output.
void MainWindow::on_pushButton_glink_format_clicked()
{
     if (glink_file == "") {
        return;
    }

    std::ofstream outFile(glink_out_file);
    std::ifstream inFile(glink_file.toStdString());
    std::string line;

    // parse file header ignore all lines before data
    while (line != "DATA_START")
    {
        std::getline(inFile, line);
    }

    while (std::getline(inFile, line))
    {
        outFile << line << std::endl;
    }

}

// STALE: assumes input data is 3 glink sensor results outputted into one file. ex) xyz xyz xyz
//
// Format glink data into tab delimited acceleration data and write to out file.
//
/*
void MainWindow::on_pushButton_glink_format_clicked()
{
    if (glink_file == "") {
        return;
    }

    std::ofstream outFile(glink_out_file);
    std::ifstream inFile(glink_file.toStdString());
    std::string line, value, temp;
    std::vector<std::string> row;

    // parse file header ignore all lines before data
    while (line != "DATA_START")
    {
        std::getline(inFile, line);
    }

    std::getline(inFile, line); // additional line before data

    // parse data
    std::stringstream ss;

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
                //std::cerr << *i << '\t';
                outFile << *i << '\t' << std::flush;
            }
            else
            {
                //std::cerr << *i;
                outFile << *i << std::flush;
            }

        }

        //std::cerr << std::endl;
        outFile << std::endl;
    }

}
*/
