/*
 * strings.h
 *
 *  Created on: 1 ���� 2016 �.
 *      Author: lihodey_i
 */

#ifndef VIDEO_H_
#define VIDEO_H_


#define ARRAY_SYMBOLS_OFFSET 32
#define RUS_ARRAY_OFFSRET 66


#define SPACE_WIDTH 1

#include "string.h"
#include "fonts.h"
#include "images.h"

//extern static const tChar Font_array[];


typedef struct
{
   uint16_t size;
   uint16_t visibleRightEdge;	//visible to
   uint16_t visibleLeftEdge;	//visible from
   uint16_t xLength;			//bit (pixels)
   uint16_t yLength;			//byte (matrix)
   int16_t xOffset;				//x offset in bit
   int16_t yOffset;				//y offset in byte
   uint8_t *imageArrayPtr;		//pointer to array
} image;

typedef struct
{
   uint16_t size;
   uint16_t xLength;			//bit (pixels)
   uint16_t yLength;			// byte (matrix)
   int16_t xOffset;
   int16_t yOffset;
   uint8_t *bufferArrayPtr;
} videoBuff;

typedef struct
{
	uint16_t xMicroOffset;
	uint16_t yMicroOffset;
	uint16_t xOffset;
	uint16_t yOffset;
	uint8_t letterHight;
	uint8_t letterWidth;
	uint8_t *stringPtr;
} text;

typedef struct
{
	uint16_t visibleSymbols;
	uint16_t visibleRightEdge;
	uint16_t visibleLeftEdge;
	uint16_t xOffset;
	uint16_t yOffset;
	uint8_t *stringPtr;
} textBuff;

typedef struct
{
	//image formImage;
	uint16_t score1XOffset;
	uint16_t scoreYOffset;
	uint16_t score2XOffset;
	uint16_t command1XOffset;;
	uint16_t command2XOffset;
	uint16_t commandyOffset;
	const tChar *commandsFont;
	const tChar *scoreFont;
	uint8_t *score1Ptr;
	uint8_t *score2Ptr;
	uint8_t *command1Ptr;
	uint8_t *command2Ptr;
} scoreForm;







void Video_put_string (text *textPtr, image *videoBuffPtr);
void Video_put_image (image *imgPtr, videoBuff *videoBuffPtr);
uint8_t *Video_put_string_fonts (uint8_t *text, const tChar *fonts, image *videoBuffPtr);
void Video_put_and_move_string (uint8_t *text, const tChar *fonts, image *videoBuffPtr);
uint8_t Video_put_image_edge (image *imgPtr, videoBuff *videoBuffPtr);
void Video_move_image (image *imgPtr, videoBuff *videoBuffPtr, uint16_t xMove, uint16_t yMove);
uint8_t Video_put_gif (imageGif *imgPtr, videoBuff *videoBuffPtr);

#endif /* STRINGS_H_ */
