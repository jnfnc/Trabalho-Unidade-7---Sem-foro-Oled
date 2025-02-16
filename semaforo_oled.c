#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h"  // Para controle de tom no buzzer

// Definição dos pinos I2C
const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

// Definição dos pinos do semáforo
const uint LED_VERMELHO = 16;
const uint LED_AMARELO = 17;
const uint LED_VERDE = 18;

// Definição dos pinos do LED RGB (apenas vermelho e verde)
const uint LED_RED_PIN = 13;   // Vermelho
const uint LED_GREEN_PIN = 11; // Verde

// Definição do pino do buzzer
const uint BUZZER_PIN = 10;

// Função para inicializar o display OLED
void init_display() {
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    ssd1306_init();
}

// Função para exibir uma mensagem no display
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

// Função para inicializar os LEDs do semáforo
void init_semaforo() {
    gpio_init(LED_VERMELHO);
    gpio_init(LED_AMARELO);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_set_dir(LED_AMARELO, GPIO_OUT);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    // Desliga todos os LEDs no início
    gpio_put(LED_VERMELHO, 0);
    gpio_put(LED_AMARELO, 0);
    gpio_put(LED_VERDE, 0);
}

// Função para inicializar o LED RGB (apenas vermelho e verde)
void init_rgb_led() {
    gpio_init(LED_RED_PIN);
    gpio_init(LED_GREEN_PIN);

    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);

    // Desliga todos os LEDs no início
    gpio_put(LED_RED_PIN, 0);
    gpio_put(LED_GREEN_PIN, 0);
}

// Função para controlar o LED RGB (apenas vermelho e verde)
void set_rgb_color(bool red, bool green) {
    gpio_put(LED_RED_PIN, red);
    gpio_put(LED_GREEN_PIN, green);
}

// Função para inicializar o buzzer
void init_buzzer() {
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    gpio_put(BUZZER_PIN, 0); // Desliga o buzzer no início
}

// Função para emitir um som no buzzer
void play_sound(uint frequency, uint duration_ms) {
    if (frequency == 0) {
        gpio_put(BUZZER_PIN, 0); // Desliga o buzzer
        return;
    }

    // Configura o PWM para gerar o tom
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
    uint channel_num = pwm_gpio_to_channel(BUZZER_PIN);

    pwm_set_clkdiv(slice_num, 125.0f); // Define o divisor de clock
    pwm_set_wrap(slice_num, 1000000 / frequency); // Define a frequência
    pwm_set_chan_level(slice_num, channel_num, 500000 / frequency); // Define o ciclo de trabalho (50%)
    pwm_set_enabled(slice_num, true); // Habilita o PWM

    sleep_ms(duration_ms); // Mantém o som pelo tempo especificado

    pwm_set_enabled(slice_num, false); // Desliga o PWM
    gpio_put(BUZZER_PIN, 0); // Desliga o buzzer
}

int main() {
    stdio_init_all(); // Inicializa a comunicação serial (opcional para depuração)

    // Inicializa o display OLED
    init_display();

    // Inicializa os LEDs do semáforo
    init_semaforo();

    // Inicializa o LED RGB
    init_rgb_led();

    // Inicializa o buzzer
    init_buzzer();

    while (true) {
        // Sinal vermelho
        gpio_put(LED_VERMELHO, 1); // Liga o LED vermelho do semáforo
        gpio_put(LED_AMARELO, 0);
        gpio_put(LED_VERDE, 0);
        set_rgb_color(1, 0); // Liga o LED RGB na cor vermelha
        display_message("Paciencia");
        play_sound(500, 1000); // Emite um som de 500 Hz por 1 segundo
        sleep_ms(4000); // Aguarda 4 segundos (totalizando 5 segundos)

        // Sinal amarelo
        gpio_put(LED_VERMELHO, 0);
        gpio_put(LED_AMARELO, 1); // Liga o LED amarelo do semáforo
        gpio_put(LED_VERDE, 0);
        set_rgb_color(1, 1); // Liga o LED RGB na cor amarela (vermelho + verde)
        display_message("Calma");
        play_sound(1000, 500); // Emite um som de 1000 Hz por 0,5 segundo
        sleep_ms(1500); // Aguarda 1,5 segundo (totalizando 2 segundos)

        // Sinal verde
        gpio_put(LED_VERMELHO, 0);
        gpio_put(LED_AMARELO, 0);
        gpio_put(LED_VERDE, 1); // Liga o LED verde do semáforo
        set_rgb_color(0, 1); // Liga o LED RGB na cor verde
        display_message("Cuidado");
        play_sound(2000, 2000); // Emite um som de 2000 Hz por 2 segundos
        sleep_ms(3000); // Aguarda 3 segundos (totalizando 5 segundos)
    }

    return 0;
}