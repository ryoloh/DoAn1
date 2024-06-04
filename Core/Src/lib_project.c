#include "lib_project.h"

void init_mainKey(){
	uint8_t mainKey[6] = {0x31,0x31,0x31,0x31,0x31,0x31};
	Flash_Earse(Flash_Page_Pass_Keypad);
	Flash_Write_Array(Flash_Page_Pass_Keypad,mainKey,6);
}

void change_mainKey(){
	uint8_t mainkey[6];
	uint8_t temp = 0;
	int8_t key;
	while(temp < 6){
		key = read_keypad();
		if(key != 0x01){
			if(key != 'A' && key != 'C' && key != 'D' && key != 'B'){
				mainkey[temp] = key;
				ssd1306_display_char(pos_oled[temp] ,50, '*', 12,1);
				ssd1306_refresh_gram();
				temp++;
			}
		}
	}
	Flash_Earse(Flash_Page_Pass_Keypad);
	Flash_Write_Array(Flash_Page_Pass_Keypad,mainkey,6);
	ssd1306_clear_screen(0);
	ssd1306_display_string(1,15,(uint8_t*)"ChangePawssword",16,1);
	ssd1306_display_string(12,45,(uint8_t*)"Sucessfully",16,1);
  	ssd1306_refresh_gram();
	
}

void init_main_Card(){
	//uint8_t mainCard[4] = {0x58,0xD9,0x20,0x01};
	uint8_t mainCard[4] = {0xB2,0x9A,0x8A,0x5A};
	// init counter page card
	Flash_Earse(Flash_Page_Couter_Card);
	Flash_Write_Int(Flash_Page_Couter_Card,1);
	// init main card
	Flash_Earse(Flash_Page_Base);
	Flash_Write_Array(Flash_Page_Base,mainCard,4);
	
}
void swapToArr(uint8_t* arr , uint8_t *arrSwap){
	for(uint8_t index = 0; index < 4;index++){
		arrSwap[index] = arr[index+1];
	}
}

// Open the door and clock after 3s
void UnClock_Door(){
	count_buzzer = 0;
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
	HAL_Delay(2000);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);

	clearScreen();
}


void Input_Key(int8_t key, int8_t *PassArr){
			// PassArr full
			if(check_arrpass(PassArr,6) == 7){
				seclect_button_full(key,PassArr);
			}
			// PassArr non full
			else{
				seclect_button_nonfull(key,PassArr);
			}
}
// return 0 if true 
uint8_t checkCard(uint8_t *strCard, uint8_t *str_page){
	uint8_t check =0;
	for(uint8_t index =0; index < 4; index ++){
		if(strCard[index] != str_page[index]){
			check = 1;
			break;
		}
	}
	return check;
}
// Return 0 : Card valid
//				1 : Card Invalid
uint8_t Check_Input_Card(uint8_t *strCard){
	uint8_t check = 1;
	int numberCard = Flash_Read_Int(Flash_Page_Couter_Card);
	for(uint8_t index = 0; index < numberCard; index++){
		uint8_t tempCard[4];
		Flash_Read_Array(Caculate_Adress_Flash(Flash_Page_Base,index),tempCard,4);
		if(!checkCard(strCard,tempCard)){
			check = 0;
			break;
		}
	}
	return check;
}

// Return address of Card 
uint32_t FindCard(uint8_t *cardId){
	uint32_t result = 0;
	int numberCard = Flash_Read_Int(Flash_Page_Couter_Card);
	for(uint8_t index = 0; index < numberCard; index++){
		uint8_t tempCard[4];
		Flash_Read_Array(Caculate_Adress_Flash(Flash_Page_Base,index),tempCard,4);
		if(!checkCard(cardId,tempCard)){
			result = Caculate_Adress_Flash(Flash_Page_Base,index);
		}
	}
	return result;
}

// Input card -> 
uint8_t CardInput_return(uint8_t *cardId){
	uint8_t tempArr[MAX_LEN];
	if(!MFRC522_Request(PICC_REQIDL,tempArr)){
		if(!MFRC522_Anticoll(tempArr)){
			swapToArr(tempArr,cardId);
			return 1;
		}
	}
	return 0;
}

