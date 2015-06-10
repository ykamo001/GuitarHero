/*
 * Final_Project.c
 *
 * Created: 6/1/2015 6:00:03 PM
 *  Author: YASH
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "C:\Users\YASH\Documents\College\CS120B\includes\bit.h"
#include "C:\Users\YASH\Documents\College\CS120B\includes\timer.h"
#include "C:\Users\YASH\Documents\College\CS120B\includes\io.c"
#include <stdio.h>
#include <stdlib.h>

// Returns '\0' if no key pressed,
// Else returns char '1', '2', ... '9', 'A', ...
// If multiple keys pressed, returns leftmost-topmost one
// Keypad must be connected to port C
/* Keypad arrangement:

	PC4 PC5 PC6 PC7
	col 1 2 3 4
row
PC0 1 1 | 2 | 3 | A
PC1 2 4 | 5 | 6 | B
PC2 3 7 | 8 | 9 | C
PC3 4 * | 0 | # | D
*/
unsigned char GetKeypadKey() {
	// Check keys in col 1
	// Enable col 4 with 0, disable others with 1’s
	// The delay allows PORTC to stabilize before checking
	PORTA = 0xEF;
	asm("nop");
	if (GetBit(PINA,0)==0) { return('1'); }
	if (GetBit(PINA,1)==0) { return('4'); }
	if (GetBit(PINA,2)==0) { return('7'); }
	if (GetBit(PINA,3)==0) { return('*'); }
	// Check keys in col 2
	// Enable col 5 with 0, disable others with 1’s
	// The delay allows PORTC to stabilize before checking
	PORTA = 0xDF;
	asm("nop");
	if (GetBit(PINA,0)==0) { return('2'); }
	if (GetBit(PINA,1)==0) { return('5'); }
	if (GetBit(PINA,2)==0) { return('8'); }
	if (GetBit(PINA,3)==0) { return('0'); }
	// ... *****FINISH*****
	// Check keys in col 3
	// Enable col 6 with 0, disable others with 1’s
	// The delay allows PORTC to stabilize before checking
	PORTA = 0xBF;
	asm("nop");
	if (GetBit(PINA,0)==0) { return('3'); }
	if (GetBit(PINA,1)==0) { return('6'); }
	if (GetBit(PINA,2)==0) { return('9'); }
	if (GetBit(PINA,3)==0) { return('#'); }
	// ... *****FINISH*****
	// Check keys in col 4
	PORTA = 0x7F;
	asm("nop");
	if (GetBit(PINA,0)==0) { return('A'); }
	if (GetBit(PINA,1)==0) { return('B'); }
	if (GetBit(PINA,2)==0) { return('C'); }
	if (GetBit(PINA,3)==0) { return('D'); }
	// ... *****FINISH*****
	return('\0'); // default value
}

/*void matrix_clock_off(char element)
{
	if(element > 0)
	{
		PORTD = SetBit(PORTD, 2, 0);
	}
	else if(element < 0)
	{
		PORTD = SetBit(PORTD, 5, 0);
	}
}

void matrix_clock_on(char element)
{
	if(element > 0)
	{
		PORTD = SetBit(PORTD, 2, 1);
	}
	else if(element < 0)
	{
		PORTD = SetBit(PORTD, 5, 1);
	}
}

void set_latch(char element)
{
	if(element > 0)
	{
		PORTD = SetBit(PORTD, 1, 1);
	}
	else if(element < 0)
	{
		PORTD = SetBit(PORTD, 4, 1);
	}
}

void unset_latch(char element)
{
	if(element > 0)
	{
		PORTD = SetBit(PORTD, 1, 0);
	}
	else if(element < 0)
	{
		PORTD = SetBit(PORTD, 4, 0);
	}
}

void set_matrix_element(char element, char val)
{
	matrix_clock_on(element);
	if(element > 0)
	{
		PORTD = SetBit(PORTD, 0, val);
	}
	else if(element < 0)
	{
		PORTD = SetBit(PORTD, 3, val);
	}
	matrix_clock_off(element);
}

void initial_matrix(char element, char on_off)
{
	set_latch(element);
	for(unsigned char i = 0; i < 8; ++i)
	{
		set_matrix_element(element, on_off);
	}
	unset_latch(element);
}*/

