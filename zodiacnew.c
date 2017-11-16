#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define TRUE  1
#define FALSE  0


//VARIABEL GLOBAL

char userMonth[20];                                         //PERPENDEK LAGI CODENYA//
char userWuku[20];                                         //HIAS OR NOT? :thonkang://
char userName[20];                                          //PELAJARI SAVE FILE//
char userZodiac[20];
char userBirthday[20];

                    //list wuku disini
char *wukudef[30] = {"Watugunung","Sinta","Landep","Ukir","Kulantir","Tolu","Gumbreg","Wariga","Warigadean",
"Julungwangi","Sungsang","Dungulan","Kuningan","Langkir","Medangsia","Pujut","Pahang","Klurut","Merakih",
"Tambir","Medangkungan","Matal","Uye","Menail","Perangbakat","Bala","Ugu","Wayang","Kulawu","Dukut"};

                    //list bulan disini
char *monthdef[12] = {"January ","February ","March ","April ","May ","June ","July ","August ","September ","October ","November ","December "};

typedef struct birthday{
    int day;
    int month;
    int year;
} birthdayStruct;

typedef struct today{
    int day;
    int month;
    int year;
} todayStruct;

typedef struct parameter_yes{
    int y ;
    int Y ;
} parameterYes;

typedef struct parameter_no{
    int n;
    int N;
} parameterNo;

//DEKLARASI FUNGSI DAN PROSEDUR//

int get_weeks(int birthdayYear,int birthdayMonth, int birthdayDay);//Fungsi mendapatkan wuku

birthdayStruct check_birth_valid(int day,int month,int year);//Fungsi mengecek kebenaran tanggal lahir
birthdayStruct input_birthday();//Fungsi untuk menginput tanggal lahir user
todayStruct today_date();//Fungsi untuk mendapatkan tanggal hari ini

char * get_month_name(int month); //Fungsi mendapatkan nama bulan 
char *get_wuku(int countWeeks);//Prosedur print wuku
char * get_user_name();//Fungsi mendapatkan user name 
char *get_zodiac(int month,int day);//Prosedur cetak zodiac

void print_error(int checkDay,int checkMonth, int checkYear);//Prosedur cetak error
void print_age(int day,int month,int year,int todayDay,int todayMonth,int todayYear);//Prosedur print umur
void get_wuku_zodiac (int day,int month,int year,int todayDay,int todayMonth,int todayYear,char* userName);//Prosedur print Profile User Name
void registration();//Fungsi sebagai bagian utama dari bagian untuk meramal
void clear_buffer(); //Fungsi clear buffer stdin
void put_to_file(char * userName,char * userWuku, char * userZodiac ,int birthdayDay,int birthdayMonth,int birthdayYear);
void check_username_valid(char * userName);
void user_interface();
void menu();
void get_user_profile();
void reset();//Fungsi mereset program


int main(){
    user_interface();
    menu();
    return 0;   
}

void user_interface(){
    printf("PROGRAM RAMALAN by : \nNila Arta & Bagus Prasetyo\n\n(RENTANG TANGGAL 1 JANUARI 1917 - 31 DESEMBER 2117)\n\n");
    todayStruct today = today_date();
    printf("Tanggal saat ini: %d %s %d\n\n",today.day,get_month_name(today.month),today.year);
    return;
}

void menu(){
    int choice;

    printf("Pilih Menu :\n\n");
    printf("1.Mendaftar \n");
    printf("2.Melihat Profile User \n");
    printf("3.Exit Program\n\n");
    printf("Pilihan : ");
    scanf("%d",&choice);
    clear_buffer();
    system("cls");
    switch(choice){
        case 1 :
            user_interface();
            registration();
            break;
        case 2 :
            user_interface();
            get_user_profile();
            break;
        case 3 :
            return;
        default :
            user_interface();
            printf("Pesan Error : Invalid Input!\n\n");
            menu();
    }
}

void registration(){

    birthdayStruct birthday;
    birthdayStruct check;
    todayStruct today;
    int parameter_reset;
   
    today = today_date();
    strcpy(userName,get_user_name());
    birthday = input_birthday();
    clear_buffer(); // habis input string selalu inget clear buffer
    check = check_birth_valid(birthday.day,birthday.month,birthday.year);
    if ((check.day == FALSE) || (check.month == FALSE) || (check.year == FALSE)){
        
        print_error(check.day,check.month,check.year);
        
    } else {
        
        get_wuku_zodiac (birthday.day,birthday.month,birthday.year,today.day,today.month,today.year,userName);
        put_to_file(userName,userWuku,userZodiac,birthday.day,birthday.month,birthday.year);

    }        
        reset();
}

//Tolong inget pelajari ini since you cuman copas
todayStruct today_date(){
   

    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);
    todayStruct today;
    
    today.day = aTime->tm_mday;
    today.month = aTime->tm_mon + 1; 
    today.year = aTime->tm_year + 1900;

    return today;
}


