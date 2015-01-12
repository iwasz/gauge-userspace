/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

const unsigned int VENDOR_ID = 0x20a0;
const unsigned int PRODUCT_ID = 0x41fe;

//const unsigned int VENDOR_ID = 0x2047;
//const unsigned int PRODUCT_ID = 0x0302;

const size_t OUTPUT_DATA_SIZE = 2;
const unsigned int OUTPUT_DATA_ENDPOINT = 0x03;

const uint16_t USTEPS_PER_CYCLE = 128;
const uint16_t TEETH = 5;
const uint16_t TOTAL_USTEPS = USTEPS_PER_CYCLE * TEETH;

#endif /* CONSTANTS_H_ */