unsigned char x;
unsigned char lives;
long level = 1;
unsigned char entered = 0;
unsigned char start = 0;
unsigned char correct = 0x00;
long occurances = 1;
long occ_counter = 0;
unsigned char active = 0x00;
int r;
unsigned int myseed = 0x00;
unsigned long int willchange = 200;
unsigned char timework = 0;
unsigned char lost = 0;
unsigned char changed = 0;
short score = 0;
short maxscore = 0;
enum keysms {wait, exec} keysm;
enum LCDstates{init, menu, modify} LCDstate;
enum generatePos{gameInit, gameBegin, gameDo} randGen;


int SMTick1(int state)
{
	switch(keysm)
	{
		case -1:
			keysm = wait;
			break;
		case wait:
			x = GetKeypadKey();
			keysm = exec;
			break;
		case exec:
			break;
		default:
			break;
	}
	
	switch(keysm)
	{
		case wait:
			break;
		case exec:
			if(x !='\0')
			{
				if(x == '1')
				{
					entered = 1;
				}
				else if(x == '2')
				{
					entered = 2;
				}
				else if(x == '3')
				{
					entered = 3;
				}
				else if(x == '4')
				{
					entered = 4;
				}
				else if(x == '5')
				{
					entered = 5;
				}
				else if(x == '6')
				{
					entered = 6;
				}
				else if(x == '7')
				{
					entered = 7;
				}
				else if(x == '8')
				{
					entered = 8;
				}
				else if(x == '#')
				{
					entered = 0;
				}
				else
				{
					entered = 9;
				}
				correct = 0x00;
				if(start == 1)
				{
					if((entered != 9) && ( entered != 0))
					{
						if(!GetBit(PORTB, entered-1))
						{
							correct = 0x01;
						}
						else
						{
							correct = 0x02;
						}
					}
					else if(entered == 9)
					{
						correct = 0x01;
					}
					else if(entered == 0)
					{
						start = 0;
						lives = 9;
						level = 1;
						start = 0;
						lost = 1;
						score = 0;
						occurances = 5;
						changed = 0;
						occ_counter = occurances;
						willchange = 200;
						PORTB = 0x00;
						LCDstate = init;
						randGen = gameInit;
					}
				}
			}
			else
			{
				correct = 0x00;
			}
			keysm = wait;
			break;
		default:
			break;
	}
	return state;
}

