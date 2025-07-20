#include "mainwindow.h"
/*
 * create table list_of_experiments (name_of_the_experiment text, id_of_the_experiment integer);
create table list_of_series (name_of_the_series text, id_of_the_series integer, id_of_the_experiment integer);
create table list_of_measurement (name_of_the_measurement text, id_of_the_measurement integer, id_of_the_series integer , id_of_the_experiment integer);
create table measurement (type integer, x integer, y integer, id integer, numeric double precision, string text);
*/

Cell_off_main_table *main_table;
int size_of_main_table;
cell *database_val;
int size_of_database_val;

//========================функции для загрузки файла в базу=====================================================//
void create_a_record_of_the_experiment(){
    int QUERY_LEN = 1000, i, n, counter_of_experiments=0;
    char query[QUERY_LEN];
    memset(query, 0, QUERY_LEN);
    sprintf(query, "select id_of_the_experiment from list_of_experiments;");
    res = PQexec(conn, query);
    if (PQntuples(res) > 0){
        i = PQntuples(res)-1;
        n = PQnfields(res)-1;
        char str[10];
        memset(str, 0, 10);
        strcpy(str, PQgetvalue(res, i, n));
        counter_of_experiments = atoi(str);
        counter_of_experiments+=1;
    }
    if (PQntuples(res) == 0){
        counter_of_experiments=1;
    }
    memset(query, 0, QUERY_LEN);
    sprintf(query, "select name_of_the_experiment from list_of_experiments");
    res = PQexec(conn, query);
    int new_flag=0, flag =0, count=0;
    if (PQntuples(res) > 0){
        for(i = 0; i < PQntuples(res); i++) {
            for(n = 0; n < PQnfields(res); n++) {
                count = strcmp(experiment_name, PQgetvalue(res, i, n));
                if (count ==0) new_flag += 1;
            }
        }
    }
    if (new_flag != 0) flag = 1;
    if((flag == 0)||(PQntuples(res) == 0)){
        memset(query, 0, QUERY_LEN);
        sprintf(query, "insert into list_of_experiments (name_of_the_experiment, id_of_the_experiment) values ('%s', %d);", experiment_name, counter_of_experiments);
        res = PQexec(conn, query);
        memset(query, 0, QUERY_LEN);
    }
}

void reate_a_record_of_the_series(){
    int QUERY_LEN = 1000, counter_of_experiments, i=0,n=0, counter_of_series = 0, flag=0, flag_new = 0;
    char query[QUERY_LEN];
    memset(query, 0, QUERY_LEN);
    sprintf(query, "select id_of_the_experiment from list_of_experiments where name_of_the_experiment = '%s'", experiment_name);
    res = PQexec(conn, query);
    char str[100];
    strcpy(str, PQgetvalue(res, 0, 0));
    counter_of_experiments = atoi(str);
    memset(query, 0, QUERY_LEN);
    sprintf(query, "select name_of_the_series from list_of_series");
    res = PQexec(conn, query);
    if (PQntuples(res) > 0){
        for(i = 0; i < PQntuples(res); i++) {
            for(n = 0; n < PQnfields(res); n++) {
                if (strcmp(series_name, PQgetvalue(res, i, n)) == 0){
                    flag_new = 1;
                }
            }
        }
    }
    if (flag_new==1){
        memset(query, 0, QUERY_LEN);
        sprintf(query, "select id_of_the_experiment from list_of_series where name_of_the_series = '%s'", series_name);
        res = PQexec(conn, query);
        for(i = 0; i < PQntuples(res); i++) {
            for(n = 0; n < PQnfields(res); n++){
                char str2[100];
                strcpy(str2, PQgetvalue(res,i,n));
                int id=0;
                id = atoi(str2);
                if (id == counter_of_experiments) {
                    flag_new = 2;
                }
            }
        }
        if (flag_new == 2) flag = 1;
    }
    memset(query, 0, QUERY_LEN);
    sprintf(query, "select id_of_the_series from list_of_series;");
    res = PQexec(conn, query);
    if (PQntuples(res) > 0){
        i = PQntuples(res)-1;
        n = PQnfields(res)-1;
        char str1[100];
        strcpy(str1, PQgetvalue(res, i, n));
        counter_of_series = atoi(str1);
        counter_of_series+=1;
    }
    if (PQntuples(res) == 0){
        counter_of_series=1;
    }
    if((flag == 0)||(PQntuples(res) == 0)){
        memset(query, 0, QUERY_LEN);
        sprintf(query, "insert into list_of_series  values ('%s', %d, %d)", series_name, counter_of_series, counter_of_experiments );
        res = PQexec(conn, query);
        add_records_of_the_measurement(counter_of_series, counter_of_experiments);
    }
}

