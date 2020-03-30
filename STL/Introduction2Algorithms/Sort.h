#pragma once

template<class T>
void InsertSort(T* arr, int len)
{
	for (int i = 1; i < len; ++i)
	{
		T ope = arr[i];
		int j = i - 1;
		while (j >= 0)
		{
			if (ope < arr[j])
			{
				arr[j + 1] = arr[j];
				j--;
			}
			else
			{
				break;
			}
		}
		arr[j+1] = ope;
	}
}