// Project1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include <iostream>
#include <fstream>
#include "Windows.h"
#include <conio.h> //для использования getch()
#include <Wininet.h>
#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>//для print_f
#include <time.h>


#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "wininet.lib")

using namespace std;//подключаем функции стандартных библиотек

void russs(char strr[]);//проверка на ввод символов
void alfavit(char strr[], int i, int dlina); void alfavit2(char strr[], int i, int dlina);//какие символы на какие заменять
void BIN(int a, int n, char str[], int k); void BIN2(int a, int n, char str[], int k); void tire(char str[]);//формирование различных вариантов
void PodborSimvolov(char strr[]);//весь список возможных вариантов заменвы букв в домене
void ProvFormata(char strr[]);//проверка формата введённого домена и выделение нужной части
void sdvig(char strr[], int i,int dlina);//сдвиг массива для увеличения длины домена
 char* OpenURLL(const char* url); void proverka(char prishlo[]);
int dd = 0; int var = 0; char domen[512];//глобальгая переменная


int main(){
    setlocale(LC_ALL, "rus"); cout.imbue(locale("rus_rus.1251"));//выводит русские буквы
    char str[40]; char varianti[512];
    while (exit) {
        if (!InternetCheckConnection(L"http://google.com", FLAG_ICC_FORCE_CONNECTION, 0)) {
            cout << "Не подключен интернет на устройстве. Невозможно произвести проверку. Подключите интернет и повторите попытку\n";
            _getch();
        }
        else {
            cout << "Интернет подключен на устройстве.\n";
            cout << "\nЗдравствуйте!\nВведите домен вашего сайта:";
            cin >> str;
            russs(str);
            ProvFormata(str);
            PodborSimvolov(str);
            cout << "Проверка закончена";
            exit(0); break;
        }
    }
     _getch();
    return 0;
}



