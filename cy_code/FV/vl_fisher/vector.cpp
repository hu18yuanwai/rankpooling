#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string.h>
#include <set>
#include <iterator>
#include <math.h>
#include <algorithm>
using namespace std;
void test()
{
	int a[] = {1,2,2,3,3,2,1,21,32,34,34,2,3};
	vector<int>ivec(a,a+13);
	
	sort(ivec.begin(), ivec.end());
	copy(ivec.begin(), ivec.end(),ostream_iterator<int>(cout," "));
	cout<<endl;
	set<int> s(ivec.begin(), ivec.end());
	set<int>::iterator it;
	copy(s.begin(), s.end(),ostream_iterator<int>(cout," "));
	cout<<endl;

	int value = 0;
	vector<int>::iterator itv = ivec.begin();
	int startindex = 0,aa,b;
	for (it = s.begin();it != s.end(); it++)
	{
		aa = startindex;
		cout<<aa<<" ";
		while(*itv == *it && itv!= ivec.end())
		{
			ivec.erase(itv);
			startindex++;
		}
		b = startindex-1;
		cout<<b<<endl;
	}
	return ;
}
int main(int argc, char const *argv[])
{
	test();
	return 0;
}