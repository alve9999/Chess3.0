#pragma once
#include <cstdint>
#include "Bit.h"
#include "Board.h"
#include "Moves.h"
struct entry {
    uint64_t key;
    int depth;
    int flags;
    int value;
};

void gen_random(uint64_t(&random_key)[769]);
class TranspositionTable {
public:
    uint64_t size;
	entry* Table;
	TranspositionTable(uint64_t size);

    void store(int depth, int val, int flag, uint64_t key);
    int probe_hash(int depth, int alpha, int beta, uint64_t key);
};


uint64_t update_hash(uint64_t key, Move move, bool colour);
uint64_t create_hash(bool colour);

extern uint64_t random_key[769];
extern TranspositionTable TT;

