#include "board_resources.h"

/// holds available resources - L1 | L2 | l3 | DOME
static int8_t g_resources[4] = {0};

/// Resets resources to their initial state
void reset_resources() {
    g_resources[0] = 22;
    g_resources[1] = 18;
    g_resources[2] = 14;
    g_resources[3] = 18;
}

/// Removes one resource of given level from the stock
/// OKAY - there was piece of given level available
/// NORESOURCE - no resource of that level available
/// INVALIDACTION - level out of bounds
t_status resources_get_one(int8_t level) {
    if (level < 0 || level > 3) {
        return (INVALIDACTION);
    }
    if (g_resources[level] > 0) {
        g_resources[level] -= 1;
        return (OKAY);
    }
    return (NORESOURCE);
}

/// Simple check of there is any resource of given level
/// 0 - no resource or our of bounds
/// 1 - there's at least one of the resource
int resources_has_level(int8_t level) {
    if (level < 0 || level > 3) {
        return (0);
    }
    return(g_resources[level] > 0);
}

/// Specific level resource amount getter
int8_t reseources_get_n(int8_t level) {
    if (level < 0 || level > 3) {
        return (-1);
    }
    return(g_resources[level]);
}