//kalok sempet buat fungsi lagi 1 khusus ngecek user name

char * get_user_name(){
    printf("Masukkan Nama User (Max. 20 character (termasuk spasi)) : ");
    gets(userName);
    check_username_valid(userName);
    return userName;
}

void check_username_valid(char *userName){
    if (strlen(userName) > 20){//buat ngecek lebih dari 20 apa gak user nginputnya. pake strlen (string length)
        system("cls");   
        user_interface();  
        printf("Pesan Error : Maaf, User Name tidak boleh lebih dari 20 character ! \n\n");
        get_user_name();
    } else if (strcmp(userName,"\0") == 0){
        system("cls");
        user_interface();
        printf("Pesan Error : Maaf, User Name tidak boleh kosong ! \n\n");
        get_user_name();
    } else {
        return;
    }
}

char * get_month_name(int month){
    //string copy berdasarkan array yang diatas
    //-1 karena array mulai dari 0 
    strcpy(userMonth,monthdef[month-1]);
    return userMonth;
}

birthdayStruct input_birthday(){
    
    birthdayStruct birthday;//return 3 value makanya pake struct (lihat diatas)
    int day,month,year;
    
    printf ("Masukkan tanggal lahir (DD MM YYYY)  : ");
    scanf("%d %d %d",&birthday.day,&birthday.month,&birthday.year);
    printf("\n");
    
    return birthday;
}

void clear_buffer(){
    char c;
    while ((c = getchar()) != '\n' && c != EOF) ; 
    
}

birthdayStruct check_birth_valid(int day,int month,int year){
    
    birthdayStruct valid;
    valid.day = TRUE;
    valid.month = TRUE;
    valid.year = TRUE;
    
    if (day > 31 || day < 1 )  {
        valid.day = FALSE;
    } if (day > 30 && month == 4) {
        valid.day = FALSE;
    } if (day > 30 && month == 6) {
        valid.day = FALSE;
    } if (day > 30 && month == 9) {
        valid.day = FALSE;
    } if (day > 30 && month == 11) {
        valid.day = FALSE;
    } if (day >28 && month == 2 && year %4 != 0){// cek kabisat
        valid.day = FALSE;
    } if (day > 29 && month == 2){ 
        valid.day = FALSE;
    } if (month > 12 || month < 1){
        valid.month = FALSE;
    } if (year < 1917 || year > 2117){//batasan tahunya 1917-2117
        valid.year = FALSE;
    } 
        
    return valid;
}

void print_error(int checkDay,int checkMonth, int checkYear){
    
    printf("\nProgram Error!\n\n");
    
    if (checkDay == FALSE) {//error bagian hari
        printf("- Maaf tanggal yang anda masukkan tidak valid \n");
    }

    if (checkMonth == FALSE) {//error bagian bulan
        printf("- Maaf bulan yang anda masukkan tidak valid \n");
    }    

    if (checkYear == FALSE) {//error bagian tahun
        printf("- Maaf tahun lahir anda di luar rentang tahun program \n");
    }
    return;
}

void get_wuku_zodiac (int birthdayDay,int birthdayMonth,int birthdayYear,int todayDay,int todayMonth,int todayYear,char* userName){
  
    birthdayStruct birthday;
    
    
    get_zodiac(birthdayMonth,birthdayDay);
    get_wuku(get_weeks(birthdayYear,birthdayMonth,birthdayDay));
    printf("Profile dengan User Name %s berhasil disimpan !",userName);
    return;
}

int get_weeks(int birthdayYear,int birthdayMonth, int birthdayDay){
    int countDays = 1,countWeeks;

    //hitung hari berdasarkan tahunnya
    //tahun normal hari nya ada 365 kalau kabisat 366
    //loop terus sampai kurang dari tahun lahir

    for (int initYear = 1917 ; initYear < birthdayYear ; initYear ++ ){
        if (initYear % 4 == 0){
            countDays += 366;
        } else {
            countDays += 365; 
        }
    }

    //kalok yang ini berdasarkan bulannya
    for (int initMonth = 1 ; initMonth < birthdayMonth ; initMonth ++){
        if ((initMonth == 1) || (initMonth == 3) || (initMonth == 5) || (initMonth == 7) || (initMonth == 8) || (initMonth == 10) || (initMonth == 12)) {
            countDays += 31;
        } else if ((initMonth == 2) && (birthdayYear % 4 == 0)){//cek untuk kabisat
            countDays += 29;
        } else if ((initMonth == 2) && (birthdayYear % 4 != 0)){
            countDays += 28;
        } else {
            countDays += 30;
        }
        
    }

    for (int initDay = 1 ; initDay < birthdayDay ; initDay ++){
        countDays += 1;
    }
    countWeeks = countDays / 7  ;//cara nyari minggu tinggal bagi 7 aja ea
    return countWeeks;
}

char *get_wuku(int countWeeks){
    //nyari wuku tinggal bagi 30 since wuku adanya 30 
    strcpy(userWuku,wukudef[countWeeks%30]);
    return userWuku;
}

