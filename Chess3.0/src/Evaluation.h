#pragma once
#include "Board.h"
#include "Bit.h"
#include <iostream>
#define weight(x) (int8_t)(0.2*x)
#define VALUE_WEIGHT 5
#include <intrin.h>
#pragma intrinsic(_BitScanForward64)

const int8_t pawntable0[64] = { weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(
50) , weight(50) , weight(50) , weight(50) , weight(50) , weight(50) , weight(50) , weight(50) , weight(
10) , weight(10) , weight(20) , weight(30) , weight(30) , weight(20) , weight(10) , weight(10) , weight(
5) , weight(5) , weight(10) , weight(25) , weight(25) , weight(10) , weight(5) , weight(5) , weight(
0) , weight(0) , weight(0) , weight(20) , weight(20) , weight(0) , weight(0) , weight(0) , weight(
5) , weight(-5) , weight(-10) , weight(0) , weight(0) , weight(-10) , weight(-5) , weight(5) , weight(
5) , weight(10) , weight(10) , weight(-20) , weight(-20) , weight(10) , weight(10) , weight(5) , weight(
0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) };
const int8_t pawntable1[64] = { weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(
5) , weight(10) , weight(10) , weight(-20) , weight(-20) , weight(10) , weight(10) , weight(5) , weight(
5) , weight(-5) , weight(-10) , weight(0) , weight(0) , weight(-10) , weight(-5) , weight(5) , weight(
0) , weight(0) , weight(0) , weight(20) , weight(20) , weight(0) , weight(0) , weight(0) , weight(
5) , weight(5) , weight(10) , weight(25) , weight(25) , weight(10) , weight(5) , weight(5) , weight(
10) , weight(10) , weight(20) , weight(30) , weight(30) , weight(20) , weight(10) , weight(10) , weight(
50) , weight(50) , weight(50) , weight(50) , weight(50) , weight(50) , weight(50) , weight(50) , weight(
0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) };

const int8_t knightstable[64] = { weight(-50) , weight( -40) , weight( -30) , weight( -30) , weight( -30) , weight( -30) , weight( -40) , weight( -50) , weight(
-40) , weight( -20) , weight( 0) , weight( 5) , weight( 5) , weight( 0) , weight( -20) , weight( -40) , weight(
-30) , weight( 5) , weight( 10) , weight( 15) , weight( 15) , weight( 10) , weight( 5) , weight( -30) , weight(
-30) , weight( 0) , weight( 15) , weight( 20) , weight( 20) , weight( 15) , weight( 0) , weight( -30) , weight(
-30) , weight( 5) , weight( 15) , weight( 20) , weight( 20) , weight( 15) , weight( 5) , weight( -30) , weight(
-30) , weight( 0) , weight( 10) , weight( 15) , weight( 15) , weight( 10) , weight( 0) , weight( -30) , weight(
-40) , weight( -20) , weight( 0) , weight( 0) , weight( 0) , weight( 0) , weight( -20) , weight( -40) , weight(
-50) , weight( -40) , weight( -30) , weight( -30) , weight( -30) , weight( -30) , weight( -40) , weight( -50 )};

const int8_t bishopstable0[64] = { weight(-20) , weight(-10) , weight(-10) , weight(-10) , weight(-10) , weight(-10) , weight(-10) , weight(-20) , weight(
-10) , weight(5) , weight(0) , weight(0) , weight(0) , weight(0) , weight(5) , weight(-10) , weight(
-10) , weight(10) , weight(10) , weight(10) , weight(10) , weight(10) , weight(10) , weight(-10) , weight(
-10) , weight(0) , weight(10) , weight(10) , weight(10) , weight(10) , weight(0) , weight(-10) , weight(
-10) , weight(5) , weight(5) , weight(10) , weight(10) , weight(5) , weight(5) , weight(-10) , weight(
-10) , weight(0) , weight(5) , weight(10) , weight(10) , weight(5) , weight(0) , weight(-10) , weight(
-10) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(-10) , weight(
-20) , weight(-10) , weight(-10) , weight(-10) , weight(-10) , weight(-10) , weight(-10) , weight(-20) };

