#include "../src/lhz_log.h"


int main(void){

    lhz_log_init(3 , 1, NULL);
    for (size_t i = 0; i < 100; i++)
    {
        lhz_error("name:%s\n", "i am lhz");
        lhz_warning("name:%s\n", "i am lhz");
        lhz_info("name:%s\n", "i am lhz");
        lhz_debug("name:%s\n", "i am lhz");
    }

    lhz_log_exit();

    return 0;
}