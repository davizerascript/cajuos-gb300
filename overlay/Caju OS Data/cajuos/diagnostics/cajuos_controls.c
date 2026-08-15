#include "cajuos_controls.h"

#include <string.h>

#define DEBOUNCE_MS 25u
#define REPEAT_DELAY_MS 420u
#define REPEAT_RATE_MS 95u
#define COMBO_HOLD_MS 450u

static int is_down(uint16_t state, unsigned button)
{
    return (state & CAJU_BIT(button)) != 0;
}

static void clear_combo_latches(CajuControls *c)
{
    c->combo_quick_menu_sent = 0;
    c->combo_resume_sent = 0;
    c->combo_screenshot_sent = 0;
    c->combo_flush_sent = 0;
    c->combo_reset_sent = 0;
}

void caju_controls_init(CajuControls *c)
{
    if (!c)
        return;
    memset(c, 0, sizeof(*c));
}

void caju_controls_tick(CajuControls *c, CajuInputSample sample)
{
    if (!c)
        return;

    if (sample.raw_buttons != c->candidate) {
        c->candidate = sample.raw_buttons;
        c->candidate_since = sample.now_ms;
    } else if (c->candidate != c->stable &&
               (uint32_t)(sample.now_ms - c->candidate_since) >= DEBOUNCE_MS) {
        c->previous_stable = c->stable;
        c->stable = c->candidate;
        c->pressed = (uint16_t)(c->stable & (uint16_t)~c->previous_stable);
        c->released = (uint16_t)(c->previous_stable & (uint16_t)~c->stable);
        c->repeat = 0;

        for (unsigned i = 0; i < CAJU_BTN_COUNT; ++i) {
            if (is_down(c->stable, i)) {
                c->pressed_at[i] = sample.now_ms;
                c->repeated_at[i] = sample.now_ms;
            } else {
                c->pressed_at[i] = 0;
                c->repeated_at[i] = 0;
            }
        }
    } else {
        c->pressed = 0;
        c->released = 0;
        c->repeat = 0;
    }

    if (is_down(c->stable, CAJU_BTN_UP) || is_down(c->stable, CAJU_BTN_DOWN) ||
        is_down(c->stable, CAJU_BTN_LEFT) || is_down(c->stable, CAJU_BTN_RIGHT)) {
        for (unsigned i = CAJU_BTN_UP; i <= CAJU_BTN_RIGHT; ++i) {
            if (is_down(c->stable, i) && c->pressed_at[i] != 0 &&
                (uint32_t)(sample.now_ms - c->pressed_at[i]) >= REPEAT_DELAY_MS &&
                (uint32_t)(sample.now_ms - c->repeated_at[i]) >= REPEAT_RATE_MS) {
                c->repeat |= CAJU_BIT(i);
                c->repeated_at[i] = sample.now_ms;
            }
        }
    }

    if (!is_down(c->stable, CAJU_BTN_SELECT))
        clear_combo_latches(c);
}

static int combo_held(const CajuControls *c, CajuButton other, uint32_t now_ms)
{
    return is_down(c->stable, CAJU_BTN_SELECT) && is_down(c->stable, other) &&
           c->pressed_at[CAJU_BTN_SELECT] != 0 &&
           (uint32_t)(now_ms - c->pressed_at[CAJU_BTN_SELECT]) >= COMBO_HOLD_MS;
}

