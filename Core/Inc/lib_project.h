#include "Fonts.h"
#include "SSD1306.h"
#include "rc522.h"
#include "flash.h"


#define Flash_Page_Base 0x08019000		// page for counter card
#define Flash_Page_Couter_Card 0x08018C00
#define Flash_Page_Pass_Keypad 0x08018800

static int8_t pos_oled[6] = {32,42,52,62,72,82};
static  int8_t count_buzzer = 0;


void init_mainKey();
void init_main_Card();
void change_mainKey();

uint8_t check_arrpass(int8_t *pass, int length);
void seclect_button_full(int8_t key,int8_t *passKey);
void seclect_button_nonfull(int8_t key, int8_t *temp_pass);
uint8_t check_PassKey(int8_t *pass_key);
void swapToArr(uint8_t* arr , uint8_t *arrSwap);
char read_keypad (void);
void begin_pass(int8_t *keypass, int8_t length, int8_t value);

void UnClock_Door();
void Input_Key(int8_t key, int8_t *PassArr);
uint8_t checkCard(uint8_t *strCard, uint8_t *str_page);
uint8_t Check_Input_Card(uint8_t *strCard);
uint32_t FindCard(uint8_t *cardId);
uint8_t CardInput_return(uint8_t *cardId);
void InputKeyDisplay(int8_t key, int8_t* passArr, uint8_t index , uint8_t mode);
void InputKeyFail();
void clearScreen();
int8_t checkMaincard(uint8_t* card_id);
int8_t DeleteCard();
int8_t AddCard();

