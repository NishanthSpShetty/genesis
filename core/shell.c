#include "../include/shell.h"

#include "../include/stdtypes.h"
#include "../include/string.h"
#include "../kernel/tty.h"

int exec_command(const char *cmd)
{
    int i = 0;
    char shell_cmd[20];
    if (str_len(cmd) == 0) return 0;
    while (cmd[i] != ' ' && cmd[i] != 0) {
        shell_cmd[i] = cmd[i];
        i++;
    }
    shell_cmd[i] = 0;

    if (str_cmp(shell_cmd, "clear") == 0) {
        // terminal_writestring("Clearing,,,,,");
        // clear_screen();
        clear_window();
    }
    else if (str_cmp(shell_cmd, "echo") == 0) {
        terminal_writestring(cmd + i);
    }
    else if (str_cmp(shell_cmd, "say") == 0) {
        terminal_writestring(cmd + i);
        terminal_putchar('\n');
    }
    else {
        error("Invalid command\n");
        return 1;
    }
    return 0;
}

void clear_buffer()
{
    int i = 0;
    while (cmd_buffer[i]) cmd_buffer[i++] = 0;
}
