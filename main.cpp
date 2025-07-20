#include "mainwindow.h"
#include <QApplication>
PGresult *res;
PGconn *conn;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    char dbname[10], user[10], pwd[10];
    memcpy(dbname, "TestData", sizeof(dbname));
    memcpy(user, "postgres", sizeof(user));
    memcpy(pwd, "hkDQv2gn*", sizeof(pwd));
    conn = PQsetdbLogin(NULL, NULL, NULL, NULL, dbname, user, pwd);
    if(PQstatus(conn) == CONNECTION_BAD) {
        fprintf(stderr, "Connection to database failed.\n");
        fprintf(stderr, "%s", PQerrorMessage(conn));
        exit(1);
    }
    w.setWindowTitle("Хранение и обработка экспериментальных данных");
    w.show();
    return a.exec();
}
