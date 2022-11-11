#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include "functions.h"

#define N 1000

int main() {
    FILE *data;
    SetConsoleOutputCP(CP_UTF8);/*Трогать не надо, делает русский вывод текста*/
    zastavka();
    int switcher = 0;/*переключалка*/
    float t[N]/*Массив времени зависит от точек*/, Uvx[N] = {0}/*Массив входных сигналов*/, Uvix[N] = {0}/*Массив выходных*/, dt/*Как это называется? цена деления? Шаг времени зависящий от ко-ва точек*/;
    int n; //Кол-во точек
    float tn = -10, tk = 10;

    while(switcher!=6){
        printf("\n1 - Контрольный расчет для n точек\n"
               "2- Рассчёт с данными из файла\n"
               "3 – Расчёт параметра для Uvx с заданной точностью\n"
               "4 – Расчёт параметра для Uvix с заданной точностью\n"
               "5 – Запись данных в файл\n"
               "6 - Выход из программы\n");
        scanf("%d", &switcher);
        scanf( "%*[^\n]" );
        fflush(stdin);
        switch(switcher){
            case 1:
                system("cls");
                printf("Введите количество точек:");
                scanf("%d", &n);
                scanf( "%*[^\n]" );
                fflush(stdin);
                dt=(tk-tn)/(n);
                time(t, tn, dt, n);
                Uvh(Uvx, t, n);
                Uvih(n, Uvx, Uvix);
                show(t,Uvx,Uvix,n);
                break;
            case 2:
                system("cls");
                data = fopen("../data.txt", "r");
                fscanf(data, "%f %f %d", &tn, &tk, &n);
                printf("tn=%.3f tk=%.3f n=%d\n", tn, tk, n);
                dt=(tk-tn)/(n);
                time(t, tn, dt, n);
                Uvh(Uvx, t, n);
                Uvih(n, Uvx, Uvix);
                show(t,Uvx,Uvix,n);
                fclose(data);
                break;
            case 3:
                system("cls");
                float eps = 0.01;	// заданная погрешность
                float p = 1;	 // текущая погрешность
                float par = 1000000;  // начальное значение параметра (очень большое число)
                float par1 = 0;
                n = 11;	// начальное значение точек
                while (p > eps){
                    dt=(tk-tn)/(n);
                    time(t, -10, dt, n);
                    Uvh(Uvx, t, n);
                    Uvih( n, Uvx, Uvix);
                    par1 = parametr(t, n, Uvx, 150);
                    p=fabsf(par-par1)/par1;
                    printf("n = %4.d;    Время = %3.4f;    погрешность = %3.4f;\n", n, par1, p);
                    par = par1;
                    n = 2 * n;
                }
                break;
            case 4:
                system("cls");
                eps = 0.01;	// заданная погрешность
                p = 1;	 // текущая погрешность
                par = 1000000;  // начальное значение параметра (очень большое число)
                par1 = 0;
                n = 11;	// начальное значение точек
                while (p > eps){
                    dt=(tk-tn)/(n);
                    time(t, tn, dt, n);
                    Uvh(Uvx, t, n);
                    Uvih( n, Uvx, Uvix);
                    par1 = parametr(t, n, Uvix, 40);
                    p=fabsf(par-par1)/par1;
                    printf("n = %4.d;    Время = %3.4f;    погрешность = %3.4f;\n", n, par1, p);
                    par = par1;
                    n = 2 * n;
                }
                break;
            case 5:
                system("cls");
                printf("Файл записан");
                files(n,Uvx,Uvix,t);
                break;
            case 6:
                printf("Завершение работы");
                break;
            default:
                printf("Ошибка!");
                break;
        }
    }

}

//time(t, -10, dt, n);
//Uvh(Uvx, t, n);
//Uvih(n, Uvx, Uvix);
//fronts(Uvx,n,dt,Uvh_dlit,U1,U2);
//files(n,Uvx,Uvix,t);