unsigned char loc;
int LCDSM(int state)
{
	switch(LCDstate)
	{
		case init:
			PORTD = SetBit(PORTD, 0, 0);
			PORTD = SetBit(PORTD, 1, 0);
			PORTD = SetBit(PORTD, 2, 0);
			PORTD = SetBit(PORTD, 3, 1);
			PORTD = SetBit(PORTD, 4, 0);
			PORTD = SetBit(PORTD, 5, 0);
			loc = 1;
			lives = 9;
			level = 1;
			start = 0;
			changed = 0;
			occurances = 5;
			score = 0;
			occ_counter = occurances;
			willchange = 200;
			PORTB = 0x00;
			LCDstate = menu;
			LCD_init();
			LCD_DisplayString(1, "Press * to begingame, # to reset", 1);
			break;
		case menu:
			myseed++;
			if(x == '*')
			{
				LCD_init();
				LCD_DisplayString(1, "Score:", 0);
				short temp = 10000;
				short scoretemp = score;
				char printtemp = 0;
				while(scoretemp > 0)
				{
					scoretemp = scoretemp - temp;
					if(scoretemp >= 0)
					{
						printtemp = printtemp + 1;
					}
				}
				LCD_Cursor(7);
				LCD_WriteData(printtemp + 48);
				if(scoretemp < 0)
				{
					scoretemp = scoretemp + temp;
				}
				temp = 1000;
				printtemp = 0;
				while(scoretemp > 0)
				{
					scoretemp = scoretemp - temp;
					if(scoretemp >= 0)
					{
						printtemp = printtemp + 1;
					}
				}
				LCD_Cursor(8);
				LCD_WriteData(printtemp + 48);
				if(scoretemp < 0)
				{
					scoretemp = scoretemp + temp;
				}
				temp = 100;
				printtemp = 0;
				while(scoretemp > 0)
				{
					scoretemp = scoretemp - temp;
					if(scoretemp >= 0)
					{
						printtemp = printtemp + 1;
					}
				}
				LCD_Cursor(9);
				LCD_WriteData(printtemp + 48);
				if(scoretemp < 0)
				{
					scoretemp = scoretemp + temp;
				}
				temp = 10;
				printtemp = 0;
				while(scoretemp > 0)
				{
					scoretemp = scoretemp - temp;
					if(scoretemp >= 0)
					{
						printtemp = printtemp + 1;
					}
				}
				LCD_Cursor(10);
				LCD_WriteData(printtemp + 48);
				if(scoretemp < 0)
				{
					scoretemp = scoretemp + temp;
				}
				temp = 1;
				printtemp = 0;
				while(scoretemp > 0)
				{
					scoretemp = scoretemp - temp;
					if(scoretemp >= 0)
					{
						printtemp = printtemp + 1;
					}
				}
				LCD_Cursor(11);
				LCD_WriteData(printtemp + 48);
				LCD_DisplayString(17, "Level:", 0);
				loc = 23;
				LCD_Cursor(loc);
				LCD_WriteData(level + 48);
				LCD_DisplayString(25, "Lives:", 0);
				loc = 31;
				LCD_Cursor(loc);
				LCD_WriteData(lives + 48);
				start = 1;
				srand(myseed);
				myseed = 0;
				LCDstate = modify;
			}
			else
			{
				LCDstate = menu;
			}
			break;
		case modify:
			if(start == 1)
			{
				if(correct == 0x01)
				{
					if(lives > 0)
					{
						lives = lives - 1;
						LCD_Cursor(31);
						LCD_WriteData(lives + 48);
					}
					if(score >= 10)
					{
						score = score - 10;
					}
					short temp = 10000;
					short scoretemp = score;
					char printtemp = 0;
					while(scoretemp > 0)
					{
						scoretemp = scoretemp - temp;
						if(scoretemp >= 0)
						{
							printtemp = printtemp + 1;
						}
					}
					LCD_Cursor(7);
					LCD_WriteData(printtemp + 48);
					if(scoretemp < 0)
					{
						scoretemp = scoretemp + temp;
					}
					temp = 1000;
					printtemp = 0;
					while(scoretemp > 0)
					{
						scoretemp = scoretemp - temp;
						if(scoretemp >= 0)
						{
							printtemp = printtemp + 1;
						}
					}
					LCD_Cursor(8);
					LCD_WriteData(printtemp + 48);
					if(scoretemp < 0)
					{
						scoretemp = scoretemp + temp;
					}
					temp = 100;
					printtemp = 0;
					while(scoretemp > 0)
					{
						scoretemp = scoretemp - temp;
						if(scoretemp >= 0)
						{
							printtemp = printtemp + 1;
						}
					}
					LCD_Cursor(9);
					LCD_WriteData(printtemp + 48);
					if(scoretemp < 0)
					{
						scoretemp = scoretemp + temp;
					}
					temp = 10;
					printtemp = 0;
					while(scoretemp > 0)
					{
						scoretemp = scoretemp - temp;
						if(scoretemp >= 0)
						{
							printtemp = printtemp + 1;
						}
					}
					LCD_Cursor(10);
					LCD_WriteData(printtemp + 48);
					if(scoretemp < 0)
					{
						scoretemp = scoretemp + temp;
					}
					temp = 1;
					printtemp = 0;
					while(scoretemp > 0)
					{
						scoretemp = scoretemp - temp;
						if(scoretemp >= 0)
						{
							printtemp = printtemp + 1;
						}
					}
					LCD_Cursor(11);
					LCD_WriteData(printtemp + 48);
					LCDstate = modify;
				}
				else if(correct == 0x02)
				{
					PORTB = SetBit(PORTB, entered-1, 0);
					active = SetBit(active, entered-1, 0);
					score = score + 10;
					short temp = 10000;
					short scoretemp = score;
					char printtemp = 0;
					while(scoretemp > 0)
					{
						scoretemp = scoretemp - temp;
						if(scoretemp >= 0)
						{
							printtemp = printtemp + 1;
						}
					}
					LCD_Cursor(7);
					LCD_WriteData(printtemp + 48);
					if(scoretemp < 0)
					{
						scoretemp = scoretemp + temp;
					}
					temp = 1000;
					printtemp = 0;
					while(scoretemp > 0)
					{
						scoretemp = scoretemp - temp;
						if(scoretemp >= 0)
						{
							printtemp = printtemp + 1;
						}
					}
					LCD_Cursor(8);
					LCD_WriteData(printtemp + 48);
					if(scoretemp < 0)
					{
						scoretemp = scoretemp + temp;
					}
					temp = 100;
					printtemp = 0;
					while(scoretemp > 0)
					{
						scoretemp = scoretemp - temp;
						if(scoretemp >= 0)
						{
							printtemp = printtemp + 1;
						}
					}
					LCD_Cursor(9);
					LCD_WriteData(printtemp + 48);
					if(scoretemp < 0)
					{
						scoretemp = scoretemp + temp;
					}
					temp = 10;
					printtemp = 0;
					while(scoretemp > 0)
					{
						scoretemp = scoretemp - temp;
						if(scoretemp >= 0)
						{
							printtemp = printtemp + 1;
						}
					}
					LCD_Cursor(10);
					LCD_WriteData(printtemp + 48);
					if(scoretemp < 0)
					{
						scoretemp = scoretemp + temp;
					}
					temp = 1;
					printtemp = 0;
					while(scoretemp > 0)
					{
						scoretemp = scoretemp - temp;
						if(scoretemp >= 0)
						{
							printtemp = printtemp + 1;
						}
					}
					LCD_Cursor(11);
					LCD_WriteData(printtemp + 48);
				}
				if(lives <= 0)
				{
					LCD_DisplayString(17, "You Lost!       ", 0);
					delay_ms(300);
					PORTB = 0x00;
					start = 0;
					lost = 1;
					LCDstate = init;
				}
			}
			else
			{
				LCDstate = menu;
			}
			if(changed == 1)
			{
				LCD_init();
				LCD_DisplayString(1, "Score:", 0);
				short temp = 10000;
				short scoretemp = score;
				char printtemp = 0;
				while(scoretemp > 0)
				{
					scoretemp = scoretemp - temp;
					if(scoretemp >= 0)
					{
						printtemp = printtemp + 1;
					}
				}
				LCD_Cursor(7);
				LCD_WriteData(printtemp + 48);
				if(scoretemp < 0)
				{
					scoretemp = scoretemp + temp;
				}
				temp = 1000;
				printtemp = 0;
				while(scoretemp > 0)
				{
					scoretemp = scoretemp - temp;
					if(scoretemp >= 0)
					{
						printtemp = printtemp + 1;
					}
				}
				LCD_Cursor(8);
				LCD_WriteData(printtemp + 48);
				if(scoretemp < 0)
				{
					scoretemp = scoretemp + temp;
				}
				temp = 100;
				printtemp = 0;
				while(scoretemp > 0)
				{
					scoretemp = scoretemp - temp;
					if(scoretemp >= 0)
					{
						printtemp = printtemp + 1;
					}
				}
				LCD_Cursor(9);
				LCD_WriteData(printtemp + 48);
				if(scoretemp < 0)
				{
					scoretemp = scoretemp + temp;
				}
				temp = 10;
				printtemp = 0;
				while(scoretemp > 0)
				{
					scoretemp = scoretemp - temp;
					if(scoretemp >= 0)
					{
						printtemp = printtemp + 1;
					}
				}
				LCD_Cursor(10);
				LCD_WriteData(printtemp + 48);
				if(scoretemp < 0)
				{
					scoretemp = scoretemp + temp;
				}
				temp = 1;
				printtemp = 0;
				while(scoretemp > 0)
				{
					scoretemp = scoretemp - temp;
					if(scoretemp >= 0)
					{
						printtemp = printtemp + 1;
					}
				}
				LCD_Cursor(11);
				LCD_WriteData(printtemp + 48);
				LCD_DisplayString(17, "Level:", 0);
				loc = 23;
				LCD_Cursor(loc);
				LCD_WriteData(level + 48);
				LCD_DisplayString(25, "Lives:", 0);
				loc = 31;
				LCD_Cursor(loc);
				LCD_WriteData(lives + 48);
				timework = 1;
				changed = 0;
			}
			if(start == 1) {
				if(level == 1)
				{
					maxscore = 50;
				}
				else if(level == 2)
				{
					maxscore = 150;
				}
				else if(level == 3)
				{
					maxscore = 300;
				}
				else if(level == 4)
				{
					maxscore = 500;
				}
				else if(level == 5)
				{
					maxscore = 750;
				}
				else if(level == 6)
				{
					maxscore = 1050;
				}
				else if(level == 7)
				{
					maxscore = 1400;
				}
				else if(level == 8)
				{
					maxscore = 1800;
				}
				else if(level == 9)
				{
					maxscore = 2250;
				}
				short placeholder = maxscore/4;
				if((score <= maxscore) && (score > (maxscore - placeholder)))
				{
					PORTD = SetBit(PORTD, 0, 0);
					PORTD = SetBit(PORTD, 1, 1);
					PORTD = SetBit(PORTD, 2, 0);
					PORTD = SetBit(PORTD, 3, 0);
					PORTD = SetBit(PORTD, 4, 0);
					PORTD = SetBit(PORTD, 5, 0);
				}
				else if((score <= (maxscore - placeholder)) && (score > (maxscore - (2*placeholder))))
				{
					PORTD = SetBit(PORTD, 0, 1);
					PORTD = SetBit(PORTD, 1, 0);
					PORTD = SetBit(PORTD, 2, 0);
					PORTD = SetBit(PORTD, 3, 0);
					PORTD = SetBit(PORTD, 4, 0);
					PORTD = SetBit(PORTD, 5, 1);
				}
				else if((score <= (maxscore - (2*placeholder))) && (score > (maxscore - (3*placeholder))))
				{
					PORTD = SetBit(PORTD, 0, 1);
					PORTD = SetBit(PORTD, 1, 0);
					PORTD = SetBit(PORTD, 2, 1);
					PORTD = SetBit(PORTD, 3, 1);
					PORTD = SetBit(PORTD, 4, 0);
					PORTD = SetBit(PORTD, 5, 0);
				}
				else
				{
					PORTD = SetBit(PORTD, 0, 0);
					PORTD = SetBit(PORTD, 1, 0);
					PORTD = SetBit(PORTD, 2, 0);
					PORTD = SetBit(PORTD, 3, 0);
					PORTD = SetBit(PORTD, 4, 1);
					PORTD = SetBit(PORTD, 5, 1);
				}
			}
			else
			{
				PORTD = SetBit(PORTD, 0, 0);
				PORTD = SetBit(PORTD, 1, 0);
				PORTD = SetBit(PORTD, 2, 0);
				PORTD = SetBit(PORTD, 3, 1);
				PORTD = SetBit(PORTD, 4, 0);
				PORTD = SetBit(PORTD, 5, 0);
			}
			break;
		default:
			break;
	}
	return state;
}

