#include "wb.h"
#include <arpa/inet.h>
#include <string.h>
#include <assert.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#define PORT 8080

int parse(unsigned char* in, size_t len, char **a, char **b){
  char new[50] = "";
  //iterate over string
  int i;
  for (i = 0; i < len; i++) {
    char ptr = in[i]; 
    if (isdigit(in[i])) {
        strncat(new, &ptr, 1);
    }

    char j = ',';

    if ( in[i] == j ) {
        strncat(new, &ptr, 1);
    }
  }

  char * separator = ",";
  char * one = strtok(new, separator);
  char * two = strtok(NULL, "");


  *a = one;
  *b = two;

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

    while (1 == 1){


    unsigned char buf[1000] = {};
    /* return code of recv gives me the acutual amount of data */
    int s = recv(new_socket, buf, sizeof(buf),0);

    unsigned char keys[20] = {};

    unsigned char mask[1000] = {};

    char unmask[1000] = {};

    int i2 = 0;
    int i3 = 0;
    int i = 0;

    while(i != s){
        /* get key */
        if ((i > 1) && (i < 6)){
        keys[i2] = buf[i];
        //printf("%x : %i  k\n", keys[i2], i);
        i2++;

        }
        
        /* Get mask */
        if ((i >= 6) && (i < s)){
        
            //printf("\n%x : %i  b \n", buf[i], i);

            mask[i3] = buf[i];

            //printf("%x : %i\n", keys[i3], i3);

            i3++;

        }
        
        i++;
    }
    //puts("\n\n\n");
    i = 0;

    /* Demask */
    for (int i = 0; i < s - 6; i++) {
    unmask[i] = mask[i] ^= keys[i % 4];
    printf("%c", unmask[i]);

    }

    /* add null char at the end so its a string */
    unmask[s + 1] = '\0';
    printf("%s", unmask);






    char *xj;
    char *yj;


    parse(unmask, strlen(unmask), &xj, &yj);

    printf("%s %s \n", xj, yj);


    Display *dpy;
    Window root_window;

    dpy = XOpenDisplay(0);

    root_window = XRootWindow(dpy, 0);
     
    XSelectInput(dpy, root_window, KeyReleaseMask);

    XWarpPointer(dpy, None, root_window, 0, 0, 0, 0, xj, yj);

    XFlush(dpy);
    
    }




























    }







    


