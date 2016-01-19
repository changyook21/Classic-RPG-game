#ifndef TESTCASES_H
#define TESTCASES_H

//#define TEST_MODE

//------------------------------------------------------------------------------
#ifdef TEST_MODE
//------------------------------------------------------------------------------
//#define TEST_CASE_01
//#define TEST_CASE_02
//#define TEST_CASE_03
//#define TEST_CASE_04
//#define TEST_CASE_05
#define TEST_CASE_06
//#define TEST_CASE_07

#ifdef TEST_CASE_01
#define TEST_01_ROW_SIZE 20
#define TEST_01_COL_SIZE 40
#define ROW_SIZE TEST_01_ROW_SIZE
#define COL_SIZE TEST_01_COL_SIZE
extern char TEST_01[ROW_SIZE][COL_SIZE+1];
#define TEST_BOARD TEST_01
#endif

#ifdef TEST_CASE_02
#define TEST_02_ROW_SIZE 5
#define TEST_02_COL_SIZE 5
#define ROW_SIZE TEST_02_ROW_SIZE
#define COL_SIZE TEST_02_COL_SIZE
extern char TEST_02[ROW_SIZE][COL_SIZE+1];
#define TEST_BOARD TEST_02
#endif

#ifdef TEST_CASE_03
#define TEST_03_ROW_SIZE 5
#define TEST_03_COL_SIZE 5
#define ROW_SIZE TEST_03_ROW_SIZE
#define COL_SIZE TEST_03_COL_SIZE
extern char TEST_03[ROW_SIZE][COL_SIZE+1];
#define TEST_BOARD TEST_03
#endif

#ifdef TEST_CASE_04
#define TEST_04_ROW_SIZE 5
#define TEST_04_COL_SIZE 5
#define ROW_SIZE TEST_04_ROW_SIZE
#define COL_SIZE TEST_04_COL_SIZE
extern char TEST_04[ROW_SIZE][COL_SIZE+1];
#define TEST_BOARD TEST_04
#endif

#ifdef TEST_CASE_05
#define TEST_05_ROW_SIZE 5
#define TEST_05_COL_SIZE 5
#define ROW_SIZE TEST_05_ROW_SIZE
#define COL_SIZE TEST_05_COL_SIZE
extern char TEST_05[ROW_SIZE][COL_SIZE+1];
#define TEST_BOARD TEST_05
#endif

// to check whether the boss exit when he blocked by himself. 
#ifdef TEST_CASE_06
#define TEST_06_ROW_SIZE 8
#define TEST_06_COL_SIZE 6
#define ROW_SIZE TEST_06_ROW_SIZE
#define COL_SIZE TEST_06_COL_SIZE
extern char TEST_06[ROW_SIZE][COL_SIZE+1];
#define TEST_BOARD TEST_06
#endif

// to check when all the cells around boss are bocked
#ifdef TEST_CASE_07
#define TEST_07_ROW_SIZE 8
#define TEST_07_COL_SIZE 6
#define ROW_SIZE TEST_07_ROW_SIZE
#define COL_SIZE TEST_07_COL_SIZE
extern char TEST_07[ROW_SIZE][COL_SIZE+1];
#define TEST_BOARD TEST_07
#endif

//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------

#endif
