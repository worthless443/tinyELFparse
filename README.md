# Tiny ELF-style parser for ELF headers
The ELF binary is structured and abstracted when loaded into memory with compilant data structures, the ELF header section size always remains the same with the same format. In the project, I have created a basic binary file format and a compilant data-structure that parses the format, and displays information. 

## Building and running
[Note: it only works on Linux (and windows is irrelavant)]
it's very tiny, so no need multithreaded build.
```bash
$ cd tinyELFparse
$ make 
$ ./eparser <flags>
# or 
$ make TARGET=<your_target>
./<your_target> <flags>
```
### help 
```bash
./<TARGET> <start_pos> <content> <outfile>
```
(yes, the help message updates with respect the target set)

An example run would be:
```
./eparser 0xfe1 "hello world" tinyelf
```
produces a binary file `tinyelf`
To read the file
```bash
./eparser tinyelf -ro
```
Produces:

```bash
Header type - ELF
Header Content - "hello world"
Param 0 == -96; Param 1 == 64; Param 2 == -128
Masked Param 0 == -42; Masked Param 1 == -33; Masked Param 2 == 84
```
## Notes
This is a still work-in-progress, and the argument parsing is tackled but is not enough but still is enough to get the job done.
r
