
#include <stdint.h>
#include "ugui.h"


static int g_button_target = 0;
static int keyboard_window	= 19;
UG_WINDOW* g_keyboard_src_window_ptr;
UG_WINDOW g_keyboard_window;
static const char *g_keyboard_button_text[19] = {
		"q", "w", "e", "r",
		"a", "s", "d", "f",
		"z", "x", "c", "v",
		".", " ", ",", ">",
        "1", ":", "7" // ICON FONT
        };
UG_WINDOW g_keyboard2_window;
static const char *g_keyboard2_button_text[19] = {
		"t", "y", "u", "i",
		"g", "h", "j", "k",
		"b", "n", "m", "<",
		"<", "'", ":", ">",
        "1", ":", "7" // ICON FONT
        };
UG_WINDOW g_keyboard3_window;
static const char *g_keyboard3_button_text[19] = {
		"o", "p", "[", "]",
		"l", ";", "\"", "\\",
		">", "?", "/", "!",
		"<", "+", "-", ">",
        "1", ":", "7" // ICON FONT
        };
UG_WINDOW g_keyboard4_window;
static const char *g_keyboard4_button_text[19] = {
		"|", "7", "8", "9",
		"#", "4", "5", "6",
		"@", "1", "2", "3",
		"<", " ", "0", ">",
        "1", ":", "7" // ICON FONT
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
                case 15: // next
                    UG_ButtonSetText(&g_keyboard2_window, keyboard_window, g_keyboard_string);
                    UG_WindowShow(&g_keyboard2_window);
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
                                *g_keyboard_button_text[index];
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
            UG_ButtonSetText(&g_keyboard_window, index, g_keyboard_button_text[index]);
            UG_ButtonSetStyle(&g_keyboard_window, index,
                    BTN_STYLE_2D | BTN_STYLE_TOGGLE_COLORS
                            | BTN_STYLE_NO_BORDERS);
        }
    }

    for (j = 0; j < 3; j++) {
        int index = 4 * 4 + j;
        UG_ButtonCreate(&g_keyboard_window, buttons + index, index, 80 * j,
                40 * (i + 1), 80 * (j + 1) - 1, 40 * (i + 2) - 1);
        UG_ButtonSetFont(&g_keyboard_window, index, &FONT_ICON24);
        UG_ButtonSetText(&g_keyboard_window, index, g_keyboard_button_text[index]);
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

    keyboard2_window_create();
}

void keyboard_window_show(char *buf2, int len2, int target)
{
    g_button_target = target;

    g_keyboard_string = buf2;
    g_keyboard_string_max_length= len2;
    g_keyboard_string_length = 0;
    g_keyboard_src_window_ptr	= UG_GetActiveWindow();
    //UG_ButtonSetText(&g_keyboard_window, keyboard_window, "");
    UG_WindowShow(&g_keyboard_window);
}

