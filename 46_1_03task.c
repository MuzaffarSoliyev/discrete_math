#include <stdio.h>
#include <stdlib.h>
#include "46_1_03.h"

/*  Функция для вывода значений битов, представляющих
    заданное целое число в памяти компьютера.
*/
//void ShowInBin(int x)
//{
//    int     i, j, num_bits_in_int, num_bits;
//    char *  Arr;
//
//    /*  Количество битов, необходимое
//            для представления числа x.  */
//    //num_bits = (int)floor(log((double)x) / log(2.0)) + 1; -- это работает во всех средах одинаково --
//    //printf("%d\n", num_bits);
//
//    /*  Количество битов, необходимое
//        для представления максимального целого числа.   */
//    j = num_bits_in_int = sizeof(int) * 8;
//
//    Arr = (char *) calloc(num_bits_in_int, sizeof(char)); // (sizeof(char) * num_bits_in_int);
//
//// -- -- это не нужно, при выводе символы будем писать, а не в массив
//    /*  Обнуляем необходимое количество битов слева.
//    for (i = 0; i < num_bits_in_int - num_bits; ++i)
//        Arr[i] = '0';
//    */
//
//// -- обрабатываем ВСЕ биты --
//    i = 0;
//    while (i < j)
//    {
//        Arr[i] = x & 1;    // -- выделяем самый правый бит --
//        x = x >> 1;       // сдвигаем на 1 разряд направо
//        ++i;
//    }
//// -- вывод в обратном порядке --
//    for (i = num_bits_in_int-1; i >=0; --i)
//        if(Arr[i]) printf("%c", '1'); else printf("%c", '0');
//    free(Arr);
//}

int task_46_1_03(const char* ifilename, const char* ofilename) {
    FILE* file;
    int* sums; //массив из эелементов sumc
    int k, n, m, i, j, mask,f, f1, f2, s1,s2; //k еще используем как  врЕменное число;
    //s - флаг самодвойственности
    char* tmpSum, //врЕменный массив для считывания a11 a22 и тд в цикле
          *end; //Для strtol
    file = fopen(ifilename, "r");
    if(file == NULL) return E_FILEOPEN;
    fscanf(file, "%d %d", &k, &n);
    if(k == 2) { // У нас же булева алгебра!!! Для неё только и проканает решение

        if((fscanf(file, "%d", &m) != 1) || m < 0) { // Если длина неверна возвращаем ошибку
            //Т.к у нас m штук элементов 'sumc' в массиве sums
            fclose(file);
            return E_WRONGDATA;
        }
        sums = (int*)(malloc(m * sizeof(int)));
        if(sums == NULL) {
            fclose(file);
            return E_MEM; // Если malloc выдал ошибку возвращаем ошибку
        }
        for(i = 0; i < m; i++) { //Получаем массив из элементов sum
            tmpSum = (char*)malloc((n + 1) * sizeof(char));
            if(fscanf(file, "%s", tmpSum) != 1) {
                fclose(file);
                return E_WRONGDATA; // Если какой-то элемент не считался возвращаем ошибку
            }
            //В sums хранятся наши числа sum1 sum2 ... summ
            sums[i] = (int)(strtol(tmpSum, &end, 2)); // tmpSum = ['1','0','1']=> sums[i] = 5
            //Тк strtol возвращает long переделываем в int
            //
            free(tmpSum); //Освобождаем память от ВРЕМЕННОГО массива перед следующей итерацией
            fscanf(file, "%d", &k); //Заглушка - просто считываем Ci
        }
        fclose(file);
        file = fopen(ofilename, "w");
        if(file == NULL) {
            return E_FILEOPEN;
        }
         f=1; //Сначала считаем нашу ф-ю самодвойственной
        //Пееребераем mask от 00.. до 11...
        k = (1 << n) - 1; //макс значение mask (2^n)-1
        for(mask = 0; mask < k/2; mask++) {
            f1 = 0; f2 = 0;
            for(i = 0; i < m; i++) {
                    s1=s2=1;
                    for(j=0;j<n;j++){ //sums[i]&(1<<j) jй бит в описании слагаемых
                                 //mask&(1<<j) jй бит в описании набора значений
                        //printf("i=%d; j=%d: ",i,j);
                        if((sums[i]&(1<<j))){ //Если это слагаемое есть
                        s1=s1&&(mask&(1<<j)); //то делаем & с его значением
                        }
                        if((sums[i]&(1<<j))){ //То же самое  на противоположном наборе
                        s2=s2&&((~mask)&(1<<j));
                        }

                    }
//                    printf("%dth s1(",i);
//                        ShowInBin(sums[i]);
//                        printf(") on ");
//                        ShowInBin(mask);
//                        printf(" is %d", s1);
//                        printf("\n");
//                        printf("%dth s2(",i);
//                        ShowInBin(sums[i]);
//                        printf(") on ");
//                        ShowInBin(~mask);
//                        printf(" is %d", s2);
//                        printf("\n@\n");
                    f1 ^= s1;
                    f2 ^= s2;
                    //printf("%d");
            }

            if(f1 == f2) { // f1 несовпал c ~f2 ? - не самодвойств! перестаём переберать mask
                f = 0;
                break;
            }
        }
        //
        fprintf(file, "%d ", f);
    }
    fclose(file);
    return 0;
}
