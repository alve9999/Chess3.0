#pragma once
#include "Evaluation.h"
#include "Moves.h"
#include "Graphics.h"
#include <chrono>
#include <algorithm>
#include <thread>
#include <iostream>

int MinMax(int depth, bool colour, bool first, float alpha, float beta,uint64_t hash,float score);

Move* ai(int time, bool colour);
