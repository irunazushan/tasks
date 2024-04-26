#include <stdio.h>
#include <sys/types.h>

#include <rrc_coder.h>
#include <unistd.h>

int main() {
    uint8_t *buffer;
    ssize_t len;
    int sockfd;
    int ctl = 0;
    RRCConnectionRequest_coder(&buffer, &len);
    ctl = tx_send(&sockfd, &buffer, &len);
    free(buffer);
    if (ctl >= 0) {
        ctl = tx_read(&sockfd, &buffer, &len);
    }

    // далее будет обработка инфомрации UE от eNb
    // после:
    free(buffer); 
       
    RRCConnectionRequest_coder(&buffer, &len);
    tx_send(&sockfd, &buffer, &len);
    free(buffer);
    
    return 0;
}
