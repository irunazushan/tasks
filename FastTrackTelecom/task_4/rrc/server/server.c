#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "../rrc_coder.h"

#define PORT 8080
#define MAX_SIZE 1024

int main() {
  int server_fd, new_socket;
  struct sockaddr_in address;
  int opt = 1;
  int addrlen = sizeof(address);
  uint8_t *buffer = NULL;
  ssize_t len;

  if ((server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }
  if (listen(server_fd, 1000) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }
  while (1) {
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addrlen)) < 0) {
      perror("accept");
      exit(EXIT_FAILURE);
    }
    int isRead = 0;
    // Чтение и вывод сообщения от клиента
    isRead = tx_read(new_socket, &buffer, &len);
    // Получаем сообщение, конвертируем из asn1, читаем и обрабатываем ...
    asn_dec_rval_t rval;
    RRCConnectionRequest_t *decoded_message = NULL;
    rval = asn_decode(NULL, ATS_CANONICAL_XER, &asn_DEF_RRCConnectionRequest,
                      (void **)&decoded_message, buffer, len);

    if (rval.code != RC_OK) {
      fprintf(stderr, "Error decoding rrc message\n");
      exit(1);
    }
    free(buffer);
    RRCConnectionSetup_coder(&buffer, &len);
    tx_send(&new_socket, &bufer, &len, 0);

    isRead = tx_read(new_socket, &buffer, &len);
    // Получаем сообщение, конвертируем из asn1, читаем и обрабатываем ...
    asn_dec_rval_t rval2;
    RRCConnectionSetupComplete_t *decoded_message = NULL;
    rval2 =
        asn_decode(NULL, ATS_CANONICAL_XER, &asn_DEF_RRCConnectionSetupComplete,
                   (void **)&decoded_message, buffer, len);

    if (rval2.code != RC_OK) {
      fprintf(stderr, "Error decoding rrc message\n");
      exit(1);
    }

    close(new_socket);
  }

  // Закрытие сокетов
  close(new_socket);
  close(server_fd);

  return 0;
}