/*
 * strings.h
 *
 *  Created on: 1 ���� 2016 �.
 *      Author: lihodey_i
 */

#ifndef STRINGS_H_
#define STRINGS_H_

#define FONT_SIZE 5 // ���� � ������� ���� 1 ������ �����������
#define ARRAY_SYMBOLS_OFFSET 32
#define RUS_ARRAY_OFFSRET 66

#include "inttypes.h"
#include "string.h"



void Strings_put_string (char *inputString, char *outputArray, uint32_t xOffset, uint32_t yOffset, uint32_t bytesInRow);


#endif /* STRINGS_H_ */
