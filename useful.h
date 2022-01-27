#pragma once

#include <intrin.h>

//
// CoronaVirus Chess
// =================

// (C) Chris Whittington 2020, All Rights Reserved for time being, 
// this code will likely eventually be put into Public Domain, but not just yet.
// =============================================================================


#define TRUE 1
#define FALSE 0

#define NAME_STRING "Corona-Virus-Chess"
#define VERSION_STRING "-1.21"

#define AMD64 1
#define INTEL6 2
#define INTEL4 3

#define THIS_PC AMD64
//#define THIS_PC INTEL6
//#define THIS_PC INTEL4

#define RELEASE_BENCHMARK 1		// optimised version that does a benchmark test
#define DEBUG 2					// traps stuff in development testing
#define TEST_EVERYTHING 3		// heavy debug mode, integrity tests everything
#define UCI_RELEASE	4			// release executable, UCI mode
#define UCI_DEBUG 5
//#define DO_SELFPLAY 6 // now sorted via command line


#define USE_NN 14

// with PEXT is broken, magic lookups
#define USE_PEXT 0
#define DO_PREFETCH 1
#define BULLET_HASH 128 //2048*2 //512 //(2048*2) //512	// 2048 for normaller speeds

// TEXEL tuning, switches off pawnhash, builds eval trace
// not yet fully implemented
#define MAKE_NN_TRAIN_DATA 0

#if (MAKE_NN_TRAIN_DATA == 1)
#define TRACE 1
#else
#define TRACE 0
#endif

#define DO_PONDERING 0
#define DO_SMP 0	// 0 = used to force n_threads=1, or else, currently DEFAULT_THREADS

#if DO_SMP
#if (THIS_PC == AMD64)
#define DEFAULT_THREADS 32
#else
#define DEFAULT_THREADS 6
#endif
#else
#define DEFAULT_THREADS 1	//ALWAYS
#endif

#define MAXTHREADS	32

#define USE_BUILT_IN_BOOK 0
#define USE_STRONGEST_BOOK_MOVE 0
#define BOOKDEPTHLIMIT 18 // for blitz tourney 60	// this might be too large (only really there to limit potential bad hash matches)
#define CREATE_BOOK_BINARY 0

// this had erroneously been left undefined, spotted 24-Sept
// appears better without - maybe something got broken?
#define USE_SIDEHASH 1

// no evalhashing with Texel
#if TRACE
#define USE_EVALHASH 0
#else
#define USE_EVALHASH 1
#endif

// ???? test without ???? 1.09.03.exe was without and performing better 2%
#define DO_UCI_PV 1

#if TRACE 

#define LAKAS_TUNING 0
// processes epds to quiet state (either this or Texel)
#define MAKEQUIETS 0	// 0 for normal TRACE

// process endgame epds for NN-Endgames
#define MAKE_ENDGAME_EPDS 0
//
#define DO_ASSERTS 0
#define UCI 0
#define UCI_LOGFILE 0
#define UCI_LOGFILE_VERBOSE 0
#define TESTING 0
#define PERFT_TESTING 0
#define BENCHMARK_SPEED_TESTING 0
#define BENCHMARK_TESTING 0
#define BULLET_TESTING 0
#define INTEGRITY_TESTING_PERFT 0
#define INTEGRITY_TESTING_MOVES 0
#define INTEGRITY_TESTING_EPD_HANDLERS 0
#define DEBUG_BEST_MOVE_STATS 0
#define TEST_SEARCH_PARAMS 0
#define STATS_ON_STATS 0
#define SELFPLAY 0
#else

// ===================
#define VERSION_STATUS UCI_RELEASE //RELEASE_BENCHMARK //UCI_RELEASE //RELEASE_BENCHMARK //UCI_RELEASE // DEBUG

#define LAKAS_TUNING 0


// ===================

#if (VERSION_STATUS == TEST_EVERYTHING)
#define DO_ASSERTS 1
#define UCI 0
#define UCI_LOGFILE UCI
#define UCI_LOGFILE_VERBOSE 0
#define TESTING 1
#define PERFT_TESTING 0
#define BENCHMARK_SPEED_TESTING 0
#define BENCHMARK_TESTING 1
#define BULLET_TESTING 0
#define INTEGRITY_TESTING_PERFT 0
#define INTEGRITY_TESTING_MOVES 1
#define INTEGRITY_TESTING_EPD_HANDLERS 0 // this is broken (sets a null pos at some point, prob quite easy to fix)
#define DEBUG_BEST_MOVE_STATS 1
#define TEST_SEARCH_PARAMS 0
#define STATS_ON_STATS 0
#define SELFPLAY 0
#else

