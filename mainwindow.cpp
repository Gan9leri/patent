#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui -> spinBox-> setRange(0,1000);
    ui -> spinBox_2-> setRange(0,1000);
    ui -> spinBox_3-> setRange(0,1000);
    ui -> spinBox_4-> setRange(0,1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked()
{
    int form;
    int potential1 = ui -> spinBox->value();
    int potential2 = ui ->spinBox_2->value();
    int edge_length = ui -> spinBox_3 ->value();
    if (ui -> radioButton-> isChecked() == 1) form = 1;
    if (ui -> radioButton_2 -> isChecked() == 1) form = 2;
    int n = ui -> spinBox_4->value();
    double dx = ui ->doubleSpinBox_6->value();
    double dy = ui ->doubleSpinBox_7->value();
    double f = ui ->doubleSpinBox_8->value();
    double electron_density = ui ->doubleSpinBox-> value();
    double hole_density = ui->doubleSpinBox_2->value();
    double electron_mobility = ui ->doubleSpinBox_3->value();
    double hole_mobility = ui->doubleSpinBox_4->value();
    double r = ui->doubleSpinBox_5->value();
    double alpha = ui -> doubleSpinBox_9->value();
    int grafic = 2;
    FILE *file;
    file = fopen("/home/roland/build-ModelingHoll3-Desktop-Debug/parametres.dat", "w+");
    fprintf(file, "%d\n", potential1);
    fprintf(file, "%d\n", potential2);
    fprintf(file, "%d\n", edge_length);
    fprintf(file, "%d\n", form);
    fprintf(file, "%d\n", n);
    fprintf(file, "%lf\n", dx);
    fprintf(file, "%lf\n", dy);
    fprintf(file, "%lf\n", f);
    fprintf(file, "%lf\n", electron_density);
    fprintf(file, "%lf\n", hole_density);
    fprintf(file, "%lf\n", electron_mobility);
    fprintf(file, "%lf\n", hole_mobility);
    fprintf(file, "%lf\n", r);
    fprintf(file, "%lf\n", alpha);
    fprintf(file, "%d\n", grafic);
    fclose(file);
    system("/home/roland/build-ModelingHoll3-Desktop-Debug/modeling_holl8");
}

void MainWindow::on_pushButton_2_clicked()
{
    int form;
    int potential1 = ui -> spinBox->value();
    int potential2 = ui ->spinBox_2->value();
    int edge_length = ui -> spinBox_3 ->value();
    if (ui -> radioButton-> isChecked() == 1) form = 1;
    if (ui -> radioButton_2 -> isChecked() == 1) form = 2;
    int n = ui -> spinBox_4->value();
    double dx = ui ->doubleSpinBox_6->value();
    double dy = ui ->doubleSpinBox_7->value();
    double f = ui ->doubleSpinBox_8->value();
    double electron_density = ui ->doubleSpinBox-> value();
    double hole_density = ui->doubleSpinBox_2->value();
    double electron_mobility = ui ->doubleSpinBox_3->value();
    double hole_mobility = ui->doubleSpinBox_4->value();
    double r = ui->doubleSpinBox_5->value();
    double alpha = ui -> doubleSpinBox_9->value();
    int grafic = 1;
    FILE *file;
    file = fopen("/home/roland/build-ModelingHoll3-Desktop-Debug/parametres.dat", "w+");
    fprintf(file, "%d\n", potential1);
    fprintf(file, "%d\n", potential2);
    fprintf(file, "%d\n", edge_length);
    fprintf(file, "%d\n", form);
    fprintf(file, "%d\n", n);
    fprintf(file, "%lf\n", dx);
    fprintf(file, "%lf\n", dy);
    fprintf(file, "%lf\n", f);
    fprintf(file, "%lf\n", electron_density);
    fprintf(file, "%lf\n", hole_density);
    fprintf(file, "%lf\n", electron_mobility);
    fprintf(file, "%lf\n", hole_mobility);
    fprintf(file, "%lf\n", r);
    fprintf(file, "%lf\n", alpha);
    fprintf(file, "%d\n", grafic);
    fclose(file);
    system("/home/roland/build-ModelingHoll3-Desktop-Debug/modeling_holl8");
    //system("gnuplot  'main.gnu' &");
}

void MainWindow::on_pushButton_3_clicked()
{
    int form;
    int potential1 = ui -> spinBox->value();
    int potential2 = ui ->spinBox_2->value();
    int edge_length = ui -> spinBox_3 ->value();
    if (ui -> radioButton-> isChecked() == 1) form = 1;
    if (ui -> radioButton_2 -> isChecked() == 1) form = 2;
    int n = ui -> spinBox_4->value();
    double dx = ui ->doubleSpinBox_6->value();
    double dy = ui ->doubleSpinBox_7->value();
    double f = ui ->doubleSpinBox_8->value();
    double electron_density = ui ->doubleSpinBox-> value();
    double hole_density = ui->doubleSpinBox_2->value();
    double electron_mobility = ui ->doubleSpinBox_3->value();
    double hole_mobility = ui->doubleSpinBox_4->value();
    double r = ui->doubleSpinBox_5->value();
    double alpha = ui -> doubleSpinBox_9->value();
    int grafic = 4;
    FILE *file;
    file = fopen("/home/roland/build-ModelingHoll3-Desktop-Debug/parametres.dat", "w+");
    fprintf(file, "%d\n", potential1);
    fprintf(file, "%d\n", potential2);
    fprintf(file, "%d\n", edge_length);
    fprintf(file, "%d\n", form);
    fprintf(file, "%d\n", n);
    fprintf(file, "%lf\n", dx);
    fprintf(file, "%lf\n", dy);
    fprintf(file, "%lf\n", f);
    fprintf(file, "%lf\n", electron_density);
    fprintf(file, "%lf\n", hole_density);
    fprintf(file, "%lf\n", electron_mobility);
    fprintf(file, "%lf\n", hole_mobility);
    fprintf(file, "%lf\n", r);
    fprintf(file, "%lf\n", alpha);
    fprintf(file, "%d\n", grafic);
    fclose(file);
    system("/home/roland/build-ModelingHoll3-Desktop-Debug/modeling_holl8");
}


void MainWindow::on_pushButton_4_clicked()
{
    int form;
    int potential1 = ui -> spinBox->value();
    int potential2 = ui ->spinBox_2->value();
    int edge_length = ui -> spinBox_3 ->value();
    if (ui -> radioButton-> isChecked() == 1) form = 1;
    if (ui -> radioButton_2 -> isChecked() == 1) form = 2;
    int n = ui -> spinBox_4->value();
    double dx = ui ->doubleSpinBox_6->value();
    double dy = ui ->doubleSpinBox_7->value();
    double f = ui ->doubleSpinBox_8->value();
    double electron_density = ui ->doubleSpinBox-> value();
    double hole_density = ui->doubleSpinBox_2->value();
    double electron_mobility = ui ->doubleSpinBox_3->value();
    double hole_mobility = ui->doubleSpinBox_4->value();
    double r = ui->doubleSpinBox_5->value();
    double alpha = ui -> doubleSpinBox_9->value();
    int grafic = 3;
    FILE *file;
    file = fopen("/home/roland/build-ModelingHoll3-Desktop-Debug/parametres.dat", "w+");
    fprintf(file, "%d\n", potential1);
    fprintf(file, "%d\n", potential2);
    fprintf(file, "%d\n", edge_length);
    fprintf(file, "%d\n", form);
    fprintf(file, "%d\n", n);
    fprintf(file, "%lf\n", dx);
    fprintf(file, "%lf\n", dy);
    fprintf(file, "%lf\n", f);
    fprintf(file, "%lf\n", electron_density);
    fprintf(file, "%lf\n", hole_density);
    fprintf(file, "%lf\n", electron_mobility);
    fprintf(file, "%lf\n", hole_mobility);
    fprintf(file, "%lf\n", r);
    fprintf(file, "%lf\n", alpha);
    fprintf(file, "%d\n", grafic);
    fclose(file);
    system("/home/roland/build-ModelingHoll3-Desktop-Debug/modeling_holl8");
}

