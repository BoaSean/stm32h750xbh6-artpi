#include <rtthread.h>
#include <rtdevice.h>


#ifdef PKG_USING_EASYFLASH

#include "easyflash.h"

#endif

#ifdef RT_USING_FAL

static int rt_fal_user_init(void)
{

    extern int fal_init(void);
    fal_init();


#ifdef PKG_USING_EASYFLASH
    easyflash_init();
#endif
    return 0;
}
INIT_COMPONENT_EXPORT(rt_fal_user_init);

#endif