#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"coreutils.h"

int convert_hex_string_int(char *str) {
	if(*str != '0' && str[1] != 'x')
		return ERROR_PARSE;
	return strtol(str + 2,NULL,16);
}

int main(int argc, char **argv) {
	int start_pos;
	int read_only = 0;
	char *out_fn;
	for(int i=1;i<argc;++i)
		if(0 == strcmp(argv[i],"-ro"))
			read_only = 1;
	
	if(!read_only) {
		if(argc < 4 || argc > 4) {
			fprintf(stderr, "./" STRFY(_TARGET) " <start_pos> <content> <outfile>\n");
			return 1;
		}
	}
	if(!read_only) {
		out_fn = argv[3];
		if((start_pos = convert_hex_string_int(argv[1])) == ERROR_PARSE) {
			fprintf(stderr, STRFY(_TARGET) ":invalid hex start position:\"%s\"\n",argv[1]);
		}
		int size;
		struct hdr_loader *ld= malloc(sizeof(struct hdr_loader)*25); 
		if((size = write_and_get_hdr(ld, start_pos,argv[2],out_fn)) == 0)
			return 2;
	}
	if(read_only) {
		out_fn = argv[1];
		struct hdr_loader *f_ld = malloc(sizeof(char)*25);
		if(read_model_fmt(out_fn, f_ld) == ERROR_FILE_NOT_FOUND)
			return ~ERROR_FILE_NOT_FOUND;
		print_hdr(*f_ld);
		free(f_ld);
	}
    return 0;
}
