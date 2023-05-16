#include<stdio.h>
#include<stdlib.h>

#include"coreutils.h"
#include"xtoi.h"

#ifndef _TARGET
#define _TARGET "<prog>"
#endif

#define STRFY(str) STRFY1(str)
#define STRFY1(str) STRFY2(str)
#define STRFY2(str) #str

int convert_hex_string_int(char *str) {
	if(*str != '0' && str[1] != 'x')
		return ERROR_PARSE;
			
	return strtol(str + 2,NULL,16);
}

int main(int argc, char **argv) {
	int start_pos;
	
	if(argc < 4 || argc > 4) {
		fprintf(stderr, "./" STRFY(_TARGET) " <start_pos> <content> <outfile>\n");
		return 1;
	}
	
	// the basic model
	if((start_pos = convert_hex_string_int(argv[1])) == ERROR_PARSE) {
		fprintf(stderr, STRFY(_TARGET) ":invalid hex start position:\"%s\"\n",argv[1]);
	}
	int size;
	struct hdr_loader *ld = malloc(sizeof(char)*25), *f_ld = malloc(sizeof(char)*25); 
	
	if((size = write_and_get_hdr(ld, start_pos,argv[2],argv[3])) == 0)
		return 2;
	read_model_fmt(argv[3], f_ld);
//	if(mk_executable(argv[3]) == ERROR_CHMOD) {
//		fprintf(stderr, "%s: error for chmod\n", argv[3]);
//		return 3;
//	}
	print_hdr(*f_ld);
	free(f_ld);
	free(ld);
}
