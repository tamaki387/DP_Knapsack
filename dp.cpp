#include <string>
#include <fstream>
#include <iostream>
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

	//表の作成
	max_weight = max_weight+1;
	int** table_NW = new int*[num_of_items];
	for (int i = 0; i < num_of_items; ++i)
	{
		table_NW[i] = new int[max_weight];
	}
	table_NW[0][0] = 0;

	//表を埋める
	//一行目
	start = std::chrono::system_clock::now();//計測開始
	int N = 1000;//計測のため、同じ処理をN回繰り返す
	for (int ii = 0; ii < N; ++ii)
	{


		for (int j = 0; j < max_weight; ++j)
		{
			if(j >= item_weight[0])
			{
				table_NW[0][j] = item_value[0];
			}else
			{
				table_NW[0][j] = 0;
			}
		}
	//二行目以降
		for (int i = 1; i < num_of_items; ++i)
		{
			for (int j = 0; j < max_weight; ++j)
			{
				if(j < item_weight[i])
				{
					table_NW[i][j] = table_NW[i-1][j];
				}
				else
				{
					if (table_NW[i-1][j] > table_NW[i-1][j - item_weight[i]] + item_value[i])
					{
						table_NW[i][j] = table_NW[i-1][j];
					}
					else
					{
						table_NW[i][j] = table_NW[i-1][j - item_weight[i]] + item_value[i];
					}
				}
			}
		}
	}

	end = std::chrono::system_clock::now();//計測終了
	auto elapsed = std::chrono::duration_cast< std::chrono::milliseconds >(end - start).count();
    std::cout << elapsed <<"ms"<< std::endl;//タイム表示
    std::cout << table_NW[num_of_items-1][max_weight-1];
    return 0;
}