#ifndef SHELL_H
#define SHELL_H 

//utilty macros
#define COMMAND_LEN 127
#define COMMAND_BUFFER_LEN COMMAND_LEN+1


char cmd_buffer[COMMAND_BUFFER_LEN];

void clear_buffer();
int exec_command(const char *); 


#endif
