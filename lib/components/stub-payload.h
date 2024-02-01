#ifndef STUB_PAYLOAD_H
#define STUB_PAYLOAD_H

typedef struct StubPayload {
  void (*destroy)(struct StubPayload *ip);
} StubPayload;

#endif // STUB_PAYLOAD_H
