//http upgrade response generator
#include "wb.h"
#include <math.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <string.h>

const char *BASE64_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
 
/**
 * encode three bytes using base64 (RFC 3548)
 *
 * @param triple three bytes that should be encoded
 * @param result buffer of four characters where the result is stored
 */  
void _base64_encode_triple(unsigned char triple[3], char result[4])
 {
    int tripleValue, i;
 
    tripleValue = triple[0];
    tripleValue *= 256;
    tripleValue += triple[1];
    tripleValue *= 256;
    tripleValue += triple[2];
 
    for (i=0; i<4; i++)
    {
 result[3-i] = BASE64_CHARS[tripleValue%64];
 tripleValue /= 64;
    }
} 
 
/**
 * encode an array of bytes using Base64 (RFC 3548)
 *
 * @param source the source buffer
 * @param sourcelen the length of the source buffer
 * @param target the target buffer
 * @param targetlen the length of the target buffer
 * @return 1 on success, 0 otherwise
 */  
int base64_encode(unsigned char *source, size_t sourcelen, char *target, size_t targetlen)
 {
    /* check if the result will fit in the target buffer */
    if ((sourcelen+2)/3*4 > targetlen-1)
 return 0;
 
    /* encode all full triples */
    while (sourcelen >= 3)
    {
 _base64_encode_triple(source, target);
 sourcelen -= 3;
 source += 3;
 target += 4;
    }
 
    /* encode the last one or two characters */
    if (sourcelen > 0)
    {
 unsigned char temp[3];
 memset(temp, 0, sizeof(temp));
 memcpy(temp, source, sourcelen);
 _base64_encode_triple(temp, target);
 target[3] = '=';
 if (sourcelen == 1)
     target[2] = '=';
 
 target += 4;
    }
 
    /* terminate the string */
    target[0] = 0;
 
    return 1;
} 

void serverHttpGen(char *wbkey, char *httpv, char *out){

    strcpy(out, "HTTP/");
    strcat(out, httpv);
    strcat(out, " 101 Switching Protocols");
    strcat(out, "\r\n");
    strcat(out, "Upgrade: websocket\r\nConnection: Upgrade\r\n");
    strcat(out, "Sec-WebSocket-Accept: ");
    strcat(out, wbkey);
    strcat(out, "\r\n\r\n");



}

void removesub(char *in, char *sub){
    char *p, *q, *r;
    if (*sub && (q = r = strstr(in, sub)) != NULL) {
        size_t len = strlen(sub);
        while ((r = strstr(p = r + len, sub)) != NULL) {
            while (p < r)
                *q++ = *p++;
        }
        while ((*q++ = *p++) != '\0')
            continue;
    }

}

void convertSHA1BinaryToCharStr(const unsigned char * const hashbin, char * const hashstr) {
  for(int i = 0; i<20; ++i)
  {
    sprintf(&hashstr[i*2], "%02X", hashbin[i]);
  }
  hashstr[40]=0;
}

int mainparse(char *pch, char *out) {
    char *ret;

    char *ret2;

    char data[250] = "";

    char httppro[50] = "";

    //search for websocket client key in http packet and htp version
    while (pch != NULL)
    {
        ret = strstr(pch, "Sec-WebSocket-Key:");
        if (ret) {

                strcpy(data, pch);

        }

        ret2 = strstr(pch, "HTTP");
        if (ret2) {

                strcpy(httppro, pch);

        }
        pch = strtok(NULL, "\r\n");
    }


    //only get http version
    char sub1[50] = "GET / HTTP/";
    removesub(httppro, sub1);
    puts(httppro);

    //remove 'Sec-WebSocket-Key: ' from str for key
    char sub2[50] = "Sec-WebSocket-Key: ";
    removesub(data, sub2);           

    //concatinate clients websocket key and magic string as seen in... https://developer.mozilla.org/en-US/docs/Web/API/WebSockets_API/Writing_WebSocket_servers#exchanging_data_frames
    char magicstring[150] = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    strcat(data, magicstring);


    unsigned char hash[SHA_DIGEST_LENGTH];


    SHA1(data, strlen(data), hash);
    
    //this causes no mem leaks.. for some reason..
    base64_encode(hash,sizeof(hash),data,250);


    //combine everything together into a pretty http packet and copy to out var
    strcat(out, data);

    serverHttpGen(data, httppro, out);
    
    printf("\n\n%s", out);
    

    return 0;
}