unsigned char turn = 0;
void thegame()
{
	switch(randGen)
	{
		case gameInit:
			if(start == 1)
			{
				randGen = gameBegin;
			}
			else
			{
				randGen = gameInit;
			}
			break;
		case gameBegin:
			if(start == 1)
			{
				occurances = (5 * level);
				occ_counter = occurances;
				randGen = gameDo;
			}
			else
			{
				randGen = gameInit;
			}
			break;
		case gameDo:
			if (start == 1)
			{
				if(occ_counter > 0)
				{
					if(PORTB != 0xFF)
					{
						r = rand() % 8;
						while(GetBit(PORTB, r))
						{
							r = rand() % 8;
						}
						PORTB = SetBit(PORTB, r, 1);
						active = SetBit(active, r, 1);
						occ_counter = occ_counter - 1;
						randGen = gameDo;
					}
					else
					{
						LCD_DisplayString(17, "You Lost!       ", 0);
						delay_ms(300);
						PORTB = 0x00;
						lost = 1;
						start = 0;
						randGen = gameInit;
						LCDstate = init;
					}
				}
				else
				{
					if(turn <= 4) 
					{
						if(PORTB == 0x00)
						{
							if(level < 9) {
								LCD_init();
								LCD_DisplayString(1, "You beat the    level!", 0);
								delay_ms(300);
								if(level < 9)
								{
									level++;
									turn = 0;
									changed = 1;
									randGen = gameInit;
								}
							}
							else
							{
								LCD_DisplayString(1, "You Won!        ", 0);
								delay_ms(300);
								PORTB = 0x00;
								start = 0;
								turn = 0;
								lost = 1;
								randGen = gameInit;
								LCDstate = init;
							}
						}
					}
					else {
						LCD_DisplayString(17, "You Lost!       ", 0);
						delay_ms(300);
						PORTB = 0x00;
						start = 0;
						turn = 0;
						level = 1;
						lost = 1;
						randGen = gameInit;
						LCDstate = init;
					}
					turn++;
				}
			}
			else
			{
				randGen = gameInit;
			}
			break;
		default:
			break;
	}
}

