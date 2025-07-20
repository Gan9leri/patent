#include "mainwindow.h"
#include "ui_mainwindow.h"
QString filename;
char *experiment_name;
char * series_name;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui -> spinBox-> setRange(0,1000);
    ui -> spinBox_2-> setRange(0,1000);
    ui -> spinBox_3-> setRange(0,1000);
    ui -> spinBox_4-> setRange(0,1000);
    ui -> spinBox_5-> setRange(0,1000);
    ui -> spinBox_6-> setRange(0,1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    filename = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr(""));
    xls_parser();
    QString str= ui -> textEdit ->toPlainText();
    QByteArray ba = str.toLocal8Bit();
    experiment_name = ba.data();
    create_a_record_of_the_experiment();
    reate_a_record_of_the_series();
    create_records_in_measurement();
}

void MainWindow::on_pushButton_2_clicked()
{
    int id_of_the_experiment = ui -> spinBox -> value();
    int id_of_the_series = ui -> spinBox_2 -> value();
    upload_list_of_measurement(id_of_the_experiment, id_of_the_series);
    int i;
    QStandardItemModel *model = new QStandardItemModel(0,0,this);
    for (i=0; i< size_of_main_table; i++){
        QStandardItem *firstRow;
        firstRow = new QStandardItem(main_table[i].string_value);
        int x = main_table[i].x,y = main_table[i].y;
        model->setItem(x,y, firstRow);
    }
    free(main_table);
    ui->tableView_3->setModel(model);
}

void MainWindow::on_pushButton_3_clicked()
{
    int id_of_the_experiemnt = ui -> spinBox_3-> value();
    upload_list_of_the_series(id_of_the_experiemnt);
    int i;
    QStandardItemModel *model = new QStandardItemModel(0,0,this);
    for (i=0; i< size_of_main_table; i++){
        QStandardItem *firstRow;
        firstRow = new QStandardItem(main_table[i].string_value);
        int x = main_table[i].x,y = main_table[i].y;
        model->setItem(x,y, firstRow);
    }
    free(main_table);
    ui->tableView_2->setModel(model);
}

void MainWindow::on_pushButton_4_clicked()
{
    upload_list_of_experiments();
    int i;
    QStandardItemModel *model = new QStandardItemModel(0,0,this);
    for (i=0; i< size_of_main_table; i++){
        QStandardItem *firstRow;
        firstRow = new QStandardItem(main_table[i].string_value);
        int x= main_table[i].x, y = main_table[i].y;
        model->setItem(x,y, firstRow);
    }
    free(main_table);
    ui->tableView->setModel(model);
}

void MainWindow::on_pushButton_5_clicked()
{
    int id_of_the_measurement = ui -> spinBox_4->value();
    upload_measurement(id_of_the_measurement);
    int i, max_x=0, max_y=0;
    for (i=0;i<size_of_database_val;i++){
        if (database_val[i].x > max_x) {
            max_x = database_val[i].x;
        }
        if (database_val[i].y > max_y) {
            max_y = database_val[i].y;
        }
    }
    QStandardItemModel *model = new QStandardItemModel(max_x,max_y,this);
    for (i=0; i< size_of_database_val; i++){
        QStandardItem *firstRow;
        if(database_val[i].type==2){
            firstRow = new QStandardItem(database_val[i].string_value);
        }
        if(database_val[i].type==1){
            firstRow = new QStandardItem((QString::number(database_val[i].numeric_value)));
        }
        int x = database_val[i].x ,y = database_val[i].y;
        model->setItem(x,y, firstRow);
    }
    ui->tableView_4->setModel(model);
}

void MainWindow::on_pushButton_6_clicked()
{
    system("/home/roland/build-ModelingHoll3-Desktop-Debug/ModelingHoll3");
}

void MainWindow::on_pushButton_7_clicked()
{
    int a =ui->spinBox_5  ->value();
    int b =ui->spinBox_6->value();
    a--;
    b--;
    int i, q=0, size_x=0, size_y=0, w=0;
    for(i=0; i<size_of_database_val; i++){
        if (database_val[i].y==a && database_val[i].type == 1){
            size_x++;
        }
        if (database_val[i].y==b && database_val[i].type == 1){
            size_y++;
        }
    }
    QVector<double> x(size_x), y(size_y);
    double x_max = x[0], y_max=y[0], y_min = y[0];
    for(i=0; i<size_of_database_val; i++){
        if (database_val[i].y==a && database_val[i].type == 1){
            x[q]= database_val[i].numeric_value;
            if (x[q]>x_max) x_max=x[q];
            q++;
        }
        if (database_val[i].y==b && database_val[i].type == 1){
            y[w]= database_val[i].numeric_value;
            if (y[w]>y_max) y_max=y[w];
            if (y[w]<y_min) y_min=y[w];
            w++;
        }
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x, y);
    ui->widget->xAxis->setLabel("(U1-U2)/2");
    ui->widget->yAxis->setLabel("Угол а");
    ui->widget->xAxis->setRange(0, x_max);
    ui->widget->yAxis->setRange(y_min, y_max);
    ui->widget->replot();
}
