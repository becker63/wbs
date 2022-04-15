// Server side C/C++ program to demonstrate Socket
// programming
#include "wb.h"
#include "./libs/b64/b64.h"

char serverHttpGen(char *wbkey, char *httpv, char *out){

    strcpy(out, "HTTP/");
    strcat(out, httpv);
    strcat(out, "\r\n");
    strcat(out, "Upgrade: websocket\r\nConnection: Upgrade\r\n");
    strcat(out, "Sec-WebSocket-Accept: ");
    strcat(out, wbkey);
    strcat(out, "\r\n");


}

char removesub(char *in, char *sub){
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

    //remove 'Sec-WebSocket-Key: ' from str
    char sub2[50] = "Sec-WebSocket-Key: ";

    removesub(data, sub2);           

    //concatinate clients websocket key and magic string as seen in... https://developer.mozilla.org/en-US/docs/Web/API/WebSockets_API/Writing_WebSocket_servers#exchanging_data_frames
    char magicstring[150] = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";

    strcat(data, magicstring);


    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(data, strlen(data), hash);


    size_t input_size = strlen(hash);
    char * encoded_data = b64_encode(hash, input_size);


    //copy to out var
    strcat(out, encoded_data);

    char out2[500] = "";

    serverHttpGen(encoded_data, httppro, out2);

    strcpy(out, out2);

    return 0;
}