#include <stdio.h>
#include "46_1_03.h"

// E_FILEOPEN ��� ������ �������� �����
// ET_FILEOPEN ����� ������ �������� �����
// E_WRONGDATA ��� ������ �������� ������� ������
// ET_WRONGDATA ����� ������ �������� ������� ������
// E_MEM ��� ������ ��������� ������
// ET_MEM ����� ������ ��������� ������

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
