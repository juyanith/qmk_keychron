#include "juyanith.h"
#include "primary_editing.h"

// QMK overrides keep movement keys held for native host repeat, while consuming
// Shift/Alt selectors without changing the physical modifier state. Four variants
// per action let QMK update selection/scope when modifiers change during a hold.
#define MOVEMENT_COUNT 10
#define VARIANT_COUNT (MOVEMENT_COUNT * 4)
static key_override_t movement[VARIANT_COUNT];
static const key_override_t *movement_ptrs[VARIANT_COUNT + 1];

#ifdef PRIMARY_EDITING_MODERN_OVERRIDES
uint16_t key_override_count(void) { return VARIANT_COUNT; }
const key_override_t *key_override_get(uint16_t index) {
    return index < VARIANT_COUNT ? &movement[index] : NULL;
}
#else
const key_override_t **key_overrides = movement_ptrs;
#endif

void prepare_primary_movement(void) {
    static bool initialized;
    static bool last_apple;
    const bool apple = is_apple_os();
    if (initialized && apple == last_apple) return;
    for (unsigned action = 0; action < MOVEMENT_COUNT; ++action) {
        for (unsigned variant = 0; variant < 4; ++variant) {
            const unsigned i = action * 4 + variant;
            const uint8_t required = ((variant & 1) ? MOD_MASK_SHIFT : 0) |
                                     ((variant & 2) ? MOD_MASK_ALT : 0);
            movement[i] = (key_override_t){
                .trigger = NV_LEFT + action,
                .trigger_mods = required,
                .negative_mod_mask = (MOD_MASK_SHIFT | MOD_MASK_ALT) & ~required,
                .suppressed_mods = MOD_MASK_SHIFT | MOD_MASK_ALT,
                .layers = ~(layer_state_t)0,
                .replacement = primary_editing_key(NV_LEFT + action, apple, variant & 1, variant & 2),
                .options = ko_options_all_activations | ko_option_no_reregister_trigger,
            };
            movement_ptrs[i] = &movement[i];
        }
    }
    last_apple = apple;
    initialized = true;
}
