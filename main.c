#include<stdio.h>
#include<stdlib.h>

#include"coreutils.h"
#include"xtoi.h"

int main(int argc, char **argv) {
	if(argc < 4 || argc > 4) {
		fprintf(stderr,"./<prog> <start_pos> <content> <outfile>\n");
		return 1;
	}
	// the basic model
	char *desg = "elf\0you are shit\0\x10\xf1\x69";
	struct hdr_loader *ld = malloc(sizeof(char)*20), *f_ld = malloc(sizeof(char)*20); 
	write_and_get_hdr(ld, _atoi(argv[1]),argv[2],argv[3]);
	read_model_fmt(argv[3], f_ld);
	print_hdr(*f_ld);
	free(f_ld);
	free(ld);
}
