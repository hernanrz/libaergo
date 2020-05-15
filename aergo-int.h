//#include "mbedtls/bignum.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <stdint.h>
//#include <stdbool.h>

#include <errno.h>

#ifdef _WIN32
#include <winsock.h>
#else
#include <sys/socket.h>  /* socket, connect */
//#include <sys/select.h>
#include <netinet/in.h>  /* struct sockaddr_in, struct sockaddr */
#include <netinet/tcp.h> /* TCP_NODELAY */
//#include <netinet/ip.h>
#include <netdb.h>  /* struct hostent, gethostbyname */
#include <unistd.h> /* read, write, close */
#define SOCKET int
#define INVALID_SOCKET  (~0)
#define SOCKET_ERROR    (-1)
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
#endif


typedef struct request request;

struct request {
  struct request *next;
  char txn_hash[32];
  process_response_cb process_response;
  void *callback;
  void *arg;
  SOCKET sock;
  char *response; // dynamically allocated ?
  int received;
};


// Aergo connection instance
struct aergo {
  char host[32];
  int port;
  uint8_t blockchain_id_hash[32];
  request *requests;
};



uint32_t encode_http2_data_frame(uint8_t *buffer, uint32_t content_size);
