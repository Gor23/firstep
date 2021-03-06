/*
 * main.h
 *
 *  Created on: 31 ��� 2016 �.
 *      Author: IGOR
 */

#ifndef MAIN_H_
#define MAIN_H_

#define UART_SPEED 256000

#define xMatrix	2
#define yMatrix 2

#define TRANCIEVE_ARRAY_SIZE 	256*xMatrix*yMatrix
#define RECIEVE_BUFFER_SIZE 	10


#define TEXT_BUF_SIZE 1024
#define COMM_TEXT_BUF_SIZE 256
#define STRING_BUF_SIZE 2048

#define TIMER_1_STOP_VALUE	100
#define TIMER_2_STOP_VALUE	200


enum modes {LOGO_MODE, SCORE_MODE, GOAL_MODE, STRING_MODE, WINNER_MODE};

extern volatile uint32_t timer1;
extern volatile uint32_t timer2;
extern volatile uint16_t timerStopValue;
extern volatile uint8_t ready;

#endif /* MAIN_H_ */
