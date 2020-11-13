#include <string>
#include <fstream>
#include <iostream>
#include <bitset>
#include <cmath>
#include <chrono>

int main(int argc, char const *argv[])
{
	std::string filename = "dp_items.txt";
	int num_of_items = 12;//詰める荷物の種類
	int max_weight = 100;//ナップサックの容量の限界
	std::chrono::system_clock::time_point start,end;//処理時間の計測用

	//データのインプット
	std::ifstream ifs(filename);
	ifs >> num_of_items;
	std::string* item_name = new std::string[num_of_items];
	int* item_weight = new int[num_of_items];
	int* item_value = new int[num_of_items];
	for (int i = 0; i < num_of_items; ++i)
	{
		ifs >> item_name[i];
		ifs >> item_weight[i];
		ifs >> item_value[i];
		//std::cout << item_value[i] << std::endl;
	}

	max_weight = max_weight + 1;
	int max_i = std::pow(2,num_of_items);
	int max;
	start = std::chrono::system_clock::now();//計測開始
	int N = 1000;//計測のため、同じ処理をN回繰り返す
	for (int ii = 0; ii < N; ++ii)
	{
		for (int i = 0; i < max_i; ++i)
		{
			std::string i_str = std::bitset<12>(i).to_string();
			int tmp_sum_value=0;
			int tmp_sum_weight=0;
			for (int j = 0; j < num_of_items; ++j)
			{
				if (i_str[num_of_items - 1 - j]=='1')
				{
					tmp_sum_value = tmp_sum_value + item_value[j];
					tmp_sum_weight = tmp_sum_weight + item_value[j];
				}
			}
			if (max < tmp_sum_value && tmp_sum_weight < max_weight)
			{
				max = tmp_sum_value;
			}
		}
	}
	end = std::chrono::system_clock::now();//計測終了
	auto elapsed = std::chrono::duration_cast< std::chrono::milliseconds >(end - start).count();
    std::cout << elapsed <<"ms"<< std::endl;//タイム表示
    std::cout << max;
    return 0;
}