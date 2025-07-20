#include "mainwindow.h"
int real_counter;
cell *Cells;
int sheet_counter;

void xls_parser(){
    QByteArray ba = filename.toLocal8Bit();
    char *xls_file = ba.data();
    int i,q=0, n=0;
    char txt_file[strlen(xls_file)+1];
    strcpy(txt_file, xls_file);
    txt_file[strlen(txt_file)-1] = 't';
    txt_file[strlen(txt_file)-2] = 'x';
    txt_file[strlen(txt_file)-3] = 't';
    int len_str = strlen(txt_file);
    for(i=0; i<len_str; i++) if(txt_file[i]=='/') q = i;
    q++;
    series_name = (char*)malloc(strlen(txt_file)-q-3);
    len_str = strlen(txt_file);
    for(i=0; i<len_str-q-4; i++, n++) series_name[i] = txt_file[i+q];
    series_name[n] = '\0';
    i=0;
    n=0;
    q=0;
    len_str = strlen(txt_file);
    for(i=0; i<len_str; i++) if(txt_file[i]=='/') q = i;
    q++;
    char *command;
    command = (char*)malloc( ((strlen(xls_file)+strlen(txt_file))*2) * sizeof(char));
    sprintf(command, "./libxls/src/xls2csv '%s' > '%s'", xls_file, txt_file);
    system(command);
    analyzing_txt_file(txt_file);
}

void analyzing_txt_file(char *txt_file){
    char buf[100];
    memset(buf, 0, 100);
    FILE *counter;
    counter = fopen("/home/roland/build-finalwork15-Desktop-Debug/libxls/src/counter.dat", "r+");
    //fgets(buf, 100, counter);
    //sheet_counter = atoi(buf);
   // memset(buf, 0, 100);
    fscanf(counter, "%s", buf);
    real_counter = atoi(buf);
    fclose(counter);
    Cells = (cell*)malloc(real_counter*sizeof(cell));
    int type = 1, i=0, coordinate_x=0, coordinate_y = 0, value = 0, sheet = 0;
    FILE *file;
    file = fopen(txt_file, "r+");
    memset(buf, 0, 100);
    while(feof(file)==0){
        memset(buf, 0, 100);
        fgets(buf, 100, file);
        if (buf[strlen(buf)-1]=='\n') buf[strlen(buf)-1]='\0';
        if ( (type == 1) && (buf[0]!='\0')) {
            int type_new = atoi(buf);
            if (type_new !=3) {
                Cells[i].type = type_new;
                coordinate_x=1;
            }
            type =0;
            continue;
        }
        if ((coordinate_x == 1)){
            Cells[i].x = atoi(buf);
            coordinate_x=0;
            coordinate_y=1;
            continue;
        }
        if(coordinate_y == 1 ){
            Cells[i].y = atoi(buf);
            coordinate_y=0;
            value = 1;
            continue;
        }
        if(value == 1){
            if(Cells[i].type ==1 ) {
                int k, z = strlen(buf);
                for (k = 0; k<z; k++){
                    if (buf[k]=='.') buf[k] = ',';
                }
                Cells[i].numeric_value = atof(buf);
            }
            if(Cells[i].type ==2 ) {
                strcpy(Cells[i].string_value, buf);
            }
            value = 0;
            sheet = 1;
            continue;
        }
        if(sheet == 1){
            strcpy(Cells[i].sheet, buf);
            sheet = 0;
            i++;
            continue;
        }
        if (buf[0]=='\0') {
            type = 1;
        }
    }
    fclose(file);


}
