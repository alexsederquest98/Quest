#pragma once

// Common platform headers
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <cstdint>

#include "Quasar/Core/Base.h"
#include "Quasar/Core/Logger.h"

// Platform specific headers
#ifdef QS_PLATFORM_WINDOWS
#include <Windows.h>
#endif