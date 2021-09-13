// B.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

int main()
{
	std::ifstream inp_file("traffic_control_input.txt");
	std::ofstream out_file("output.txt");

	int test_count = 0;
	inp_file >> test_count;
	for (int test_index = 0; test_index < test_count; test_index++)
	{
		int n_rows, n_cols, tl_br, tr_bl;
		inp_file >> n_rows >> n_cols >> tl_br >> tr_bl;

		bool is_possible = true;
		std::vector<std::vector<int>> town(n_rows);
		for (int row = 0; row < n_rows; row++)
		{
			town[row].resize(n_cols);

			if (!row)
				std::fill(town[row].begin(), town[row].end(), 1);
			else
				std::fill(town[row].begin(), town[row].end(), 1000);

			town[row][0] = town[row][n_cols - 1] = 1;
		}

		town[n_rows - 1][n_cols - 1] = tl_br - (n_cols + n_rows - 2);
		if (town[n_rows - 1][n_cols - 1] < 1)
			is_possible = false;

		town[n_rows - 1][0] = tr_bl - (n_cols + n_rows - 2);
		if (town[n_rows - 1][0] < 1)
			is_possible = false;

		out_file << "Case #" << test_index + 1 << ": " << (is_possible ? "Possible" : "Impossible") << std::endl;

		if (is_possible)
		{
			for (int row = 0; row < n_rows; row++)
			{
				for (int col = 0; col < n_cols; col++)
				{
					if (col)
						out_file << ' ';
					out_file << town[row][col];
				}

				out_file << std::endl;
			}
		}
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
