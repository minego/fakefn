#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#include <unistd.h>
#include <linux/input.h>


#ifndef TRUE
# define TRUE 1
#endif
#ifndef FALSE
# define FALSE 0
#endif
typedef int BOOL;

typedef enum {
	KEY_STROKE_UP			= 0,
	KEY_STROKE_DOWN			= 1,
	KEY_STROKE_REPEAT		= 2,
} KEY_STROKE_ENUM;

typedef struct input_event input_event;

const struct input_event	syn	= { .type = EV_SYN, .code = SYN_REPORT, .value = 0 };

static void usage(const char *program)
{
    fprintf(stderr,
			"%s - Simple tool to allow 'fn' on a thinkpad to be used for other things\n"
			"\n"
			"usage %s [-h]\n"
			"\n"
			"options:\n"
			"   -h          Show this message and exit\n"

			, program, program);
}

static int read_event(struct input_event *event)
{
    return fread(event, sizeof(struct input_event), 1, stdin) == 1;
}

static void write_event(const struct input_event *event)
{
    if (fwrite(event, sizeof(struct input_event), 1, stdout) != 1)
        exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
	char				o;
	input_event			event;
	BOOL				fn_held		= FALSE;

	while (-1 != (o = getopt(argc, argv, "htTsk:c:"))) {
        switch (o) {
            case 'h':
                usage(argv[0]);
				return EXIT_SUCCESS;
        }
    }


    setbuf(stdin,  NULL);
	setbuf(stdout, NULL);

    while (read_event(&event)) {
        if (event.type == EV_MSC && event.code == MSC_SCAN) {
            continue;
		}

        if (event.type != EV_KEY) {
            write_event(&event);
            continue;
        }

		if (KEY_LEFTCTRL == event.code) {
			switch (event.value) {
				case KEY_STROKE_UP:
					fn_held = FALSE;
					break;

				case KEY_STROKE_DOWN:
					fn_held = TRUE;
					break;
			}

			/* Do NOT send the original events through */
			continue;
		}

		if (fn_held) {
			switch (event.code) {
				case KEY_1:			event.code = KEY_F1;		break;
				case KEY_2:			event.code = KEY_F2;		break;
				case KEY_3:			event.code = KEY_F3;		break;
				case KEY_4:			event.code = KEY_F4;		break;
				case KEY_5:			event.code = KEY_F5;		break;
				case KEY_6:			event.code = KEY_F6;		break;
				case KEY_7:			event.code = KEY_F7;		break;
				case KEY_8:			event.code = KEY_F8;		break;
				case KEY_9:			event.code = KEY_F9;		break;
				case KEY_0:			event.code = KEY_F10;		break;
				case KEY_MINUS:		event.code = KEY_F11;		break;
				case KEY_EQUAL:		event.code = KEY_F12;		break;

				case KEY_H:			event.code = KEY_LEFT;		break;
				case KEY_J:			event.code = KEY_DOWN;		break;
				case KEY_K:			event.code = KEY_UP;		break;
				case KEY_L:			event.code = KEY_RIGHT;		break;

				case KEY_U:			event.code = KEY_PAGEUP;	break;
				case KEY_D:			event.code = KEY_PAGEDOWN;	break;

				default:
					/* Eat the event */
					continue;
			}
		}

		write_event(&event);
    }
}

