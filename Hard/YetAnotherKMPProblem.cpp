/*
 * Yet Another KMP Problem (Hard)
 * https://www.hackerrank.com/challenges/kmp-problem/problem
 */

#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

void minFreqCharacter (vector<int> &x, int &min_count_index);
void findLeftRightCharacters(const vector<int> &x, const int &min_freq_index,
                             int &left_char_index, int &right_char_index);

    /*
     * Complete the kmp function below.
     */
    string kmp(vector<int> x) {
        string s = "";
        // Find character with minimum occurence
        int min_freq_index = 0;
        minFreqCharacter(x, min_freq_index);

        // Subtract 1 from the count of the character with min occurence
        // and set string = the char with min occurence
        --x[min_freq_index];
        s += (97 + min_freq_index);

        // Find a character on left and right side of the min freq character
        int left_char_index, right_char_index;
        findLeftRightCharacters(x, min_freq_index, left_char_index, right_char_index);

        // Add all the characters according to their occurence to the string if
        // 1. Minimum frequency = 1
        // 2. There exists a character on left side of the min freq char
        // 3. There is only one character with non-zero frequency
        if (x[min_freq_index] < 2 ||
            left_char_index >= 0 ||
            (right_char_index < 0 && left_char_index < 0)){

            for (int i = 0; i < x.size(); i++) {
                for (int j = 0; j < x[i]; j++) {
                    s += 97 + i;
                }
            }
        } else {
            // Append min_freq char and right side char as a group
            for (int i = 0; i < x[min_freq_index]; i++) {
                s += (97 + min_freq_index);
                s += (97 + right_char_index);
                --x[right_char_index];
            }
            x[min_freq_index] = 0;
            // Apend rest of the characters in order
            for (int i = 0; i < x.size(); i++) {
                for (int j = 0; j < x[i]; j++) {
                    s += 97 + i;
                }
            }
        }

        return s;
    }

void minFreqCharacter (vector<int> &x, int &min_count_index) {
    int min_count = 1000001;
    for (int i = 0; i < x.size(); i++) {
        if (min_count > x[i] && x[i] != 0) {
            min_count_index = i;
            min_count = x[i];
        }
    }
}

void findLeftRightCharacters (const vector<int> &x, const int &min_freq_index, int &left_char_index, int &right_char_index) {
    left_char_index = -1;
    right_char_index = -1;
    for (int i = 0; i < x.size(); i++) {
        if (x[i] > 0) {
            if (left_char_index < 0 && i < min_freq_index)
                left_char_index = i;
            else if (right_char_index < 0 && i > min_freq_index)
                right_char_index = i;
        }
    }
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string x_temp_temp;
    getline(cin, x_temp_temp);

    vector<string> x_temp = split_string(x_temp_temp);

    vector<int> x(26);

    for (int x_itr = 0; x_itr < 26; x_itr++) {
        int x_item = stoi(x_temp[x_itr]);

        x[x_itr] = x_item;
    }

    string result = kmp(x);

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