static void keyboard2_window_callback(UG_MESSAGE *msg)
{
    if (msg->type == MSG_TYPE_OBJECT) {
        if (msg->id == OBJ_TYPE_BUTTON && msg->event == OBJ_EVENT_RELEASED) {
            switch (msg->sub_id) {
                case 19: // text
                    break;
                case 12: // prev
                    UG_ButtonSetText(&g_keyboard_window, keyboard_window, g_keyboard_string);
                    UG_WindowShow(&g_keyboard_window);
                	break;
                case 15: // next
                    UG_ButtonSetText(&g_keyboard3_window, keyboard_window, g_keyboard_string);
                    UG_WindowShow(&g_keyboard3_window);
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
                        UG_ButtonSetText(&g_keyboard2_window, keyboard_window,
                                g_keyboard_string);
                    }
                    break;
                default:
                    if (g_keyboard_string_length
                            < (g_keyboard_string_max_length - 1)) {
                        int index = msg->sub_id;
                        g_keyboard_string[g_keyboard_string_length] =
                                *g_keyboard2_button_text[index];
                        UG_ButtonSetText(&g_keyboard2_window, keyboard_window,
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

void keyboard2_window_create(void)
{
    static UG_BUTTON buttons[20];
    static UG_OBJECT objects[20];
    int i = 0;
    int j = 0;

    UG_WindowCreate(&g_keyboard2_window, objects, 20, keyboard2_window_callback);
    UG_WindowSetStyle(&g_keyboard2_window, WND_STYLE_2D);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            int index = i * 4 + j;
            UG_ButtonCreate(&g_keyboard2_window, buttons + index, index, 60 * j,
            		40 * (i + 1), 60 * j + 60 - 1, 40 * (i + 2) - 1);
            UG_ButtonSetFont(&g_keyboard2_window, index, &FONT_SIZE20);
            UG_ButtonSetText(&g_keyboard2_window, index, g_keyboard2_button_text[index]);
            UG_ButtonSetStyle(&g_keyboard2_window, index,
                    BTN_STYLE_2D | BTN_STYLE_TOGGLE_COLORS
                            | BTN_STYLE_NO_BORDERS);
        }
    }

    for (j = 0; j < 3; j++) {
        int index = 4 * 4 + j;
        UG_ButtonCreate(&g_keyboard2_window, buttons + index, index, 80 * j,
                40 * (i + 1), 80 * (j + 1) - 1, 40 * (i + 2) - 1);
        UG_ButtonSetFont(&g_keyboard2_window, index, &FONT_ICON24);
        UG_ButtonSetText(&g_keyboard2_window, index, g_keyboard2_button_text[index]);
        UG_ButtonSetStyle(&g_keyboard2_window, index,
                BTN_STYLE_2D | BTN_STYLE_TOGGLE_COLORS | BTN_STYLE_NO_BORDERS);
    }

    UG_ButtonCreate(&g_keyboard2_window, buttons + keyboard_window, keyboard_window, 0, 0,
            239, 39);
    UG_ButtonSetFont(&g_keyboard2_window, keyboard_window, &FONT_SIZE20);
    UG_ButtonSetText(&g_keyboard2_window, keyboard_window,
            g_keyboard_string);
    UG_ButtonSetStyle(&g_keyboard2_window, keyboard_window,
            BTN_STYLE_2D | BTN_STYLE_NO_BORDERS);
    UG_ButtonSetBackColor(&g_keyboard2_window, keyboard_window, 0);

    keyboard3_window_create();
}

static void keyboard3_window_callback(UG_MESSAGE *msg)
{
    if (msg->type == MSG_TYPE_OBJECT) {
        if (msg->id == OBJ_TYPE_BUTTON && msg->event == OBJ_EVENT_RELEASED) {
            switch (msg->sub_id) {
                case 19: // text
                    break;
                case 12: // prev
                    UG_ButtonSetText(&g_keyboard2_window, keyboard_window, g_keyboard_string);
                    UG_WindowShow(&g_keyboard2_window);
                	break;
                case 15: // next
                    UG_ButtonSetText(&g_keyboard4_window, keyboard_window, g_keyboard_string);
                    UG_WindowShow(&g_keyboard4_window);
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
                        UG_ButtonSetText(&g_keyboard3_window, keyboard_window,
                                g_keyboard_string);
                    }
                    break;
                default:
                    if (g_keyboard_string_length
                            < (g_keyboard_string_max_length - 1)) {
                        int index = msg->sub_id;
                        g_keyboard_string[g_keyboard_string_length] =
                                *g_keyboard3_button_text[index];
                        UG_ButtonSetText(&g_keyboard3_window, keyboard_window,
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

void keyboard3_window_create(void)
{
    static UG_BUTTON buttons[20];
    static UG_OBJECT objects[20];
    int i = 0;
    int j = 0;

    UG_WindowCreate(&g_keyboard3_window, objects, 20, keyboard3_window_callback);
    UG_WindowSetStyle(&g_keyboard3_window, WND_STYLE_2D);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            int index = i * 4 + j;
            UG_ButtonCreate(&g_keyboard3_window, buttons + index, index, 60 * j,
            		40 * (i + 1), 60 * j + 60 - 1, 40 * (i + 2) - 1);
            UG_ButtonSetFont(&g_keyboard3_window, index, &FONT_SIZE20);
            UG_ButtonSetText(&g_keyboard3_window, index, g_keyboard3_button_text[index]);
            UG_ButtonSetStyle(&g_keyboard3_window, index,
                    BTN_STYLE_2D | BTN_STYLE_TOGGLE_COLORS
                            | BTN_STYLE_NO_BORDERS);
        }
    }

    for (j = 0; j < 3; j++) {
        int index = 4 * 4 + j;
        UG_ButtonCreate(&g_keyboard3_window, buttons + index, index, 80 * j,
                40 * (i + 1), 80 * (j + 1) - 1, 40 * (i + 2) - 1);
        UG_ButtonSetFont(&g_keyboard3_window, index, &FONT_ICON24);
        UG_ButtonSetText(&g_keyboard3_window, index, g_keyboard3_button_text[index]);
        UG_ButtonSetStyle(&g_keyboard3_window, index,
                BTN_STYLE_2D | BTN_STYLE_TOGGLE_COLORS | BTN_STYLE_NO_BORDERS);
    }

    UG_ButtonCreate(&g_keyboard3_window, buttons + keyboard_window, keyboard_window, 0, 0,
            239, 39);
    UG_ButtonSetFont(&g_keyboard3_window, keyboard_window, &FONT_SIZE20);
    UG_ButtonSetText(&g_keyboard3_window, keyboard_window,
            g_keyboard_string);
    UG_ButtonSetStyle(&g_keyboard3_window, keyboard_window,
            BTN_STYLE_2D | BTN_STYLE_NO_BORDERS);
    UG_ButtonSetBackColor(&g_keyboard3_window, keyboard_window, 0);

    keyboard4_window_create();
}

static void keyboard4_window_callback(UG_MESSAGE *msg)
{
    if (msg->type == MSG_TYPE_OBJECT) {
        if (msg->id == OBJ_TYPE_BUTTON && msg->event == OBJ_EVENT_RELEASED) {
            switch (msg->sub_id) {
                case 19: // text
                    break;
                case 12: // prev
                    UG_ButtonSetText(&g_keyboard3_window, keyboard_window, g_keyboard_string);
                    UG_WindowShow(&g_keyboard3_window);
                	break;
                case 15: // next
                    //UG_ButtonSetText(&g_keyboard5_window, keyboard_window, g_keyboard_string);
                    //UG_WindowShow(&g_keyboard5_window);
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
                        UG_ButtonSetText(&g_keyboard4_window, keyboard_window,
                                g_keyboard_string);
                    }
                    break;
                default:
                    if (g_keyboard_string_length
                            < (g_keyboard_string_max_length - 1)) {
                        int index = msg->sub_id;
                        g_keyboard_string[g_keyboard_string_length] =
                                *g_keyboard4_button_text[index];
                        UG_ButtonSetText(&g_keyboard4_window, keyboard_window,
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

void keyboard4_window_create(void)
{
    static UG_BUTTON buttons[20];
    static UG_OBJECT objects[20];
    int i = 0;
    int j = 0;

    UG_WindowCreate(&g_keyboard4_window, objects, 20, keyboard4_window_callback);
    UG_WindowSetStyle(&g_keyboard4_window, WND_STYLE_2D);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            int index = i * 4 + j;
            UG_ButtonCreate(&g_keyboard4_window, buttons + index, index, 60 * j,
            		40 * (i + 1), 60 * j + 60 - 1, 40 * (i + 2) - 1);
            UG_ButtonSetFont(&g_keyboard4_window, index, &FONT_SIZE20);
            UG_ButtonSetText(&g_keyboard4_window, index, g_keyboard4_button_text[index]);
            UG_ButtonSetStyle(&g_keyboard4_window, index,
                    BTN_STYLE_2D | BTN_STYLE_TOGGLE_COLORS
                            | BTN_STYLE_NO_BORDERS);
        }
    }

    for (j = 0; j < 3; j++) {
        int index = 4 * 4 + j;
        UG_ButtonCreate(&g_keyboard4_window, buttons + index, index, 80 * j,
                40 * (i + 1), 80 * (j + 1) - 1, 40 * (i + 2) - 1);
        UG_ButtonSetFont(&g_keyboard4_window, index, &FONT_ICON24);
        UG_ButtonSetText(&g_keyboard4_window, index, g_keyboard4_button_text[index]);
        UG_ButtonSetStyle(&g_keyboard4_window, index,
                BTN_STYLE_2D | BTN_STYLE_TOGGLE_COLORS | BTN_STYLE_NO_BORDERS);
    }

    UG_ButtonCreate(&g_keyboard4_window, buttons + keyboard_window, keyboard_window, 0, 0,
            239, 39);
    UG_ButtonSetFont(&g_keyboard4_window, keyboard_window, &FONT_SIZE20);
    UG_ButtonSetText(&g_keyboard4_window, keyboard_window,
            g_keyboard_string);
    UG_ButtonSetStyle(&g_keyboard4_window, keyboard_window,
            BTN_STYLE_2D | BTN_STYLE_NO_BORDERS);
    UG_ButtonSetBackColor(&g_keyboard4_window, keyboard_window, 0);

    // UG_ButtonSetBackColor(&g_keyboard4_window, 13, 0x4CAF50);
    // keyboard5_window_create();
}
