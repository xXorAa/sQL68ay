/*
 * Copyright (c) 2022 Graeme Gregory
 *
 * SPDX: GPL-2.0-only
 */

#include <cstdint>
#include <queue>

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

constexpr uint32_t pc_ipcrd     = 0x18020;

constexpr uint32_t pc_intr      = 0x18021;
constexpr uint8_t pc_intrf      = 0x08;

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