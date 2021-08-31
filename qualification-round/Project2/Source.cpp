#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>

enum CharType
{
	Vowel = 0,
	Consonant = 1,
	CharType_Count
};

int main()
{
	std::ifstream inp_file("consistency_chapter_1_input.txt");
	std::ofstream out_file("output.txt");

	int test_count = 0;
	inp_file >> test_count;

	inp_file.ignore(INT_MAX, '\n');
	
	std::set<char> vowels = {'A', 'E', 'I', 'O', 'U'};

	for (int test_index = 0; test_index < test_count; test_index++)
	{
		std::string line;
		std::getline(inp_file, line);

		std::map<char, int> freq_map[CharType_Count];
		for (char c : line)
		{
			int char_type = CharType::Vowel;
			if (vowels.find(c) == vowels.end())
				char_type = CharType::Consonant;

			if (freq_map[char_type].find(c) == freq_map[char_type].end())
				freq_map[char_type][c] = 1;
			else
				freq_map[char_type][c]++;
		}
		int top_freq[CharType_Count] = { 0 };
		int normal_freq_sum[CharType_Count] = { 0 };

		for (int char_type = 0; char_type < CharType_Count; char_type++)
		{
			std::vector<int> freqs;
			freqs.reserve(freq_map[char_type].size());
			for (auto freq_pair : freq_map[char_type])
				freqs.push_back(freq_pair.second);

			std::sort(freqs.begin(), freqs.end(), [](int left, int right) { return left > right; });

			if (freqs.size())
				top_freq[char_type] = freqs[0];
			if (freqs.size() > 1)
				normal_freq_sum[char_type] = std::accumulate(std::next(freqs.begin()), freqs.end(), 0);
		}

		int min_step_count = INT_MAX;
		for (int char_type = 0; char_type < CharType_Count; char_type++)
		{
			int current_step_count = normal_freq_sum[char_type] << 1;
			int opposite_step_count = top_freq[!char_type] + normal_freq_sum[!char_type];

			int step_count = current_step_count + opposite_step_count;
			if (step_count < min_step_count)
				min_step_count = step_count;
		}

		out_file << "Case #" << test_index + 1 << ": " << min_step_count << std::endl;
	}

	inp_file.close();
	out_file.close();

	return 0;
}