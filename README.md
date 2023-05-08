# Tiny ELF-style parser for ELF headers
The ELF binary is structured and abstracted when loaded into memory with compilant data structures, the ELF header section size always remains the same with the same format. In the project, I have created a basic binary file format and a compilant data-structure that parses the format, and displays information. 

## Building and running
[Note: it only works on Linux (and windows is irrelavant)]
it's very tiny, so no need multithreaded build.
```bash
$ cd tinyELFparse
$ make 
./main
```
### help 
```bash
./<prog> <start_pos> <content> <outfile>
```
An example run would be:
```
./main $((0xa0)) "hello world" model
```
outputs 

```bash
Header type - ELF
Header Content - "hello world"
Param 0 == -96; Param 1 == 64; Param 2 == -128
```
## Notes
This is a still work-in-progress, and the argument parsing is not done well at all, hopefully it will be solved in the next or twocommits
r
