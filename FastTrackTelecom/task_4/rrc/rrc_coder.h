#ifndef _RRC_CODER_H
#define _RRC_CODER_H

#include <stdio.h>
#include <sys/types.h>
#include <RRCConnectionRequest.h>
#include <RRCConnectionSetup.h>
#include <RRCConnectionSetupComplete.h>

void RRCConnectionRequest_coder(uint8_t **buffer, ssize_t *len);
void RRCConnectionSetup_coder(uint8_t **buffer, ssize_t *len);
void RRCConnectionSetupComplete_coder(uint8_t **buffer, ssize_t *len);
int tx_send(int* sockfd, uint8_t **buffer, ssize_t *len);
int tx_read(int* sockfd, uint8_t **buffer, ssize_t *len);

#endif