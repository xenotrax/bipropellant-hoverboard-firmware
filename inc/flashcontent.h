/*
* This file is part of the hoverboard-firmware-hack project.
*
* Copyright (C) 2018 Simon Hailes <btsimonh@googlemail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// this file defines the structure to store variables in the flash
// e.g. PID constants
// such that they can be configured through protocol.c
// and saved to flash

// a copy is kept in ram.
// a pointer to each variable alnog with methods for modification is kept in a structure in protocol

// to write to it, use protocol to write to magic, this will commit content to flash

// decimal to make it easier to type!
#pragma once

#define CURRENT_MAGIC 1235

#pragma pack(push, 2)
typedef struct tag_CONFIG_PID{
    unsigned short PositionKpx100; // pid params for Position
    unsigned short PositionKix100;
    unsigned short PositionKdx100;
    unsigned short PositionPWMLimit; // e.g. 200

    unsigned short SpeedKpx100; // pid params for Speed
    unsigned short SpeedKix100;
    unsigned short SpeedKdx100;
    unsigned short SpeedPWMIncrementLimit; // e.g. 20
} CONFIG_PID;
#pragma pack(pop)

#pragma pack(push, 2)
typedef struct tag_CONFIG_HOVERBOARD{
    unsigned short HoverboardEnable; // non zero to enable
    unsigned short calibration_0;
    unsigned short calibration_1;
    unsigned short HoverboardPWMLimit;
} CONFIG_HOVERBOARD;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct tag_CONFIG_MOTORS{
  char motor1_invert;
  char motor2_invert;
  unsigned short MaxCurrLim;
} CONFIG_MOTORS;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct tag_CONFIG_ANALOGINPUT{
  unsigned short adc1_min;
  unsigned short adc1_zero;
  unsigned short adc1_max;
  float adc1_mult_neg;
  float adc1_mult_pos;
  unsigned short adc1_button_threshold;

  unsigned short adc2_min;
  unsigned short adc2_zero;
  unsigned short adc2_max;
  float adc2_mult_neg;
  float adc2_mult_pos;
  unsigned short adc2_button_threshold;

  unsigned short chan1_off_start;
  unsigned short chan1_off_end;
  float chan1_off_filter;

  char switch_channels;
  char chan2_reverse;
} CONFIG_ANALOGINPUT;
#pragma pack(pop)

#pragma pack(push, 2) // all variables of type unsigned short (2 bytes)
typedef struct tag_FLASH_CONTENT{
    unsigned short magic;  // write this with CURRENT_MAGIC to commit to flash
    CONFIG_PID cfg_pid;
    CONFIG_HOVERBOARD cfg_hoverboard;
    CONFIG_MOTORS cfg_motors;
    CONFIG_ANALOGINPUT cfg_analoginput;
} FLASH_CONTENT;
#pragma pack(pop)

extern FLASH_CONTENT FlashContent;

extern const FLASH_CONTENT FlashDefaults;

#ifndef FLASH_DEFAULT_HOVERBOARD_ENABLE
#define FLASH_DEFAULT_HOVERBOARD_ENABLE 0
#endif

#define FLASH_DEFAULTS { CURRENT_MAGIC,    50, 50, 0, 1000,    20, 10, 0, 20,    1500,   FLASH_DEFAULT_HOVERBOARD_ENABLE, 0, 0, 1000 }
