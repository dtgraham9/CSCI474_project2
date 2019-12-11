#pragma once

/*
Keeps track of drive head direction its reading
IDLE = Basically used when drive is
just spinning up for the first time or has been idle.  
INC = increasing track number from 0
DEC = decreasing from max track number
*/
enum direction { IDLE, INC, DEC };