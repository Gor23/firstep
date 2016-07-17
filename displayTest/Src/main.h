/*
 * main.h
 *
 *  Created on: 31 мая 2016 г.
 *      Author: IGOR
 */

#ifndef MAIN_H_
#define MAIN_H_



#define xMatrix	2
#define yMatrix 2

#define TRANCIEVE_ARRAY_SIZE 	256*xMatrix*yMatrix
#define RECIEVE_BUFFER_SIZE 	10

#define TEXT_BUF_SIZE 512

#define TIMER_1_STOP_VALUE	50
#define TIMER_2_STOP_VALUE	60

extern volatile uint32_t timer1;
extern volatile uint32_t timer2;

#endif /* MAIN_H_ */
