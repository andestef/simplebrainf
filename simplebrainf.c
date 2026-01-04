#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CTYPE_LINUX
//#define CTYPE_NT
#define MAX_FILE_SIZE 2048
#define DATATYPE char
#define MAXCELLS 256
#define SMARTLOOP
//#define MAXLOOPSIZE 1024

#if defined(CTYPE_LINUX) && defined(CTYPE_NT)
#error "Set Compile type to either LINUX or NT"
#elif !defined(CTYPE_LINUX) && !defined(CTYPE_NT)
#error "Set Compile type to either LINUX or NT"
#endif
#if defined(SMARTLOOP) && defined(MAXLOOPSIZE)
#error "Define either SMARTLOOP or MAXLOOPSIZE"
#elif !defined(SMARTLOOP) && !defined(MAXLOOPSIZE)
#error "Define either SMARTLOOP or MAXLOOPSIZE"
#endif
#ifdef SMARTLOOP
#define MAXLOOPSIZE MAX_FILE_SIZE/2
#endif

int main(){
    FILE *fptr;
    fptr = fopen("hello.bf", "r");
    if (!fptr) {
        perror("hello.bf");
        return 1;
    }
    char code[MAX_FILE_SIZE];
    if (!fgets(code, MAX_FILE_SIZE, fptr)) {
        printf("Empty file\n");
        return 1;
    }
    DATATYPE cells[MAXCELLS];
    for (unsigned int i=0;i<MAXCELLS;i++){
        cells[i] = 0;
    }
    unsigned int skip = 0;
    unsigned int current = 0;
    unsigned int jumpto[MAXLOOPSIZE];
    unsigned int jumptolength = 0;
    for (unsigned int i=0;i<MAXLOOPSIZE;i++){
        jumpto[i] = 0;
    }
    char cc;
    for(unsigned int i=0;i<strlen(code);i++){
        cc = code[i];
        if (skip != 0){
            if (cc == '['){
                skip++;
            }
            else if(cc == ']'){
                skip--;
            }
        }
        else if (cc == '>'){
            if (current != MAXCELLS-1){
            current++;
            }
            else{
                printf("BrainFErr (Fatal): Too many cells\n");
                return 1;
            }
        }
        else if (cc == '<'){
            if (current != 0){
            current--;
            }
            else{
                printf("BrainFErr (Fatal): Can't have cell less than 0.\n");
                return 1;
            }
        }
        else if (cc == '+'){
            cells[current]++;
        }
        else if (cc == '-'){
            cells[current]--;
        }
        else if(cc == '.'){
            printf("%c",cells[current]);
        }
        else if(cc == ','){
            #ifdef CTYPE_LINUX
            system("/bin/stty raw");
            cells[current] = getchar();
            system("/bin/stty cooked");
            #endif
            #ifdef CTYPE_NT
            printf("NO INPUT WITH WINDOWS YET!!!!\n");
            #endif
        }
        else if(cc == '_'){
            #if DATATYPE == char || DATATYPE == int
            printf("%i",cells[current]);
            #endif
        }
        else if (cc == '['){
            if (cells[current] == 0){
                skip += 1;
            }
            else{
                jumpto[jumptolength] = i;
                jumptolength++;
            }
        }
        else if (cc == ']'){
            if (cells[current] != 0){
                if (jumptolength == 0) {
                    printf("BrainFErr: Unmatched ']'\n");
                    return 1;
                }
                i = jumpto[jumptolength - 1];
            }   
            else{
                jumptolength--;
            }
        }
    }
    return 0;
}
