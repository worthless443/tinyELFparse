#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<coreutils.h>

#define __get_masked(a) a & 0xf0 & (a >> 1)

static void create_bytes_string(char *bytesstring, int start_pos) {
	for(int i=0,mask=0xf0;i<3;) {
		if(start_pos & 0xf0) {
			*(bytesstring + i) = start_pos;
			start_pos+=start_pos & ++mask;
			++i;
		}
	}
}

int create_rawbytes(char *rawstring, char *input, int start_pos) {
	int size;
	char tmpstring[10];
	strcat(rawstring, "ELF");
	rawstring[3] = '\0';
	memcpy(tmpstring,rawstring,4);
	if(strlen(input) == 12)
		strcat(rawstring, input);
	else {
		for(int i=strlen(tmpstring) + 1,ii=0;i<12 + strlen(tmpstring) + 1;++i,++ii) {
			rawstring[i] = input[ii];
		}
	}
	rawstring[strlen(tmpstring) + 12 + 2] = '\0';
	char bytesstring[3];
	create_bytes_string(bytesstring, start_pos);
	size=12 + strlen(tmpstring) + 2;
	for(int ii=0;ii<3;++size,++ii)
		rawstring[size] = bytesstring[ii];
	return size;
	//strcat(rawstring,bytesstring);
}

void get_hdr(struct hdr_loader *ld, int start_pos, char *input_str) {
	char rawstring[32];
	int size = create_rawbytes(rawstring, input_str, start_pos);
	memcpy(ld,(struct hdr_loader*)rawstring,size);
}

void write_and_get_hdr(struct hdr_loader *ld, int start_pos, char *input_str, char *output) {
	char rawstring[32];
	int size = create_rawbytes(rawstring, input_str, start_pos);
	memcpy(ld,(struct hdr_loader*)rawstring,size);
	FILE *f = fopen(output, "w");
	fwrite("\0",1,1,f);
	fwrite(rawstring,1,size,f);
	fclose(f);
}

void read_model_fmt(const char *input, struct hdr_loader *ld) {
	int i;
	FILE *f = fopen(input,"r");
	char *data = malloc(sizeof(char)*20);
	char *buffer = data;
	for(i=1;fread(buffer,1,1,f);++i) {
		data = realloc(data,i);
		buffer = data + (i - 1);
	}
	memcpy(ld,(struct hdr_loader*)data,20);
	free(data);
	fclose(f);
}

void print_hdr(struct hdr_loader ld) {
	printf("Header type - %s\n", ld.first);
	printf("Header Content - \"%s\"\n",ld.second);
	printf("Param 0 == %d; Param 1 == %d; Param 2 == %d\n", ld.load_struct->bytes,ld.load_struct->bytes1,ld.load_struct->bytes2);
}

