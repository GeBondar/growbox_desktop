#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QSqlQuery>
#include <dialog_error.h>
#include <info_link.h>

//#include <anotherwindow.h>

class QProgressBar;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QSqlTableModel;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QString &tableName, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void submit();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_progressBar_2_valueChanged(int value);

    void on_pushButton_3_clicked();

    void on_actionexit_please_triggered();

    void on_actiondownload_data_from_database_triggered();

    void on_actioninfo_triggered();

    //void on_actiondatasheet_triggered();

    void on_actiondeath_laser_triggered();

    void on_actioncreate_experiment_series_triggered();

    void on_actionopen_experiment_series_triggered();

    void on_actionadd_new_measurement_2_triggered();

    void on_actionsoil_sensor_diagram_triggered();

    void on_actioncameras_2_triggered();

    void on_actiondatasheet_triggered();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *model;
    QSqlQuery *query;

    QProgressBar *progressBar;

    Dialog_error error;
    info_link info;
    //AnotherWindow *sWindow;
    //AnotherWindow *thirdWindow;

    int row; //active number of row
};

#endif // MAINWINDOW_H
