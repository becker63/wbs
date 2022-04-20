#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

uint32_t hex2int(char *hex) {
    uint32_t val = 0;
    while (*hex) {
        // get current character then increment
        char byte = *hex++; 
        // transform hex character to the 4bit equivalent number, using the ascii table indexes
        if (byte >= '0' && byte <= '9') byte = byte - '0';
        else if (byte >= 'a' && byte <='f') byte = byte - 'a' + 10;
        else if (byte >= 'A' && byte <='F') byte = byte - 'A' + 10;    
        // shift 4 to make space for new digit, and add the 4 bits of the new digit 
        val = (val << 4) | (byte & 0xF);
    }
    return val;
}

int split (const char *txt, char delim, char ***tokens)
{
    int *tklen, *t, count = 1;
    char **arr, *p = (char *) txt;

    while (*p != '\0') if (*p++ == delim) count += 1;
    t = tklen = calloc (count, sizeof (int));
    for (p = (char *) txt; *p != '\0'; p++) *p == delim ? *t++ : (*t)++;
    *tokens = arr = malloc (count * sizeof (char *));
    t = tklen;
    p = *arr++ = calloc (*(t++) + 1, sizeof (char *));
    while (*txt != '\0')
    {
        if (*txt == delim)
        {
            p = *arr++ = calloc (*(t++) + 1, sizeof (char *));
            txt++;
        }
        else *p++ = *txt++;
    }
    free (tklen);
    return count;
}

int main(void) {
  char **tokens;
  int count, i;
  const char *str = "81 83 e1 7e 8e b9 95 1b fd cd c1 13 eb ca 92 1f e9 dc";


  int key[6];
  int i2 = 0;
  int i4 = 0;
  count = split (str, ' ', &tokens);
  for (i = 0; i < count; i++) {
    
    
    
    if ((i > 1) && (i < 6))  {
        int keytonum = (int)strtol(tokens[i], NULL, 16); 
        key[i2] = keytonum;
        i2++;
        //printf("%d , %d , %d\n",i2, key[i2], keytonum);
    }
    if ((i > 6))  {
        i4++;
        
        //this is the wrong int conversion \/ TODO, use sprintf to correct turn the hex string to int

        int maskednum = (int)strtol(tokens[i], NULL, 16); 
        //printf("%d : %d : %d", maskednum, key[i4 - 1], i4 - 1);

        int k = maskednum ^= key[i4 - 1];

   

        char charValue = k;
        printf("%i : %i : %i\n",k, maskednum, key[i4 - 1]);

        if ( i4 == 4 ){
            i4 = 0;
        }

        
    }
  
  }
  //printf("%d", key[0]);

  return 0;
}