#if (VERSION_STATUS == DEBUG)
#define DO_ASSERTS 1
#define UCI 0
#define UCI_LOGFILE 0
#define UCI_LOGFILE_VERBOSE 0
#define TESTING 0
#define PERFT_TESTING 0
#define BENCHMARK_SPEED_TESTING 0
#define BENCHMARK_TESTING 1
#define BULLET_TESTING 0
#define INTEGRITY_TESTING_PERFT 0
#define INTEGRITY_TESTING_MOVES 1
#define INTEGRITY_TESTING_EPD_HANDLERS 0
#define DEBUG_BEST_MOVE_STATS 0
#define TEST_SEARCH_PARAMS 0 // ????????????? usually 0
#define STATS_ON_STATS 0 // usually 0
#define SELFPLAY 0
#else

#if (VERSION_STATUS == RELEASE_BENCHMARK)
#define DO_ASSERTS 0
#define UCI 0
#define UCI_LOGFILE 0
#define UCI_LOGFILE_VERBOSE 0
#define TESTING 0
#define PERFT_TESTING 0
#define BENCHMARK_SPEED_TESTING 0
#define BENCHMARK_TESTING 1
#define BULLET_TESTING 0
#define INTEGRITY_TESTING_PERFT 0
#define INTEGRITY_TESTING_MOVES 0
#define INTEGRITY_TESTING_EPD_HANDLERS 0
#define DEBUG_BEST_MOVE_STATS 0
#define TEST_SEARCH_PARAMS 0
#define STATS_ON_STATS 0
#define SELFPLAY 0
// #define NDEBUG
#define NDEBUG
#else

#if (VERSION_STATUS == UCI_RELEASE)
#define DO_ASSERTS 0
#define UCI 1
#define UCI_LOGFILE 0		// log file on
#define UCI_LOGFILE_VERBOSE 0	// 0=only error messages, 1=full UCI
#define TESTING 0
#define PERFT_TESTING 0
#define BENCHMARK_SPEED_TESTING 0
#define BENCHMARK_TESTING 0
#define BULLET_TESTING 0
#define INTEGRITY_TESTING_PERFT 0
#define INTEGRITY_TESTING_MOVES 0
#define INTEGRITY_TESTING_EPD_HANDLERS 0
#define DEBUG_BEST_MOVE_STATS 0
#define TEST_SEARCH_PARAMS 0
#define STATS_ON_STATS 0
#define SELFPLAY 0
// #define NDEBUG
//#define NDEBUG

#else

#if (VERSION_STATUS == DO_SELFPLAY)
#define DO_ASSERTS 0
#define UCI 0
#define UCI_LOGFILE 0			// log file on
#define UCI_LOGFILE_VERBOSE 0	// 0=only error messages, 1=full UCI
#define TESTING 0
#define PERFT_TESTING 0
#define BENCHMARK_SPEED_TESTING 0
#define BENCHMARK_TESTING 0
#define BULLET_TESTING 0
#define INTEGRITY_TESTING_PERFT 0
#define INTEGRITY_TESTING_MOVES 0
#define INTEGRITY_TESTING_EPD_HANDLERS 0
#define DEBUG_BEST_MOVE_STATS 0
#define TEST_SEARCH_PARAMS 0
#define STATS_ON_STATS 0
#else

#if (VERSION_STATUS == UCI_DEBUG)
#define DO_ASSERTS 0
#define UCI 0	// select manually at console
#define UCI_LOGFILE 1	// usually keep switched off
#define UCI_LOGFILE_VERBOSE 1
#define TESTING 0
#define PERFT_TESTING 0
#define BENCHMARK_SPEED_TESTING 0
#define BENCHMARK_TESTING 0
#define BULLET_TESTING 0
#define INTEGRITY_TESTING_PERFT 0
#define INTEGRITY_TESTING_MOVES 0
#define INTEGRITY_TESTING_EPD_HANDLERS 0
#define DEBUG_BEST_MOVE_STATS 0
#define TEST_SEARCH_PARAMS 0
#define STATS_ON_STATS 0
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#include <cstdalign>

#define ALIGN64 //alignas(64)

#define FILE_SIZE_ERROR -1

// usually keep this switched off, unless want masses of EPD data as part of executable
// is better to load epd suites as needed from HD
#define USE_INLINE_EPDS 0

// FEN plus 1000 moves really ought to be enough
#define MAX_LEN_FEN_PLUS_MOVES (128 + (1000 * 5))
#define INPUT_BUFFER_SIZE 256 //MAX_LEN_FEN_PLUS_MOVES

// ======================================
#define MAIN_THREAD 0	// always the first thread is the main thread
#define TIMEOUT_POLLER 500

#define ONE 1ULL

#define CACHELINESIZE 64

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;

#if DO_ASSERTS
#if UCI_LOGFILE
void uci_error_message(char* str);
#define ASSERT(x, y) if (!(x)) uci_error_message(y), assert(x) 
#else
#define ASSERT(x, y) assert(x)
#endif
#else
#define ASSERT(x,y)
#endif


// if using Visual Studio C Compiler ...
#define VSTUDIO TRUE

#if VSTUDIO
inline void prefetch64(char* addr)
{
#if 1
	_mm_prefetch(addr, 1);
#endif
}
inline int popcount64(u64 x)
{
	return ((int)(__popcnt64(x)));
}
//

