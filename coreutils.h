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
};


int create_rawbytes(char *rawstring, char *input, int start_pos);

void get_hdr(struct hdr_loader *ld, int start_pos, char *input_str);

void write_and_get_hdr(struct hdr_loader *ld, int start_pos, char *input_str, char *output);

void read_model_fmt(const char *input, struct hdr_loader *ld);

void print_hdr(struct hdr_loader ld);
