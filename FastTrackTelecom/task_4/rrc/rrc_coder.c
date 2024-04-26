#include "rrc_coder.h"

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
#include <asn_application.h>

#define PORT 8080

void RRCConnectionRequest_coder(uint8_t **buffer, ssize_t *len){
    RRCConnectionRequest_t *conReq = NULL;
    conReq = (RRCConnectionRequest_t*)calloc(1, sizeof(RRCConnectionRequest_t));
    conReq->criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.present = InitialUE_Identity_PR_randomValue;
    conReq->criticalExtensions.present = RRCConnectionRequest__criticalExtensions_PR_rrcConnectionRequest_r8;
    conReq->criticalExtensions.choice.rrcConnectionRequest_r8.establishmentCause = EstablishmentCause_mt_Access;
    const size_t randomValueSize = 5;
    uint8_t *bufNum = (uint8_t*)calloc(randomValueSize, sizeof(uint8_t));
    for (int i = 0; i < randomValueSize; ++i) {
        bufNum[i] = rand() % 256;
    }
    conReq->criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.choice.randomValue.buf = bufNum;
    conReq->criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.choice.randomValue.size = randomValueSize;
    
    asn_encode_to_new_buffer_result_t res = {NULL, {0, NULL, NULL}};
    res = asn_encode_to_new_buffer(NULL, ATS_CANONICAL_XER, &asn_DEF_RRCConnectionRequest, conReq);
    free(res.buffer);
    memset(&res, 0, sizeof(res));
    res = asn_encode_to_new_buffer(NULL, ATS_ALIGNED_CANONICAL_PER, &asn_DEF_RRCConnectionRequest_r8_IEs, conReq);

    *buffer = res.buffer;
    *len = res.result.encoded;

    if (*buffer == NULL) {
        fprintf(stderr, "Error enconing rrc buffer\n");
        exit(1);
    } else {
        fprintf(stderr, "Encoded buffer\n");
    }

    xer_fprint(stdout, &asn_DEF_RRCConnectionRequest, conReq);    
}

void RRCConnectionSetup_coder(uint8_t **buffer, ssize_t *len) {
    RRCConnectionSetup_t *conSet = NULL;
    conSet = (RRCConnectionSetup_t*)calloc(1, sizeof(RRCConnectionSetup_t));
    conSet->rrc_TransactionIdentifier = 2;
    conSet->criticalExtensions.choice.c1.choice.rrcConnectionSetup_r8 = RRCConnectionSetup__criticalExtensions__c1_PR_rrcConnectionSetup_r8;

    asn_encode_to_new_buffer_result_t res = {NULL, {0, NULL, NULL}};
    res = asn_encode_to_new_buffer(NULL, ATS_CANONICAL_XER, &asn_DEF_RRCConnectionRequest, conSet);
    free(res.buffer);
    memset(&res, 0, sizeof(res));
    res = asn_encode_to_new_buffer(NULL, ATS_ALIGNED_CANONICAL_PER, &asn_DEF_RRCConnectionSetup_r8_IEs, conSet);

    *buffer = res.buffer;
    *len = res.result.encoded;

    if (*buffer == NULL) {
        fprintf(stderr, "Error enconing rrc buffer\n");
        exit(1);
    } else {
        fprintf(stderr, "Encoded buffer\n");
    }

    xer_fprint(stdout, &asn_DEF_RRCConnectionRequest, conSet);    
}

void RRCConnectionSetupComplete_coder(uint8_t **buffer, ssize_t *len) {
    RRCConnectionSetupComplete_t *conCmplt = NULL;
    conCmplt = (RRCConnectionSetupComplete_t*)calloc(1, sizeof(RRCConnectionSetupComplete_t));
    conCmplt->rrc_TransactionIdentifier = 2;
    conCmplt->criticalExtensions.choice.c1.choice.rrcConnectionSetupComplete_r8 = RRCConnectionSetupComplete__criticalExtensions__c1_PR;
    conCmplt->criticalExtensions.choice.c1.choice.rrcConnectionSetupComplete_r8.selectedPLMN_Identity = 1;

      asn_encode_to_new_buffer_result_t res = {NULL, {0, NULL, NULL}};
    res = asn_encode_to_new_buffer(NULL, ATS_CANONICAL_XER, &asn_DEF_RRCConnectionRequest, conCmplt);
    free(res.buffer);
    memset(&res, 0, sizeof(res));
    res = asn_encode_to_new_buffer(NULL, ATS_ALIGNED_CANONICAL_PER, &asn_DEF_RRCConnectionSetup_r8_IEs, conCmplt);

    *buffer = res.buffer;
    *len = res.result.encoded;

    if (*buffer == NULL) {
        fprintf(stderr, "Error enconing rrc buffer\n");
        exit(1);
    } else {
        fprintf(stderr, "Encoded buffer\n");
    }

    xer_fprint(stdout, &asn_DEF_RRCConnectionRequest, conCmplt); 
}

int tx_read(int *sockfd, uint8_t **buffer, ssize_t *len) {
    ret = read(sock, buffer, 1024);
    //конвертировать сообщения из asn1 и обработать его...
    return ret;
}


int tx_send(int *sockf, uint8_t **buffer, ssize_t *len) {
    if (*sockf == -2) {
        struct sockaddr_in servaddr = {
            .sin_family = AF_INET,
            .sin_port = htons(8080),
            .sin_addr.s_addr = inet_addr("172.22.86.50"),
        };

        *sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP);
        if (sockfd < 0) {
            printf("Error when opening socket\n");
            exit(1);
        }

        int ret = connect(*sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
        if (ret < 0) {
            printf("Error when connecting socket\n");
            exit(1);
        }
    }

    ret = sctp_sendmsg(*sockfd, *buffer, *len, NULL, 0, 0, 0, 0, 0, 0);
    if (ret < 0) {
        printf("Error when sending msg\n");
        exit(1);
    }
    printf("Sent packet\n");

    return ret;

}