const int8_t bishopstable1[64] = { weight(-20) , weight(-10) , weight(-10) , weight(-10) , weight(-10) , weight(-10) , weight(-10) , weight(-20) , weight(
-10) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(-10) , weight(
-10) , weight(0) , weight(5) , weight(10) , weight(10) , weight(5) , weight(0) , weight(-10) , weight(
-10) , weight(5) , weight(5) , weight(10) , weight(10) , weight(5) , weight(5) , weight(-10) , weight(
-10) , weight(0) , weight(10) , weight(10) , weight(10) , weight(10) , weight(0) , weight(-10) , weight(
-10) , weight(10) , weight(10) , weight(10) , weight(10) , weight(10) , weight(10) , weight(-10) , weight(
-10) , weight(5) , weight(0) , weight(0) , weight(0) , weight(0) , weight(5) , weight(-10) , weight(
-20) , weight(-10) , weight(-10) , weight(-10) , weight(-10) , weight(-10) , weight(-10) , weight(-20) };

const int8_t rookstable0[64] = {weight(0) , weight(0) , weight(0) , weight(5) , weight(5) , weight(0) , weight(0) , weight(0) , weight(
-5) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(-5) , weight(
-5) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(-5) , weight(
-5) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(-5) , weight(
-5) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(-5) , weight(
-5) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(-5) , weight(
5) , weight(10) , weight(10) , weight(10) , weight(10) , weight(10) , weight(10) , weight(5) , weight(
0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0)};

const int8_t rookstable1[64] = { weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(
5) , weight(10) , weight(10) , weight(10) , weight(10) , weight(10) , weight(10) , weight(5) , weight(
-5) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(-5) , weight(
-5) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(-5) , weight(
-5) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(-5) , weight(
-5) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(-5) , weight(
-5) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(-5) , weight(
0) , weight(0) , weight(0) , weight(5) , weight(5) , weight(0) , weight(0) , weight(0) };

const int8_t queenstable[64] = { weight(-20) , weight(-10) , weight(-10) , weight(-5) , weight(-5) , weight(-10) , weight(-10) , weight(-20) , weight(
-10) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(-10) , weight(
-10) , weight(5) , weight(5) , weight(5) , weight(5) , weight(5) , weight(0) , weight(-10) , weight(
0) , weight(0) , weight(5) , weight(5) , weight(5) , weight(5) , weight(0) , weight(-5) , weight(
-5) , weight(0) , weight(5) , weight(5) , weight(5) , weight(5) , weight(0) , weight(-5) , weight(
-10) , weight(0) , weight(5) , weight(5) , weight(5) , weight(5) , weight(0) , weight(-10) , weight(
-10) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(0) , weight(-10) , weight(
-20) , weight(-10) , weight(-10) , weight(-5) , weight(-5) , weight(-10) , weight(-10) , weight(-20) };

const int8_t kingstable0[64] = {weight(20) , weight(30) , weight(10) , weight(0) , weight(0) , weight(10) , weight(30) , weight(20) , weight(
20) , weight(20) , weight(0) , weight(0) , weight(0) , weight(0) , weight(20) , weight(20) , weight(
-10) , weight(-20) , weight(-20) , weight(-20) , weight(-20) , weight(-20) , weight(-20) , weight(-10) , weight(
-20) , weight(-30) , weight(-30) , weight(-40) , weight(-40) , weight(-30) , weight(-30) , weight(-20) , weight(
-30) , weight(-40) , weight(-40) , weight(-50) , weight(-50) , weight(-40) , weight(-40) , weight(-30) , weight(
-30) , weight(-40) , weight(-40) , weight(-50) , weight(-50) , weight(-40) , weight(-40) , weight(-30) , weight(
-30) , weight(-40) , weight(-40) , weight(-50) , weight(-50) , weight(-40) , weight(-40) , weight(-30) , weight(
-30) , weight(-40) , weight(-40) , weight(-50) , weight(-50) , weight(-40) , weight(-40) , weight(-30)};

const int8_t kingstable1[64] = {weight(-30) , weight( -40) , weight( -40) , weight( -50) , weight( -50) , weight( -40) , weight( -40) , weight( -30) , weight(
-30) , weight( -40) , weight( -40) , weight( -50) , weight( -50) , weight( -40) , weight( -40) , weight( -30) , weight(
-30) , weight( -40) , weight( -40) , weight( -50) , weight( -50) , weight( -40) , weight( -40) , weight( -30) , weight(
-30) , weight( -40) , weight( -40) , weight( -50) , weight( -50) , weight( -40) , weight( -40) , weight( -30) , weight(
-20) , weight( -30) , weight( -30) , weight( -40) , weight( -40) , weight( -30) , weight( -30) , weight( -20) , weight(
-10) , weight( -20) , weight( -20) , weight( -20) , weight( -20) , weight( -20) , weight( -20) , weight( -10) , weight(
20) , weight( 20) , weight( 0) , weight( 0) , weight( 0) , weight( 0) , weight( 20) , weight( 20) , weight(
 20) , weight( 30) , weight( 10) , weight( 0) , weight( 0) , weight( 10) , weight( 30) , weight( 20)};



