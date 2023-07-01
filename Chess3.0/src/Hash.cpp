#include "Hash.h"
#include <cstdint>
#include "Bit.h"
#include <cassert>
#define HASH_CHECK DEBUG
#define UNKNOWN 989
TranspositionTable TT(640000);
uint64_t random_key[769];
void gen_random(uint64_t (&random_key)[769]) {
	for (int i = 0; i < 769; i++) {
		random_key[i] = rand64bit;
	}
}

TranspositionTable::TranspositionTable(uint64_t size) {
	this->size = size;
	this->Table = (entry*)malloc(size*sizeof(entry));
}

void TranspositionTable::store(int depth, float val, int flag, uint64_t key) {
	entry* node = &Table[key%size];
	node->depth = depth;
	node->value = val;
	node->flags = flag;
	node->key = key;
}

int TranspositionTable::probe_hash(int depth, float alpha, float beta, uint64_t key) {
	entry* node = &Table[key % size];
	if (node->key == key) {
		if (node->depth >= depth) {
			//exact
			if (node->flags == 0) {
				return node->value;
			}
			//alpha
			if (node->flags == 1 and node->value <= alpha) {
				return alpha;
			}
			//beta
			if (node->flags == 2 and node->value >= beta) {
				return beta;
			}
		}
	}
	return UNKNOWN;
}

uint64_t update_hash(uint64_t key, Move move,bool colour) {
	key ^= random_key[768];
	key ^= random_key[384 * colour + move.fromtype * 64 + move.to];
	key ^= random_key[384 * colour + move.fromtype * 64 + move.from];
	if (move.special & 16) {
		key ^= random_key[384 * (!colour) + move.totype * 64 + move.to];
	}
	if (move.special& 2){
		key ^= random_key[384 * colour + move.fromtype * 64 + move.to];
		key ^= random_key[384 * colour + 4 * 64 + move.to];
	}
	if (move.special & 4 or move.special & 8) {
		return create_hash(colour);
	}
	if (HASH_CHECK) {
		if (create_hash(colour) != key and create_hash(!colour)!=key) {
			uint64_t cor = create_hash(colour);
			std::cout << "incorect hash" << std::endl;
			std::cout << move<< std::endl;
			//assert(false);
		}
	}
	return key;
}
uint64_t create_hash(bool colour) {
	uint64_t key = 0;
	for (int i = 0; i < 64; i++) {
		bool c0 = (((board.colours[0] >> i) & 1));
		bool c1 = (((board.colours[1] >> i) & 1));
		if ((((board.Types[0] >> i) & 1)) && c0) {
			key ^= random_key[i];
		}
		if ((((board.Types[1] >> i) & 1)) && c0) {
			key ^= random_key[i + 64];
		}
		if ((((board.Types[2] >> i) & 1)) && c0) {
			key ^= random_key[i + 128];
		}
		if ((((board.Types[3] >> i) & 1)) && c0) {
			key ^= random_key[i + 192];
		}
		if ((((board.Types[4] >> i) & 1)) && c0) {
			key ^= random_key[i + 256];
		}
		if ((((board.Types[5] >> i) & 1)) && c0) {
			key ^= random_key[i + 320];
		}
		if ((((board.Types[0] >> i) & 1)) && c1) {
			key ^= random_key[i + 384];
		}
		if ((((board.Types[1] >> i) & 1)) && c1) {
			key ^= random_key[i + 448];
		}
		if ((((board.Types[2] >> i) & 1)) && c1) {
			key ^= random_key[i + 512];
		}
		if ((((board.Types[3] >> i) & 1)) && c1) {
			key ^= random_key[i + 576];
		}
		if ((((board.Types[4] >> i) & 1)) && c1) {
			key ^= random_key[i + 640];
		}
		if ((((board.Types[5] >> i) & 1)) && c1) {
			key ^= random_key[i + 704];
		}
	}
	if (colour) {
		key ^= random_key[768];
	}
	return key;
}

