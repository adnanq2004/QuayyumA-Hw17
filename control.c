#include "control.h"

void create_thing() {
  int sem = semget(SEMKEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  if (sem == -1) {
    sem = semget(SEMKEY, 1, 0);
  }
  union semun num1;
  num1.val = 1;
  int r = semctl(sem, 0, SETVAL, num1);
  printf("value of sempahore: %d\n", r);

  int shm = shmget(SHMKEY, 4, IPC_CREAT | IPC_EXCL | 0644);
  if (shm == -1) {
    shm = shmget(SHMKEY, 1, 0);
  }

  int file = open("sempahorefun", O_CREAT | O_EXCL | O_TRUNC, 0644);
  close(file);

  printf("thing has been created?\n");
}

void remove_thing() {
  int sem = semget(SEMKEY, 0, 0);
  if (sem == -1) {
    sem = semget(SEMKEY, 1, 0);
  }
  semctl(sem, IPC_RMID, 0);

  int shm = shmget(SHMKEY, 0, 0);
  if (shm == -1) {
    shm = shmget(SHMKEY, 1, 0);
  }
  semctl(shm, IPC_RMID, 0);

  int file = open("sempahorefun", O_RDONLY);
  struct stat s;
  stat("sempahorefun", &s);
  char str[s.st_size];
  read(file, str, s.st_size-1);
  printf("%s\n", str);

  printf("thing has been removed?\n");
}

int main(int argc, char * argv) {
  // printf("are you creating or removing?\n");
  if (!strcmp(argv[1], "control")) {
    create_thing();
  }
  else if (!strcmp(argv[1], "remove")) {
    remove_thing();
  }

  return 0;
}
