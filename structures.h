#pragma once

//
// CoronaVirus Chess
// =================

// (C) Chris Whittington 2020, All Rights Reserved for time being, 
// this code will likely eventually be put into Public Domain, but not just yet.
// =============================================================================

#define MAXTIME	(ONE << 62)			// infinite search, milliseconds (130,000 years or so)
#define MAXNODES (ONE << 62)		// infinite nodes 1.3 years at 1000 Giga-nodes per second
#define MAXDEPTH 96					// who knows? (hash.c requires less that about 120)
#define MAX_QUIET_MOVEWIDTH 96		// testing found 77 max so far
#define MAX_NON_QUIET_MOVEWIDTH 32	// testing found 22 max so far
#define MAXMOVEWIDTH 128			// who knows?
#define MAXGAMELENGTH 1000 //500			// who knows?
//
//
typedef u64 MOVE;
typedef u64 BOARD;
typedef u64 HASHKEY;
typedef int SQUARE;

//
#define PAWNHASHSIZE (ONE << 16)
#define PAWNHASHMASK (PAWNHASHSIZE - ONE)

#if USE_EVALHASH
#define EVALHASHSIZE (ONE << 17)
#define EVALHASHMASK (EVALHASHSIZE - ONE)
#endif

#if USE_SIDEHASH
#define SIDEHASHSIZE (8ULL * 1024ULL * 1024ULL)
#define SIDEHASHMASK (SIDEHASHSIZE - ONE)

#define SIDEANDPRIORHASHSIZE (8ULL * 1024ULL * 1024ULL)
#define SIDEANDPRIORHASHMASK (SIDEANDPRIORHASHSIZE - ONE)
#endif

#if USE_BUILT_IN_BOOK
#define BOOKBUCKETS 4
#define BOOKSIZE (2ULL * 8ULL * 1024ULL * 1024ULL)
#define BOOKMASK (BOOKSIZE - ONE)

#define BOOK_WEIGHT_MASK ((4ULL * 1024ULL * 1024ULL) - ONE)
#endif

#define MAX_LOWPLYHEIGHT 4

typedef struct PAWNHASH
{
	u64 hashkey;
	//BOARD pawnpushes[2];
	int eval;
	//int eval[2];
	int closedness;
} PAWNHASH;

#if USE_EVALHASH
// temporary - squash u32 to u16 and int to int16 at some stage
// it ought to be possible to steal 16 lsbits off the key as well if ever needed
typedef struct EVALHASH
{
	u64 evalkey;
	u32 r0;
	u32 r1;
	u32 r2;
	int eval;
} EVALHASH;
#endif


// Information about pieces impacted by a move
struct dirty_pieces {
	int ndirty;
	int piece[3];
	int from[3];
	int to[3];
};

// The state of NNUE input features for a position
struct nnue_input_state {
	// State data
	alignas(64) int16 data[2][256];	// OTT 256
	// Flag indicating if the state data us up to date
	bool valid;
};

// Item in the evaluation stack
struct eval_item {
	/* State of NNUE input features */
	struct nnue_input_state state;
	/* Pieces impacted by the latest move */
	struct dirty_pieces dirty_pieces;
	/* The evaluation score */
	int score;
};

//
typedef struct POSITIONDATA
{	// computer when we do MakeMove()
	ALIGN64 u64 miniboard[4];	// 64*4 bit nibbles contains (type), 0b1111 for empty
	ALIGN64 BOARD pieces[2];		// whites, blacks
	ALIGN64 BOARD pawns;
	ALIGN64 BOARD nites;
	ALIGN64 BOARD diagonals;
	ALIGN64 BOARD manhattans;
	int king_sq[2];

	ALIGN64 u64 sidehashindex;
	ALIGN64 u64 mainhashindex[2];
	ALIGN64 u64 pawnhashindex;
	//u64 knphashindex;
	int epsquare;
	int rule50;
	int repetition_cycles[2];

	// count of immediate cycles this move, done in testpremovedraw
	int cycles;

	int flags;
	int pst_balance;
	int non_pawn_material[2];

	// not computed by MakeMove(), done in Search() and QSearch() shortly after MakeMove()
	ALIGN64 BOARD   checkers;			// pieces that check enemy king (0, 1 or 2)

	// not computed by MakeMove(), done in Search() and QSearch() before GetNextMove - GenerateMoves()
	ALIGN64 BOARD   blockers[2];		// both sides pieces on opponent pinray to king
	ALIGN64 BOARD   pinners[2];		// opponent's pinning pieces (includes "pin's" of same side opponent blockers, revealing a discovery, as well as actual pinners)
	//MOVE	move_suggestions[32];
	//int		suggestion_scores[32];
#if 1
	int runaway;			// give some bonus to moving this piece (init -1)
	ALIGN64 BOARD safetorunawayto;	// possible safe squares to move to (init 0), only set if runaway
#endif
	ALIGN64 MOVE r0;
	ALIGN64 MOVE r1;
	ALIGN64 MOVE r2;

	struct eval_item eval_stack;
} POSITIONDATA;
//

#if USE_BUILT_IN_BOOK
typedef struct BOOKDATA
{
	u64 hashkey[BOOKBUCKETS];
} BOOKDATA;
#endif
//
typedef struct FENLOADER
{
	char* epdptr;
	POSITIONDATA* position;
} FENLOADER;
//

