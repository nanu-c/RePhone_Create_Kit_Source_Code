
#include <stdint.h>
#include "ugui.h"

int g_keyboard_screen_num		= 0;
static int g_keyboard_screen_max= 4;
static int g_button_target		= 0;
static int keyboard_window		= 19;
UG_WINDOW* g_keyboard_src_window_ptr;
UG_WINDOW g_keyboard_window;
static const char *g_keyboard_button_text[5][19] = {
		{	// Page 1
			"a", "o", "e", "u",
			"i", "d", "h", "t",
			"n", "s", "p", "y",
			".", " ", ",", ">",
			"1", ":", "7" // ICON FONT
        },
        {	// Page 2
			"f", "g", "c", "r",
			"l", "q", "j", "k",
			"x", "b", "m", "w",
			"<", "'", "\"", ">",
			"1", ":", "7" // ICON FONT
        },
        {	// Page 3
			"v", "7", "8", "9",
			"z", "4", "5", "6",
			"!", "1", "2", "3",
			"<", " ", "0", ">",
			"1", ":", "7" // ICON FONT
        },
        {	// Page 4
			"-", "_", "=", "+",
			"#", "$", "%", "@",
			"&", "*", ":", ";",
			"<", "/", "?", ">",
			"1", ":", "7" // ICON FONT
        },
        {	// Page 5
			"<", ">", "(", ")",
			"[", "]", "\\", "|",
			"{", "}", "^", "`",
			"<", "~", " ", " ",
			"1", ":", "7" // ICON FONT
        }
};
static char *g_keyboard_string;
static uint8_t g_keyboard_string_length = 0;
static uint8_t g_keyboard_string_max_length = 0;

static void keyboard_window_callback(UG_MESSAGE *msg)
{
    if (msg->type == MSG_TYPE_OBJECT) {
        if (msg->id == OBJ_TYPE_BUTTON && msg->event == OBJ_EVENT_RELEASED) {
            switch (msg->sub_id) {
                case 19: // text
                    break;
                case 12: // prev
                	if (g_keyboard_screen_num > 0) {
						g_keyboard_screen_num--;
						update_keyboard_layout(g_keyboard_screen_num);
                	} else {
                        if (g_keyboard_string_length
                                < (g_keyboard_string_max_length - 1)) {
                            int index = msg->sub_id;
                            g_keyboard_string[g_keyboard_string_length] =
                                    *g_keyboard_button_text[g_keyboard_screen_num][index];
                            UG_ButtonSetText(&g_keyboard_window, keyboard_window,
                                    g_keyboard_string);
                            g_keyboard_string_length++;
                            g_keyboard_string[g_keyboard_string_length] =
                                    '\0';
                        }
                	}
                	break;
                case 15: // next
                	if (g_keyboard_screen_num < g_keyboard_screen_max) {
						g_keyboard_screen_num++;
						update_keyboard_layout(g_keyboard_screen_num);
                	} else {
                        if (g_keyboard_string_length
                                < (g_keyboard_string_max_length - 1)) {
                            int index = msg->sub_id;
                            g_keyboard_string[g_keyboard_string_length] =
                                    *g_keyboard_button_text[g_keyboard_screen_num][index];
                            UG_ButtonSetText(&g_keyboard_window, keyboard_window,
                                    g_keyboard_string);
                            g_keyboard_string_length++;
                            g_keyboard_string[g_keyboard_string_length] =
                                    '\0';
                        }
                	}
                	break;
                case 16: // return
                    UG_WindowShow(g_keyboard_src_window_ptr);
                    break;
                case 17: // return string
                    UG_ButtonSetText(g_keyboard_src_window_ptr, g_button_target, g_keyboard_string);
                    UG_WindowShow(g_keyboard_src_window_ptr);
                    break;
                case 18: // delete
                    if (g_keyboard_string_length > 0) {
                        g_keyboard_string_length--;
                        g_keyboard_string[g_keyboard_string_length] =
                                '\0';
                        UG_ButtonSetText(&g_keyboard_window, keyboard_window,
                                g_keyboard_string);
                    }
                    break;
                default:
                    if (g_keyboard_string_length
                            < (g_keyboard_string_max_length - 1)) {
                        int index = msg->sub_id;
                        g_keyboard_string[g_keyboard_string_length] =
                                *g_keyboard_button_text[g_keyboard_screen_num][index];
                        UG_ButtonSetText(&g_keyboard_window, keyboard_window,
                                g_keyboard_string);
                        g_keyboard_string_length++;
                        g_keyboard_string[g_keyboard_string_length] =
                                '\0';
                    }
                    break;
            }
        }
    }
}

