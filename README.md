O sistema desenvolvido é um sistema de semáforo utiliza uma placa BitDogLab (baseada na Raspberry Pi Pico W) para controlar um LED RGB e exibir mensagens em um display OLED de 128x64 pixels com comunicação I2C. 
O sistema simula o funcionamento de um semáforo, alternando entre as cores vermelho, amarelo e verde, enquanto exibe mensagens no display OLED correspondentes a cada estado do semáforo.

Componentes do Sistema
1. Placa BitDogLab (Raspberry Pi Pico W):

- Microcontrolador baseado no chip RP2040.

- Controla o LED RGB e o display OLED.

- Comunicação I2C para o display OLED.

2. LED RGB (cátodo comum):

- Vermelho: Conectado ao GPIO 13 com um resistor de 220 ohms.

- Verde: Conectado ao GPIO 11 com um resistor de 220 ohms.

- Azul: Conectado ao GPIO 12 com um resistor de 150 ohms.

3. Display OLED 128x64 (I2C):

- Conectado aos pinos GPIO 14 (SDA) e GPIO 15 (SCL).

- Endereço I2C padrão: 0x3C.

- Exibe mensagens correspondentes ao estado do semáforo.

4. Biblioteca SSD1306:

- Usada para controlar o display OLED.

- Implementa funções para exibir texto e limpar a tela.



Funcionamento do Sistema

O sistema opera em um loop infinito, alternando entre três estados principais:

1. Sinal Vermelho:

- O LED RGB acende a cor vermelha.

- O display OLED exibe a mensagem "Paciência".

- Duração: 5 segundos.

2. Sinal Amarelo:

- O LED RGB acende a cor amarela (combinação de vermelho e verde).

- O display OLED exibe a mensagem "Calma".

- Duração: 2 segundos.

3. Sinal Verde:

- O LED RGB acende a cor verde.

- O display OLED exibe a mensagem "Cuidado".

- Duração: 5 segundos.

Após o ciclo completo, o sistema reinicia, repetindo a sequência indefinidamente.



Fluxo de Operação

1. Inicialização:

- Configura os pinos do LED RGB como saída.

- Inicializa o display OLED via I2C.

- Limpa o display e prepara-o para exibir mensagens.

2. Loop Principal:

- Alterna entre os estados do semáforo (vermelho, amarelo, verde).

Para cada estado:

- Acende a cor correspondente no LED RGB.

- Exibe a mensagem correspondente no display OLED.

- Aguarda o tempo definido para o estado.
  

Mensagens no Display OLED

- Vermelho: Exibe "Paciência".

Indica que os usuários devem esperar.

- Amarelo: Exibe "Calma".

Indica que o sinal está prestes a mudar.

- Verde: Exibe "Cuidado".

Indica que os usuários podem prosseguir, mas com atenção.


Código Principal
- O código principal do sistema está escrito em C e utiliza as seguintes bibliotecas:

- pico/stdlib.h: Para controle dos GPIOs e temporização.

- hardware/i2c.h: Para comunicação I2C com o display OLED.

- ssd1306.h: Para controlar o display OLED.


Aplicações do Sistema

Educação:

Ideal para ensinar conceitos de programação embarcada, controle de GPIOs e comunicação I2C.

Prototipagem:

Pode ser usado como base para projetos mais complexos, como semáforos inteligentes com sensores.

Demonstração:

Simula o funcionamento de um semáforo real, com feedback visual no display OLED.
