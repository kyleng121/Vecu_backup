#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <thread>

#include <QMainWindow>
#include <QListWidget>
#include <QPropertyAnimation>
#include <gRPC_shared_lib/lib_grpc_jetson/grpc_client_interface.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum class log_type
{
    airLog,
    seatLog,
    lightLog,
    statusLog
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_homeBtn_2_toggled(bool checked);

    void on_lightBtn_2_toggled(bool checked);

    void on_seatBtn_2_toggled(bool checked);

    void on_airBtn_2_toggled(bool checked);

    void on_lightLevel_valueChanged(int value);

    void on_onLightBtn_clicked();

    void on_offLightBtn_clicked();

    void on_offAirBtn_clicked();

    void on_onAirBtn_clicked();

    void on_airLevel_valueChanged(int value);

    void on_airLevel1Btn_clicked();

    void on_airLevel2Btn_clicked();

    void on_airLevel3Btn_clicked();

    void on_airLevel4Btn_clicked();

    void on_upSeatBtn_clicked();

    void on_downSeatBtn_clicked();

    void on_seatLevel_valueChanged(int value);

    void GrpcReadThread();

    void LOG(std::string content, QListWidget* logWidget);

private:
    Ui::MainWindow *ui;
    std::shared_ptr<GrpcClientInterface> client_;
    std::string light_control_api = "Vehicle.Cabin.Light.AmbientLight.Row1.DriverSide.Intensity";
    std::string air_control_api = "Vehicle.Cabin.HVAC.Station.Row1.Driver.FanSpeed";
    std::string seat_control_api = "Vehicle.Cabin.Seat.Row1.DriverSide.Position";
    std::string button_state_read_api = "Vehicle.Cabin.Button";
    uint32_t seat_position_val;

    std::thread grpcReadThread;
    uint32_t readThreadRunning;
    uint32_t buttonState_current;
    uint32_t buttonState_previous;

};
#endif // MAINWINDOW_H
