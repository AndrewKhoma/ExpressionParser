#pragma comment(linker, "/STACK:100000000")
#define _SCL_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma GCC ostarimize("O500")
#include "MathExpression.h"
#define _USE_MATH_DEFINES
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <algorithm>
#include <memory.h>
#include <iostream>
#include <iterator>
#include <ostream>
#include <iomanip>
#include <cstring>
#include <sstream>
#include <cassert>
#include <cstdlib>
#include <istream>
#include <fstream>
#include <climits>
#include <complex>
#include <memory>
#include <string>
#include <bitset>
#include <vector>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <map>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef complex <ld> cd;

const bool db = false;

#define fs first
#define sd second
#define mp make_pair
#define pb push_back
#define ppb pop_back

#define inf 1000000007
#define nmax 100100
#define mmax 100100
#define eps 1e-12

void test(const char* input) 
{
	try 
	{
		Parser p(input);
		auto result = eval(p.parse());
		cout << fixed << setprecision(3) << "Your result = " << result << '\n';
	}
	catch (std::exception& e) {
		std::cout << input << " : exception: " << e.what() << '\n';
	}
}

char Expression_input[nmax];

int main()
{
#ifdef Ahoma
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
#endif
	scanf("%s\n", Expression_input);
	test(Expression_input);
	return 0;
}