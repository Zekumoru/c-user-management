#include "user.h"
#include <stdlib.h>
#include <string.h>

User *createUser(char *name, char *surname, double wage)
{
  User *user = malloc(sizeof(User));
  user->name = strdup(name);
  user->surname = strdup(surname);
  user->wage = wage;
  return user;
}

void destroyUser(User *user)
{
  free(user->name);
  free(user->surname);
  free(user);
}
