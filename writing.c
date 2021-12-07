#include "writing.h"

int main() {
  int sem = semget(SEMKEY, 0, 0);
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1;

  int shm = shmget(SHMKEY, 0, 0);
  int * d = shmat(shm, 0, 0);
  printf("shared data: %d\n", *d);

  int file = open("sempahorefun", O_RDWR | O_APPEND);

  struct stat s;
  stat("sempahorefun", &s);
  char str[s.st_size];
  read(file, str, s.st_size-2);
  str[s.st_size] = '\n';

  char *line;
  char * temp = str;
  temp += s.st_size -1 - *d;
  strcpy(line, temp);
  printf("last line: %s\n", line);
  char input[100];
  printf("enter your line: ");
  fgets(input, 100, stdin);
  printf("%s\n", input);

  write(file, input, strlen(input));
  *d = strlen(input);

  sb.sem_op = 1;

  shmdt(d);

  close(file);

  return 0;
}
