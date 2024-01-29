#include "user.h"
#include <stdlib.h>
#include <string.h>

User *createUser()
{
  User *user = malloc(sizeof(User));
  user->name = NULL;
  user->surname = NULL;
  user->wage = NULL;
  return user;
}

void destroyUser(User *user)
{
  free(user->name);
  free(user->surname);
  free(user->wage);
  free(user);
}
