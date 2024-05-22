#pragma once

#define NOMINMAX

#include "Types.h"
#include "Names.h"
#include "Paths.h"

#include <iostream>
#include <map>
#include <cassert>
#include <functional>

#ifdef _WIN32
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#define PRINT_FUNCTION_NAME() std::cout << "[FILE]" << __FILENAME__ << ", [FUNCTION]" << __FUNCTION__ << ", [LINE]" << __LINE__  << std::endl

using namespace std;