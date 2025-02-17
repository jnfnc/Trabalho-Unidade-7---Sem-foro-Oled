#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h"  


const uint I2C_SDA = 14;
const uint I2C_SCL = 15;


const uint LED_VERMELHO = 16;
const uint LED_AMARELO = 17;
const uint LED_VERDE = 18;


const uint LED_RED_PIN = 13;   
const uint LED_GREEN_PIN = 11; 


const uint BUZZER_PIN = 10;


void init_display() {
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    ssd1306_init();
}


void display_message(const char *message) {
    uint8_t ssd[ssd1306_buffer_length];
    memset(ssd, 0, ssd1306_buffer_length);

    struct render_area frame_area = {
        start_column : 0,
        end_column : ssd1306_width - 1,
        start_page : 0,
        end_page : ssd1306_n_pages - 1
    };

    calculate_render_area_buffer_length(&frame_area);
    ssd1306_draw_string(ssd, 5, 10, message);
    render_on_display(ssd, &frame_area);
}


void init_semaforo() {
    gpio_init(LED_VERMELHO);
    gpio_init(LED_AMARELO);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_set_dir(LED_AMARELO, GPIO_OUT);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    
    gpio_put(LED_VERMELHO, 0);
    gpio_put(LED_AMARELO, 0);
    gpio_put(LED_VERDE, 0);
}


    gpio_init(LED_RED_PIN);
    gpio_init(LED_GREEN_PIN);

    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);

    // Desliga todos os LEDs no início
    gpio_put(LED_RED_PIN, 0);
    gpio_put(LED_GREEN_PIN, 0);
}


void set_rgb_color(bool red, bool green) {
    gpio_put(LED_RED_PIN, red);
    gpio_put(LED_GREEN_PIN, green);
}


void init_buzzer() {
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    gpio_put(BUZZER_PIN, 0); // Desliga o buzzer no início
}


void play_sound(uint frequency, uint duration_ms) {
    if (frequency == 0) {
        gpio_put(BUZZER_PIN, 0); // Desliga o buzzer
        return;
    }

   
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
    uint channel_num = pwm_gpio_to_channel(BUZZER_PIN);

    pwm_set_clkdiv(slice_num, 125.0f); 
    pwm_set_wrap(slice_num, 1000000 / frequency); 
    pwm_set_chan_level(slice_num, channel_num, 500000 / frequency); 
    pwm_set_enabled(slice_num, true); 

    sleep_ms(duration_ms); 

    pwm_set_enabled(slice_num, false); 
    gpio_put(BUZZER_PIN, 0); 
}

int main() {
    stdio_init_all(); 

    
    init_display();

    
    init_semaforo();

    
    init_rgb_led();

    
    init_buzzer();

    while (true) {
        
        gpio_put(LED_VERMELHO, 1); 
        gpio_put(LED_AMARELO, 0);
        gpio_put(LED_VERDE, 0);
        set_rgb_color(1, 0); 
        display_message("Paciencia");
        play_sound(500, 1000); 
        sleep_ms(4000); 

        
        gpio_put(LED_VERMELHO, 0);
        gpio_put(LED_AMARELO, 1); 
        gpio_put(LED_VERDE, 0);
        set_rgb_color(1, 1); 
        display_message("Calma");
        play_sound(1000, 500); 
        sleep_ms(1500); 

        
        gpio_put(LED_VERMELHO, 0);
        gpio_put(LED_AMARELO, 0);
        gpio_put(LED_VERDE, 1); 
        set_rgb_color(0, 1); 
        display_message("Cuidado");
        play_sound(2000, 2000); 
        sleep_ms(3000); 
    }

    return 0;
}
