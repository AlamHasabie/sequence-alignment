#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

#include "scoringMatrix.cpp"

using namespace std;


map<char, int> initAlphaEnum(vector<char> alphabet){
    int i;
    map<char, int> alphEnum;
    for (i=0; i<alphabet.size(); i++){
        alphEnum.insert(pair<char, int>(alphabet[i], i));
    }

    return alphEnum;
}


vector<string> nw(int choice, string seq1, string seq2, vector<vector<int>> simMatrix, map<char, int> alphEnum, int gapPenalty){
    int i, j, m, n;
    int score, scoreDiag, scoreUp, scoreLeft;
    vector<vector <int>> mat;

    string alignment1;
    string alignment2;

    m = seq1.length();
    n = seq2.length();

   

    mat = generateMatrix(choice, seq1, seq2, simMatrix, alphEnum, gapPenalty);

    i = m;
    j = n;

    while (i && j){
        
        score = mat[i][j];
        scoreDiag = mat[i-1][j-1];
        scoreUp = mat[i-1][j];
        scoreLeft = mat[i][j-1];

        map<char, int>::iterator it; 
        it = alphEnum.find(seq1[i-1]);
        int indexi = it->second;
        it = alphEnum.find(seq2[j-1]);
        int indexj = it->second;


        if(score == scoreUp + gapPenalty){
            alignment1 = seq1[i-1] + alignment1;
            alignment2 = '-' + alignment2;
            i--;
        }

        else if(score == scoreLeft + gapPenalty){
            alignment1 = '-' + alignment1;
            alignment2 = seq2[j-1] + alignment2;
            j--;
        }

        else {
            alignment1 = seq1[i-1] + alignment1;
            alignment2 = seq2[j-1] + alignment2;
            i--;
            j--;
        }

    }

    while (i){
        alignment1 = seq1[i-1] + alignment1;
        alignment2 = '-' + alignment2;
        i--;
    }

    while (j){
        alignment1 = '-' + alignment1;
        alignment2 = seq2[j-1] + alignment2;
        j--;
    }



    vector<string> final;
    final.push_back(alignment1);
    final.push_back(alignment2);
    int temp;
    final.push_back(to_string(mat[m][n]));

    return final;

}
