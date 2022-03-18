# include "status.h"

static const t_status_info g_status_info[] = {
    {
        OKAY,
        "OKAY",
        NULL
    },
    {
        OUTOFBOUNDS,
        "OUT OF BOUNDS",
        NULL
    },
    {
        OCCUPIED,
        "OCCUPIED",
        NULL
    },
    {
        DOMED,
        "DOMED",
        NULL
    },
    {
        INVALIDACTION,
        "INVALID ACTION",
        NULL
    },
    {
        OUTOFRANGE,
        "OUT OF RANGE",
        NULL
    },
    {
        NORESOURCE,
        "NO RESOURCE",
        NULL
    },
    {
        FREEWORKER,
        "FREE WORKER",
        NULL
    },
    {
        VICTORY,
        "VICTORY",
        NULL
    },
    {
        LOSS,
        "LOSS",
        NULL
    },
    {
        _UNUSED ,
        "_UNUSED",
        NULL
    },
};

void status_print(t_status e, char *buffer) {
    for (int i=OKAY; i < _UNUSED; i++) {
        if (g_status_info[i].status == e) {
            sprintf(buffer, "Status: %s", g_status_info[i].text);
            break;
        }
    }
}