CajuAction caju_controls_next_action(CajuControls *c, uint32_t now_ms)
{
    if (!c)
        return CAJU_ACTION_NONE;

    /* Long combos are checked first, so they cannot also confirm a menu row. */
    if (combo_held(c, CAJU_BTN_START, now_ms) && !c->combo_quick_menu_sent) {
        c->combo_quick_menu_sent = 1;
        return CAJU_ACTION_QUICK_MENU;
    }
    if (combo_held(c, CAJU_BTN_A, now_ms) && !c->combo_resume_sent) {
        c->combo_resume_sent = 1;
        return CAJU_ACTION_RESUME_LAST;
    }
    if (combo_held(c, CAJU_BTN_X, now_ms) && !c->combo_screenshot_sent) {
        c->combo_screenshot_sent = 1;
        return CAJU_ACTION_SCREENSHOT;
    }
    if (combo_held(c, CAJU_BTN_Y, now_ms) && !c->combo_flush_sent) {
        c->combo_flush_sent = 1;
        return CAJU_ACTION_FLUSH_LOG;
    }
    if (combo_held(c, CAJU_BTN_B, now_ms) && !c->combo_reset_sent) {
        c->combo_reset_sent = 1;
        return CAJU_ACTION_RESET;
    }

    if (c->pressed & CAJU_BIT(CAJU_BTN_UP)) return CAJU_ACTION_MOVE_UP;
    if (c->pressed & CAJU_BIT(CAJU_BTN_DOWN)) return CAJU_ACTION_MOVE_DOWN;
    if (c->pressed & CAJU_BIT(CAJU_BTN_LEFT)) return CAJU_ACTION_MOVE_LEFT;
    if (c->pressed & CAJU_BIT(CAJU_BTN_RIGHT)) return CAJU_ACTION_MOVE_RIGHT;
    if (c->repeat & CAJU_BIT(CAJU_BTN_UP)) return CAJU_ACTION_MOVE_UP;
    if (c->repeat & CAJU_BIT(CAJU_BTN_DOWN)) return CAJU_ACTION_MOVE_DOWN;
    if (c->repeat & CAJU_BIT(CAJU_BTN_LEFT)) return CAJU_ACTION_MOVE_LEFT;
    if (c->repeat & CAJU_BIT(CAJU_BTN_RIGHT)) return CAJU_ACTION_MOVE_RIGHT;
    if (c->pressed & CAJU_BIT(CAJU_BTN_A)) return CAJU_ACTION_CONFIRM;
    if (c->pressed & CAJU_BIT(CAJU_BTN_B)) return CAJU_ACTION_BACK;
    if (c->pressed & CAJU_BIT(CAJU_BTN_X)) return CAJU_ACTION_FAVORITE;
    if (c->pressed & CAJU_BIT(CAJU_BTN_L)) return CAJU_ACTION_PAGE_PREV;
    if (c->pressed & CAJU_BIT(CAJU_BTN_R)) return CAJU_ACTION_PAGE_NEXT;
    return CAJU_ACTION_NONE;
}

uint16_t caju_normalize_wireless_raw(uint16_t raw)
{
    uint16_t normalized = 0;
    if (raw & 0x0008u) normalized |= CAJU_BIT(CAJU_BTN_UP);
    if (raw & 0x0004u) normalized |= CAJU_BIT(CAJU_BTN_DOWN);
    if (raw & 0x0002u) normalized |= CAJU_BIT(CAJU_BTN_LEFT);
    if (raw & 0x0001u) normalized |= CAJU_BIT(CAJU_BTN_RIGHT);
    if (raw & 0x0080u) normalized |= CAJU_BIT(CAJU_BTN_A);
    if (raw & 0x0040u) normalized |= CAJU_BIT(CAJU_BTN_B);
    if (raw & 0x4000u) normalized |= CAJU_BIT(CAJU_BTN_X);
    if (raw & 0x2000u) normalized |= CAJU_BIT(CAJU_BTN_Y);
    if (raw & 0x0800u) normalized |= CAJU_BIT(CAJU_BTN_L);
    if (raw & 0x1000u) normalized |= CAJU_BIT(CAJU_BTN_R);
    if (raw & 0x0020u) normalized |= CAJU_BIT(CAJU_BTN_SELECT);
    if (raw & 0x0010u) normalized |= CAJU_BIT(CAJU_BTN_START);
    return normalized;
}
