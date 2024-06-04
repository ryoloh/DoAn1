#include "keypad.h"

static int8_t button_enter = 'A';
static int8_t button_deletekey = 'B';
static int8_t button_changekey[2] = {'C','C'};
static int8_t button_add[2] = {'C','C'};
static int8_t button_change[2] = {'C','D'};
static int8_t button_delete[2] = {'D','D'};
static int8_t temp_button[2];


char read_keypad (void)
{
	/* Make ROW 1 LOW and all other ROWs HIGH */
	HAL_GPIO_WritePin (R1_PORT, R1_PIN, GPIO_PIN_RESET);  //Pull the R1 low
	HAL_GPIO_WritePin (R2_PORT, R2_PIN, GPIO_PIN_SET);  // Pull the R2 High
	HAL_GPIO_WritePin (R3_PORT, R3_PIN, GPIO_PIN_SET);  // Pull the R3 High
	HAL_GPIO_WritePin (R4_PORT, R4_PIN, GPIO_PIN_SET);  // Pull the R4 High
	
	if (!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN)))   // if the Col 1 is low
	{
		while (!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN)));   // wait till the button is pressed
		return '1';
	}    
	
	if (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)))   // if the Col 2 is low
	{
		while (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)));   // wait till the button is pressed
		return '2';
	}
	
	if (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)))   // if the Col 3 is low
	{
		while (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)));   // wait till the button is pressed
		return '3';
	}
	
	if (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)))   // if the Col 4 is low
	{
		while (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)));   // wait till the button is pressed
		return 'A';
	}
	
	/* Make ROW 2 LOW and all other ROWs HIGH */
	HAL_GPIO_WritePin (R1_PORT, R1_PIN, GPIO_PIN_SET);  //Pull the R1 low
	HAL_GPIO_WritePin (R2_PORT, R2_PIN, GPIO_PIN_RESET);  // Pull the R2 High
	HAL_GPIO_WritePin (R3_PORT, R3_PIN, GPIO_PIN_SET);  // Pull the R3 High
	HAL_GPIO_WritePin (R4_PORT, R4_PIN, GPIO_PIN_SET);  // Pull the R4 High
	
	if (!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN)))   // if the Col 1 is low
	{
		while (!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN)));   // wait till the button is pressed
		return '4';
	}
	
	if (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)))   // if the Col 2 is low
	{
		while (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)));   // wait till the button is pressed
		return '5';
	}
	
	if (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)))   // if the Col 3 is low
	{
		while (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)));   // wait till the button is pressed
		return '6';
	}
	
	if (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)))   // if the Col 4 is low
	{
		while (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)));   // wait till the button is pressed
		return 'B';
	}
	
	
	/* Make ROW 3 LOW and all other ROWs HIGH */
	HAL_GPIO_WritePin (R1_PORT, R1_PIN, GPIO_PIN_SET);  //Pull the R1 low
	HAL_GPIO_WritePin (R2_PORT, R2_PIN, GPIO_PIN_SET);  // Pull the R2 High
	HAL_GPIO_WritePin (R3_PORT, R3_PIN, GPIO_PIN_RESET);  // Pull the R3 High
	HAL_GPIO_WritePin (R4_PORT, R4_PIN, GPIO_PIN_SET);  // Pull the R4 High
	
	if (!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN)))   // if the Col 1 is low
	{
		while (!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN)));   // wait till the button is pressed
		return '7';
	}
	
	if (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)))   // if the Col 2 is low
	{
		while (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)));   // wait till the button is pressed
		return '8';
	}
	
	if (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)))   // if the Col 3 is low
	{
		while (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)));   // wait till the button is pressed
		return '9';
	}
	
	if (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)))   // if the Col 4 is low
	{
		while (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)));   // wait till the button is pressed
		return 'C';
	}
	
		
	/* Make ROW 4 LOW and all other ROWs HIGH */
	HAL_GPIO_WritePin (R1_PORT, R1_PIN, GPIO_PIN_SET);  //Pull the R1 low
	HAL_GPIO_WritePin (R2_PORT, R2_PIN, GPIO_PIN_SET);  // Pull the R2 High
	HAL_GPIO_WritePin (R3_PORT, R3_PIN, GPIO_PIN_SET);  // Pull the R3 High
	HAL_GPIO_WritePin (R4_PORT, R4_PIN, GPIO_PIN_RESET);  // Pull the R4 High
	
	if (!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN)))   // if the Col 1 is low
	{
		while (!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN)));   // wait till the button is pressed
		return '*';
	}
	
	if (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)))   // if the Col 2 is low
	{
		while (!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN)));   // wait till the button is pressed
		return '0';
	}
	
	if (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)))   // if the Col 3 is low
	{
		while (!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN)));   // wait till the button is pressed
		return '#';
	}
	
	if (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)))   // if the Col 4 is low
	{
		while (!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN)));   // wait till the button is pressed
		return 'D';
	}
	return 0x01;
}



