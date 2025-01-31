#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

#define LED1_PIN 13
#define LED2_PIN 12
#define LED3_PIN 11
#define BUTTON_PIN 5

// Protótipos das funções de callback
int64_t debounce_check_callback(alarm_id_t id, void *user_data);
int64_t alarm_callback(alarm_id_t id, void *user_data);

volatile bool is_running = false;
volatile alarm_id_t debounce_alarm_id = 0;

static void gpio_callback(uint gpio, uint32_t events) {
    if (gpio == BUTTON_PIN) {
        if (debounce_alarm_id != 0) {
            cancel_alarm(debounce_alarm_id);
            debounce_alarm_id = 0;
        }
        debounce_alarm_id = add_alarm_in_ms(50, debounce_check_callback, NULL, false);
    }
}

int64_t debounce_check_callback(alarm_id_t id, void *user_data) {
    if (!gpio_get(BUTTON_PIN) && !is_running) {
        is_running = true;
        gpio_put(LED1_PIN, 1);
        gpio_put(LED2_PIN, 1);
        gpio_put(LED3_PIN, 1);
        add_alarm_in_ms(3000, alarm_callback, (void *)(uintptr_t)2, false);
    }
    debounce_alarm_id = 0;
    return 0;
}

int64_t alarm_callback(alarm_id_t id, void *user_data) {
    uint32_t step = (uint32_t)(uintptr_t)user_data;

    switch (step) {
        case 2:
            gpio_put(LED3_PIN, 0);
            add_alarm_in_ms(3000, alarm_callback, (void *)(uintptr_t)3, false);
            break;
        case 3:
            gpio_put(LED2_PIN, 0);
            add_alarm_in_ms(3000, alarm_callback, (void *)(uintptr_t)0, false);
            break;
        case 0:
            gpio_put(LED1_PIN, 0);
            is_running = false;
            break;
    }
    return 0;
}

int main() {
    stdio_init_all();

    gpio_init(LED1_PIN);
    gpio_set_dir(LED1_PIN, GPIO_OUT);
    gpio_init(LED2_PIN);
    gpio_set_dir(LED2_PIN, GPIO_OUT);
    gpio_init(LED3_PIN);
    gpio_set_dir(LED3_PIN, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);

    while (1) {
        tight_loop_contents();
    }

    return 0;
}