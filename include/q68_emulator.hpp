/*
 * Copyright (c) 2022 Graeme Gregory
 *
 * SPDX: GPL-2.0-only
 */

namespace emulator {

void q68LoadFile(std::string name, uint8_t *addr, size_t fsize = 0);
int q68MainLoop(void *ptr);
void q68AllocateMemory(void);
uint32_t cycles(void);

extern uint8_t *q68MemorySpace;
extern uint8_t *q68ScreenSpace;

extern uint32_t msClk;
extern bool doIrq;

extern uint32_t cycleNextEvent;

} // namespace emulator
