#include "cajuos_controls.h"

#include <assert.h>
#include <stdio.h>

static void tick(CajuControls *c, uint16_t buttons, uint32_t time)
{
    CajuInputSample sample = { buttons, time };
    caju_controls_tick(c, sample);
}

int main(void)
{
    CajuControls c;
    caju_controls_init(&c);

    /* A single press becomes stable only after the debounce interval. */
    tick(&c, CAJU_BIT(CAJU_BTN_A), 0);
    assert(caju_controls_next_action(&c, 0) == CAJU_ACTION_NONE);
    tick(&c, CAJU_BIT(CAJU_BTN_A), 30);
    assert(caju_controls_next_action(&c, 30) == CAJU_ACTION_CONFIRM);
    tick(&c, CAJU_BIT(CAJU_BTN_A), 45);
    assert(caju_controls_next_action(&c, 45) == CAJU_ACTION_NONE);

    /* Long D-pad hold repeats only after its initial delay. */
    tick(&c, 0, 60);
    tick(&c, CAJU_BIT(CAJU_BTN_DOWN), 90);
    tick(&c, CAJU_BIT(CAJU_BTN_DOWN), 120);
    assert(caju_controls_next_action(&c, 120) == CAJU_ACTION_MOVE_DOWN);
    tick(&c, CAJU_BIT(CAJU_BTN_DOWN), 500);
    assert(caju_controls_next_action(&c, 500) == CAJU_ACTION_NONE);
    tick(&c, CAJU_BIT(CAJU_BTN_DOWN), 600);
    assert(caju_controls_next_action(&c, 600) == CAJU_ACTION_MOVE_DOWN);

    /* SELECT+START is a single guarded action, not repeated every frame. */
    tick(&c, 0, 650);
    tick(&c, CAJU_BIT(CAJU_BTN_SELECT) | CAJU_BIT(CAJU_BTN_START), 700);
    tick(&c, CAJU_BIT(CAJU_BTN_SELECT) | CAJU_BIT(CAJU_BTN_START), 730);
    tick(&c, CAJU_BIT(CAJU_BTN_SELECT) | CAJU_BIT(CAJU_BTN_START), 1200);
    assert(caju_controls_next_action(&c, 1200) == CAJU_ACTION_QUICK_MENU);
    tick(&c, CAJU_BIT(CAJU_BTN_SELECT) | CAJU_BIT(CAJU_BTN_START), 1300);
    assert(caju_controls_next_action(&c, 1300) == CAJU_ACTION_NONE);
    tick(&c, 0, 1400);

    /* Wireless raw mapping: SELECT, START, A, B and directions. */
    uint16_t raw = 0x0020u | 0x0010u | 0x0080u | 0x0008u | 0x0001u;
    uint16_t normalized = caju_normalize_wireless_raw(raw);
    assert(normalized & CAJU_BIT(CAJU_BTN_SELECT));
    assert(normalized & CAJU_BIT(CAJU_BTN_START));
    assert(normalized & CAJU_BIT(CAJU_BTN_A));
    assert(normalized & CAJU_BIT(CAJU_BTN_UP));
    assert(normalized & CAJU_BIT(CAJU_BTN_RIGHT));

    puts("CajuOS controls: PASS");
    return 0;
}
