#ifndef USER_H
#define USER_H

typedef struct User
{
  char *name;
  char *surname;
  double *wage;
} User;

User *createUser();
void destroyUser(User *user);

#endif // USER_H
