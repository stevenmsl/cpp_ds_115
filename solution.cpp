#include "solution.h"
#include "util.h"
#include <unordered_set>
#include <numeric>
#include <iterator>
#include <unordered_map>
#include <queue>
#include <string>
#include <sstream>
#include <algorithm>
using namespace sol940;
using namespace std;

/*takeaways
  - Input: S = "rabbbit", T = "rabbit"
    - scan in 'r' from T , and scan entire S one char at a time
      - we found only one 'r' from S can produce 'r'
        for T
        - dp[1][1]=1, so is dp[1][7]=1
        - use 1 based index for convenience
        - so here we define dp[i][j] as
          how many subsequences for S[1..j]
          can produce to match T[1..i]
    - scan in 'a' from T, we are looking at "ra" now
      - dp[2][1] = 0, you can't produce "ra" from just a 'r' from S
      - dp[2][2] = dp[2][1] + dp[1][1] = 0 + 1 = 1
        - this is the key
          - T="ra", S="ra" (i=2, j=2)
          - since T[1] == S[1] (second char 'a' == 'a')
            - we extend every subsequence that have
              the length of i-1 forming from the
              first j-1 chars from S
            - plus subsequences of length of i
              using the first j-1 chars from S

*/

int Solution::findDistinct(string s, string t)
{
  const int m = t.size(), n = s.size();

  /*
    the number of subsequences we can get
    using the first j letters from S to form
    the first i letters from T
  */
  auto dp = vector<vector<int>>(m + 1, vector<int>(n + 1));

  /* don't choose anything from S to produce T
     which is an empty string
  */
  fill(begin(dp[0]), end(dp[0]), 1);

  /* start from S */
  for (auto i = 1; i <= m; i++)
    /* loop through S */
    for (auto j = 1; j <= n; j++)
      /* don't forget the ith letter is from t[i-1]
         - so if the incoming letters are different,
           introduce one additional letter from S
           is not helping, so it will be the same
           as dp[i][j-1]; just carry over
         - if they are the same, we extend every
           subsequence in dp[i-1][j-1] by one
      */
      dp[i][j] = dp[i][j - 1] + (t[i - 1] == s[j - 1] ? dp[i - 1][j - 1] : 0);

  return dp[m][n];
}
