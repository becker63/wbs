#include "wb.h"
#include <arpa/inet.h>
#include <string.h>
#include <assert.h>
#define PORT 8080

void strit(char *str, int it1, int it2, char *out, size_t slen){
int i = 0;
char * token = strtok(str, " ");
char spaces[20] = " ";
   while( token != NULL ) {
      token = strtok(NULL, " ");
      if ((i > it1) && (i < it2)){
//            strcat(spaces, token);
//            printf("%s : %i : %i : %i \n", out, i, slen, olen);
            if (str != "") {
                int c = strtol(token, NULL, 16);
                printf("%i\n", c);
            }
//            strcpy(spaces, " ");
        }
        i++;
   }
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

    


    char hexbuf[100] = "";

    int number = 0;
    
    int i2 = 0;
    while ( i2 != 4 ) {
        read(new_socket, (char*)&number, sizeof(number));
        number = ntohl(number);
        sprintf(&hexbuf[strlen(hexbuf)],"%x", number);
        i2++;
    }

    char hex[100];

    for(int i = 0; hexbuf[i]; i++) {
        
        if(i % 2 == 0) {
            sprintf(&hex[strlen(hex)], "%c%c ", hexbuf[i],hexbuf[i + 1]);
        }
        //puts("\n");
        //printf("%c ", hexbuf[i]);
        

    }
    printf("\n\n%s\n\n", hex);

   char key[20] = "";
   char mask[200] = "";
   char buf[1000];


   strcpy(buf, hex);
   strit(buf,1, 6,key, strlen(buf));
   printf("\n\n%s\n\n", key);


   
   strcpy(buf, hex);
   char strs[50][100];
   strit(buf,6, 50,mask,strlen(buf));
   printf("\n\n%s\n\n", mask);

  










    
}