// mode1 display * , mode 0 delete
void InputKeyDisplay(int8_t key, int8_t* passArr, uint8_t index , uint8_t mode){
	if(mode == 1){
		passArr[index-1] = key;
		ssd1306_display_char(pos_oled[index - 1] ,40, '*', 12,1);
		ssd1306_refresh_gram();
	}
	else{
		passArr[index - 2] = -1;
		ssd1306_display_char(pos_oled[index - 1] ,40, ' ', 12,1);
		ssd1306_display_char(pos_oled[index - 2] ,40, ' ', 12,1);
		ssd1306_refresh_gram();
	}
}
void InputKeyFail(){
	ssd1306_clear_screen(0);
	ssd1306_display_string(22,15,(uint8_t*)"Fail Input",16,1);
	ssd1306_refresh_gram();	
	HAL_Delay(2000);
	clearScreen();
}

void clearScreen(){
	ssd1306_clear_screen(0);
	ssd1306_display_string(32,15,(uint8_t*)"WELCOME",16,1);
	ssd1306_refresh_gram();	
}


void swapCard(uint32_t address){
	uint8_t add1[4];
	Flash_Read_Array(address,add1,4);
	uint8_t add2[4];
	uint32_t lastCard = Caculate_Adress_Flash(Flash_Page_Base,Flash_Read_Int(Flash_Page_Couter_Card) -1);
	Flash_Read_Array(lastCard,add2,4);
	Flash_Earse(address);
	Flash_Earse(lastCard);
	Flash_Write_Array(address,add2,4);
	Flash_Write_Array(lastCard,add1,4);
}

int8_t checkMaincard(uint8_t* card_id){
	uint8_t tempCard[4];
	Flash_Read_Array(Flash_Page_Base,tempCard,4);
	for(uint8_t index = 0; index < 4; index++){
		if(card_id[index] != tempCard[index]){
			return 1;
		}
	}
	return 0;
}

int8_t DeleteCard(){
	int8_t ret = 0;
	ssd1306_clear_screen(0);
	ssd1306_display_string(45,5,(uint8_t*)"Add",16,1);
	ssd1306_display_string(12,35,(uint8_t*)"Main Card",16,1);
	ssd1306_refresh_gram();
	uint8_t mainCard[4];
	while(!CardInput_return(mainCard));
	if(!checkMaincard(mainCard)){
		ssd1306_clear_screen(0);
		ssd1306_display_string(45,5,(uint8_t*)"Add",16,1);
		ssd1306_display_string(12,35,(uint8_t*)"Card Delete",16,1);
		ssd1306_refresh_gram();
		uint8_t cardId[4];
		while(!CardInput_return(cardId));	
		if(!Check_Input_Card(cardId)){
				int numberCard = Flash_Read_Int(Flash_Page_Couter_Card);
				swapCard(FindCard(cardId));
				uint32_t lastCard = Caculate_Adress_Flash(Flash_Page_Base,Flash_Read_Int(Flash_Page_Couter_Card) -1);
				Flash_Earse(lastCard);
				Flash_Earse(Flash_Page_Couter_Card);
				Flash_Write_Int(Flash_Page_Couter_Card,numberCard-1);
				ret = 1;
		}	
	}
	return ret;
}
int8_t AddCard(){
	int8_t ret = 0;
	ssd1306_clear_screen(0);
	ssd1306_display_string(35,5,(uint8_t*)"Add",16,1);
	ssd1306_display_string(12,35,(uint8_t*)"Main Card",16,1);
	ssd1306_refresh_gram();
	uint8_t mainCard[4];
	while(!CardInput_return(mainCard));
	if(!checkMaincard(mainCard)){
		ssd1306_clear_screen(0);
		ssd1306_display_string(35,5,(uint8_t*)"Add",16,1);
		ssd1306_display_string(12,35,(uint8_t*)"New Card",16,1);
		ssd1306_refresh_gram();
		uint8_t cardId[4];
		while(!CardInput_return(cardId));		
		if(Check_Input_Card(cardId)){
			int numberCard = Flash_Read_Int(Flash_Page_Couter_Card);
			Flash_Earse(Caculate_Adress_Flash(Flash_Page_Base,numberCard));
			Flash_Write_Array(Caculate_Adress_Flash(Flash_Page_Base,numberCard),cardId,4);
			Flash_Earse(Flash_Page_Couter_Card);
			Flash_Write_Int(Flash_Page_Couter_Card,numberCard+1);
			ret = 1;
		}	
	}
	return ret;
}