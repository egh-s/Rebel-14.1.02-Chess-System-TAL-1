# Rebel-14.1.02

Cleans up the code base of Rebel-14.1 and add enhanced NNUE capability. Should run straight out of VS2019. You may need to unzip the NNUE's in the folder embedded-nnues.

http://rebel13.nl/windows/rebel-14.html

Added two new NNUE.nets designed to play in style of Tal, which they'll do provided the opposition is of similar Elo (3100-3150), it helps to use a gambit opening book too.

Re-organised the directories and project structure.

Gambit Opening Book, test games against a pool of around 3100 engines

Rank | Name | Elo | +/- | Games | Score | Draw
| :---: | :---: | :---: | :---: | :---: | :---: | :---:
   0  | Rebel-14.1.02-ChrisW-NNUE-Tal-0-10MinuteBlitzer |       65 |       19 |     1000 |    59.3% |    23.6%
   1 |  Combusken_1.4.0 |                                      -21 |       41 |      200 |    47.0%  |   28.0%
   2 |  Clover_2.3.1 |                                         -24 |       42 |      200 |    46.5% |    26.0%
   3 |  Counter_4.0 |                                          -35 |       41 |      200 |    45.0% |    27.0%
   4 |  Winter_0.9 |                                            -37 |       43 |      200 |    44.8% |    21.5%
   5 |  Marvin_5.1 |                                            -238 |       53 |      200 |    20.3%  |   15.5%


Rank | Name | Elo | +/- | Games | Score | Draw
| :---: | :---: | :---: | :---: | :---: | :---: | :---:
   0  |Rebel-14.1.02-ChrisW-NNUE-Tal-0-5MinuteBlitzer      | 10     |  19   |  1000 |   51.4%  |  24.3%
   1  |Counter_4.0                  |   33     |  41    |  200  |  54.8%   | 28.5%
   2  |Combusken_1.4.0          |       26     |  44   |   200  |  53.8%   | 18.5%
   3  |Winter_0.9             |         24   |    41    |  200  |  53.5%   | 29.0%
   4  |Clover_2.3.1          |          19   |    42   |   200  |  52.8%  |  24.5%
   5 | Marvin_5.1         |           -164   |    46  |    200  |  28.0%  |  21.0%

Source is set to compile AVX2 version. This can be changed to SSE in file SIMD.CPP ...

#define USE_SSE true

#define USE_AVX2 false

Source is set to compile 5-Minute Blitz version. This can be changed in file NNUE.CPP ...

//#include "embedded-nnues/resume-iter=1-pos=1.2B-d6+d7-lambda=0.5-lr=0.000004-epoch=147-arch=3-loss=0.16804.txt"

//#include "embedded-nnues/ChrisW-NNUE-Tal-10-MinuteBlitz.txt"

#include "embedded-nnues/ChrisW-NNUE-Tal-5-MinuteBlitz.txt"
