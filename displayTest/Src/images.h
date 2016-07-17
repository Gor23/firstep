/*
 * images.h
 *
 *  Created on: 17 июля 2016 г.
 *      Author: IGOR
 */

#ifndef IMAGES_H_
#define IMAGES_H_

#include <stdint.h>

typedef struct
{
   uint16_t frames;
   uint16_t frameSize;
   uint16_t xLength;			//bit (pixels)
   uint16_t yLength;			//byte (matrix)
   int16_t xOffset;				//x offset in bit
   int16_t yOffset;				//y offset in byte
   const uint8_t *imageArrayPtr;		//pointer to array
} imageGif;

extern imageGif goalGif;
extern imageGif logoGif;

#endif /* IMAGES_H_ */
