// A2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>

#define MODULO 1000000007

int main()
{
	std::ifstream inp_file("weak_typing_chapter_2_input.txt");
	std::ofstream out_file("output.txt");

	int test_count = 0;
	inp_file >> test_count;
	for (int test_index = 0; test_index < test_count; test_index++)
	{
		int line_length;
		inp_file >> line_length;
		inp_file.ignore(INT_MAX, '\n');

		std::string line;
		std::getline(inp_file, line);

		for (auto it_first = line.begin(); it_first != line.end(); it_first++)
		{
			if (*it_first != 'F')
			{
				for (auto it = line.begin(); it != it_first; it++)
					*it = *it_first;

				break;
			}
		}

		for (auto it_last = line.rbegin(); it_last != line.rend(); it_last++)
		{
			if (*it_last != 'F')
			{
				for (auto it = line.rbegin(); it != it_last; it++)
					*it = *it_last;

				break;
			}
		}

		for (int index = 0; index < line.length(); index++)
		{
			if (line[index] == 'X')
			{
				auto nearest_x_pos = line.find_first_of('X', index + 1);
				auto nearest_o_pos = line.find_first_of('O', index + 1);

				if (nearest_x_pos != std::string::npos)
				{
					if (nearest_x_pos < nearest_o_pos)
					{
						std::fill(line.begin() + index, line.begin() + nearest_x_pos, 'X');						
					}

					index = nearest_x_pos - 1;
				}
				else
					break;				
			}
		}

		for (int index = 0; index < line.length(); index++)
		{
			if (line[index] == 'O')
			{
				auto nearest_o_pos = line.find_first_of('O', index + 1);
				auto nearest_x_pos = line.find_first_of('X', index + 1);

				if (nearest_o_pos != std::string::npos)
				{
					if (nearest_o_pos < nearest_x_pos)
					{
						std::fill(line.begin() + index, line.begin() + nearest_o_pos, 'O');
					}

					index = nearest_o_pos - 1;
				}
				else
					break;
			}
		}

		int last_not_f_pos = 0;
		std::vector<int64_t> switch_counts(line.size(), 0);
		for (int index = 1; index < line.length(); index++)
		{
			if (line[index] != line[index - 1])
			{
				// F -> X/O
				if (line[index - 1] == 'F')
				{
					switch_counts[index] = switch_counts[index - 1] + last_not_f_pos + 1;
				}
				// X/O -> F
				else if (line[index] == 'F')
				{
					switch_counts[index] = switch_counts[index - 1];
				}
				// X/O -> O/X
				else
				{
					switch_counts[index] = switch_counts[index - 1] + index;
				}
			}
			else
			{
				switch_counts[index] = switch_counts[index - 1];
			}

			switch_counts[index] %= MODULO;

			if (line[index] != 'F')
				last_not_f_pos = index;
		}

		int64_t total_switch_count = 0;
		for (int index = 0; index < line.length(); index++)
		{
			total_switch_count += switch_counts[index];
			total_switch_count %= MODULO;
		}

		out_file << "Case #" << test_index + 1 << ": " << total_switch_count << std::endl;
	}

	inp_file.close();
	out_file.close();

	return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