void keyboard_window_create(void)
{
    static UG_BUTTON buttons[20];
    static UG_OBJECT objects[20];
    int i = 0;
    int j = 0;

    UG_WindowCreate(&g_keyboard_window, objects, 20, keyboard_window_callback);
    UG_WindowSetStyle(&g_keyboard_window, WND_STYLE_2D);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            int index = i * 4 + j;
            /* UG_ButtonCreate(&g_keyboard_window, buttons + index, index, 80 * j,
                    40 * (i + 1), 80 * (j + 1) - 1, 40 * (i + 2) - 1); */
            UG_ButtonCreate(&g_keyboard_window, buttons + index, index, 60 * j,
            		40 * (i + 1), 60 * j + 60 - 1, 40 * (i + 2) - 1);
            UG_ButtonSetFont(&g_keyboard_window, index, &FONT_SIZE20);
            UG_ButtonSetText(&g_keyboard_window, index, g_keyboard_button_text[g_keyboard_screen_num][index]);
            UG_ButtonSetStyle(&g_keyboard_window, index,
                    BTN_STYLE_2D | BTN_STYLE_TOGGLE_COLORS
                            | BTN_STYLE_NO_BORDERS);
			if ((i == 3) && (j == 3)) {
			    UG_ButtonSetBackColor(&g_keyboard_window, index, C_PURPLE);
			}
        }
    }

    for (j = 0; j < 3; j++) {
        int index = 4 * 4 + j;
        UG_ButtonCreate(&g_keyboard_window, buttons + index, index, 80 * j,
                40 * (i + 1), 80 * (j + 1) - 1, 40 * (i + 2) - 1);
        UG_ButtonSetFont(&g_keyboard_window, index, &FONT_ICON24);
        UG_ButtonSetText(&g_keyboard_window, index, g_keyboard_button_text[g_keyboard_screen_num][index]);
        UG_ButtonSetStyle(&g_keyboard_window, index,
                BTN_STYLE_2D | BTN_STYLE_TOGGLE_COLORS | BTN_STYLE_NO_BORDERS);
    }

    UG_ButtonCreate(&g_keyboard_window, buttons + keyboard_window, keyboard_window, 0, 0,
            239, 39);
    UG_ButtonSetFont(&g_keyboard_window, keyboard_window, &FONT_SIZE20);
    UG_ButtonSetText(&g_keyboard_window, keyboard_window,
            g_keyboard_string);
    UG_ButtonSetStyle(&g_keyboard_window, keyboard_window,
            BTN_STYLE_2D | BTN_STYLE_NO_BORDERS);
    UG_ButtonSetBackColor(&g_keyboard_window, keyboard_window, 0);

}

void keyboard_window_show(char *buf2, int len2, int target)
{
    g_button_target = target;

    g_keyboard_string			= buf2;
    g_keyboard_string_max_length= len2;
    // g_keyboard_string_length	= 0;
    g_keyboard_src_window_ptr	= UG_GetActiveWindow();
    //UG_ButtonSetText(&g_keyboard_window, keyboard_window, "");
    UG_WindowShow(&g_keyboard_window);
}

void update_keyboard_layout(int screen_num)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            int index = i * 4 + j;
			UG_ButtonSetText(&g_keyboard_window, index, g_keyboard_button_text[screen_num][index]);
			switch (screen_num){
				case 0:
					if ((i == 3) && (j == 0)) {
					    UG_ButtonSetBackColor(&g_keyboard_window, index, C_BUTTON_BC);
					}
					if ((i == 3) && (j == 3)) {
					    UG_ButtonSetBackColor(&g_keyboard_window, index, C_PURPLE);
					}
					break;
				case 4:
					if ((i == 3) && (j == 0)) {
					    UG_ButtonSetBackColor(&g_keyboard_window, index, C_PURPLE);
					}
					if ((i == 3) && (j == 3)) {
					    UG_ButtonSetBackColor(&g_keyboard_window, index, C_BUTTON_BC);
					}
					break;
				default:
					if ((i == 3) && ((j == 0) || (j == 3))) {
					    UG_ButtonSetBackColor(&g_keyboard_window, index, C_PURPLE);
					}
					break;
			}
        }
    }
}
