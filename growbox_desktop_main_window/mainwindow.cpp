#include <QtWidgets>
#include <QtSql>
#include <QSqlQuery>
#include <QMainWindow>
#include <QPixmap>
#include <QVector>
#include <QDateTime>
#include <QDebug>

#include "mainwindow.h"
#include <qcustomplot.h>

#include "./ui_mainwindow.h"
#include <connection.h>



MainWindow::MainWindow(const QString &tableName, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this);
    model->setTable("sensor_values");
    //model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //model->select();

    ui->customplot->xAxis->setLabel("Time");
    ui->customplot->yAxis->setLabel("Temp");

    ui->customplot->replot();

    setWindowIcon(QIcon("..\\growbox_desktop_main_window\\img\\icon.png"));
    setWindowTitle(tr("Growbox Desktop"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::submit()
{
    model->database().transaction();
    if (model->submitAll()) {
        model->database().commit();
    } else {
        model->database().rollback();
        QMessageBox::warning(this, tr("GrowBox Desktop"),
                             tr("The database reported an error: %1")
                             .arg(model->lastError().text()));
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    model->insertRow(model->rowCount());
}


void MainWindow::on_pushButton_clicked()
{
    model->removeRow(row);
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}


void MainWindow::on_progressBar_2_valueChanged(int value)
{
 //   value = 100;
    progressBar->setValue(progressBar->value()+100);
}



void MainWindow::on_pushButton_3_clicked()
{
    createConnection();

    model = new QSqlTableModel(this);
    model->setTable("sensor_values");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    ui->tableView->setModel(model);
}


void MainWindow::on_actionexit_please_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actiondownload_data_from_database_triggered()
{
    createConnection();

    model = new QSqlTableModel(this);
    model->setTable("sensor_values");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    ui->tableView->setModel(model);
}


void MainWindow::on_actioninfo_triggered()
{
    ui->statusbar->showMessage("Извините, информации нет, или обратитесь к Ефимову");
    info.show();
}

void MainWindow::on_actiondeath_laser_triggered()
{
    error.show();
}


void MainWindow::on_actioncreate_experiment_series_triggered()
{
    error.show();
}


void MainWindow::on_actionopen_experiment_series_triggered()
{
    error.show();
}



void MainWindow::on_actionadd_new_measurement_2_triggered()
{
    error.show();
}


void MainWindow::on_actionsoil_sensor_diagram_triggered()
{
    error.show();
}


void MainWindow::on_actioncameras_2_triggered()
{
    error.show();
}


void MainWindow::on_actiondatasheet_triggered()
{
    info.show();
}


void MainWindow::on_pushButton_5_clicked()
{
    int i = model->rowCount();
    QString s = QString::number(i);
    qDebug() << i;
    //qDebug() << model->rowCount();
    if(i<2){

        qDebug("in this");
        createConnection();
        model = new QSqlTableModel(this);
        model->setTable("sensor_values");
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();

        ui->tableView->setModel(model);
    }


    ui->customplot->xAxis->setLabel("Time");
    ui->customplot->yAxis->setLabel("Temp");

   // QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
   // dateTicker->setDateTimeFormat("dd/MM/yyyy hh:mm:ss");
   // ui->customplot->xAxis->setTicker(dateTicker);
    //qDebug(model->index(1, model->fieldIndex("sensor_time")).data().toString());
    //qDebug(model->index(1, model->fieldIndex("sensor_temperature")).data().toString());

    /*QVector<QCPGraphData> timeData(model->rowCount());

    for(int i=0; i< model->rowCount(); ++i){
        timeData[i].key = model->index(i, model->fieldIndex("sensor_time")).data().toDateTime().timeSpec();
        timeData[i].value = model->index(i, model->fieldIndex("sensor_temperature")).data().toDouble();
    }

    double Tmin = (*std::min_element(timeData.begin(), timeData.end(),[](const QCPGraphData& x, const QCPGraphData& y){  return x.key < y.key; })).key;

    double Tmax = (*std::max_element(timeData.begin(), timeData.end(), [](const QCPGraphData& x, const QCPGraphData& y) {  return x.key < y.key; })).key;

    double Ymin = (*std::min_element(timeData.begin(), timeData.end(), [](const QCPGraphData& x, const QCPGraphData& y) {  return x.value < y.value; })).value;

    double Ymax = (*std::max_element(timeData.begin(), timeData.end(),[](const QCPGraphData& x, const QCPGraphData& y) {  return x.value < y.value; })).value;
*/
    ui->customplot->xAxis->setRange(0, 1);
    ui->customplot->yAxis->setRange(0, 250);
    //ui->customplot->graph(0)->data()->set(timeData);
    //ui->customplot->replot();



    // add two new graphs and set their look:
    ui->customplot->addGraph();
    ui->customplot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    ui->customplot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
    ui->customplot->addGraph();
    ui->customplot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    // generate some points of data (y0 for first, y1 for second graph):
    QVector<double> x(251), y0(251), y1(251);
    for (int i=0; i<251; ++i)
    {
      x[i] = i;
      y0[i] = qExp(-i/150.0)*qCos(i/10.0); // exponentially decaying cosine
      y1[i] = qExp(-i/150.0);              // exponential envelope
    }
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
     ui->customplot->xAxis2->setVisible(true);
    ui->customplot->xAxis2->setTickLabels(false);
    ui->customplot->yAxis2->setVisible(true);
     ui->customplot->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect( ui->customplot->xAxis, SIGNAL(rangeChanged(QCPRange)),  ui->customplot->xAxis2, SLOT(setRange(QCPRange)));
    connect( ui->customplot->yAxis, SIGNAL(rangeChanged(QCPRange)),  ui->customplot->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
     ui->customplot->graph(0)->setData(x, y0);
     ui->customplot->graph(1)->setData(x, y1);
    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
     ui->customplot->graph(0)->rescaleAxes();
    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
     ui->customplot->graph(1)->rescaleAxes(true);
    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
     ui->customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->customplot->replot();
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->customplot->xAxis->setLabel("Time");
    ui->customplot->yAxis->setLabel("Temp");

    if (ui->customplot->graph(0))
    {
        ui->customplot->graph(0)->data()->clear();
        ui->customplot->graph(1)->data()->clear();
        ui->customplot->replot();
    }


}


void MainWindow::on_pushButton_4_clicked()
{
    error.show();
}


void MainWindow::on_pushButton_7_clicked()
{
     error.show();
}

