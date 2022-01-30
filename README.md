# Rebel-14.1.02

Licensed under the GNU General Public License v3.0


Cleans up the code base of Rebel-14.1 and add enhanced NNUE capability. Should run straight out of VS2019. You may need to unzip the NNUE's in the folder embedded-nnues.

[More information on Rebel-14](http://rebel13.nl/windows/rebel-14.html)

Added several new NNUE.nets designed to play in style of Tal, which they'll do provided the opposition is of similar Elo (3100-3150), it helps to use a gambit opening book too.


Re-organised the directories and project structure.

Gambit Opening Book, test games against a pool of around 3100 Elo rated engines, fast time control 40/10

10-Minute-Blitzer results  (3100+65=3165 Elo)
Rank | Name | Elo | +/- | Games | Score | Draw
| :---: | :---: | :---: | :---: | :---: | :---: | :---:
   0  | Rebel-14.1.02-ChrisW-NNUE-Tal-0-10MinuteBlitzer |       65 |       19 |     1000 |    59.3% |    23.6%
   1 |  Combusken_1.4.0 |                                      -21 |       41 |      200 |    47.0%  |   28.0%
   2 |  Clover_2.3.1 |                                         -24 |       42 |      200 |    46.5% |    26.0%
   3 |  Counter_4.0 |                                          -35 |       41 |      200 |    45.0% |    27.0%
   4 |  Winter_0.9 |                                            -37 |       43 |      200 |    44.8% |    21.5%
   5 |  Marvin_5.1 |                                            -238 |       53 |      200 |    20.3%  |   15.5%



5-Minute-Blitzer results (3100+10=3110 Elo)
Rank | Name | Elo | +/- | Games | Score | Draw
| :---: | :---: | :---: | :---: | :---: | :---: | :---:
   0  |Rebel-14.1.02-ChrisW-NNUE-Tal-0-5MinuteBlitzer      | 10     |  19   |  1000 |   51.4%  |  24.3%
   1  |Counter_4.0                  |   33     |  41    |  200  |  54.8%   | 28.5%
   2  |Combusken_1.4.0          |       26     |  44   |   200  |  53.8%   | 18.5%
   3  |Winter_0.9             |         24   |    41    |  200  |  53.5%   | 29.0%
   4  |Clover_2.3.1          |          19   |    42   |   200  |  52.8%  |  24.5%
   5 | Marvin_5.1         |           -164   |    46  |    200  |  28.0%  |  21.0%
   
   
   
2-Minute-Blitzer results (3100+3=3103 Elo)
Rank | Name | Elo | +/- | Games | Score | Draw
| :---: | :---: | :---: | :---: | :---: | :---: | :---:
   0 |Rebel-14.1.02-ChrisW-NNUE-Tal-0-2MinuteBlitzer   |     3   |    19  |   1000  |  50.5% |   22.8%
   1 |Combusken_1.4.0        |         53|       43|      200|    57.5% |   23.0%
   2| Winter_0.9               |       31  |     42  |    200 |   54.5%  |  26.0%
   3 |Counter_4.0                |     28    |   42    |  200  |  54.0%   | 25.0%
   4| Clover_2.3.1                 |   10      | 43  |    200   | 51.5% |   20.0%
   5| Marvin_5.1                 |   -147      | 46   |   200  |  30.0%   | 20.0%



1-Minute-Blitzer results (3100-5=3095 Elo)
Rank | Name | Elo | +/- | Games | Score | Draw
| :---: | :---: | :---: | :---: | :---: | :---: | :---:
   0| Rebel-14.1.02-ChrisW-NNUE-Tal-0-1MinuteBlitzer   |   -5   |   19  |  1000  | 49.3%  | 23.7%
   1| Winter_0.9             |        53  |    43  |   200  | 57.5% |  22.0%
   2 |Combusken_1.4.0        |        51   |   43  |   200  | 57.3%  | 21.5%
   3 |Clover_2.3.1          |         42   |   43  |   200 |  56.0%  | 22.0%
   4 |Counter_4.0         |           31    |  41  |   200 |  54.5% |  29.0%
   5 |Marvin_5.1        |           -160   |   45  |   200 |  28.5%  | 24.0%


Source is set to compile AVX2 version. This can be changed to SSE in file SIMD.CPP ...

#define USE_SSE true

#define USE_AVX2 false

Source is set to compile 5-Minute Blitz version. This can be changed in file NNUE.CPP ...

//#include "embedded-nnues/resume-iter=1-pos=1.2B-d6+d7-lambda=0.5-lr=0.000004-epoch=147-arch=3-loss=0.16804.txt"

//#include "embedded-nnues/ChrisW-NNUE-Tal-10-MinuteBlitz.txt"

#include "embedded-nnues/ChrisW-NNUE-Tal-5-MinuteBlitz.txt"
