#define E_FILEOPEN -1
#define ET_FILEOPEN "ERROR: open file error\n"
#define E_WRONGDATA -2
#define ET_WRONGDATA "ERROR: Wrong data\n"
#define E_MEM -3
#define ET_MEM "ERROR: malloc error\n"

int task_46_2_01(const char* ifilename, const char* ofilename);
int task_46_2_01_getVal(char c);
void task_46_2_01_fromDecToBase(long long i, int k, int* temp, int n);
