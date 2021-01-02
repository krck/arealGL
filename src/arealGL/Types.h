#ifndef Types_h
#define Types_h

#include <chrono>

// Signed integer typedefs (fastest option, with a width of at least (!) 8, 16, 32 and 64 bits) 
using int8 = std::int_fast8_t;
using int16 = std::int_fast16_t;
using int32 = std::int_fast32_t;
using int64 = std::int_fast64_t;
// Unsigned integer typedefs (fastest option, with a width of at least (!) 8, 16, 32 and 64 bits) 
using uint8 = std::uint_fast8_t;
using uint16 = std::uint_fast16_t;
using uint32 = std::uint_fast32_t;
using uint64 = std::uint_fast64_t;
// Default typedefs (normal int option, with a width of exactly (!) 32 or 64 bits) 
using abyte = std::uint8_t;
using ushort = std::uint16_t;
using uint = std::uint32_t;
using ulong = std::uint64_t;
using hash = std::uint64_t;

typedef std::chrono::high_resolution_clock::time_point  time_point;

// Basic Color definitions
#define CL_BLACK            Color(0.0f,0.0f,0.0f)
#define CL_WHITE            Color(1.0f,1.0f,1.0f)
#define CL_GRAY             Color(0.3f,0.3f,0.3f)
#define CL_RED              Color(1.0f,0.0f,0.0f)
#define CL_GREEN            Color(0.0f,1.0f,0.0f)
#define CL_BLUE             Color(0.0f,0.0f,1.0f)
#define CL_YELLOW           Color(1.0f,1.0f,0.0f)
#define CL_YELLOW_PALE      Color(1.0f,1.0f,0.8f)
#define CL_ORANGE           Color(1.0f,0.4f,0.0f)
#define CL_BROWN            Color(0.6f,0.3f,0.1f)
#define CL_PURPLE           Color(0.5f,0.0f,1.0f)
#define CL_AQUA             Color(0.0f,1.0f,1.0f)
#define CL_PINK             Color(0.9f,0.0f,0.9f)

#endif
