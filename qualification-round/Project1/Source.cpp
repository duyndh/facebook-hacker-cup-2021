#include <fstream>
#include <iostream>
#include <vector>
#include <string>

int main()
{
	std::ifstream inp_file("xs_and_os_input.txt");
	std::ofstream out_file("output.txt");

	int test_count = 0;
	inp_file >> test_count;
	for (int test_index = 0; test_index < test_count; test_index++)
	{
		int table_size = 0;
		inp_file >> table_size;
		inp_file.ignore(INT_MAX, '\n');
		
		std::vector<std::vector<char>> table(table_size);
		std::vector<int> row_sum(table_size, 0);
		std::vector<int> col_sum(table_size, 0);

		for (int row_index = 0; row_index < table_size; row_index++)
		{
			table[row_index].resize(table_size);
			
			std::string line;
			std::getline(inp_file, line);
						
			for (int col_index = 0; col_index < table_size; col_index++)
			{
				char cell = line[col_index];
				table[row_index][col_index] = cell;

				if (cell == 'O')
				{
					row_sum[row_index] = -1;
					col_sum[col_index] = -1;
				}
				else if (cell == 'X')
				{
					if (row_sum[row_index] != -1)
						row_sum[row_index]++;

					if (col_sum[col_index] != -1)
						col_sum[col_index]++;
				}
			}
		}

		int max_sum = -1;
		for (int row_index = 0; row_index < table_size; row_index++)
		{
			if (row_sum[row_index] != -1 && row_sum[row_index] > max_sum)
				max_sum = row_sum[row_index];
		}

		for (int col_index = 0; col_index < table_size; col_index++)
		{
			if (col_sum[col_index] != -1 && col_sum[col_index] > max_sum)
				max_sum = col_sum[col_index];
		}

		int set_count = 0;
		if (max_sum != -1)
		{
			if (max_sum == table_size - 1)
			{
				for (int row_index = 0; row_index < table_size; row_index++)
				{
					for (int col_index = 0; col_index < table_size; col_index++)
					{
						if (table[row_index][col_index] == '.')
						{
							if (row_sum[row_index] == table_size - 1 || col_sum[col_index] == table_size - 1)
								set_count++;
						}
					}
				}
			}
			else
			{
				for (int row_index = 0; row_index < table_size; row_index++)
					if (row_sum[row_index] == max_sum)
						set_count++;
				for (int col_index = 0; col_index < table_size; col_index++)
					if (col_sum[col_index] == max_sum)
						set_count++;
			}
		}

		out_file << "Case #" << test_index + 1 << ": ";
		if (max_sum == -1)
			out_file << "Impossible" << std::endl;
		else
			out_file << table_size - max_sum << ' ' << set_count << std::endl;
	}

	inp_file.close();
	out_file.close();

	return 0;
}