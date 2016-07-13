/*
 * strings.h
 *
 *  Created on: 1 июля 2016 г.
 *      Author: lihodey_i
 */

#ifndef VIDEO_H_
#define VIDEO_H_


#define ARRAY_SYMBOLS_OFFSET 32
#define RUS_ARRAY_OFFSRET 66

#define SPACE_WIDTH 1

#include "string.h"
#include "fonts.h"

//extern static const tChar Font_array[];

typedef struct
{
   uint32_t size;
   uint16_t xLength;		//bit (pixels)
   uint16_t yLength;			// byte (matrix)
   int16_t xOffset;
   int16_t yOffset;
   uint8_t *imageArrayPtr;
} image;

typedef struct
{
   uint32_t size;
   uint16_t xLength;			//bit (pixels)
   uint16_t yLength;			// byte (matrix)
   uint8_t *bufferArrayPtr;
} videoBuff;

typedef struct
{
	uint16_t visibleSymbols;
	uint16_t xMicroOffset;
	uint16_t yMicroOffset;
	uint16_t xOffset;
	uint16_t yOffset;
	uint8_t letterHight;
	uint8_t letterWidth;
	uint8_t *stringPtr;

} text;




void Video_put_string (text *textPtr, image *videoBuffPtr);
void Video_put_image (image *imgPtr, videoBuff *videoBuffPtr);
uint8_t Video_put_string_fonts (uint8_t *text, tChar *fonts, image *videoBuffPtr);
uint8_t Video_put_image_edge (image *imgPtr, videoBuff *videoBuffPtr);
void Video_move_image (image *imgPtr, videoBuff *videoBuffPtr, uint16_t xMove, uint16_t yMove);

#endif /* STRINGS_H_ */