void add_records_of_the_measurement(int counter_of_series, int counter_of_experiments){
    int QUERY_LEN = 1000, counter_of_the_mesurement, i;
    char query[QUERY_LEN];
    memset(query, 0, QUERY_LEN);
    sprintf(query, "select id_of_the_measurement from list_of_measurement");
    res = PQexec(conn, query);
    int k =  PQntuples(res)-1, w = PQnfields(res)-1;
    if (PQntuples(res) > 0) {
        counter_of_the_mesurement = atoi(PQgetvalue(res, k, w));
        counter_of_the_mesurement++;
    }
    if (PQntuples(res) == 0) counter_of_the_mesurement=0;
    for (i=0; i<real_counter; i++){
        if (i==0){
            Cells[i].sheet_id = counter_of_the_mesurement;
            memset(query, 0, QUERY_LEN);
            sprintf(query, "insert into list_of_measurement values ('%s', %d , %d, %d)",Cells[i].sheet, Cells[i].sheet_id, counter_of_series, counter_of_experiments );
            res = PQexec(conn, query);
        }
        if ((i!=0) && (strcmp(Cells[i-1].sheet, Cells[i].sheet)!=0)){
            counter_of_the_mesurement++;
            Cells[i].sheet_id = counter_of_the_mesurement;
            memset(query, 0, QUERY_LEN);
            sprintf(query, "insert into list_of_measurement values ('%s', %d , %d, %d)",Cells[i].sheet, counter_of_the_mesurement, counter_of_series, counter_of_experiments );
            res = PQexec(conn, query);
        }
        if ((i!=0) && (strcmp(Cells[i-1].sheet, Cells[i].sheet)==0)) Cells[i].sheet_id = counter_of_the_mesurement;
    }
}

void create_records_in_measurement(){
    int QUERY_LEN = 1000, i, w;
    char query[QUERY_LEN];
    memset(query, 0, QUERY_LEN);
    for (i=0; i<real_counter; i++){
        if (Cells[i].type == 1) {
            memset(query, 0, QUERY_LEN);
            sprintf(query, "insert into measurement (type, x, y, id, numeric)  values (%d, %d, %d, %d, %lf);", Cells[i].type, Cells[i].x, Cells[i].y, Cells[i].sheet_id, Cells[i].numeric_value);
            for (w = strlen(query); query[w] != ','; w--);
            query[w]='.';
            res = PQexec(conn, query);
        }
        if (Cells[i].type == 2) {
            memset(query, 0, QUERY_LEN);
            sprintf(query, "insert into measurement (type, x, y, id, string )values (%d, %d, %d,  %d, '%s');", Cells[i].type, Cells[i].x, Cells[i].y, Cells[i].sheet_id, Cells[i].string_value);
            res = PQexec(conn, query);
        }
    }
}
//======================================================================================================================================//

