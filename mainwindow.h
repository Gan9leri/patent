#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QMainWindow>
#include <QMainWindow>
#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include </usr/include/postgresql/libpq-fe.h>
#include <QCommonStyle>
#include <QTableWidget>
#include <QtGui>
#include <stdio.h>

class cell{
public:
    int type;
    int x;
    int y;
    union {
        double numeric_value;
        char string_value[100];
    };
    char sheet[100];
    int sheet_id;
};

class Cell_off_main_table{
public:
        int x;
        int y;
        char string_value[100];
};





extern  int sheet_counter;
extern int real_counter;
extern cell *Cells;
extern QString filename;
extern char *experiment_name;
extern char * series_name;
extern  PGresult *res;
extern PGconn *conn;
extern Cell_off_main_table *main_table;
extern int size_of_main_table;
extern cell *database_val;
extern int size_of_database_val;

//=======функции для работы с файлами==================//
void xls_parser();
void analyzing_txt_file(char *txt_file);
//====================================================//

//======функции для работы с базой===================//
void create_a_record_of_the_experiment();
void reate_a_record_of_the_series();
void create_records_in_measurement();
void add_records_of_the_measurement(int counter_of_series, int counter_of_experiments);
void upload_list_of_experiments();
void upload_list_of_the_series(int id_of_the_experiemnt);
void upload_list_of_measurement(int id_of_the_experiment, int id_of_the_series);
void upload_measurement(int id_of_the_measurement);
//===================================================//
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
