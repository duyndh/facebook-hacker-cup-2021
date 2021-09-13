// A1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <string>

int main()
{
	std::ifstream inp_file("weak_typing_chapter_1_input.txt");
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
		
		int ready_switch = false;
		int switch_count = 0;
		int is_left_hand = false;
		for (int char_index = 0; char_index < line.length(); char_index++)
		{
			if (line[char_index] != 'F')
			{
				if (!ready_switch)
				{
					is_left_hand = line[char_index] == 'X';
					ready_switch = true;
				}
				else
				{
					if (line[char_index] == 'X')
					{
						if (!is_left_hand)
						{
							switch_count++;
							is_left_hand = !is_left_hand;
						}
					}
					else if (line[char_index] == 'O')
					{
						if (is_left_hand)
						{
							switch_count++;
							is_left_hand = !is_left_hand;
						}
					}
				}
			}
		}

		out_file << "Case #" << test_index + 1 << ": " << switch_count << std::endl;
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
