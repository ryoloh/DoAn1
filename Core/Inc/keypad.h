#include "stm32f103xb.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "SSD1306.h"
#include "lib_project.h"



#define R1_PORT GPIOB
#define R1_PIN GPIO_PIN_11

#define R2_PORT GPIOB
#define R2_PIN GPIO_PIN_10

#define R3_PORT GPIOB
#define R3_PIN GPIO_PIN_1

#define R4_PORT GPIOB
#define R4_PIN GPIO_PIN_0

#define C1_PORT GPIOA
#define C1_PIN GPIO_PIN_3

#define C2_PORT GPIOA
#define C2_PIN GPIO_PIN_2

#define C3_PORT GPIOA
#define C3_PIN GPIO_PIN_1

#define C4_PORT GPIOA
#define C4_PIN GPIO_PIN_0



char read_keypad (void);
void begin_pass(int8_t *keypass, int8_t length, int8_t value);

//void add_keypass(int8_t key, int8_t *pass_key, int8_t *temp_pass);
//void clear_oled40();
//uint8_t check_arrpass(uint8_t *pass, int length);


//void initPassKey(int8_t *keypass);