//===================функции для выгрузки чего-либо из базы============================================================================//
void upload_list_of_experiments(){
    int QUERY_LEN = 1000, i,n,j=0;
    char query[QUERY_LEN];
    memset(query, 0, QUERY_LEN);
    sprintf(query, "SELECT * FROM list_of_experiments;");
    res = PQexec(conn, query);
    int local_fields = PQnfields(res), local_tuples = PQntuples(res);
    int size = local_fields * local_tuples;
    size_of_main_table = size;
    main_table = (Cell_off_main_table *)malloc((size+1) * sizeof(Cell_off_main_table));
    for(i = 0; i < PQntuples(res); i++) {
        for(n = 0; n < PQnfields(res); n++) {
            strcpy(main_table[j].string_value, PQgetvalue(res, i, n) );
            main_table[j].x = i;
            main_table[j].y = n;
            j++;
        }
    }
}

void upload_list_of_the_series(int id_of_the_experiemnt){
    int QUERY_LEN = 1000, i,n,j=0;
    char query[QUERY_LEN];
    memset(query, 0, QUERY_LEN);
    sprintf(query, "select name_of_the_series, id_of_the_series from list_of_series where id_of_the_experiment = %d", id_of_the_experiemnt );
    res = PQexec(conn, query);
    int local_fields = PQnfields(res), local_tuples = PQntuples(res);
    int size = local_fields * local_tuples;
    size_of_main_table = size;
    main_table = (Cell_off_main_table *)malloc((size+1) * sizeof(Cell_off_main_table));
    for(i = 0; i < PQntuples(res); i++) {
        for(n = 0; n < PQnfields(res); n++) {
            strcpy(main_table[j].string_value, PQgetvalue(res, i, n) );
            main_table[j].x = i;
            main_table[j].y = n;
            j++;
        }
    }
}

void upload_list_of_measurement(int id_of_the_experiment, int id_of_the_series){
    int QUERY_LEN = 1000, i,n,j=0;
    char query[QUERY_LEN];
    memset(query, 0, QUERY_LEN);
    sprintf(query, "select name_of_the_measurement, id_of_the_measurement from list_of_measurement where id_of_the_experiment = %d and id_of_the_series = %d", id_of_the_experiment, id_of_the_series );
    res = PQexec(conn, query);
    int local_fields = PQnfields(res), local_tuples = PQntuples(res);
    int size = local_fields * local_tuples;
    size_of_main_table = size;
    main_table = (Cell_off_main_table *)malloc((size+1) * sizeof(Cell_off_main_table));
    for(i = 0; i < PQntuples(res); i++) {
        for(n = 0; n < PQnfields(res); n++) {
            strcpy(main_table[j].string_value, PQgetvalue(res, i, n) );
            main_table[j].x = i;
            main_table[j].y = n;
            j++;
        }
    }
}

void upload_measurement(int id_of_the_measurement){
    int QUERY_LEN = 1000, i,n;
    char query[QUERY_LEN];
    memset(query, 0, QUERY_LEN);
    sprintf(query, "select type, x, y, numeric, string from measurement where id = %d", id_of_the_measurement);
    res = PQexec(conn, query);
    size_of_database_val = PQntuples(res);
    database_val = (cell *)malloc(size_of_database_val * sizeof(cell));
    for(i = 0; i < PQntuples(res); i++) {
        for(n = 0; n < PQnfields(res); n++) {//printf("%-20s", PQgetvalue(res, i, n));    printf("\n");
            char *str;
            str = (char *)malloc((strlen(PQgetvalue(res, i, n))+2) * sizeof(char));
            sprintf(str, "%s",  PQgetvalue(res, i, n));
            if (n==0){
                database_val[i].type = atoi(str);
            }
            if (n==1){
                database_val[i].x = atoi(str);
            }
            if (n==2){
                database_val[i].y = atoi(str);
            }
            if(n==3 && database_val[i].type == 1){
                int q=0;
                char k = ',';
                for (q = strlen(str)-1; str[q] != '.'; q--){
                    if (q<1) break;
                }
                if (q>=1) {
                    str[q]=k;
                }
                database_val[i].numeric_value = atof(str);
            }
            if(n==4 && database_val[i].type == 2){
                strcpy(database_val[i].string_value, PQgetvalue(res, i, n) );
            }
            free(str);
        }
    }
}

//=====================================================================================================================================//
