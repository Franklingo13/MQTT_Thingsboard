#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "dht11.h"
#define CONFIG_FREERTOS_HZ 1000

void app_main()
{
    DHT11_init(GPIO_NUM_27);

    while(1) {
        printf("Temperature is %d \n", DHT11_read().temperature);
        printf("Humidity is %d\n", DHT11_read().humidity);
        printf("Status code is %d\n", DHT11_read().status);
        vTaskDelay(pdMS_TO_TICKS(1000));  // Wait for 1 second
    }
}
