#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>


using namespace std;


int findDScore(int diagonol, string codon1, string codon2){
    if (codon1 == codon2){
        return diagonol + 1;
    }
    else{
        return diagonol - 1;
    }
}

int findHScore(int left, int gapPenalty){
    return left + gapPenalty;
}

int findVScore(int top, int gapPenalty){
    return top + gapPenalty;
}

int findScoreNucl(int diagonol, int left, int top, string codon1, string codon2, int gapPenalty){
    int dScore = findDScore(diagonol, codon1, codon2);
    int hScore = findHScore(left, gapPenalty);
    int vScore = findVScore(top, gapPenalty);

    vector<int> arr{dScore, hScore, vScore};

    return (*max_element (arr.begin(), arr.end()));
}

int findScorePro(int idxi, int idxj, vector <vector <int>> simMatrix, int diagonol, int left, int top, int gapPenalty){
    int dScore = diagonol + simMatrix[idxi][idxj];
    int hScore = findHScore(left, gapPenalty);
    int vScore = findVScore(top, gapPenalty);

    vector<int> arr{dScore, hScore, vScore};

    return (*max_element (arr.begin(), arr.end()));
}

vector<vector <int>> generateMatrix(int choice, string seq1, string seq2, vector<vector<int>> simMatrix, map<char, int> alphEnum, int gapPenalty){
    int m, n, nProtein;
    int i, j;
    string codon1, codon2;
    int diagonol, left, top, result;

    m = seq1.length();
    n = seq2.length();

    vector < vector <int> > 
    mat(m+1, std::vector<int>(n+1, 0));

    for (i = 0; i<=m; i++){
        mat[i][0] = gapPenalty * i;
    }

    for (i = 0; i<=n; i++){
        mat[0][i] = gapPenalty * i;
    }

    if (choice == 1){
        for (i = 1; i <= m; i++){
            codon1 = seq1[i-1];
            for (j = 1; j <= n; j++){
                diagonol = mat[i-1][j-1];
                left = mat[i][j-1];
                top = mat[i-1][j];

                codon2 = seq2[j-1];

                result = findScoreNucl(diagonol, left, top, codon1, codon2, -1);

                mat[i][j] = result;

            }
        }
    }

    else{
        map<char, int>::iterator it ; 
        for (i = 1; i<=m; i++){
            for(j = 1; j<=n; j++){
                it = alphEnum.find(seq1[i-1]);
                int indexi = it->second;
                it = alphEnum.find(seq2[j-1]);

                int indexj = it->second;

                diagonol = mat[i-1][j-1];
                left = mat[i][j-1];
                top = mat[i-1][j];

                result = findScorePro(indexi, indexj, simMatrix, diagonol, left, top, gapPenalty);

                mat[i][j] = result;
            }
        }
    }
    

    return mat;
    
}
        