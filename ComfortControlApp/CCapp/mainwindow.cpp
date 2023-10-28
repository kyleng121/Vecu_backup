#include <unistd.h>
#include <stdint.h>
#include <iostream>
#include <string>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      seat_position_val(0),
      readThreadRunning(0),
      buttonState_current(0),
      buttonState_previous(0)

{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    QFile file(":/resource/resource/style/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    setStyleSheet(styleSheet);
    ClientBuilder tmpBuilder;
    client_ = tmpBuilder.CreateClient(std::string("192.168.56.49:55555"));

    std::cout << "Starting gRPC reading thread..." << std::endl;
    readThreadRunning = 1;
    grpcReadThread = std::thread(std::bind(&MainWindow::GrpcReadThread, this));
}

MainWindow::~MainWindow()
{
    readThreadRunning = 0;
    if (grpcReadThread.joinable())
    {
        grpcReadThread.join();
    }
    else
    {
        grpcReadThread.detach();
    }
    delete ui;
}

void MainWindow::GrpcReadThread()
{
    std::cout << "gRPC read thread running..." << std::endl;
    while (readThreadRunning)
    {
        usleep(100000);
        buttonState_previous = buttonState_current;
        buttonState_current = client_->GetDatapoint(button_state_read_api);
        if (buttonState_previous != buttonState_current)
            LOG(buttonState_current > 0 ? "Button is TRUE" : "Button is FALSE", ui->statusLog);
    }
    std::cout << "gRPC read thread ending..." << std::endl;
}

void MainWindow::LOG(std::string content, QListWidget* logWidget)
{
    logWidget->addItem(content.c_str());
}

void MainWindow::on_homeBtn_2_toggled(bool checked)
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_lightBtn_2_toggled(bool checked)
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_seatBtn_2_toggled(bool checked)
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_airBtn_2_toggled(bool checked)
{
    ui->stackedWidget->setCurrentIndex(2);
}

// Light Control

void MainWindow::on_lightLevel_valueChanged(int value)
{
    client_->SetDatapoint(light_control_api,(uint32_t)value);
    LOG("Light Value: " + std::to_string(value), ui->lightLog);
}

void MainWindow::on_onLightBtn_clicked()
{
    client_->SetDatapoint(light_control_api,(uint32_t)255);
    LOG("set Light On", ui->lightLog);
}

void MainWindow::on_offLightBtn_clicked()
{
    client_->SetDatapoint(light_control_api,(uint32_t)0);
    LOG("set Light OFF", ui->lightLog);
}

// Air Condition Control

void MainWindow::on_airLevel_valueChanged(int value)
{
    client_->SetDatapoint(air_control_api,(uint32_t)value);
    LOG("Air Value: " + std::to_string(value), ui->airLog);
}

void MainWindow::on_offAirBtn_clicked()
{
    LOG("set Air Conditioner OFF", ui->airLog);
    ui->airLevel->setSliderPosition(0);
}

void MainWindow::on_onAirBtn_clicked()
{
    LOG("set Air Conditioner ON", ui->airLog);
    ui->airLevel->setSliderPosition(100);
}

void MainWindow::on_airLevel1Btn_clicked()
{
    LOG("Air Value: Level 1", ui->airLog);
    ui->airLevel->setSliderPosition(64);
}
void MainWindow::on_airLevel2Btn_clicked()
{
    LOG("Air Value: Level 2", ui->airLog);
    ui->airLevel->setSliderPosition(128);
}

void MainWindow::on_airLevel3Btn_clicked()
{
    LOG("Air Value: Level 3", ui->airLog);
    ui->airLevel->setSliderPosition(191);
}

void MainWindow::on_airLevel4Btn_clicked()
{
    LOG("Air Value: Level 4", ui->airLog);
    ui->airLevel->setSliderPosition(255);
}

// Seat Control

void MainWindow::on_seatLevel_valueChanged(int value)
{
    client_->SetDatapoint(seat_control_api,(uint32_t)value);
    LOG("Seat Position Value: " + std::to_string(value), ui->seatLog);
}

void MainWindow::on_upSeatBtn_clicked()
{
    seat_position_val += 25;
    if (seat_position_val > 255)
        seat_position_val = 255;
    LOG("Seat Position: Up", ui->seatLog);
    ui->seatLevel->setSliderPosition(seat_position_val);
}

void MainWindow::on_downSeatBtn_clicked()
{
    if (seat_position_val >= 25)
        seat_position_val-=25;
    else
        seat_position_val = 0;
    LOG("Seat Position: Down", ui->seatLog);
    ui->seatLevel->setSliderPosition(seat_position_val);
}
