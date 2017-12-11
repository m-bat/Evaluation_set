#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 256

int main(int argc, char *argv[])
{
    FILE *fp;
    char buf[BUFSIZE], str[BUFSIZE];
    int i, count, start;
    unsigned int hi = 0, lo = 0;
    unsigned long long stime = 0, etime = 0;
             

    if (argc != 2) {
        fprintf(stderr, "Usage: ./a.out file\n");
        return -1;
    }
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open file\n");
        return -1;
    }
    while(fgets(buf, BUFSIZE, fp) != NULL) {
        i = 0;
        count = 0;
        stime = 0;
        etime = 0;
        hi = 0;
        lo =  0;
        start = 0;
        while (buf[i] != '\0') {
            if (buf[i] == ',') {
                count++;
                buf[i] = '\0';
                strcpy(str, &buf[start]);
                if (count == 1 || count == 3) {
                    lo = (unsigned int)atoi(str);
                    //printf("lo %u\n", lo);
                } else if (count == 2) {                    
                    hi = (unsigned int)atoi(str);
                    //printf("hi %u\n", hi);        
                    stime = hi;
                    stime = (stime << 32) | lo;         
                }
                start = i + 1;
            }
            i++;
        }
        strcpy(str, &buf[start]);
        hi = (unsigned int)atoi(str);
        etime = hi;
        etime = (etime << 32) | lo;        
        //printf("stime %llu\n", stime);
        //printf("etime %llu\n", etime);
        printf("%llu\n", etime - stime);
    }
    
    fclose(fp);       
    return 0;
}