__forceinline int evaluate0() {
	int score = 0;
	unsigned long index = 0;
	int c = 0;
	uint64_t opponent = board.colours[1];
	uint64_t your = board.colours[0];
	if (popCount64bit(board.Types[5]) == 1) {
		_BitScanForward64(&index, board.Types[5]);
		return ((board.colours[0] >> index) & 1) ? -INFINITY : INFINITY;
	}
	while (your) {
		_BitScanForward64(&index, your);
		c += index;
		your = your >> index;
		score += (((board.Types[0] >> c) & 1)) * (20 + (pawntable1[c]));

		score += (((board.Types[1] >> c) & 1)) * (60 + (knightstable[c]));

		score += (((board.Types[2] >> c) & 1)) * (60 + (bishopstable1[c]));

		score += (((board.Types[3] >> c) & 1)) * (100 + (rookstable1[c]));

		score += (((board.Types[4] >> c) & 1)) * (180 + (queenstable[c]));

		score += (((board.Types[5] >> c) & 1)) * (2000 + (kingstable1[c]));
		your = your >> 1;
		c++;
	}
	c = 0;
	while (opponent) {
		_BitScanForward64(&index, opponent);
		c += index;
		opponent = opponent >> index;
		score -= (((board.Types[0] >> c) & 1)) * (20 + (pawntable1[c]));

		score -= (((board.Types[1] >> c) & 1)) * (60 + (knightstable[c]));

		score -= (((board.Types[2] >> c) & 1)) * (60 + (bishopstable1[c]));

		score -= (((board.Types[3] >> c) & 1)) * (100 + (rookstable1[c]));

		score -= (((board.Types[4] >> c) & 1)) * (180 + (queenstable[c]));

		score -= (((board.Types[5] >> c) & 1)) * (1000 + (kingstable1[c]));

		opponent = opponent >> 1;
		c++;
	}
	return score;
}
__forceinline int evaluate1() {
	int score = 0;
	unsigned long index = 0;
	int c = 0;
	uint64_t opponent = board.colours[0];
	uint64_t your = board.colours[1];
	if(popCount64bit(board.Types[5])==1){
		_BitScanForward64(&index, board.Types[5]);
		return ((board.colours[1] >> index) & 1) ? -INFINITY : INFINITY;
	}
	while (your) {
		_BitScanForward64(&index, your);
		c += index;
		your = your >> index;
		score += (((board.Types[0] >> c) & 1)) * (20 + (pawntable1[c]));

		score += (((board.Types[1] >> c) & 1)) * (60 + (knightstable[c]));

		score += (((board.Types[2] >> c) & 1)) * (60 + (bishopstable1[c]));

		score += (((board.Types[3] >> c) & 1)) * (100 + (rookstable1[c]));

		score += (((board.Types[4] >> c) & 1)) * (180 + (queenstable[c]));

		score += (((board.Types[5] >> c) & 1)) * ((kingstable1[c]));
		your = your >> 1;
		c++;
	}
	c = 0;
	while (opponent) {
		_BitScanForward64(&index, opponent);
		c += index;
		opponent = opponent >> index;
		score -= (((board.Types[0] >> c) & 1)) * (20 + (pawntable1[c]));

		score -= (((board.Types[1] >> c) & 1)) * (60 + (knightstable[c]));

		score -= (((board.Types[2] >> c) & 1)) * (60 + (bishopstable1[c]));

		score -= (((board.Types[3] >> c) & 1)) * (100 + (rookstable1[c]));

		score -= (((board.Types[4] >> c) & 1)) * (180 + (queenstable[c]));

		score -= (((board.Types[5] >> c) & 1)) * ((kingstable1[c]));

		opponent = opponent >> 1;
		c++;
	}
	return score;
}

__forceinline int evaluate(bool colour) {
	return colour ? evaluate1() : evaluate0();
}