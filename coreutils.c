#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/stat.h>

#include<coreutils.h>

static int create_bytes_string(char *bytesstring, int start_pos) {
	for(int i=0,ii=0,mask=0xf0;i<3;++ii) {
		if(start_pos & 0xf0) {
			*(bytesstring + i) = start_pos;
			start_pos+=start_pos & ++mask;
			++i;
		}
		if(ii>100) return ERROR_TRAP;
	}
	return 0;
}

static int create_bytes_string_masked(char *bytesstring, int start_pos) {
	int masked;
	for(int i=0,ii=0,mask=0xf0;i<3;ii++) {
		if((start_pos & 0xf0) & (1 << (start_pos % 8))) {
			*(bytesstring + i) = start_pos;
			i+=1;
		}
		if((masked = __get_masked(start_pos & ++mask)) == 0) 
			start_pos+=9;
		if(ii>100) return ERROR_TRAP;
	}
	return masked;
}

int mk_executable(const char *fn) {
	int flag = strtol("1",NULL,8);
	if(chmod(fn,flag) < 0) 
		return ERROR_CHMOD;
	return 0;	
}

int create_rawbytes(char *rawstring, char *input, int start_pos) {
	int size;
	int err;
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
	rawstring[strlen(tmpstring) + 12 + 1] = '\0';
	char bytesstring[3], bytesstring_masked[3];
	if((err = create_bytes_string(bytesstring, start_pos)) == ERROR_TRAP) {
		fprintf(stderr, "create_bytes_string: Input start position ened up in ERROR_TRAP\n");
		return 0;
	}

	if((err = create_bytes_string_masked(bytesstring_masked, start_pos)) == ERROR_TRAP) {
		fprintf(stderr, "create_bytes_string_masked: Input start position ened up in ERROR_TRAP\n");
		return 0;
	} size=12 + strlen(tmpstring) + 2;
	for(int ii=0;ii<3;++size,++ii)
		rawstring[size] = bytesstring[ii];
	for(int ii=0;ii<3;++size,++ii) 
		rawstring[size] = bytesstring_masked[ii];
	rawstring[size] = size + 1;
	return size + 1;
}

void get_hdr(struct hdr_loader *ld, int start_pos, char *input_str) {
	char rawstring[32];
	int size = create_rawbytes(rawstring, input_str, start_pos);
	if(size == 0) {
		fprintf(stderr,"couldn't get header\n");
		return;
	}
	memcpy(ld,(struct hdr_loader*)rawstring,size);
}

int write_and_get_hdr(struct hdr_loader *ld, int start_pos, char *input_str, char *output) {
	char rawstring[32];
	int size = create_rawbytes(rawstring, input_str, start_pos);
	if(size == 0) {
		fprintf(stderr,"couldn't get header\n");
		return 0;
	}
	memcpy(ld,(struct hdr_loader*)rawstring,size);
	FILE *f = fopen(output, "wb");
	fwrite("\0",1,1,f);
	fwrite(rawstring,1,size,f);
	fclose(f);
	return size;
}

int read_model_fmt(const char *input, struct hdr_loader *ld) {
	int i;
	FILE *f;
	if((f = fopen(input,"r")) == NULL) {
		perror(STRFY(_TARGET));
		return ERROR_FILE_NOT_FOUND;
	}
	char *data = malloc(sizeof(char)*4095);
	char *buffer = data;
	for(i=1;fread(buffer,1,1,f);++i) {
		data = realloc(data,i);
		buffer = data + (i - 1); }
	if(0 != strcmp(data,"ELF")) {
		return ERROR_FILE_FORMAT;
	}
	int size = ((struct hdr_loader*)data)->size->s;
	memcpy(ld,(struct hdr_loader*)data,size);
	free(data);
	fclose(f);
	return size;
}

void print_hdr(struct hdr_loader ld) {
	printf("size - %d\n", ld.size->s);
	printf("Header type - %s\n", ld.first);
	printf("Header Content - \"%s\"\n",ld.second);
	printf("Param 0 == %d; Param 1 == %d; Param 2 == %d\n", ld.load_struct->bytes,ld.load_struct->bytes1,ld.load_struct->bytes2);
	printf("Masked Param 0 == %d; Masked Param 1 == %d; Masked Param 2 == %d\n", ld.load_struct_masked->bytes,ld.load_struct_masked->bytes1,ld.load_struct_masked->bytes2);
}

