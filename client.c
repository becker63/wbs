
// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
 
char serverHttpGen(char *wbkey, char *httpv, char *out){

    strcpy(out, "HTTP/");
    strcat(out, httpv);
    strcat(out, "\r\n");
    strcat(out, "Upgrade: websocket\r\nConnection: Upgrade\r\n");
    strcat(out, "Sec-WebSocket-Key: ");
    strcat(out, wbkey);
    strcat(out, "\r\n");


}

int main(int argc, char const* argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char* hello = "Hello from client";
    char buffer[1024] = { 0 };
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
 
    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "0.0.0.0", &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }
 
    if (connect(sock, (struct sockaddr*)&serv_addr,
                sizeof(serv_addr))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    char data[500];
    char key[100] = "dGhlIHNhbXBsZSBub25jZQ==";
    char version[10] = "1.1";
    serverHttpGen(key, version, data);
    printf("\n%s\n\n", data);

    send(sock, data, strlen(data), 0);
    valread = read(sock, buffer, 1024);
    printf("%s\n", buffer);
    return 0;
}