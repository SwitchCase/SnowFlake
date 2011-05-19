#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cassert>
using namespace std;

int runningLetters(string text)
{
	int textLength = text.length();
	int * prefixFunction = new int[textLength];
	prefixFunction[0] = 0;
	int cur = 0;
	for (int i = 1; i < textLength; i++)
	{
		while (cur > 0 && text[cur] != text[i])
		    cur = prefixFunction[cur - 1];

		if (text[cur] == text[i])
		    cur++;

		prefixFunction[i] = cur;
	}
	return textLength - prefixFunction[textLength - 1];
}

int main() {
	int tc,n,x,result;
	char st[105];
	
	scanf("%d",&tc);
	while(tc--) {
		string s;

		scanf("%d",&x);
		while(x--) {
			scanf("%d",&n);
			scanf("%s",st);
			while(n--)	s.append(st,strlen(st));
		}
		assert(s.length()<=1000000);
		result=runningLetters(s);
		printf("%d\n",result);
	}
}
