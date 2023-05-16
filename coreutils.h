#define __get_masked(a) ((a & 0xf0) >> 1) & (a << 1)
#define ERROR_TRAP -1
#define ERROR_CHMOD -2
#define ERROR_PARSE -4
#define ERROR_FILE_FORMAT -5

struct hdr_loader {
	char first[3];
	char mask;
	char second[10];
	char mask1; 
	char mask2; 
	char mask3; 
	struct {
		char bytes, bytes1,bytes2;
	} load_struct[1]; 
	struct {
		char bytes, bytes1,bytes2;
	} load_struct_masked[1];
	struct {
		char s;
	} size[1];
};

int create_rawbytes(char *rawstring, char *input, int start_pos);

void get_hdr(struct hdr_loader *ld, int start_pos, char *input_str);

int write_and_get_hdr(struct hdr_loader *ld, int start_pos, char *input_str, char *output);

int read_model_fmt(const char *input, struct hdr_loader *ld);

void print_hdr(struct hdr_loader ld);

int mk_executable(const char *fn);
