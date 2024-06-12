#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <algorithm>
#include <random>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include "SFML/Graphics.hpp"

#elif defined(__linux__)
#include  <unistd.h>
#include <SFML/Graphics.hpp>

#elif defined(__APPLE__) && defined(__MACH__)

#include <TargetConditionals.h>
#if TARGET_OS_MAC
#include  <unistd.h>
#include "SFML/Graphics.hpp"
#endif
#else
#error "Unknown OS"
#endif

#endif
