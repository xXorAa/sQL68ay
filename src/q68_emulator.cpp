/*
 * Copyright (c) 2022 Graeme Gregory
 *
 * SPDX: GPL-2.0-only
 */

#include <boost/endian/conversion.hpp>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <SDL.h>
#include <string>

#include "m68k.h"
#include "q68_events.hpp"
#include "q68_memory.hpp"

namespace emulator {

uint8_t *q68MemorySpace;

void q68AllocateMemory()
{
    q68MemorySpace = new uint8_t[32_MiB];
}

void q68LoadFile(std::string name, uint8_t *addr)
{
    //if (name[0] == '~') {
    //    name.erase(0, 1);
    //    name.insert(0, "/");
    //    name.insert(0, homedir);
    //}

    std::filesystem::path p{name};
    auto size = std::filesystem::file_size(p);

    std::ifstream romFile(name, std::ios::binary);
    if (romFile.bad()) {
        throw std::runtime_error("File NOT Found");
    }
    romFile.read((char *)addr, size);
    romFile.close();
}

int q68MainLoop(void *ptr)
{
    q68LoadFile("Q68_SMSQ.bin", q68MemorySpace + 0x320000);

    m68k_set_cpu_type(M68K_CPU_TYPE_68000);
    m68k_init();
    m68k_pulse_reset();
    m68k_set_reg(M68K_REG_PC, 0x320000);

    uint64_t ticks = SDL_GetPerformanceFrequency() / 50;
    uint64_t then = SDL_GetPerformanceCounter();

    while(!exitLoop) {
        m68k_execute(100000);

        uint64_t now = SDL_GetPerformanceCounter();

        if ((now - then) > ticks) {
            then = (then + ticks);
            m68k_set_irq(2);
        }
    }

    return 0;
}

}

extern "C" {

    unsigned int m68k_read_memory_8(unsigned int address)
    {
        return emulator::q68MemorySpace[address];
    }

    unsigned int m68k_read_memory_16(unsigned int address)
    {
        uint16_t *wordAddr = (uint16_t *)&emulator::q68MemorySpace[address];
        return boost::endian::big_to_native(*wordAddr);
    }

    unsigned int  m68k_read_disassembler_16(unsigned int address)
    {
        uint16_t *wordAddr = (uint16_t *)&emulator::q68MemorySpace[address];
        return boost::endian::big_to_native(*wordAddr);
    }

    unsigned int m68k_read_memory_32(unsigned int address)
    {
        uint32_t *longAddr = (uint32_t *)&emulator::q68MemorySpace[address];
        return boost::endian::big_to_native(*longAddr);
    }

    unsigned int m68k_read_disassembler_32(unsigned int address)
    {
        uint32_t *longAddr = (uint32_t *)&emulator::q68MemorySpace[address];
        return boost::endian::big_to_native(*longAddr);
    }

    void m68k_write_memory_8(unsigned int address, unsigned int value)
    {
        emulator::q68MemorySpace[address] = value;
    }

    void m68k_write_memory_16(unsigned int address, unsigned int value)
    {
        uint16_t *wordAddr = (uint16_t *)&emulator::q68MemorySpace[address];
        *wordAddr = boost::endian::native_to_big((uint16_t)value);
    }

    void m68k_write_memory_32(unsigned int address, unsigned int value)
    {
        uint32_t *longAddr = (uint32_t *)&emulator::q68MemorySpace[address];
        *longAddr = boost::endian::native_to_big((uint32_t)value);
    }

}