#include <rtthread.h>
#include <rtdevice.h>


#ifdef PKG_USING_EASYFLASH

#include "easyflash.h"

#endif

static int rt_fal_user_init(void)
{

#ifdef RT_USING_FAL
    extern int fal_init(void);
    fal_init();
#endif

#ifdef PKG_USING_EASYFLASH
    easyflash_init();
#endif
    return 0;
}
INIT_ENV_EXPORT(rt_fal_user_init);