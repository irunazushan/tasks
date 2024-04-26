#include <rrc_coder.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  uint8_t *buffer;
  ssize_t len;
  int sockfd = -2;
  int ctl = 0;
  RRCConnectionRequest_coder(&buffer, &len);
  ctl = tx_send(&sockfd, &buffer, &len);
  free(buffer);
  if (ctl >= 0) {
    ctl = tx_read(&sockfd, &buffer, &len);
  }
  asn_dec_rval_t rval;
  RRCConnectionSetup_t *decoded_message = NULL;
  rval = asn_decode(NULL, ATS_CANONICAL_XER, &asn_DEF_RRCConnectionSetup,
                    (void **)&decoded_message, buffer, len);

  if (rval.code != RC_OK) {
    fprintf(stderr, "Error decoding rrc message\n");
    exit(1);
  }
  // далее будет обработка инфомрации UE от eNb
  // после:
  free(buffer);
  RRCConnectionRequest_coder(&buffer, &len);
  tx_send(&sockfd, &buffer, &len);
  free(buffer);

  return 0;
}
