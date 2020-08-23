#include <stdio.h>
#include "46_1_03.h"

// E_FILEOPEN Код ошибки открытия файла
// ET_FILEOPEN Текст ошибки открытия файла
// E_WRONGDATA Код ошибки неверные входные данные
// ET_WRONGDATA Текст ошибки неверные входные данные
// E_MEM Код ошибки выделения памяти
// ET_MEM Текст ошибки выделения памяти

int main(int argc, char* argv[]) {
    char ifilename[256];
    char ofilename[256];
    int err;
    if(argc < 2) {
        scanf("%s %s", ifilename, ofilename);
        err = task_46_1_03(ifilename, ofilename);
    } else {
        err = task_46_1_03(argv[1], argv[2]);
    }
    switch(err) {
    case E_FILEOPEN:
        printf(ET_FILEOPEN);
        break;
    case E_WRONGDATA:
        printf(ET_WRONGDATA);
        break;
    case E_MEM:
        printf(ET_MEM);
        break;
    }
    return  err;
}
