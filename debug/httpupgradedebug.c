#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include "./b64/b64.h"
 
 
int main(){


    char *data = "dGhlIHNhbXBsZSBub25jZQ==258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    char digest[200];
    char hexdigest[200];
    
    size_t length = strlen(data);
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(data, length, hash);

    printf("%s\n", hash);

    size_t input_size = strlen(hash);
    //printf("Input size: %ld \n",input_size);
    char * encoded_data = b64_encode(hash, input_size);

    printf("%s\n",encoded_data);
    
    return 0;
}