#pragma once
#include "Evaluation.h"
#include "Moves.h"
#include "Graphics.h"
#include <chrono>
#include <algorithm>
#include <thread>
#include <iostream>

int MinMax(int depth, bool colour, bool first, int alpha, int beta,uint64_t hash);

Move* ai(int depth, bool colour);