#ifndef CAJUOS_CONTROLS_H
#define CAJUOS_CONTROLS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    CAJU_BTN_UP = 0,
    CAJU_BTN_DOWN,
    CAJU_BTN_LEFT,
    CAJU_BTN_RIGHT,
    CAJU_BTN_A,
    CAJU_BTN_B,
    CAJU_BTN_X,
    CAJU_BTN_Y,
    CAJU_BTN_L,
    CAJU_BTN_R,
    CAJU_BTN_SELECT,
    CAJU_BTN_START,
    CAJU_BTN_COUNT
} CajuButton;

typedef enum {
    CAJU_ACTION_NONE = 0,
    CAJU_ACTION_MOVE_UP,
    CAJU_ACTION_MOVE_DOWN,
    CAJU_ACTION_MOVE_LEFT,
    CAJU_ACTION_MOVE_RIGHT,
    CAJU_ACTION_CONFIRM,
    CAJU_ACTION_BACK,
    CAJU_ACTION_FAVORITE,
    CAJU_ACTION_PAGE_PREV,
    CAJU_ACTION_PAGE_NEXT,
    CAJU_ACTION_QUICK_MENU,
    CAJU_ACTION_RESUME_LAST,
    CAJU_ACTION_SCREENSHOT,
    CAJU_ACTION_FLUSH_LOG,
    CAJU_ACTION_RESET
} CajuAction;

typedef struct {
    uint16_t raw_buttons;
    uint32_t now_ms;
} CajuInputSample;

typedef struct {
    uint16_t stable;
    uint16_t candidate;
    uint16_t previous_stable;
    uint32_t candidate_since;
    uint16_t pressed;
    uint16_t released;
    uint16_t repeat;
    uint32_t pressed_at[CAJU_BTN_COUNT];
    uint32_t repeated_at[CAJU_BTN_COUNT];
    uint8_t combo_quick_menu_sent;
    uint8_t combo_resume_sent;
    uint8_t combo_screenshot_sent;
    uint8_t combo_flush_sent;
    uint8_t combo_reset_sent;
} CajuControls;

/* Normalized menu bit positions. The runtime adapter converts hardware input
 * (local keypad or wireless raw bits) to this mask before calling tick(). */
#define CAJU_BIT(btn) ((uint16_t)(1u << (btn)))

void caju_controls_init(CajuControls *controls);
void caju_controls_tick(CajuControls *controls, CajuInputSample sample);
CajuAction caju_controls_next_action(CajuControls *controls, uint32_t now_ms);

/* Stock wireless raw-bit conversion documented by the GB300 research notes. */
uint16_t caju_normalize_wireless_raw(uint16_t raw);

#ifdef __cplusplus
}
#endif

#endif
