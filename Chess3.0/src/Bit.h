#pragma once
#include <cstdint>
#include <cstdlib>
#define DEBUG 0
#define rand64bit (((long long)std::rand()<<48) | ((long long)std::rand()<<32) | ((long long)std::rand()<<16) | ((long long)std::rand()))

#define ISSET(bitboard, pos) (bitboard & (1ULL << pos))
#define SET(bitboard, pos) (bitboard |= (1ULL << pos))
#define UNSET(bitboard, pos) (bitboard &= ~(1ULL << pos))

unsigned char reverse(unsigned char b);

int popCount8bit(uint8_t x);

int popCount64bit(uint64_t x);
