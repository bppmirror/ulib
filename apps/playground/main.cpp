#include "log.h"

#include "list.h"
#include "str.h"

#ifdef BPP_PLATFORM_ESP32
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#endif
using namespace bpp;

void start_playground(void)
{
    MSG<<"\n\nHello from BPP uLib playground!\n\n";

    ulib::List<int> a,b;
    ulib::String str("hello");

    MSG<<(int)(a == b)<<(int)(a!=b)<<"\n";
    MSG<<str<<"\n\n";
#ifdef BPP_PLATFORM_ESP32
    gpio_config_t io_conf;
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = (1UL<<GPIO_NUM_2);
    //disable pull-down mode
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    //disable pull-up mode
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    //configure GPIO with the given settings
    gpio_config(&io_conf);

    /*int cnt = 0;
        while(1) {
            //printf("cnt: %d\n", cnt++);
            cnt++;
            vTaskDelay(5000 / portTICK_RATE_MS);
            gpio_set_level(GPIO_NUM_2, cnt % 2);
        }*/
    gpio_set_level(GPIO_NUM_2, 1);
#endif
}
