#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_set>
#define LEN 100000
using namespace std;

vector<string> stop_words = { "a", "an", "and", "are", "as", "at", "be", "by", "for", "from", "has", "he", "in", "is", "it", "its", "of", "on", "that", "the", "to", "was", "were", "will", "with" };
string scepChar = ",.?!@#$%^&*()[]{}'¹<>";
int lenSC = scepChar.size();

string delSpecChar(string word) {

    const string empty;
    bool haveSpecChar = false;
    int len = word.size();
    for (int i = 0; i < len; i++) {

        for (int j = 0; j < lenSC; j++) {

            if (word[i] == scepChar[j]) {
                word.replace(i, 1, empty);
                haveSpecChar = true;
                break;
            }
        }

        if (!haveSpecChar) {
            word[i] = tolower(word[i]);
            haveSpecChar = false;
        }
    }

    return word;
}

vector<int> vectorize(vector<string> &tokens, vector<string> &merge) {

    vector<int> vecTxt;
    for (int i = 0; i < merge.size(); i++)
    {
        vecTxt.push_back(count(tokens.begin(), tokens.end(), merge[i]));
    }

    return vecTxt;
}

double cosineSimilarity(vector<int> &vector1, vector<int> &vector2) {

    double cosSim = 0;

    double mul = 0.0, d_a = 0.0, d_b = 0.0;
    int size = 0;
    if (vector1.size() < vector2.size()) size = vector2.size();
    else size = vector1.size();

    for (int i = 0; i < size; i++)
    {
        if (vector1[i] * vector2[i] != 0) mul += vector1[i] * vector2[i];
        if (i <= vector1.size()) d_a += vector1[i] * vector1[i];
        d_b += vector2[i] * vector2[i];
    }
    cosSim = mul / (sqrt(d_a) * sqrt(d_b));

    return cosSim;
}

int main() {

    string filename1 = "test1.txt";
    string filename2 = "test2.txt";

    ifstream fin1, fin2;
    fin1.open(filename1);
    fin2.open(filename2);

    vector<string> tokens1;
    vector<string> tokens2;

    string word;

    int lenTok1 = 0, lenTok2 = 0;
    while (!fin1.eof()) {

        fin1 >> word;
        word = delSpecChar(word);

        if (!(find(stop_words.begin(), stop_words.end(), word) != stop_words.end())) {
            
            tokens1.push_back(word); lenTok1++;
        }
    }
    fin1.close();

    while (!fin2.eof()) {

        fin2 >> word;
        word = delSpecChar(word);

        if (!(find(stop_words.begin(), stop_words.end(), word) != stop_words.end())) {

            tokens2.push_back(word); lenTok2++;
        }
    }
    fin2.close();


    vector<string> merge = tokens1;
    merge.insert(merge.end(), tokens2.begin(), tokens2.end());

    unordered_set<string> s(merge.begin(), merge.end());
    merge.assign(s.begin(), s.end());


    cout << endl;
    for (int i = 0; i < merge.size(); i++)
    {
        cout << merge[i] << "\t" << i << endl;
    }

    vector<int> vecTxt1;
    vector<int> vecTxt2;
    vecTxt1 = vectorize(tokens1, merge);
    vecTxt2 = vectorize(tokens2, merge);
    for (int i = 0; i < vecTxt1.size(); i++)
    {
        cout << vecTxt1[i] <<  "\t";
    }
    cout << endl;
    for (int i = 0; i < vecTxt2.size(); i++)
    {
        cout << vecTxt2[i] << "\t";
    }

    double cosSim = cosineSimilarity(vecTxt1, vecTxt2);
    cout << "\nResult = " << cosSim << endl;

    system("pause");
    return 0;
}