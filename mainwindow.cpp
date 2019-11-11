#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // start up
    // G-Link-200
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
    ui->lineEdit_glink_file_path->setText(QFileDialog::getOpenFileName(this, "Select G-Link-200 file to format", QDir::homePath()));
}
