#pragma once
#include "Evaluation.h"
#include "Moves.h"
#include "Graphics.h"
#include <chrono>
#include <algorithm>
#include <thread>
#include <iostream>

float MinMax(int depth, bool colour, bool first, float alpha, float beta);

Move* ai(int depth, bool colour);