#include <stdio.h>
#include "string.h"
#include "esp_wifi.h"
#include "esp_now.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_netif.h"
#include "esp_mac.h"
#include "esp_event.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include <string.h>

// Dirección I2C del dispositivo esclavo
#define I2C_SLAVE_ADDR	0x68
#define TIMEOUT_MS		1000
#define DELAY_MS		1000
#define tag "SSD1306"
#define ESP_CHANNEL 1
#define CONFIG_SDA_GPIO 21
#define CONFIG_SCL_GPIO 22

static const char *TAG = "esp_now_init";
static uint8_t peer_mac[ESP_NOW_ETH_ALEN] = {0xec, 0x62, 0x60, 0x84, 0x1f, 0x40}; // MAC rx vila
//static uint8_t peer_mac[ESP_NOW_ETH_ALEN] = {0x40, 0x22, 0xd8, 0xef, 0x21,0xd4};


// Inicialización del módulo Wi-Fi
static esp_err_t init_wifi(void)
{
    wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();

    esp_netif_init();
    esp_event_loop_create_default();
    nvs_flash_init();
    esp_wifi_init(&wifi_init_config);
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_storage(WIFI_STORAGE_FLASH);
    esp_wifi_start();

    ESP_LOGI(TAG, "WiFi init finished.");
    return ESP_OK;
}


// Función de retorno de llamada para el envío de ESP-NOW
void send_cb(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    ESP_LOGI(TAG, "Message sent to MAC: " MACSTR ", Status: %s", MAC2STR(mac_addr), (status == ESP_NOW_SEND_SUCCESS) ? "Success" : "Fail");
}

// Inicialización de ESP-NOW
static esp_err_t init_esp_now(void)
{
    esp_now_init();
    //esp_now_register_recv_cb(rec_cb);
    esp_now_register_send_cb(send_cb);

    ESP_LOGI(TAG, "ESP-NOW init finished.");
    return ESP_OK;
}

// Registro del dispositivo peer en la red ESP-NOW
static esp_err_t register_peer(uint8_t *peer_mac)
{
    esp_now_peer_info_t esp_now_peer_info = {};
    memcpy(esp_now_peer_info.peer_addr, peer_mac, ESP_NOW_ETH_ALEN);
    //memcpy(esp_now_peer_info.peer_addr, peer_mac, 0xec, 0x62, 0x60, 0x84, 0x1f, 0x40);
    
    esp_now_peer_info.channel = ESP_CHANNEL;
    esp_now_peer_info.ifidx = ESP_IF_WIFI_STA;
    esp_now_add_peer(&esp_now_peer_info);
    return ESP_OK;
}

void app_main()
{
    // Inicializar
    ESP_ERROR_CHECK(init_wifi());
    ESP_ERROR_CHECK(init_esp_now());
    ESP_ERROR_CHECK(register_peer(peer_mac));

    // Inicializar I2C
    int i2c_master_port = I2C_NUM_0;
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = CONFIG_SDA_GPIO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = CONFIG_SCL_GPIO,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 1000000 // 1MHz
    };

    // Configura el controlador I2C con los parámetros anteriores
    ESP_ERROR_CHECK(i2c_param_config(i2c_master_port, &conf));

    // Instala el controlador I2C
    ESP_ERROR_CHECK(i2c_driver_install(i2c_master_port, conf.mode, 0, 0, 0));

/*
    typedef struct struct_message
{
    uint8_t id[8];
    uint8_t payload[8];
} struct_message;
*/

typedef struct {
    uint8_t tipo : 2;      // 2 bits para el tipo de sensor
    uint8_t id : 8;        // 8 bits para el ID
    uint16_t temperatura : 9; // 9 bits para la temperatura
    uint8_t humedad : 7;   // 7 bits para la humedad
} struct_message1;

typedef struct {
    uint8_t tipo : 2;      // 2 bits para el tipo de sensor
    uint8_t id : 8;        // 8 bits para el ID
    uint8_t adc : 8;       // 8 bits para la lectura ADC
} struct_message2;

typedef struct {
    uint8_t tipo : 2;      // 2 bits para el tipo de sensor
    uint8_t id : 8;        // 8 bits para el ID
    uint8_t button : 1;    // 1 bit para el estado del botón (encendido/apagado)
} struct_message3;

typedef union {
    struct_message1 message1;
    struct_message2 message2;
    struct_message3 message3;
} sensor_message;


/*
Tipo: 1 -> DHT11
Tipo: 2 -> ADC
Tipo: 3 -> Buttom
*/

int Tipo_sensor = 2; //  ADC

// lectura por I2C y  transmision de datos por ESP-NOW
while (1)
{
    // Leer datos del ADC
    uint8_t adc_data[5]; // Suponiendo que el ADC devuelve 5 bytes de datos

    esp_err_t ret = i2c_master_read_from_device(I2C_NUM_0, I2C_SLAVE_ADDR, adc_data, 5, TIMEOUT_MS / portTICK_PERIOD_MS);
    ESP_LOG_BUFFER_HEX(TAG, adc_data, 5); // Ver datos en el registro
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Error al leer del ADC: %d", ret);
    }
    else
    {
        int adc_value = adc_data[1];
        ESP_LOGI(TAG, "Valor ADC:%d", adc_value);
        
        sensor_message message;

        if (Tipo_sensor == 1)
        {
            message.message1.tipo = 1;
            // Asignar valores a los otros campos de message1

        }
        else if (Tipo_sensor == 2)
        {
            message.message2.tipo = 2;
            message.message2.id = 13;
            message.message2.adc = adc_value;

            esp_now_send(peer_mac, (uint8_t *)&message.message2, sizeof(message.message2));

            // imprimir el mensaje en el registro tipo struct_message
            ESP_LOGI(TAG, "Valor enviado: %d", message.message2.adc);
            ESP_LOGI(TAG, "Tipo: %d", message.message2.tipo);
        }
        else if (Tipo_sensor == 3)
        {
            message.message3.tipo = 3;
            // Aquí puedes asignar valores a los otros campos de message3 si es necesario
        }
    }
    vTaskDelay(pdMS_TO_TICKS(500));
}
}