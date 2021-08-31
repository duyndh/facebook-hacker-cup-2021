#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <iomanip>
#include <queue>

void BFS(char root, const std::map<char, std::list<char>> &graph, int min_distances_from_root[CHAR_MAX])
{
	std::queue<std::tuple<char, int>> next_queue;
	next_queue.push(std::tuple<char, int>(root, 0));

	while (!next_queue.empty())
	{
		auto current_tup = next_queue.front();
		next_queue.pop();

		char current = std::get<0>(current_tup);
		int depth = std::get<1>(current_tup);

		if (graph.find(current) != graph.end())
		{
			for (char next : graph.at(current))
			{
				if (min_distances_from_root[next] == -1 && next != root)
				{
					next_queue.push(std::tuple<char, int>(next, depth + 1));
					min_distances_from_root[next] = depth + 1;
				}
			}
		}
	}	
}

int main()
{
	std::ifstream inp_file("consistency_chapter_2_input.txt");
	std::ofstream out_file("output.txt");

	int test_count = 0;
	inp_file >> test_count;

	inp_file.ignore(INT_MAX, '\n');

	for (int test_index = 0; test_index < test_count; test_index++)
	{
		std::string input_str;
		std::getline(inp_file, input_str);

		int replacement_count;
		inp_file >> replacement_count;

		inp_file.ignore(INT_MAX, '\n');

		std::map<char, std::list<char>> graph;
		for (int replacement_index = 0; replacement_index < replacement_count; replacement_index++)
		{
			std::string replacement_str;
			std::getline(inp_file, replacement_str);

			char src_char = replacement_str[0];
			char dst_char = replacement_str[1];

			if (graph.find(src_char) == graph.end())
			{
				std::list<char> link_list;
				link_list.push_back(dst_char);
				graph.insert(std::pair<char, std::list<char>>(src_char, link_list));
			}
			else
			{
				graph[src_char].push_back(dst_char);
			}
		}

		std::map<char, int> input_occurrences;
		for (char c : input_str)
		{
			if (input_occurrences.find(c) == input_occurrences.end())
				input_occurrences[c] = 1;
			else
				input_occurrences[c]++;
		}

		int64_t min_step = INT64_MAX;

		std::cout << input_str << std::endl;

		if (input_occurrences.size() == 1)
			min_step = 0;
		else
		{
			int min_distances[CHAR_MAX][CHAR_MAX];
			for (int src_index = 0; src_index < _countof(min_distances); src_index++)
			{
				for (int dst_index = 0; dst_index < _countof(min_distances); dst_index++)
				{
					if (src_index == dst_index)
						min_distances[src_index][dst_index] = 0;
					else
						min_distances[src_index][dst_index] = -1;
				}
			}

			for (const auto& link_pair : graph)
			{
				char root = link_pair.first;
				BFS(root, graph, min_distances[root]);
			}

			/*std::cout << "    ";
			for (char dst = 'A'; dst <= 'Z'; dst++)
				std::cout << std::setw(4) << dst;
			std::cout << std::endl;
			for (char src = 'A'; src <= 'Z'; src++)
			{
				std::cout << src << "   ";
				for (char dst = 'A'; dst <= 'Z'; dst++)
				{
					if (min_distances[src][dst] != -1)
						std::cout << std::setw(4) << min_distances[src][dst];
					else
						std::cout << std::setw(4) << " ";
				}
				std::cout << std::endl;
			}*/

			for (char dst = 'A'; dst <= 'Z'; dst++)
			{
				int64_t step = 0;

				for (auto src_pair : input_occurrences)
				{
					char src = src_pair.first;

					if (min_distances[src][dst] == -1)
					{
						step = INT64_MAX;
						break;
					}

					step += (int64_t)min_distances[src][dst] * input_occurrences[src];
				}

				if (step < min_step)
					min_step = step;
			}
		}

		if (min_step == INT64_MAX)
			min_step = -1;

		out_file << "Case #" << test_index + 1 << ": " << min_step << std::endl;

		std::cout << min_step << std::endl;
		std::cout << std::endl;
		continue;
	}

	inp_file.close();
	out_file.close();

	return 0;
}