char *get_zodiac(int month,int day){
    
    if ((day >= 21 && month == 3) || (day<=19 && month == 4)) {
        strcpy(userZodiac,"Aries");
    } else if ((day >= 20 && month == 4) || (day <= 20 && month == 5)) {
        strcpy(userZodiac,"Taurus");
    } else if ((day >= 21 && month == 5) || (day <= 20 && month == 6)) {
        strcpy(userZodiac,"Gemini");
    } else if ((day >= 21 && month == 6) || (day <= 22 && month == 7)) {
        strcpy(userZodiac,"Cancer");
    } else if ((day >= 23 && month == 7) || (day <= 22 && month == 8)) {
        strcpy(userZodiac,"Leo");
    } else if ((day >= 23 && month == 8) || (day <= 22 && month == 9)) {
        strcpy(userZodiac,"Virgo");
    } else if ((day >= 23 && month == 9) || (day <=22 && month == 10)) {
        strcpy(userZodiac,"Libra");
    } else if ((day >= 23 && month == 10) || (day <=21 && month == 11)) {
        strcpy(userZodiac,"Scorpio");
    } else if ((day >= 22 && month == 11) || (day <= 21 && month == 12)) {
        strcpy(userZodiac,"Sagitarius");
    } else if ((day >= 22 && month == 12 ) || (day <= 19 && month == 1)) {
        strcpy(userZodiac,"Capricorn");
    } else if ((day >= 20 && month == 1 ) || (day <=18 && month == 2)) {
        strcpy(userZodiac,"Aquarius");
    } else {
        strcpy(userZodiac,"Pisces");
    }
    return userZodiac;
}

void print_age(int day,int month,int year,int todayDay,int todayMonth,int todayYear){
   
    
    int age;

    if(month == todayMonth && day <= todayDay){//kalau sama bulannya sama bulan ini liat tanggalnya
        age = todayYear - year;                //sebelum tanggal lahir umurnya ga di -1
    } else if (month < todayMonth){
        age = todayYear - year;
    } else {
        age = todayYear - year - 1;
    }
    if (age < 0){
        printf("Umur 0 tahun");
    } else {
        printf("Umur %d tahun ",age);
    }
    printf("\n");
    
    return;
}

void reset(){

    parameterYes parYes;
    parameterNo parNo;
    int valid_reset;
    char parameter[0];

    printf("\nIngin Mengulang lagi?[Y/N] ");
    gets(parameter);
    parYes.Y = strcmp(parameter,"Y");
    parYes.y = strcmp(parameter,"y");
    parNo.N = strcmp(parameter,"N");
    parNo.n = strcmp(parameter,"n");
    
    
    if ((parYes.Y == 0) || (parYes.y == 0)){
        
        system("cls");
        main();

    } else if ((parNo.N == 0) || (parNo.n == 0)){
        
        return;

    } else {
        system("cls");
        printf("Invalid Input !\n");
        reset();
    }
}

void put_to_file(char * userName, char * userWuku, char * userZodiac ,int birthdayDay,int birthdayMonth,int birthdayYear){
    FILE *fw;
    fw = fopen("database_zodiac.txt","a+");
    sprintf(userBirthday,"%d %d %d",birthdayDay,birthdayMonth,birthdayYear);
    fprintf(fw,"%s\n%s\n%s\n%s\n\n",userName,userBirthday,userZodiac,userWuku);
    fclose(fw);
    return;
}

void get_user_profile(){
    FILE *fp,*fq;
    char userDatabaseName[50];
    char userDatabaseBirthday[50];
    char userDatabaseZodiac[50];
    char userDatabaseWuku[50];
    int x,valid;
    fq = fopen("database_zodiac.txt","r");
    if (fq == NULL){
        printf("Database Kosong! Silahkan mendaftar terlebih dahulu! \n");
        fclose(fq);
        reset();
    } else {
        printf("Masukkan User Name : ");
        fgets(userName,50,stdin);
        do{
            fgets(userDatabaseName,20,fq);
            x = strcmp(userDatabaseName,userName);
            while(x != 0 && !feof(fq)){
                fgets(userDatabaseName,20,fq);
                x = strcmp(userDatabaseName,userName);
            }
            if (x == 0){
            fgets(userDatabaseBirthday,20,fq);
            fgets(userDatabaseZodiac,20,fq);
            fgets(userDatabaseWuku,20,fq);
            system("cls");
            printf("Profile user Name :\n\n");
            printf("Username    : %s\nTanggal Lahir : %s\nZodiac    : %s\nWuku  :%s",userDatabaseName,userDatabaseBirthday,userDatabaseZodiac,userDatabaseWuku);
            valid = 1;
            }
        }while (!feof(fq));
        if (valid != 1){
            printf("Maaf username belum terdaftar!");
        }
        printf("\n");
        reset();
    }
    return ;
}