void begin_pass(int8_t *keypass, int8_t length, int8_t value){
	for(uint8_t index = 0 ; index < length; index++){
		keypass[index] = value;
	}
}
/*	Check index PassKey
	Index [0->5] return [1->6]
	Index = 7 : keypass full
*/
uint8_t check_arrpass(int8_t *pass, int length){
		for(uint8_t index = 0; index < length; index ++){
			if(pass[index] == -1)
				return index + 1;
		}
		return 7;
}

/*
Return 1 -> fail
			 0 -> True
*/
uint8_t check_PassKey(int8_t *pass_key){
	uint8_t checkPass[6];
	Flash_Read_Array(Flash_Page_Pass_Keypad,checkPass,6);
	for(uint8_t index = 0; index < 6; index ++){
		if(pass_key[index] != checkPass[index])
			return 1;
	}
	return 0;
}

// select button for check pass full
void seclect_button_full(int8_t key,int8_t *passKey){
	if(key == button_enter){
			// open lock
		if(check_PassKey(passKey) == 0){
			ssd1306_clear_screen(0);
			ssd1306_display_string(30,15,(uint8_t*)"CORRECT",16,1);
			ssd1306_display_string(30,35,(uint8_t*)"PASSWORD",16,1);
			ssd1306_refresh_gram();
			UnClock_Door();
			begin_pass(passKey,6,-1);
		}
		else{
			count_buzzer++;
			if(count_buzzer == 3){
				HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_9);
				HAL_Delay(2000);
				HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_9);
				count_buzzer =0;
			}
			ssd1306_clear_screen(0);
			ssd1306_display_string(30,15,(uint8_t*)"INCORRECT",16,1);
			ssd1306_display_string(30,35,(uint8_t*)"PASSWORD",16,1);
			ssd1306_refresh_gram();
			begin_pass(passKey,6,-1);
			HAL_Delay(2000);
			clearScreen();
		}

	}
	if(key == button_deletekey){
		passKey[5] = -1;
		ssd1306_display_char(pos_oled[5] ,40, ' ', 12,1);
		ssd1306_refresh_gram();
	}
}

