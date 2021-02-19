/*Keyboard handler module*/
#include "../kernel/keyboard.h"

#include "../include/shell.h"
#include "../include/stdtypes.h"
#include "../kernel/irq.h"
#include "../kernel/tty.h"

int cmd_i = 0;
// extern defined buffers
extern keystat_t key_buffer;

// key press handler
void keyboard_handler()
{
    uint8_t status = 0, shift = 0;
    // Signal EOI to PIC [ACK]
    outb(PIC1_CNTRL, EOI);
    status = inb(KEYBOARD_STATUS_PORT);
    if (status & 0x01) {
        // buffer is full->read

        key_buffer.cur_keycode = inb(KEYBOARD_DATA_PORT);
        if (key_buffer.cur_keycode < 0) return;
        // get the keyboard character :scancode

        key_buffer.cur_keychar = keyboard_map[key_buffer.cur_keycode];

        if (key_buffer.cur_keycode == CAPS_LOCK) {
            cmd_i = cmd_i + 1;
            if (key_buffer.prev_keycode == CAPS_LOCK)
                key_buffer.prev_keycode = 0;
            else
                key_buffer.prev_keycode = CAPS_LOCK;
            return;
        }

        if ((key_buffer.prev_keycode == LEFT_SHIFT ||
             key_buffer.prev_keycode == RIGHT_SHIFT ||
             key_buffer.prev_keycode == CAPS_LOCK) &&
            (key_buffer.cur_keychar <= 'z' && key_buffer.cur_keychar >= 'a')) {
            key_buffer.cur_keychar -= 32;
        }
        // display the char :[#debug]
        terminal_putchar(key_buffer.cur_keychar);
        // upon pressing ENTER key, execute the command
        if (key_buffer.cur_keychar == '\n' || cmd_i > COMMAND_LEN) {
            cmd_buffer[cmd_i] = 0;  // end string
            exec_command(cmd_buffer);
            cmd_i = 0;
            clear_buffer();
            terminal_writestring(">>");
        }

        // only on pressing the key
        if ((!(key_buffer.cur_keycode & 0x80)) &&
            key_buffer.cur_keychar != '\n') {
            cmd_buffer[cmd_i] = key_buffer.cur_keychar;
            cmd_i = cmd_i + 1;
        }
        if (key_buffer.prev_keycode != CAPS_LOCK)
            key_buffer.prev_keycode = key_buffer.cur_keycode;
    }
    return;
}
