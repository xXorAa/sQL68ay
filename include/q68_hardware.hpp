/*
 * Copyright (c) 2022 Graeme Gregory
 *
 * SPDX: GPL-2.0-only
 */
#pragma once

#include <cstdint>
#include <queue>
#include <SDL.h>

// Some macros for IO bytes to 16/32
#define BytesToU16(a,b) (           \
      (uint16_t)(a) << 8            \
    | (uint16_t)(b)                 \
)

#define BytesToU32(a,b,c,d) (       \
      (uint32_t)(a) << 24           \
    | (uint32_t)(b) << 16           \
    | (uint32_t)(c) << 8            \
    | (uint32_t)(d)                 \
)

#define U16Byte(a,b) (              \
    (uint8_t)(b >> (8 * (1 - a)))   \
)

#define U32Byte(a,b) (              \
    (uint8_t)(b >> (8 * (3 - a)))   \
)

namespace emulator {

extern uint8_t q68_mc_stat;
extern uint8_t q68_pc_intr;
extern uint8_t q68_kbd_status;
extern uint8_t q68_q68_dmode;

// time offset for RTC
constexpr uint32_t qdos_time = (9*365+2)*86400;

// keyboard lock and queue
extern SDL_SpinLock q68_kbd_lock;
extern std::queue<uint8_t> q68_kbd_queue;

constexpr uint32_t pc_clock     = 0x18000;

constexpr uint32_t pc_tctrl     = 0x18002;

constexpr uint32_t pc_ipcwr     = 0x18003;

constexpr uint32_t pc_mctrl     = 0x18020;

constexpr uint32_t pc_ipcrd     = 0x18020;

constexpr uint32_t pc_intr      = 0x18021;
constexpr uint8_t pc_intrg      = (1 << 0);
constexpr uint8_t pc_intri      = (1 << 1);
constexpr uint8_t pc_intrf      = (1 << 3);
constexpr uint32_t pc_trak1     = 0x18022; //byte microdrive read track 1
constexpr uint32_t pc_trak2     = 0x18023; //byte microdrive read track 2

constexpr uint32_t mc_stat      = 0x18063;
constexpr uint8_t mc_stat_mode  = 1 << 3;

constexpr uint32_t q68_timer    = 0x1c060;

constexpr uint32_t kbd_code     = 0x1c140;

constexpr uint32_t kbd_unlock   = 0x1c144;
constexpr uint8_t kbd_ackn      = 1 << 0;

constexpr uint32_t kbd_status   = 0x1c148;
constexpr uint8_t kbd_rcv       = 1 << 0;
constexpr uint8_t kbd_isint     = 1 << 7;

constexpr uint32_t q68_dmode     = 0xff000018;

unsigned int q68_read_hw_8(unsigned int addr);
void q68_write_hw_8(unsigned int addr, unsigned int val);
unsigned int q68_read_hw_16(unsigned int addr);
void q68_write_hw_16(unsigned int addr, unsigned int val);
unsigned int q68_read_hw_32(unsigned int addr);
void q68_write_hw_32(unsigned int addr, unsigned int val);

} // namespace emulator