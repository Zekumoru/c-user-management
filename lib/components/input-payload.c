#include "components.h"
#include <stdlib.h>
#include <string.h>

void destroyInputPayload(StubPayload *__ip)
{
  InputPayload *ip = (InputPayload *)__ip;
  free(ip->input);
  free(ip);
}

InputPayload *createInputPayload(char *input)
{
  InputPayload *ip = malloc(sizeof(InputPayload));
  ip->input = strdup(input);
  ip->destroy = destroyInputPayload;
  return ip;
}
