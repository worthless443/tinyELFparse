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

int main(int argc, char **argv) {
	char helpbuffer[100];
	if(argc < 4 || argc > 4) {
		fprintf(stderr, "./" STRFY(_TARGET) " <start_pos> <content> <outfile>\n");
		return 1;
	}
	// the basic model
	int size;
	char *desg = "elf\0you are shit\0\x10\xf1\x69\x41\x42\x43";
	struct hdr_loader *ld = malloc(sizeof(char)*20), *f_ld = malloc(sizeof(char)*20); 

	struct hdr_loader *_ld = (struct hdr_loader*)desg;
	if((size = write_and_get_hdr(ld, _atoi(argv[1]),argv[2],argv[3])) == 0)
		return 2;
	read_model_fmt(argv[3], f_ld, size);
//	if(mk_executable(argv[3]) == ERROR_CHMOD) {
//		fprintf(stderr, "%s: error for chmod\n", argv[3]);
//		return 3;
//	}
	print_hdr(*f_ld);
	free(f_ld);
	free(ld);
}
