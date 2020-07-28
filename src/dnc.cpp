#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <sstream>

#include "nw.cpp"


vector<int> forwards(int choice, string x, string y, vector<vector<int>> simMatrix, map<char, int> alphEnum, int gapPenalty){
    int n, m;
    int top, left, diagonol, result;

    string codon1,codon2;

    int i, j;

    n = x.length();
    m = y.length();


    vector < vector <int> > 
    mat(n+1, std::vector<int>(m+1, 0));

    for (i = 0; i<=n; i++){
        mat[i][0] = gapPenalty * i;
    }

    for (i = 0; i<=m; i++){
        mat[0][i] = gapPenalty * i;
    }

    if (choice == 1){
        for (i = 1; i <= n; i++){
            codon1 = x[i-1];
            for (j = 1; j <= m; j++){

                diagonol = mat[i-1][j-1];
                left = mat[i][j-1];
                top = mat[i-1][j];


                codon2 = y[j-1];

                result = findScoreNucl(diagonol, left, top, codon1, codon2, -1);

                mat[i][j] = result;

            }
            
        }
    }

    else{
        map<char, int>::iterator it ; 
        map<char, int>::iterator it1 ; 
        
        for (i = 1; i<=n; i++){
            mat[i][0] = mat[i-1][0] + gapPenalty;
            for(j = 1; j<=m; j++){
                it = alphEnum.find(x[i-1]);
                int indexi = it->second;
                it1 = alphEnum.find(y[j-1]);
                int indexj = it1->second;
                
                diagonol = mat[i-1][j-1];
                left = mat[i][j-1];
                top = mat[i-1][j];

                result = findScorePro(indexi, indexj, simMatrix, diagonol, left, top, gapPenalty);
                mat[i][j] = result;
            }
        }

    }

    return mat[n];
}


vector<int> backwards(int choice, string x, string y, vector<vector<int>> simMatrix, map<char, int> alphEnum, int gapPenalty){
    int n, m;
    int top, left, diagonol, result;

    string codon1,codon2;

    int i, j;

    n = x.length();
    m = y.length();

    vector < vector <int> > 
    mat(n+1, std::vector<int>(m+1, 0));

    for (i = 0; i<=n; i++){
        mat[i][0] = gapPenalty * i;
    }

    for (i = 0; i<=m; i++){
        mat[0][i] = gapPenalty * i;
    }

    if (choice == 1){
        for (i = 1; i <= n; i++){
            codon1 = x[i-1];
            for (j = 1; j <= m; j++){
                diagonol = mat[i-1][j-1];
                left = mat[i][j-1];
                top = mat[i-1][j];

                codon2 = y[j-1];

                result = findScoreNucl(diagonol, left, top, codon1, codon2, -1);

                mat[i][j] = result;

            }
        }
    }

    else{
        map<char, int>::iterator it ; 
        for (i = 1; i<=n; i++){
            mat[i][0] = mat[i-1][0] + gapPenalty;
            for(j = 1; j<=m; j++){
                it = alphEnum.find(x[n-i]);
                int indexi = it->second;
                it = alphEnum.find(y[m-j]);

                int indexj = it->second;

                diagonol = mat[i-1][j-1];
                left = mat[i][j-1];
                top = mat[i-1][j];

                result = findScorePro(indexi, indexj, simMatrix, diagonol, left, top, gapPenalty);
                mat[i][j] = result;
            }
        }

    }

    return mat[n];
}


vector<string> dnc(int choice, string x, string y, vector<vector<int>> simMatrix, map<char, int> alphEnum, int gapPenalty){
    int n, m;
    int i, j;

    int cut;
    
    n = x.length();
    m = y.length();

    if (n == 1 || m == 1){
        return nw(choice, x, y, simMatrix, alphEnum, gapPenalty);
    }

    else{
        vector<int> fwd;
        string subX = x.substr(0,n/2);
        fwd = forwards(choice, subX, y, simMatrix, alphEnum, gapPenalty);
        vector<int> bwd;
        bwd = backwards(choice, subX, y, simMatrix, alphEnum, gapPenalty);

        vector<int> partition;
        for(i=0; i <=m; i++){
            partition.push_back(fwd[i] + bwd[m-i]);
        }

        int max = *max_element(partition.begin(), partition.end());
        vector<int>::iterator it = find(partition.begin(), partition.end(), max);
        cut = distance(partition.begin(), it);

        fwd.clear();
        bwd.clear();
        partition.clear();

        vector<string> callLeft;
        subX = x.substr(0, n/2);
        string subY = y.substr(0,cut);

        callLeft = dnc(choice, subX, subY, simMatrix, alphEnum, gapPenalty);

        vector<string> callRight;
        subX = x.substr(n/2, x.length());
        subY = y.substr(cut, y.length());

        callRight = dnc(choice, subX, subY, simMatrix, alphEnum, gapPenalty);

        vector<string> result;
        result.push_back(callLeft[0] + callRight[0]);
        result.push_back(callLeft[1] + callRight[1]);
        int temp, templeft, tempright;

        istringstream(callLeft[2]) >> templeft;
        istringstream(callRight[2]) >> tempright;

        temp = templeft + tempright;
        result.push_back(to_string(temp));

        return result;
    }
}