void seclect_button_nonfull(int8_t key, int8_t *temp_pass){
	uint8_t posArrPass = check_arrpass(temp_pass,6);
	if(posArrPass <4){
		if(posArrPass == 1){
			if(key == button_enter){
				InputKeyFail();
				begin_pass(temp_pass,6,-1);
			}
			if(key == button_deletekey)
				return;
			if(key == 'C' || key == 'D'){
				if(key == 'C'){
					temp_pass[posArrPass-1] = key;
					ssd1306_display_char(pos_oled[posArrPass - 1] ,40, 'C', 12,1);
					ssd1306_refresh_gram();
				}
				else{
					temp_pass[posArrPass-1] = key;
					ssd1306_display_char(pos_oled[posArrPass - 1] ,40, 'D', 12,1);
					ssd1306_refresh_gram();
				}
			}
			else{
				InputKeyDisplay(key,temp_pass,posArrPass,1);
			}
		}
		// Add card and delete
		if(posArrPass == 2){
			if(key == button_enter || key == button_deletekey || key == 'C' || key == 'D'){
				if(key == button_enter){
					if(temp_pass[0] == 'D'){
						begin_pass(temp_pass,6,-1);
						
						if(DeleteCard() == 1){
							ssd1306_clear_screen(0);
							ssd1306_display_string(5,5,(uint8_t*)"Card Deleted ",16,1);
							ssd1306_display_string(12,35,(uint8_t*)"Successfully",16,1);
							ssd1306_refresh_gram();
						}
						else{
							ssd1306_clear_screen(0);
							ssd1306_display_string(8,5,(uint8_t*)"Fail Deleted ",16,1);
							ssd1306_display_string(30,35,(uint8_t*)"Card",16,1);
							ssd1306_refresh_gram();
						}
						HAL_Delay(2000);
						clearScreen();
					}
					if(temp_pass[0] == 'C'){
						begin_pass(temp_pass,6,-1);
						if(AddCard() == 1){
							ssd1306_clear_screen(0);
							ssd1306_display_string(15,5,(uint8_t*)"Card Added ",16,1);
							ssd1306_display_string(18,30,(uint8_t*)" Successfully",16,1);
							ssd1306_refresh_gram();
						}
						else{
							ssd1306_clear_screen(0);
							ssd1306_display_string(8,5,(uint8_t*)"Fail Added ",16,1);
							ssd1306_display_string(30,35,(uint8_t*)"Card",16,1);
							ssd1306_refresh_gram();
						}
						HAL_Delay(2000);
						clearScreen();
					}
				}
				if(key == button_deletekey){
					InputKeyDisplay(key,temp_pass,posArrPass,0);
				}
				if(key == 'D'){
					temp_pass[posArrPass-1] = key;
					ssd1306_display_char(pos_oled[posArrPass - 1] ,40, 'D', 12,1);
					ssd1306_refresh_gram();
				}
				if(key == 'C'){
					InputKeyFail();
					begin_pass(temp_pass,6,-1);
				}
			}
			else{
				if(temp_pass[0] != 'C' && temp_pass[0] != 'D'){
					InputKeyDisplay(key,temp_pass,posArrPass,1);
				}
				else{
					InputKeyFail();
					begin_pass(temp_pass,6,-1);
				}
			}
		}
		// Change pass
		if(posArrPass == 3 ){
			if(key == button_enter || key == button_deletekey || key == 'C' || key == 'D'){
				if(key == button_enter){
					if(temp_pass[0] == 'C' && temp_pass[1] == 'D'){
						ssd1306_clear_screen(0);
						ssd1306_display_string(45,5,(uint8_t*)"Add",16,1);
						ssd1306_display_string(15,35,(uint8_t*)"Main Card",16,1);
						ssd1306_refresh_gram();
						uint8_t mainCard[4];
						while(!CardInput_return(mainCard));
						if(!checkMaincard(mainCard)){
							ssd1306_clear_screen(0);		
							ssd1306_display_string(37,5,(uint8_t*)"Enter",16,1);
							ssd1306_display_string(8,25,(uint8_t*)"New Password",16,1);
							ssd1306_refresh_gram();
							change_mainKey();
						}
						else{
							ssd1306_clear_screen(0);		
							ssd1306_display_string(32,5,(uint8_t*)"MainCard",16,1);
							ssd1306_display_string(5,25,(uint8_t*)"Not Valid",16,1);
							ssd1306_refresh_gram();						
						}
						begin_pass(temp_pass,6,-1);
						HAL_Delay(2000);
						clearScreen();
					}
				}		
				if(key == button_deletekey){
					InputKeyDisplay(key,temp_pass, posArrPass, 0);				
				}
				if(key == 'C' || key == 'D'){
					InputKeyFail();
					begin_pass(temp_pass,6,-1);
				}
			}
			else{
				InputKeyDisplay(key, temp_pass, posArrPass, 1);
			}
		}
	}
	else{
		if(key == 'C' || key == 'D' || key == button_enter)
			return;
		if(key == button_deletekey){
			InputKeyDisplay(key,temp_pass,posArrPass,0);
		}
		else
			InputKeyDisplay(key,temp_pass,posArrPass,1);
	}
}



void clear_oled40(){
	for(int8_t i = 0; i< 6;i++){
		ssd1306_display_char(pos_oled[i],40, ' ', 12,1);
		ssd1306_refresh_gram();
	}
}




void initPassKey(int8_t *keypass){
	for(int8_t index = 0; index < 6; index++){
		keypass[index] = '1';
	}
}








