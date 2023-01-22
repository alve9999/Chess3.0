#pragma once
#include "Board.h"
#include <iostream>
#define weight(x) (int8_t)(0.1*x)

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
	for (int i = 0; i < 64; i++) {
		if ((board.Occupancy >> i) & 1) {
			int c0 = (((board.colours[0] >> i) & 1));
			int c1 = ~c0;
			score += (c0 & ((board.Types[0] >> i) & 1)) * (20 + (pawntable0[i]));
			score -= (c1 & ((board.Types[0] >> i) & 1)) * (20 + (pawntable1[i]));

			score += (c0 & ((board.Types[1] >> i) & 1)) * (60 + (knightstable[i]));
			score -= (c1 & ((board.Types[1] >> i) & 1)) * (60 + (knightstable[i]));

			score += (c0 & ((board.Types[2] >> i) & 1)) * (60 + (bishopstable0[i]));
			score -= (c1 & ((board.Types[2] >> i) & 1)) * (60 + (bishopstable1[i]));

			score += (c0 & ((board.Types[3] >> i) & 1)) * (100 + (rookstable0[i]));
			score -= (c1 & ((board.Types[3] >> i) & 1)) * (100 + (rookstable1[i]));

			score += (c0 & ((board.Types[4] >> i) & 1)) * (180 + (queenstable[i]));
			score -= (c1 & ((board.Types[4] >> i) & 1)) * (180 + (queenstable[i]));

			score += (c0 & ((board.Types[5] >> i) & 1)) * (1000 + (kingstable0[i]));
			score -= (c1 & ((board.Types[5] >> i) & 1)) * (1000 + (kingstable1[i]));
		}
	}
	return score;
}
__forceinline int evaluate1() {
	int score = 0;
	for (int i = 0; i < 64; i++) {
		if ((board.Occupancy >> i) & 1) {
			int c0 = (((board.colours[1] >> i) & 1));
			int c1 = ~c0;
			score += (c0 & ((board.Types[0] >> i) & 1)) * (20 + (pawntable1[i]));
			score -= (c1 & ((board.Types[0] >> i) & 1) * (20 + (pawntable0[i])));

			score += (c0 & ((board.Types[1] >> i) & 1)) * (60 + (knightstable[i]));
			score -= (c1 & ((board.Types[1] >> i) & 1)) * (60 + (knightstable[i]));

			score += (c0 & ((board.Types[2] >> i) & 1)) * (60 + (bishopstable1[i]));
			score -= (c1 & ((board.Types[2] >> i) & 1)) * (60 + (bishopstable0[i]));

			score += (c0 & ((board.Types[3] >> i) & 1)) * (100 + (rookstable1[i]));
			score -= (c1 & ((board.Types[3] >> i) & 1)) * (100 + (rookstable0[i]));

			score += (c0 & ((board.Types[4] >> i) & 1)) * (180 + (queenstable[i]));
			score -= (c1 & ((board.Types[4] >> i) & 1)) * (180 + (queenstable[i]));

			score += (c0 & ((board.Types[5] >> i) & 1)) * (1000 + (kingstable1[i]));
			score -= (c1 & ((board.Types[5] >> i) & 1)) * (1000 + (kingstable0[i]));
		}
	}
	return score;
}

__forceinline int evaluate(bool colour) {
	return colour ? evaluate1() : evaluate0();
}