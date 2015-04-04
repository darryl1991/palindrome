#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "merge.h"

using namespace std;

void mergesortstr (vector<string>& list, unsigned int low, unsigned int high)
{
    unsigned int mid;

    if (low < high)
    {
        mid=(low+high)/2;
        mergesortstr(list,low,mid);
        mergesortstr(list,mid+1,high);
        merge(list,low,high,mid);
    }

    return;
}

void merge(vector<string> &list, int low, int high, int mid)
{
	unsigned int i, j, k;
	vector<string> c;
    i = low;
    k = low;
    j = mid + 1;
    while (i <= mid && j <= high)
    {
        if (list.at(i).length() > list.at(j).length())
        {
            c.push_back(list[i]);
            k++;
            i++;
        }
        else
        {
        	c.push_back(list[j]);
            k++;
            j++;
        }
    }
    while (i <= mid)
    {
    	c.push_back(list[i]);
        k++;
        i++;
    }
    while (j <= high)
    {
    	c.push_back(list[j]);
        k++;
        j++;
    }
    int x = 0;
    for (i = low; i < k; i++)
    {
    	list[i] = c[x];
        x++;
    }
    return;
}