#if USE_SIDEHASH
typedef struct SIDEHASH
{
	u64 key;
	u64 move[2];
} SIDEHASH;
//


typedef struct SIDEANDPRIORHASH
{
	u64 key;
	u64 move;
} SIDEANDPRIORHASH;
//
#endif

//
#define THREAD_BACKTRACK 4+2+2	// +2 for move_history purposes +2 for safety
typedef struct THREAD
{
	// keep these contiguous ...
	int base_searched_legals[THREAD_BACKTRACK];
	int searchedlegals[MAXDEPTH];

	ALIGN64 u64 base_move_history[THREAD_BACKTRACK];
	u64 move_history[MAXDEPTH];

	int* base_continuation_history_ptr[THREAD_BACKTRACK];
	int* continuation_history_ptr[MAXDEPTH];	// ptr->[incheck][capturepromo][movingpiece][sq_to]0][0]

	int base_static_eval[THREAD_BACKTRACK];
	int static_eval[MAXDEPTH];

	bool search_timeout;
	bool sent_uci_info;
	char uci_str[MAXDEPTH * 5 + 256];
	int verbosity;
	int iteration_num;
	int selective_depth;
	int64 nodecounter;
	int64 qs_nodecounter;

	ALIGN64 u64 pv[MAXDEPTH][MAXDEPTH];
	//int static_eval[MAXDEPTH];
	ALIGN64 u64 countermove[6][64];
	ALIGN64 u64 killer[MAXDEPTH+4][2];

	int pv_length[MAXDEPTH];
	int stat_score[MAXDEPTH + 4];
	int LowPlyHistory[MAX_LOWPLYHEIGHT][64][64];	// 4, from, to
	int butterflyboard[2][64][64];
	int checkhistoryboard[2][6][64];
	int continuation_history[2][2][8][64][8][64]; // [incheck][capturepromo][movingpiece][sq_to][t1][s2]
	int capture_history[8][64][8];

	PAWNHASH pawnhashtable[PAWNHASHSIZE];
#if USE_EVALHASH
	EVALHASH evalhashtable[EVALHASHSIZE];
#endif

#if USE_SIDEHASH
	SIDEHASH sidehash[SIDEHASHSIZE];
	SIDEANDPRIORHASH sideandpriorhash[SIDEANDPRIORHASHSIZE];
#endif

	unsigned char* startstack;
	int maxstackusage;
} THREAD;
//

//
typedef struct QSEARCHQUIET
{
	int us;
	POSITIONDATA* pos;
	int v;
} QSEARCHQUIET;

//
typedef struct SEARCHINFO
{
	bool is_pondering;
	bool ponderhit;
	bool set_to_ponder;

	MOVE best_ponder;
	char pondermove_str[8];
	char opponent_actual_move_str[8];
	bool timeisfixed;
	int64 movetime;
	int64 time_target;
	int64 max_time_target;
	int64 movestogo;
	int64 timetogo;
	int64 increment;
	int64 time_overhead;
	int depthleft[MAXTHREADS];
	MOVE move[MAXTHREADS];
	int value[MAXTHREADS];
	int alpha[MAXTHREADS];
	int beta[MAXTHREADS];
	char user_data[MAX_LEN_FEN_PLUS_MOVES];
} SEARCHINFO;

typedef struct PERFTDATA
{
	int64 legals;
	int64 captures;
	int64 eps;
	int64 castles_O_O;
	int64 castles_O_O_O;
	int64 promos;
	int64 checks;
	int64 checkmates;
} PERFTDATA;

typedef struct STAGE
{	
	MOVE tt_move;
	MOVE countermove;
	MOVE k1;
	MOVE k2;
	MOVE r0;
	MOVE r1;
	MOVE r2;
	MOVE h1;
	MOVE h2;
	int* stageptr;
	bool done_k1;
	bool done_r1;
	bool done_r2;
	bool done_h1;
	bool done_h2;
	bool done_countermove;

	int movelistindex;
	int movelistcount;	
	ALIGN64 MOVE movelist[MAX_QUIET_MOVEWIDTH];
	int movelistscore[MAX_QUIET_MOVEWIDTH];

	int capturelistindex;
	int capturelistcount;
	ALIGN64 MOVE capturelist[MAX_NON_QUIET_MOVEWIDTH];
	int capturelistscore[MAX_NON_QUIET_MOVEWIDTH];

	int suggestionindex;

#if DEBUG_BEST_MOVE_STATS
	MOVE good_caps_list[MAX_NON_QUIET_MOVEWIDTH];
	MOVE bad_caps_list[MAX_NON_QUIET_MOVEWIDTH];
	MOVE good_quiets_list[MAX_QUIET_MOVEWIDTH];
	MOVE evasions_list[MAX_QUIET_MOVEWIDTH];
	MOVE qcaps_list[MAX_QUIET_MOVEWIDTH];
	int goodcaps_index;
	int badcaps_index;
	int quiets_index;
	int evasions_index;
	int qcaps_index;
#endif
	//int doneexmovecount;
	//u64 doneexmovelist[MAXMOVEWIDTH];
} STAGE;



// availability of castling flags (from FEN, or game status or whatever)
#define W_SHORTCASTLE	0b00000001
#define W_LONGCASTLE	0b00000010
#define B_SHORTCASTLE	0b00000100
#define B_LONGCASTLE	0b00001000
#define INCHECK_FLAG	0b00010000

#define NORMALRULE50 100
