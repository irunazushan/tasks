#include <RRCConnectionRequest.h>
#include <arpa/inet.h>
#include <conversions.h>
#include <net/if.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void tx_send(uint8_t **buffer, ssize_t *len) {
  struct sockaddr_in servaddr = {
      .sin_family = AF_INET,
      .sin_port = htons(8080),
      .sin_addr.s_addr = inet_addr("172.22.86.50"),
  };

  int sockfd;

  sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP);
  if (sockfd < 0) {
    printf("Error when opening socket\n");
    exit(1);
  }

  int ret = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
  if (ret < 0) {
    printf("Error when connecting socket\n");
    exit(1);
  }

  ret = sctp_sendmsg(sockfd, *buffer, *len, NULL, 0, 0, 0, 0, 0, 0);
  if (ret < 0) {
    printf("Error when sending msg\n");
    exit(1);
  }

  printf("Sent packet\n");

  close(sockfd);
}

void RRCConnectionRequest_coder(uint8_t **buffer, ssize_t *len) {
  RRCConnectionRequest_t *pdu;
  pdu->criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.choice
      .randomValue = 0b010110101010;
  asn_encode_to_buffer(pdu, buffer, len);
}