typedef struct _task {
//Task's current state, period, and the time elapsed
// since the last tick
signed char state;
unsigned long int period;
unsigned long int elapsedTime;
//Task tick function
int (*TickFct)(int);
} task;


int main(void)
{
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	DDRA = 0xF0; PORTA = 0x0F;
	DDRC = 0xFF; PORTC = 0x00;
	unsigned long int SMTick1_calc = 50;
	unsigned long int SMTick2_calc = 50;
	unsigned long int SMTick3_calc = willchange;
	unsigned long int tmpGCD = 1;
	unsigned long int GCD = tmpGCD;
	unsigned long int SMTick1_period = SMTick1_calc;
	unsigned long int SMTick2_period = SMTick2_calc;
	unsigned long int SMTick3_period = SMTick3_calc;
	static task task1, task2, task3;
	task *tasks[] = { &task1, &task2, &task3 };
	const unsigned short numTasks =	sizeof(tasks)/sizeof(task*);
	task1.state = -1;
	task1.period = SMTick1_period;
	task1.elapsedTime = SMTick1_period;
	task1.TickFct = &SMTick1;
	
	task2.state = init;
	task2.period = SMTick2_period;
	task2.elapsedTime = SMTick2_period;
	task2.TickFct = &LCDSM;
	
	task3.state = gameInit;
	task3.period = SMTick3_period;
	task3.elapsedTime = SMTick3_period;
	task3.TickFct = &thegame;
	TimerSet(GCD);
	TimerOn();
	unsigned short i;
	while(1) {
		// Scheduler code
		for ( i = 0; i < numTasks; i++ ) {
			// Task is ready to tick
			if ( tasks[i]->elapsedTime ==
			tasks[i]->period ) {
				// Setting next state for task
				tasks[i]->state =
				tasks[i]->TickFct(tasks[i]->state);
				// Reset elapsed time for next tick.
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
			if(timework == 1)
			{
				willchange = 200 - (3*occurances);
				task3.period = willchange;
				timework = 0;
				if(level >= 4)
				{
					task1.period = 40;
					task2.period = 40;
				}
			}
			if(lost == 1)
			{
				willchange = 200;
				task3.period = willchange;
				lost = 0;
				task1.period = 50;
				task2.period = 50;
			}
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}
	// Error: Program should not exit!
	return 0;
}