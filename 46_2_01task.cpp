#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "46_2_01.h"
#pragma warning(disable:4996)

/*
Во входном файле задана функция. Монотонна ли она относительно порядка 0<1<...<k−1?
Формат входного файла:
Функции k-значной логики задаются вектором значений: сначала идет k,
потом через пробел n – количество переменных функции, потом пробел,
потом без пробела k^n символов – значения функции на наборах
0..00,0..01,0..02,…,0..10,0..11,0..120..00,0..01,0..02,…,0..10,0..11,0..12 и т.д..
Например, функция x+y в P3 задается строкой: 3 2 012120201
При k>9 значения больше 9 задаются заглавными латинскими буквами A,B,C,..
*/


//Возвращает десятичное значение цифры числа (F->15)
int task_46_2_01_getVal(char c) {
    if(c >= 'A' && c <= 'Z')
        return c - 'A' + 10;
    else
        return c - '0';
}

//Перевод из 10-ой сист. сч. в base-значную записанную задом наперёд
//Например: task_46_2_01_fromDecToBase(11,2,digits,4); => digits=['1','1','0','1',..остальное не меняется...]
//Тк 11 это 1011 в 2 ичной
void task_46_2_01_fromDecToBase(long long number, int base, int* digits,  int n) {
    int t, rem;
    for(t = 0; t < n; t++)
        digits[t] = 0;
    t = 0;
    while(number != 0) {
        rem = number % base;
        number = number / base;
        digits[t] = rem;
        t++;
    }
}


int task_46_2_01(const char* ifilename, const char* ofilename) {
    FILE *file;
    char f; //Сравнимы ли наборы флаг (bool)
    int k, n, z;
    long long i, j;
    char c, res; //c тек. символ набора; res результат
    long long valVecSize; // Размер массива значений
    int* valVec; //Вектор значений функции
    int* vecToCmp1;
    int* vecToCmp2;
    //
    file = fopen(ifilename, "r");
    if(file == NULL) return E_FILEOPEN;    
    fscanf(file, "%d %d ", &k, &n);
    //
    valVecSize = pow(double(k), n);
    valVec = (int*)malloc(valVecSize * sizeof(int));
    vecToCmp1 = (int*)malloc(n * sizeof(int)); // Первый
    vecToCmp2 = (int*)malloc(n * sizeof(int)); // и второй временные наборы
    // значений переменных для сравнения
    for(i = 0; i < valVecSize; i++) {
        fscanf(file, "%c", &c);
        valVec[i] = task_46_2_01_getVal(c);
    }
    fclose(file); // Входной файл больше не нужен
    res = 1; //Пусть ф-я монотонна, проверим обратное
    //Перебор возможных наборов по возрастанию их десятичного представления
    for(i = 0; i < valVecSize - 1; i++) { // Первого
        task_46_2_01_fromDecToBase(i, k, vecToCmp1, n);
        for(j = i + 1; j < valVecSize;  j++) { // и второго набора
            task_46_2_01_fromDecToBase(j, k, vecToCmp2, n);
            f = 1; //Пусть наборы сравнимы, проверим обратное
            
            for(z = 0; z < n; z++) {
                    
                if(vecToCmp1[z] > vecToCmp2[z])
                    f = 0; //Нет не сравнимы эти два набора
            }
//            for(z = 0; z < n; z++) {
//                    printf("%d",vecToCmp1[z]);
//                
//            }
//            printf(" c ");
//            for(z = 0; z < n; z++) {
//                    printf("%d",vecToCmp2[z]);
//                
//            }
//            printf("\n");
            if(f)
                if(valVec[i] > valVec[j]) { //Нет не монотонная ф-я
                    res = 0;
                    goto printRes; //Перейти к выводу
                }
        }
        //printf("-----------\n");
    }
printRes: //Метка вывода
    free(valVec); //Освобождаем память
    free(vecToCmp1);
    free(vecToCmp2);
    file = fopen(ofilename, "w"); //Открываем выходной файл и выводим
    if(file == NULL) {
        return E_FILEOPEN;
    }
    fprintf(file, "%d", res);
    fclose(file);
    return 0;
}
