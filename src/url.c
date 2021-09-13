#include "url.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Reserved chars to encode (RFC 3986)
/*
reserved    = gen-delims / sub-delims
gen-delims  = ":" / "/" / "?" / "#" / "[" / "]" / "@"
sub-delims  = "!" / "$" / "&" / "'" / "(" / ")" / "*" / "+" / "," / ";" / "="
*/
#define RESERVED_CHARS ":/?#[]@!$&'()*+,;="
char encode_chars[256] = {};

void init_reserved_chars() __attribute__((constructor));

void init_reserved_chars(){
    // add reserved chars
    for (int i=0; i<strlen(RESERVED_CHARS); i++){
        char c = RESERVED_CHARS[i];
        encode_chars[c] = 1;
    }
    // add non alphanumeric chars
    for (int i=0; i<256; i++){
        if (!isalnum(i)){
            encode_chars[i] = 1;
        }
    }
    
}

char *url_encode(unsigned char *s){

    // create a chunk with the max possible size of the encoded data
    size_t length = strlen(s) * 3 + 1;
    char *enc = calloc(1, length);
    char* enc_ptr = enc;

    for (; *s; s++){
        if (encode_chars[*s]){ // check if the char is a reserved char
            sprintf(enc_ptr++, "%%%02x", *s);
            enc_ptr += 2;
        }
        else{
            *enc_ptr++ = *s;
        }
    }

    return enc;
}

char *url_aggressive_encode(unsigned char *s){

    size_t length = strlen(s) * 3 + 1;
    char *enc = calloc(1, length);
    char* enc_ptr = enc;

    // encode all characters
    for (; *s; s++){
        sprintf(enc_ptr++, "%%%02x", *s);
        enc_ptr += 2;
    }

    return enc;
}

char *url_decode(unsigned char *s){

    size_t length = strlen(s);
    char *dec = calloc(1, length);
    char *dec_ptr = dec;
    char hex[2] = "";

    for (; *s; s++){
        switch(*s){
            case '+':
                *dec_ptr++ = ' ';
                break;
            case '%':
                hex[0] = s[1];
                hex[1] = s[2];
                s += 2;
                *dec_ptr++ = (char)strtol(hex, NULL, 16);
                break;
            default:
                *dec_ptr++ = *s;
        }
    }
    
    return dec;

}