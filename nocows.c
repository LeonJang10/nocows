/*
ID: lindan1
LANG: C
TASK: nocows
*/

#include<stdio.h>
#include<stdlib.h>

#define maxarray 25000

FILE* result;

int n, h, count, combo[203][203];

void make();

void queue();

int combination(int want, int base);

int main()
{
	FILE* in, * out;
	int i, j;
	in = fopen("nocows.in", "r");
	out = fopen("nocows.out", "w");
	result = fopen("result.txt", "w");
	fscanf(in, "%d", &n);
	fscanf(in, "%d", &h);
	for (i = 0; i < 203; i++)
		for (j = 0; j < 203; j++)
			combo[i][j] = 0;
	for (i = 0; i < 203; i++)
		combo[0][i] = 1;
	count = 0;
	make();
	if (n % 2 == 1)
		if (h > 1)
			queue();
		else
			if (n == 1)
				count++;
	fprintf(out, "%d\n", count);
	fclose(in);
	fclose(out);
	fclose(result);
}

void make()
{
	int i, j, k, upper, lower;
	for(i=1; i<=10; i++)
		for(j=1; j<=i/2; j++)
		{
			if (i != j)
			{
				upper = 1;
				lower = 1;
				for (k = 1; k <= j; k++)
					lower = lower * k;
				for (k = i; k > i - j; k--)
					upper = upper * k;
				combo[j][i] = upper / lower;
			}
			else
				combo[i][j] = 1;
			combo[i - j][i] = combo[j][i];
		}
}

void queue()
{
	int i, start, end, levelcount[maxarray], level[maxarray], parent[maxarray], usednode[maxarray], levelnode[maxarray];
	for (i = 0; i < maxarray; i++)
	{
		levelcount[i] = 0;
		level[i] = 0;
		parent[i] = -1;
		usednode[i] = 0;
		levelnode[i] = 0;
	}
	start = -1;
	end = 0;
	level[0] = 3;
	level[1] = 3;
	for (i = 0; i < 2; i++)
	{
		levelnode[end] = (i + 1) * 2;
		usednode[end] = 3 + levelnode[end];
		levelcount[end] = combination(levelnode[end]/2, 2);
		if (level[end] == h && usednode[end] == n)
			count = count + levelcount[end];
		end++;
	}
	start++;
	while (usednode[start]!=-1&&level[end]<=h)
	{
		for(i=0; i<levelnode[start]; i++)
		{
			level[end] = level[start]+1;
			parent[end] = start;
			levelnode[end] = (i + 1)*2;
			usednode[end] = usednode[start] + levelnode[end];
			if (usednode[end] <= n)
			{
				if (usednode[end - 1] == -1)
					usednode[end] = 0;
				levelcount[end] = (combination(levelnode[end]/2, levelnode[start]) * levelcount[start]) % 9901;
				if (level[end] == h && usednode[end] == n)
					count = (count + levelcount[end]) % 9901;
				end++;
				end = end % maxarray;
				printf("start=%d end=%d level=%d\n\n", start, end, level[end]);
			}
			else
				usednode[end] = -1;
		}
		start++;

		start = start % maxarray;
	}
}

int combination(int want, int base)
{
	int i;
	if (want > base / 2)
		want = base - want;
	if (combo[want][base] > 0)
	{
		return combo[want][base];
	}
	else
	{
		combo[want][base] = (combination(want - 1, base - 1) + combination(want, base - 1))%9901;
		//printf("choose %d from %d=%d\n\n", want, base, combo[want][base]);
	//	combo[base - want][base] = combo[want][base];
		return combo[want][base];
	}
	return combo[want][base];
}
