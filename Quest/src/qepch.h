#pragma once

// Common platform headers
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <optional>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>

#include <cstdint>

#include "Quest/Core/Base.h"
#include "Quest/Core/Logger.h"

// Platform specific headers
#ifdef QE_PLATFORM_WINDOWS
#include <Windows.h>
#endif