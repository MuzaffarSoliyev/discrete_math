#include <stdio.h>
#include <stdlib.h>
#include "46_1_03.h"

/*  ������� ��� ������ �������� �����, ��������������
    �������� ����� ����� � ������ ����������.
*/
//void ShowInBin(int x)
//{
//    int     i, j, num_bits_in_int, num_bits;
//    char *  Arr;
//
//    /*  ���������� �����, �����������
//            ��� ������������� ����� x.  */
//    //num_bits = (int)floor(log((double)x) / log(2.0)) + 1; -- ��� �������� �� ���� ������ ��������� --
//    //printf("%d\n", num_bits);
//
//    /*  ���������� �����, �����������
//        ��� ������������� ������������� ������ �����.   */
//    j = num_bits_in_int = sizeof(int) * 8;
//
//    Arr = (char *) calloc(num_bits_in_int, sizeof(char)); // (sizeof(char) * num_bits_in_int);
//
//// -- -- ��� �� �����, ��� ������ ������� ����� ������, � �� � ������
//    /*  �������� ����������� ���������� ����� �����.
//    for (i = 0; i < num_bits_in_int - num_bits; ++i)
//        Arr[i] = '0';
//    */
//
//// -- ������������ ��� ���� --
//    i = 0;
//    while (i < j)
//    {
//        Arr[i] = x & 1;    // -- �������� ����� ������ ��� --
//        x = x >> 1;       // �������� �� 1 ������ �������
//        ++i;
//    }
//// -- ����� � �������� ������� --
//    for (i = num_bits_in_int-1; i >=0; --i)
//        if(Arr[i]) printf("%c", '1'); else printf("%c", '0');
//    free(Arr);
//}

int task_46_1_03(const char* ifilename, const char* ofilename) {
    FILE* file;
    int* sums; //������ �� ���������� sumc
    int k, n, m, i, j, mask,f, f1, f2, s1,s2; //k ��� ���������� ���  ��������� �����;
    //s - ���� ������������������
    char* tmpSum, //��������� ������ ��� ���������� a11 a22 � �� � �����
          *end; //��� strtol
    file = fopen(ifilename, "r");
    if(file == NULL) return E_FILEOPEN;
    fscanf(file, "%d %d", &k, &n);
    if(k == 2) { // � ��� �� ������ �������!!! ��� �� ������ � ��������� �������

        if((fscanf(file, "%d", &m) != 1) || m < 0) { // ���� ����� ������� ���������� ������
            //�.� � ��� m ���� ��������� 'sumc' � ������� sums
            fclose(file);
            return E_WRONGDATA;
        }
        sums = (int*)(malloc(m * sizeof(int)));
        if(sums == NULL) {
            fclose(file);
            return E_MEM; // ���� malloc ����� ������ ���������� ������
        }
        for(i = 0; i < m; i++) { //�������� ������ �� ��������� sum
            tmpSum = (char*)malloc((n + 1) * sizeof(char));
            if(fscanf(file, "%s", tmpSum) != 1) {
                fclose(file);
                return E_WRONGDATA; // ���� �����-�� ������� �� �������� ���������� ������
            }
            //� sums �������� ���� ����� sum1 sum2 ... summ
            sums[i] = (int)(strtol(tmpSum, &end, 2)); // tmpSum = ['1','0','1']=> sums[i] = 5
            //�� strtol ���������� long ������������ � int
            //
            free(tmpSum); //����������� ������ �� ���������� ������� ����� ��������� ���������
            fscanf(file, "%d", &k); //�������� - ������ ��������� Ci
        }
        fclose(file);
        file = fopen(ofilename, "w");
        if(file == NULL) {
            return E_FILEOPEN;
        }
         f=1; //������� ������� ���� �-� ����������������
        //����������� mask �� 00.. �� 11...
        k = (1 << n) - 1; //���� �������� mask (2^n)-1
        for(mask = 0; mask < k/2; mask++) {
            f1 = 0; f2 = 0;
            for(i = 0; i < m; i++) {
                    s1=s2=1;
                    for(j=0;j<n;j++){ //sums[i]&(1<<j) j� ��� � �������� ���������
                                 //mask&(1<<j) j� ��� � �������� ������ ��������
                        //printf("i=%d; j=%d: ",i,j);
                        if((sums[i]&(1<<j))){ //���� ��� ��������� ����
                        s1=s1&&(mask&(1<<j)); //�� ������ & � ��� ���������
                        }
                        if((sums[i]&(1<<j))){ //�� �� �����  �� ��������������� ������
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

            if(f1 == f2) { // f1 �������� c ~f2 ? - �� �����������! �������� ���������� mask
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
