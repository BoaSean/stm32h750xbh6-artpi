#include <rtthread.h>
#include <rtdevice.h>

static int rt_fal_user_init(void)
{
    extern int fal_init(void);
    fal_init();
    return 0;
}
INIT_ENV_EXPORT(rt_fal_user_init);