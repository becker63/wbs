#include "wb.h"
#include <arpa/inet.h>
#include <string.h>
#define PORT 8080

int ahex2int(char a, char b){

    a = (a <= '9') ? a - '0' : (a & 0x7) + 9;
    b = (b <= '9') ? b - '0' : (b & 0x7) + 9;

    return (a << 4) + b;
}

void append_str(char str[] , char c){
     auto char arr[2] = {c , '\0'};
     strcat(str , arr);
}



int main(int argc, char const* argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    unsigned int addrlen = sizeof(address);
    char buffer[1024] = { 0 };

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0))
        == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
 
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
 
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket
         = accept(server_fd, (struct sockaddr*)&address,
                  (socklen_t*)&addrlen))
        < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    valread = read(new_socket, buffer, 1024);


    char* pch;

    //create copy of socket buffer so we dont mess with it when parsing
    char parserbuffer[1024];
    strcpy(parserbuffer, buffer);
    pch = strtok(parserbuffer, "\r\n");
    
    
    //parse
    char httpres[1024] = "";
    mainparse(pch, httpres);
    //printf("\n%s\n", httpres);
    
    send(new_socket, httpres, strlen(httpres), 0);

    

    char hexbuf[50];


    int number = 0;
    
    int i2 = 0;
    while ( i2 != 4 ) {
        i2++;
        read(new_socket, (char*)&number, sizeof(number));
        number = ntohl(number);
        sprintf(&hexbuf[strlen(hexbuf)],"%x", number);
    }

    char hex[50];

    for(int i = 0; hexbuf[i]; i++) {
        
        if(i % 2 == 0) {
            sprintf(&hex[strlen(hex)], "0x%c%c ", hexbuf[i],hexbuf[i + 1]);
        }
        //puts("\n");
        //printf("%c", hexbuf[i]);
        

    }
    

    token = strtok(hex, " ");
     while (token ! = NULL ) {
        token = strtok(NULL, " ");
        printf("%s", token);
  /*do token processing*/
  }










    
}

