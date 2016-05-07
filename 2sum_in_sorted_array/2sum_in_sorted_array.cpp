#include<time.h>
#include<stdlib.h>
#include<assert.h>

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class TwoSum
{
	private:
		vector<int> arr;
		int x;
		vector< vector<int> > linear_ret;
		vector< vector<int> > quad_ret;
	public:
		void process_input();
		TwoSum() { srand(time(NULL)); }
		void find_sum_liner();
		void find_sum_quad();
};

void TwoSum::process_input()
{
	int size = 10+rand()%29;
	arr.clear(); arr.resize(size);
	for(int i=0; i<size; i++)
	{
		arr[i] = rand()% 100;
	}
	x = arr[rand()%size];
	sort(arr.begin(), arr.end());
	cout<<"2-sum = " << x << endl;
	for(int i=0; i<size; i++)
		cout << arr[i] << " ";
	cout << endl;

	find_sum_quad();
	find_sum_liner();
	if(linear_ret != quad_ret)
	{
		assert(false);
	}
	linear_ret.clear(); quad_ret.clear();
}
		
void TwoSum::find_sum_quad()
{
	for(int i=0; i<arr.size(); i++)
	{
		for(int j=i+1; j<arr.size(); j++)
		{
			if(arr[i]+arr[j] == x)
			{
				cout <<"arr["<<i<<"]= " << arr[i] <<", arr[" <<j<<"]= " << arr[j] << endl;
				quad_ret.push_back(vector<int>());
				quad_ret[quad_ret.size()-1].push_back(i);
				quad_ret[quad_ret.size()-1].push_back(j);
			}
		}
	}
}


void TwoSum::find_sum_liner()
{
	cout << "----- linear ----\n";
	int i=0, j= arr.size()-1;
	while(i <= j)
	{
		if(arr[i]+arr[j] == x)
		{
				cout <<"arr["<<i<<"]= " << arr[i] <<", arr[" <<j<<"]= " << arr[j] << endl;
				linear_ret.push_back(vector<int>());
				linear_ret[linear_ret.size()-1].push_back(i);
				linear_ret[linear_ret.size()-1].push_back(j);
				if(i<arr.size()-1)
				{
					if(arr[i] == arr[i+1])
						i++;
					else
						j--;
				}
				else
					i++;
		} else if(arr[i]+arr[j] > x)
		{
			j--;
		}
		else
		{
			i++;
		}
	}
}

int main()
{
	TwoSum obj1;
	obj1.process_input();

	return 0;
}
