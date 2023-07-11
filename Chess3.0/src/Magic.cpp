#include <cstdint>
#include <iostream>
#include <cmath>
#include "Bit.h"
#include "Magic.h"
#include "Board.h"
uint64_t Rindexs[64][4096];
uint64_t Bindexs[64][512];

int lsb64(uint64_t num) {
    return log2((num & ~(num - 1)));
}


uint64_t set_occupancy(int index, int bits_in_mask, uint64_t attack_mask) {
    uint64_t occupancy = 0;
    for (int count = 0; count < bits_in_mask; count++){
        int square = lsb64(attack_mask);
        attack_mask& (1ULL << square) ? (attack_mask ^= (1ULL << square)) : 0;
        if (index & 1 << count) {
            occupancy |= 1ULL << square;
        }
    }
    return occupancy;
}

uint64_t Bmask(int square) {
    // attack bitboard
    uint64_t attackboard = 0;

    //file, rank, target rank, target file
    int f, r;
    int tr = square / 8;
    int tf = square % 8;

    // generate attacks
    for (r = tr + 1, f = tf + 1; r <= 6 && f <= 6; r++, f++) attackboard |= (1ULL << (r * 8 + f));
    for (r = tr + 1, f = tf - 1; r <= 6 && f >= 1; r++, f--) attackboard |= (1ULL << (r * 8 + f));
    for (r = tr - 1, f = tf + 1; r >= 1 && f <= 6; r--, f++) attackboard |= (1ULL << (r * 8 + f));
    for (r = tr - 1, f = tf - 1; r >= 1 && f >= 1; r--, f--) attackboard |= (1ULL << (r * 8 + f));

    return attackboard;
}

uint64_t BC(uint64_t occ, int square) {
    uint64_t result = 0;

    int f, r;
    int tr = square / 8;
    int tf = square % 8;
    for (r = tr + 1, f = tf + 1; r <= 7 && f <= 7; r++, f++) {
        result |= (1ULL << (r * 8 + f));
        if ((occ >> (r * 8 + f))&1) { break; };
    }
    for (r = tr + 1, f = tf - 1; r <= 7 && f >= 0; r++, f--) {
        result |= (1ULL << (r * 8 + f));
        if ((occ >> (r * 8 + f))&1) { break; };
    }
    for (r = tr - 1, f = tf + 1; r >= 0 && f <= 7; r--, f++) {
        result |= (1ULL << (r * 8 + f));
        if ((occ>> (r * 8 + f))&1) { break; };
    }
    for (r = tr - 1, f = tf - 1; r >= 0 && f >= 0; r--, f--) {
        result |= (1ULL << (r * 8 + f));
        if ((occ >> (r * 8 + f))&1) { break; };
    }
    return result;
}

uint64_t RC(uint64_t occ, int square) {
    uint64_t result = 0ULL;

    int f, r;
    int tr = square / 8;
    int tf = square % 8;
    for (r = tr + 1; r <= 7; r++) {
        result |= (1ULL << (r * 8 + tf));
        if ((occ >> r * 8 + tf)&1) { break; };
    }
    for (r = tr - 1; r >=0; r--) {
        result |= (1ULL << (r * 8 + tf));
        if ((occ >> r * 8 + tf)&1) { break; };
    }
    for (f = tf + 1;f <= 7;f++) {
        result |= (1ULL << (tr * 8 + f));
        if ((occ >> tr * 8 + f)&1) { break; };
    }
    for (f = tf - 1;f >= 0; f--) {
        result |= (1ULL << (tr * 8 + f));
        if ((occ >> tr * 8 + f)&1) { break; };
    }
    return result;
}

uint64_t Rmask(int square) {
    // attack bitboard
    uint64_t attackboard = 0;

    //file, rank, target rank, target file
    int f, r;
    int tr = square / 8;
    int tf = square % 8;

    // generate attacks
    for (r = tr + 1; r <= 6; r++) attackboard |= (1ULL << (r * 8 + tf));
    for (r = tr - 1; r >= 1; r--) attackboard |= (1ULL << (r * 8 + tf));
    for (f = tf + 1; f <= 6; f++) attackboard |= (1ULL << (tr * 8 + f));
    for (f = tf - 1; f >= 1; f--) attackboard |= (1ULL << (tr * 8 + f));

    return attackboard;
}

uint64_t Rmasks[64];


uint64_t Bmasks[64];

void Magic_initialisation() {
    for (int i = 0; i < 64; i++) {
        //counts bit in masks
        int Rcount;
        Rcount = popCount64bit(Rmask(i));
        int Bcount;
        Bcount = popCount64bit(Bmask(i));
        //sets the nummber to 2 to the power of itself
        int PBcount = 1 << Bcount;
        int PRcount = 1 << Rcount;

        //loop over all posible variations for bishops
        for (int j = 0; j < PBcount; j++) {
            //creates the occupancy
            uint64_t occ = set_occupancy(j,Bcount,Bmask(i));
            //create the magic index
            uint64_t magic = occ * Bmagics[i] >> (64 - BBn[i]);
            Bindexs[i][magic] = BC(occ, i);
        }
        //repeat for rook
        for (int j = 0; j < PRcount; j++) {
            uint64_t occ = set_occupancy(j, Rcount, Rmask(i));
            uint64_t magic = occ* Rmagics[i] >> (64 - RBn[i]);
            Rindexs[i][magic] = RC(occ, i);
        }
    }
    for (int i = 0; i < 64; i++) {
        Rmasks[i] = Rmask(i);
        Bmasks[i] = Bmask(i);
    }
}

uint64_t getRmagic(int square,uint64_t occ) {
    occ &= Rmasks[square];
    occ *= Rmagics[square];
    occ >>= (64ULL - RBn[square]);
    return Rindexs[square][occ];
}
uint64_t getBmagic(int square, uint64_t occ) {
    occ &= Bmasks[square];
    occ *= Bmagics[square];
    occ >>= (64ULL - BBn[square]);
    return Bindexs[square][occ];
}