void russs(char strr[]) {
    int n = strlen(strr); int h = 0;int k;
    while (h == 0) {
        n = strlen(strr); h = 1;k=0;
        for (int j = 0; j < n; j++) {
            if (!((strr[j] >= 'A' && strr[j] <= 'Z') or (strr[j] >= 'a' && strr[j] <= 'z') or (strr[j] >= '0' && strr[j] <= '9') or strr[j]=='-' or strr[j] == '.')) { h = 0;break; }
            if (strr[j] == '.') { k++; }            
        }
        if (k>2) { h = 0; }//больше двух точек
        if (k == 2 and n >70 or k == 1 and n >66) { h == 0; } //максимальная длина (не более 63 символов в домене)
        if (k == 2 and n <= 8 or k==1 and n<=4) { h == 0; } //минимальная длина (не менее двух символов в домене)
        ProvFormata(strr); n = strlen(strr);
        if (strr[0] == '-' or strr[n] == '-') { h = 0; }
        if (h==0 ) { cout << "ОШИБКА: Некорректный ввод \nВведите домен ещё раз:";cin >> strr;}
    } 
    cout<<"Формат домена верный\n";
}
void ProvFormata(char strr[]){
    int i, n, dlindomen=0, tchk=0;
    n = strlen(strr);
    for (i = 0; i < n; i++) {
        if (strr[i] == '.') { tchk++;}
    }//смотрим сколько точек    
    if (tchk==2) { ///для формата www.cisco.ru 
        for (i = 0; i < n; i++) { if (strr[i] == '.') { dlindomen = i; break; } }//смотрим на первую точку ( www.)
        if (dlindomen > 0) {
            for (i = 0; i <= n + 1; i++) {
                strr[i] = strr[dlindomen + 1 + i];
                strr[n + i] = 0;
            }
        }
        n = strlen(strr);  int dlindomen2 = 0;
        for (i = n; i > 0; i--) { if (strr[i] == '.') { dlindomen2 = i; break; } }//смотрим вторую точку (.com или .ru)
        if (dlindomen2 > 0) {
            n = n - dlindomen2;
            for (i = 0; i <= n; i++) {
                strr[dlindomen2 + i] = 0;
            }
        }
    } 
    if (tchk == 1) { // для формата cisco.ru
        n = strlen(strr);  int dlindomen2 = 0;
        for (i = n; i > 0; i--) { if (strr[i] == '.') { dlindomen2 = i; break; } }//смотрим вторую точку (.com или .ru)
        if (dlindomen2 > 0) {
            n = n - dlindomen2;
            for (i = 0; i <= n; i++) {
                strr[dlindomen2 + i] = 0;
            }
        }    
    }
    else strr[n] = 0; // для формата cisco
    //cout<<strr<<'\n';
}
void BIN(int a, int n, char str[], int k) {
    char binary[20]; int tt=0; //Массив в котором символоми записано число в BIN
    dd = 0; var = 0;
    for (int i = n - 1; i >= 0; i--) {         //Заполняем массив          
        if (a % 2 == 0) { binary[i] = str[i]; }
        else { binary[i] = str[i];  alfavit(binary, i, n);  }
        a = a / 2;
    }
    binary[n+dd]=0;//обрезвем массив   
    tt = strlen(binary);
    for (int i = 0; i < tt; i++) { domen[i]=binary[i]; } //Печатаем массив
    domen[tt] = 0;
}
void BIN2(int a, int n, char str[], int k) {
    char binary[20]; int tt = 0; //Массив в котором символоми записано число в BIN
    dd = 0; 
    for (int i = n - 1; i >= 0; i--) {         //Заполняем массив          
        if (a % 2 == 0) { binary[i] = str[i]; }
        else { binary[i] = str[i];  alfavit2(binary, i, n); }
        a = a / 2;
    }
     binary[n + dd] = 0;//обрезаем массив    
    tt = strlen(binary);
    for (int i = 0; i < tt; i++) { domen[i] = binary[i]; } //Печатаем массив
    domen[tt] = 0;
}
void tire(char str[]) {
    char ssss[40] ; int n = strlen(str);
    for (int i=1;i<n;i++) {
        for (int j = 0;j<n+1;j++) {
            if(j<i){ ssss[j] = str[j]; }
            if (j==i ) { ssss[j] = '-';  ssss[j + 1] = str[j]; }
            if (j > i) { ssss[j+1]=str[j]; }
        }
        ssss[n+1]=0;
       // cout << ssss<< " ";
        proverka(ssss);
    }
}
void PodborSimvolov(char strr[]){
    int nn=1;int k=0; cout << "\n";
    int n = strlen(strr);
    for (int i = 0; i < n; i++) { nn = nn * 2; }
        for (int i = 0; i < nn; i++) {
            memset(domen, 0, sizeof(domen));//зачистка 
            if (i != 0) {
                BIN(i, n, strr, k);
                //cout<<domen<<" ";
                proverka(domen); tire(domen);
                if (var == 1) {
                    memset(domen, 0, sizeof(domen));
                    BIN2(i, n, strr, k);
                    //cout << domen << " ";
                    proverka(domen); tire(domen);
                }
            }
            if (i == nn / 2 or i == nn / 4 or i == nn / 8 or i == nn - (nn / 4) or i == nn - (nn / 8)) { cout << "Производим проверку...\n"; }
        }    
}
void sdvig(char strr[], int i,int dlina) {
    int  n; n = strlen(strr);
    char* p_darr = new char[dlina +1];
    for (int j = 0; j < dlina; j++) { p_darr[j+1]=strr[j]; }
    for (int c = 0; c < dlina + 1; c++) {  strr[c]= p_darr[c]; }
    delete[] p_darr;
}
void alfavit(char strr[], int i,int dlina){
    int  n; n = strlen(strr); 
    while (n>0) {
        if (strr[i] == 'a') { strr[i] = '4'; break; }
        if (strr[i] == 'b') { strr[i] = '6'; var = var + 1; break; }
        if (strr[i] == 'c') { strr[i] = 'k';  var = var + 1; break;}
        if (strr[i] == 'd') { strr[i] = '0'; break; }
        if (strr[i] == 'e') { strr[i] = '3'; break; }
        if (strr[i] == 'f') { strr[i] = 't'; break; }
        if (strr[i] == 'g') { strr[i] = '9'; var = var + 1; break; }
        if (strr[i] == 'h') { strr[i] = 'u'; break; }
        if (strr[i] == 'i') { strr[i] = 'l'; var = var + 1; break; }
        if (strr[i] == 'j') { strr[i] = 'i'; break; }
        if (strr[i] == 'k') { strr[i] = 'x'; break; }
        if (strr[i] == 'l') { strr[i] = '1'; var = var + 1; break; }
        if (strr[i] == 'm') { strr[i] = 'n'; sdvig(strr, i, dlina); strr[i] = 'n'; dd =1;  break; }
        if (strr[i] == 'n') { strr[i] = 'm'; break; }
        if (strr[i] == 'o') { strr[i] = '0'; break; }
        if (strr[i] == 'p') { strr[i] = 'q'; var = var + 1; break; }
        if (strr[i] == 'q') { strr[i] = '9'; break; }
        if (strr[i] == 'r') { strr[i] = 'e'; break; }
        if (strr[i] == 's') { strr[i] = '5'; var = var + 1; break; }
        if (strr[i] == 't') { strr[i] = '7'; var = var + 1; break; }
        if (strr[i] == 'u') { strr[i] = 'm'; break; }
        if (strr[i] == 'v') { strr[i] = 'w'; break; }
        if (strr[i] == 'w') { strr[i] = 'v'; sdvig(strr, i, dlina); strr[i] = 'v'; dd = 1;; break; }
        if (strr[i] == 'x') { strr[i] = 'x'; sdvig(strr, i, dlina); strr[i] = 'e'; dd = 1;  break; }
        if (strr[i] == 'y') { strr[i] = 'j'; break; }
        if (strr[i] == 'z') { strr[i] = '2'; break; }
        if (strr[i] == '0') { strr[i] = 'o'; break; }
        if (strr[i] == '1') { strr[i] = 'l'; var = var + 1; break; }
        if (strr[i] == '2') { strr[i] = 'z'; var = var + 1; break; }
        if (strr[i] == '3') { strr[i] = 'e'; var = var + 1; break; }
        if (strr[i] == '4') { strr[i] = 'a'; var = var + 1; break; }
        if (strr[i] == '5') { strr[i] = 's'; var = var + 1; break; }
        if (strr[i] == '6') { strr[i] = 'g'; var = var + 1; break; }
        if (strr[i] == '7') { strr[i] = 't'; var = var + 1; break; }
        if (strr[i] == '8') { strr[i] = 'b'; break; }
        if (strr[i] == '9') { strr[i] = 'g'; var = var + 1; break; }
    }       
}
void alfavit2(char strr[], int i, int dlina){
    int  n; n = strlen(strr); 
    while (n>1) {
        if (strr[i] == 'a') { strr[i] = '4'; break; }
        if (strr[i] == 'b') { strr[i] = '8'; break; }
        if (strr[i] == 'c') { strr[i] = 'x'; break; }
        if (strr[i] == 'd') { strr[i] = '0'; break; }
        if (strr[i] == 'e') { strr[i] = '3'; break; }
        if (strr[i] == 'f') { strr[i] = 't'; break; }
        if (strr[i] == 'g') { strr[i] = '6'; break; }
        if (strr[i] == 'h') { strr[i] = 'u'; break; }
        if (strr[i] == 'i') { strr[i] = '1'; break; }
        if (strr[i] == 'j') { strr[i] = 'i'; break; }
        if (strr[i] == 'k') { strr[i] = 'x'; break; }
        if (strr[i] == 'l') { strr[i] = '7'; break; }
        if (strr[i] == 'm') { strr[i] = 'n'; sdvig(strr, i, dlina); strr[i] = 'n'; dd = 1;  break; }
        if (strr[i] == 'n') { strr[i] = 'm'; break; }
        if (strr[i] == 'o') { strr[i] = '0'; break; }
        if (strr[i] == 'p') { strr[i] = '9'; break; }
        if (strr[i] == 'q') { strr[i] = '9'; break; }
        if (strr[i] == 'r') { strr[i] = 'e'; break; }
        if (strr[i] == 's') { strr[i] = 'z'; break; }
        if (strr[i] == 't') { strr[i] = '1'; break; }
        if (strr[i] == 'u') { strr[i] = 'm'; break; }
        if (strr[i] == 'v') { strr[i] = 'w'; break; }
        if (strr[i] == 'w') { strr[i] = 'v'; sdvig(strr, i, dlina); strr[i] = 'v'; dd = 1;; break; }
        if (strr[i] == 'x') { strr[i] = 'x'; sdvig(strr, i, dlina); strr[i] = 'e'; dd = 1;  break; }
        if (strr[i] == 'y') { strr[i] = 'j'; break; }
        if (strr[i] == 'z') { strr[i] = '2'; break; }
        if (strr[i] == '0') { strr[i] = 'o'; break; }
        if (strr[i] == '1') { strr[i] = 'e'; dd = 2; sdvig(strr, i, dlina); dlina = dlina + 1; strr[i] = 'n'; sdvig(strr, i, dlina);strr[i] = 'o'; break; }
        if (strr[i] == '2') { strr[i] = 'o'; dd = 2; sdvig(strr, i, dlina); dlina = dlina + 1; strr[i] = 'w'; sdvig(strr, i, dlina); strr[i] = 't'; break; }
        if (strr[i] == '3') { strr[i] = 'e'; dd = 3; sdvig(strr, i, dlina); dlina = dlina + 1; strr[i] = 'e'; sdvig(strr, i, dlina); dlina = dlina + 1; strr[i] = 'r'; sdvig(strr, i, dlina); strr[i] = 't'; break; }
        if (strr[i] == '4') { strr[i] = 'r'; dd = 3; sdvig(strr, i, dlina); dlina = dlina + 1; strr[i] = 'u'; sdvig(strr, i, dlina); dlina = dlina + 1; strr[i] = 'o'; sdvig(strr, i, dlina); strr[i] = 'f'; break; }
        if (strr[i] == '5') { strr[i] = 'e'; dd = 3; sdvig(strr, i, dlina); dlina = dlina + 1; strr[i] = 'v'; sdvig(strr, i, dlina); dlina = dlina + 1; strr[i] = 'i'; sdvig(strr, i, dlina); strr[i] = 'f'; break; }
        if (strr[i] == '6') { strr[i] = 'x'; dd = 2; sdvig(strr, i, dlina); dlina = dlina + 1; strr[i] = 'i'; sdvig(strr, i, dlina); strr[i] = 's'; break; }
        if (strr[i] == '7') { strr[i] = 'n'; dd = 4; sdvig(strr, i, dlina); dlina = dlina + 1; strr[i] = 'e'; sdvig(strr, i, dlina); dlina = dlina + 1; strr[i] = 'v'; sdvig(strr, i, dlina); dlina = dlina + 1; strr[i] = 'e'; sdvig(strr, i, dlina); strr[i] = 's'; break; }
        if (strr[i] == '9') { strr[i] = 'e'; dd = 3; sdvig(strr, i, dlina); dlina = dlina + 1; strr[i] = 'n'; sdvig(strr, i, dlina); dlina = dlina + 1; strr[i] = 'i'; sdvig(strr, i, dlina); strr[i] = 'n'; break; }
    }
}
char* OpenURLL(const char* url) {
    WSADATA lpWSAData;    SOCKET s;  char urrll[40];
    fd_set fds;   struct timeval	tv;  int ret;//для таймаута
    // Проверим на правильность введенный адрес. // Он должен начинаться с "http://"
    if (memcmp(url, "HTTP://", 7) != 0 && memcmp(url, "http://", 7) != 0) return(NULL);
    url += 7;
    //обрезаю ссылку для красивого вывода 
    int n=strlen(url);
    for (int i = 0; i < n-1; i++) { urrll[i] = url[i]; }
    urrll[n-1]=0;
    // Инициализация библиотеки Ws2_32.dll.
    if (WSAStartup(MAKEWORD(1, 1), &lpWSAData) != 0) return(NULL);

    // Получим имя хоста, номер порта и путь ----------------------------
    char* http_host = _strdup(url); // Имя хоста ( HTTP_HOST)
    int port_num = 80;             // Номер порта по умолчанию ( HTTP_PORT)
    char* http_path = NULL;        // Путь (REQUEST_URI)

    char* pch = strchr(http_host, ':');
    if (!pch) {
        pch = strchr(http_host, '/');
        if (pch) {
            *pch = 0;
            http_path = _strdup(pch + 1);
        }
        else http_path = _strdup("");
    }
    else {
        *pch = 0; pch++;
        char* pch1 = strchr(pch, '/');
        if (pch1) {
            *pch1 = 0;
            http_path = _strdup(pch1 + 1);
        }
        else http_path = _strdup("");
        port_num = atoi(pch);
        if (port_num == 0) port_num = 80;
    }

    // Поучаем IP адрес по имени хоста
    struct hostent* hp;
    if (!(hp = gethostbyname(http_host))) {
        free(http_host);
        free(http_path);
        return(NULL);
    }

    // Открываем сокет
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) {
        free(http_host);
        free(http_path);
        return(NULL);
    }

    // Заполняем структуру sockaddr_in
    struct sockaddr_in ssin;
    memset((char*)&ssin, 0, sizeof(ssin));
    ssin.sin_family = AF_INET;
    ssin.sin_addr.S_un.S_un_b.s_b1 = hp->h_addr[0]; ssin.sin_addr.S_un.S_un_b.s_b2 = hp->h_addr[1];
    ssin.sin_addr.S_un.S_un_b.s_b3 = hp->h_addr[2]; ssin.sin_addr.S_un.S_un_b.s_b4 = hp->h_addr[3];
    ssin.sin_port = htons(port_num);

    // Выводим IP адрес хоста, с которым будем соединятся
    cout << urrll <<"  ";
    printf("Conecting to %d.%d.%d.%d...", (unsigned char)hp->h_addr[0], (unsigned char)hp->h_addr[1], (unsigned char)hp->h_addr[2], (unsigned char)hp->h_addr[3]);

    // Соединяемся с хостом
    if (connect(s, (sockaddr*)&ssin, sizeof(ssin))==0) {
        printf("Ok\n");
    }
    
    /* Ожидание соединения */
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(s, &fds);
    ret = select(s + 1, NULL, &fds, NULL, &tv);
    if (!ret)
        printf("Время ожидания подключения истекло\n");


    // Деинициализация библиотеки Ws2_32.dll
    WSACleanup();
    //  return(result);
}
void proverka(char prishlo[]) {
    char ddomen[50];
    int kk = strlen(prishlo);
    char tt[13] = "http://www."; char tt2[6] = ".ru/";
    int k = strlen(tt);  int k2 = strlen(tt2);
    for (int i = 0; i < k; i++) {
        ddomen[i] = tt[i];
        for (int j = 0; j < kk; j++) {
            ddomen[k + j] = prishlo[j];
            for (int g = 0; g < k2; g++) {
                ddomen[k + kk + g] = tt2[g];
            }
        }
    }
    ddomen[k + kk + k2] = 0;
    const char* t = ddomen;
    char* result = OpenURLL(t);
    //////////////
    char ddomen2[50];
    char tt3[6] = ".com/"; int k3 = strlen(tt3);
    for (int i = 0; i < k; i++) {
        ddomen2[i] = tt[i];
        for (int j = 0; j < kk; j++) {
            ddomen2[k + j] = prishlo[j];
            for (int g = 0; g < k3; g++) {
                ddomen2[k + kk + g] = tt3[g];
            }
        }
    }
    ddomen2[k + kk + k3] = 0;
    const char* h = ddomen2;
    char* result2 = OpenURLL(h);

}