//_tzcnt_u64(x)
// #include <intrin.h>
//_lzcnt_u64(x)
inline int scanforward64(u64 x)
{
	ASSERT(x, "scanforward64 fail");
#if 1
	return ((int)_tzcnt_u64(x));
#else
	unsigned long idx;
	_BitScanForward64(&idx, x);
	return (int)idx;
#endif
}
//
inline int scanbackward64(u64 x)
{
	ASSERT(x, "scanbackward64 fail");
#if 0
	unsigned long index;
	unsigned char isNonzero;

	isNonzero = _BitScanReverse(&index, x);
	ASSERT(isNonzero, "bsr fail");
	return (index);
#else
	return (63 - (int)__lzcnt64(x));
#endif
}

inline u64 flipvertical64(u64 x) 
{
		return _byteswap_uint64(x);
}

#if USE_PEXT
//#include <immitrin.h>
inline u64 pext64(u64 src, u64 mask)
{
	return _pext_u64(src, mask);
}
#endif


#else
// well, if you don't have a 64 bit processor ....
inline prefetch64(void* addr)
{
}
//
// extremely slow and non machine specific popcount
// from computer chess wiki
inline int popcount64(u64 bb)
{
	int count = 0;
	for (int i = 0; i < 64; i++, bb >>= 1)
		count += (int)bb & 1;
	return count;
}

// 
inline int scanforward64(u64 bb)
{
	assert(bb);
	for (int i = 0; i < 64; i++)
	{
		if (bb & ONE)
			return i;
		bb = bb >> 1;
	}
	// fail
	return 0;
}

inline int scanbackard64(u64 bb)
{
	assert(bb);
	for (int i = 0; i < 64; i++)
	{
		if (bb & (ONE << 63))
			return (63-i);
		bb = bb << 1;
	}
	// fail
	return 0;
}
#endif


// Mirror a bitboard horizontally about the center files.
// File a is mapped to file h and vice versa.
inline u64 mirror_horizontal(u64 x)
{
	const u64 k1 = (0x5555555555555555);
	const u64 k2 = (0x3333333333333333);
	const u64 k4 = (0x0f0f0f0f0f0f0f0f);
	x = ((x >> 1) & k1) + 2 * (x & k1);
	x = ((x >> 2) & k2) + 4 * (x & k2);
	x = ((x >> 4) & k4) + 16 * (x & k4);
	return x;
}

// return TRUE if morethanone bit
inline bool morethanone(u64 x) 
{
	return x & (x - 1);
}

//inline bool exactly_one(u64 x)
//{
//}

// same concept as exactly one
inline bool onlyone(u64 x) 
{
	return x && !morethanone(x);
}

inline bool onlytwo(u64 x)
{
	return (popcount64(x) == 2);
}

inline bool morethantwo(u64 x)
{
	return (popcount64(x) > 2);
}

// return whats left of x after stripping the lsbit
inline u64 lsbitstrip(u64 x)
{
	return (x & (x - 1));
	//return (x ^ (x & (-((int64)x))));
}

// return the lsbit
inline u64 lsbit(u64 x)
{
	return (x & (-x));
	// return (x & (-((int64)x)));
}

#define swaps(a,b) (a = a ^ b, b = a ^ b, a = a ^ b)
#define swapcontents(a,b) (*a = *a ^ *b, *b = *a ^ *b, *a = *a ^ *b)


inline int minint(int a, int b)
{
	return (a < b) ? a : b;
}

inline int maxint(int a, int b)
{
	return (a > b) ? a : b;
}

inline int64 maxint64(int64 a, int64 b)
{
	return (a > b) ? a : b;
}

inline int absint(int a)
{
	return (a < 0) ? -a : a;
}

inline int limit_inclusive_int(int x, int lo, int hi)
{
	return ((x < lo) ? lo : ((x > hi) ? hi : x));
}
//
// set x>=lo, x<=hi
inline u64 limit_inclusive_uint(u64 x, u64 lo, u64 hi)
{
	return ((x < lo) ? lo : ((x > hi) ? hi : x));
}
//
// returns 1 or -1
inline int signofint(int x)
{
	return((x > 0) - (x < 0));
}
//

//
inline u64 reverse_3_bits64(u64 x)
{
	return ((x & 1) << 2) | ((x >> 2) & 1) | (x & 2);
}
//

inline float clamp_float(float x, float min, float max)
{
	if (x < min)
		return min;
	if (x > max)
		return max;
	return x;
}


inline float clamp_int(int x, int min, int max)
{
	if (x < min)
		return min;
	if (x > max)
		return max;
	return x;
}



u16 read_u16_le(u8* buffer);
u16 read_u16_be(u8* buffer);
u32 read_u32_le(u8* buffer);
u32 read_u32_be(u8* buffer);
u64 read_u64_le(u8* buffer);
u64 read_u64_be(u8* buffer);

#if 0
u32 get_file_size(char* file);
#endif


