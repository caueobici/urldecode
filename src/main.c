#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "url.h"


#define BUF_SIZE 1024
#define HELP_TEXT "\
[usage] %s [<options> <data>]\n\
    -h          shows this help and exit\n\
    -d          decode data\n\
    -a          encode all chars\n\
    [data]      the data to encode/decode (if not specified, it will be read from stdin)\n"


enum modes{
    DECODE_MODE,
    ENCODE_MODE,
    AGGRESSIVE_ENCODE_MODE
};

int8_t mode = ENCODE_MODE;
char* data = NULL;

void show_help(char *program_name){
    fprintf(stderr, HELP_TEXT, program_name);
    exit(0);
}

void parse_args(int argc, char**argv){
    char* v = NULL;

    for (int i=1; i < argc; i++){

        if (strcmp(argv[i], "--help") == 0) show_help(argv[0]); // show help

        v = argv[i];
        if (v[0] != '-'){
            data = v;
        }
        else{
            switch(v[1]){
                case 'd':
                    mode = DECODE_MODE;
                    break;
                case 'a':
                    mode = AGGRESSIVE_ENCODE_MODE;
                    break;
                case 'h':
                    show_help(argv[0]);
            }
        }
    }  

}

void read_stdin(){
    size_t contentSize = 1; 
    char buffer[BUF_SIZE];

    data = malloc(sizeof(char) * BUF_SIZE);
    
    if(data == NULL)
    {
        perror("Failed to allocate data");
        exit(1);
    }
    data[0] = '\0'; // make null-terminated
    while(fgets(buffer, BUF_SIZE, stdin))
    {
        char *old = data;
        contentSize += strlen(buffer);
        data = realloc(data, contentSize);
        if(data == NULL)
        {
            perror("Failed to reallocate data");
            free(old);
            exit(2);
        }
        strcat(data, buffer);
    }

    if(ferror(stdin))
    {
        free(data);
        perror("Error reading from stdin.");
        exit(3);
    }
}


int main(int argc, char **argv){
    parse_args(argc, argv);

    if (!data){ // read from stdin
        read_stdin();
    }

    char *result = NULL;

    switch(mode){
        case DECODE_MODE:
            result = url_decode(data);
            break;
        case ENCODE_MODE:
            result = url_encode(data);
            break;
        case AGGRESSIVE_ENCODE_MODE:
            result = url_aggressive_encode(data);
            break;
    }

    puts(result);

    return 0;
}