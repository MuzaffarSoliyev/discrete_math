#include <stdio.h>
#include <stdlib.h>

// Вспомогательные функции

char** readFromFile(const char *filename, int *var_count, int *conjuncts_count)
{
  char **DNF, i, j;
  FILE *file;

  file = fopen(filename, "r");
  fscanf(file, "%d %d", var_count, conjuncts_count);
  fseek(file, 2, SEEK_CUR);

  DNF = (char**)malloc(sizeof(char*) * *conjuncts_count);
  for(i = 0; i < *conjuncts_count; i++)
  {
    DNF[i] = (char*)malloc(*var_count);
    for(j = 0; j < *var_count; j++)
    {
      fscanf(file, "%c", &(DNF[i][j]));
      DNF[i][j] -= 48;
    }
    fseek(file, 2, SEEK_CUR);
  }

  fclose(file);

  return DNF;
}

void writeToFile(const char *filename, char ***DNF, int *var_count, int *conjuncts_count)
{
  char i, j;
  FILE *file;

  file = fopen(filename, "w");

  fprintf(file, "%d %d\n", *var_count, *conjuncts_count);
  for(i = 0; i < *conjuncts_count; i++)
  {
    for(j = 0; j < *var_count; j++)
      fprintf(file, "%c", (*DNF)[i][j] + 48);
    fprintf(file, "\n");
  }

  fclose(file);
}

// Функции для слеяния

/* 
  Функция проверяет, можно ли слить два конъюнкта.
  Возвращает:
    0 - если нельзя.
    1 - если можно.
*/
int compareConjsToMerger(char **conj_one, char **conj_two, int *var_count)
{
  	char i, error = 0;

    for(i = 0; i < *var_count; i++)
      if( ((*conj_one)[i] == 1 && (*conj_two)[i] == 0) || ((*conj_one)[i] == 0 && (*conj_two)[i] == 1) )
        if(error == 0)
          error++;
        else
          return 0;

    return error;
}

/* 
  Функция проверяет, если ли конъюнкты в ДНФ.
  Возвращает:
    0 - если нет.
    1 - если есть.
*/
int containConj(char ***DNF, int *var_count, int *conjuncts_count, char **needConj)
{
  char i, j;

  for (i = 0; i < *conjuncts_count; i++)
  {
    for (j = 0; j < *var_count; j++)
      if( (*DNF)[i][j] != (*needConj)[j] )
        break;
    if(j == *var_count)
      return 1;
  }

  return 0;
}

/* 
  Функция склеивает два конъюнкта.
*/
void mergeConj(char **conj_one, char **conj_two, int *var_count, char** conj_res)
{
  char i;
  for(i = 0; i < *var_count; i++)
  {
      (*conj_res)[i] = 
        ( ((*conj_one)[i] == 1 && (*conj_two)[i] == 0) || ((*conj_one)[i] == 0 && (*conj_two)[i] == 1) ) 
        ? - 6 
        : ((*conj_one)[i] != -6 ? (*conj_one)[i] : (*conj_two)[i]);
  }
}

/* 
  Функция клонирует конъюнкт.
*/
void cloneConj(char **conf_from, char **conf_to, int *var_count)
{
  char i;
  (*conf_to) = (char*)malloc(*var_count);
  for(i = 0; i < *var_count; i++)
    (*conf_to)[i] = (*conf_from)[i];
}

/*
  Функция склеивает все возможные конъюнкты.
*/
void mergerDNF(char ***DNF, int *var_count, int *conjuncts_count)
{
  char i, j, *mergedConj = (char*)malloc(*var_count);

  for (i = 0; i < *conjuncts_count; i++)
    for(j = 0; j < i; j++)
      if(compareConjsToMerger(&((*DNF)[i]), &((*DNF)[j]), var_count))
      {
        mergeConj(&((*DNF)[i]), &((*DNF)[j]), var_count, &mergedConj);
        if(!containConj(DNF, var_count, conjuncts_count, &mergedConj))
        {
          (*DNF) = (char**)realloc((*DNF), sizeof(char*) * (++(*conjuncts_count)) );
          cloneConj(&mergedConj, &((*DNF)[*conjuncts_count - 1]), var_count);
        }
      }

  free(mergedConj);
  mergedConj = NULL;
}


// Функции для сортировки.

/*
  Функция сравнивает конъюнкты.
  Возвращает:
    0 - если равны.
    1 - если первый конъюнкт больше второго.
    -1 - если второй коъюнкт больше первого.
*/
int compareConjs(char **conj_one, char **conj_two, int *var_count)
{
  char i, lit_one, lit_two;
  for(i = 0; i < *var_count; i++)
  {
    lit_one = (*conj_one)[i] == -6 ? 2 : (*conj_one)[i];
    lit_two = (*conj_two)[i] == -6 ? 2 : (*conj_two)[i];
    if(lit_one > lit_two)
      return 1;
    else if(lit_one < lit_two)
      return -1;
  }
  return 0;
}

/*
  Функция сортировки пузырьком для конъюнктов.
*/
void sortDNF(char ***DNF, int *var_count, int *conjuncts_count)
{
  char i, j,
    *tmpConj;

  for(i = 0; i < *conjuncts_count - 1; i++)
    for(j = 0; j < *conjuncts_count - 1 - i; j++)
      if(compareConjs( &((*DNF)[j]), &((*DNF)[j + 1]), var_count ) == 1)
      {
        tmpConj = (*DNF)[j];
        (*DNF)[j] = (*DNF)[j + 1];
        (*DNF)[j + 1] = tmpConj;
      }

  tmpConj == NULL;
}


// Main
int main(int argc, char *argv[])
{
  int var_count, conjuncts_count;
  char **DNF = readFromFile(argv[1], &var_count, &conjuncts_count);

  mergerDNF(&DNF, &var_count, &conjuncts_count); // Слеяния
  sortDNF(&DNF, &var_count, &conjuncts_count); // Сортировка


  writeToFile(argv[2], &DNF, &var_count, &conjuncts_count);

  return 0;
}