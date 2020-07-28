// CPP program to implement sequence alignment 
// problem. 
// #include <bits/stdc++.h> 
#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std; 
  
// int match = 1;
// int gap = -1;
std::map<char,map<char,int>> scoring;
char chars[20];





void loadscorematrix(string name){
    ifstream inp(name);
    string line;
    if (inp.is_open()){
        getline(inp,line);
        // cout << line;
        // cout << line.find(' ') << endl;
        line.erase(0,line.find(' ')+1);
        // cout << "Hey";
        int i = 0;
        while (line.size() > 0){
            char c = line[0];
            chars[i] = c;
            // cout << c << endl;
            if (line.size() > 2){
                // cout << line << endl;
                line.erase(0,line.find(' ')+1);
                }
            else{
                // cout << line.find(' ') << endl;
                line.erase(0,line.size()+1);
            }
            i++;
        }
        i = 0;
        int j;
        while (getline(inp,line)){
            line.erase(0,2);
            j = 0;
            while(line.size() > 2){
                // cout << chars[20-i-1] << " " << chars[j] << endl;
                int score = stoi(line.substr(0,line.find(' ')+1));
                scoring[chars[20-i-1]][chars[j]] = score;
                scoring[chars[j]][chars[20-i-1]] = score;
                // cout << score << endl;
                j++;
                line.erase(0,line.find(' ')+1);
            }
            // cout << chars[20-i-1] << "HERE" << endl;
            scoring[chars[20-i-1]][chars[j]] = stoi(line);
            // cout << stoi(line) << endl;
            i++;
        }
    }else{
        cout << "File not found" << endl;
    }
}

void writeToFile(string str, string name){
    string res = "result/" + name + ".txt";
    

}



void needleman(string seq1, string seq2,string name, string name2, int gap){
    int x,y;
    x = seq1.size();
    y = seq2.size();
    // printf("halo");
    // cout << x << " " << y ;
    // int **matrix = new int[x+1][y+1];
    // int matrix[x+1][y+1];
    cout << x << " " << y;
    int **matrix = new int*[x+1];
    for (int i = 0; i <= x; i++){
        matrix[i] = new int[y+1];
        // cout << i << endl;
    }
    for (int i=0; i<=x;i++){
        for (int j = 0; j<=y;j++){
            matrix[i][j] = 0;
            // cout << "Tes";
        }
    }

    for (int i=0; i <= x; i++){
        matrix[i][0] = i * gap;
    }
    for (int i=0; i <= y; i++){
        matrix[0][i] = i * gap;
    }

    for (int i=1; i<= x; i++){
        for (int j =1 ; j <= y; j++){
            // if (seq1[i-1] == seq2[j-1]){
            //     matrix[i][j] = scoring[seq1[i-1]][seq2[j-1]] + matrix[i-1][j-1];
            // }
            // else{
                // cout << "Tes" << endl;
                int top, left, diag, little;
                top = matrix[i-1][j] + gap;
                left = matrix[i][j-1] + gap;
                diag = matrix[i-1][j-1] + scoring[seq1[i-1]][seq2[j-1]];
                if (top < left){
                    if (left < diag){
                        little = diag;
                    }
                    else{
                        little = left;
                    }
                }else{
                    if (top < diag){
                        little = diag;
                    }
                    else{
                        little = top;
                    }
                }
                matrix[i][j] = little;
            // }
        }
    }

    string xend = "",yend = "";
    int i = x;
    int j = y;

    while ( i != 0 || j != 0){
        if (i == 0 && j != 0){
            xend = "_" + xend;
            yend = seq2[j-1] + yend;
            j--;
        }else if (j == 0 && i != 0){
            yend = "_" + yend;
            xend = seq1[i-1] + xend;
            i--;
        }
        else if (j != 0 && i != 0){
            if (matrix[i-1][j] + gap == matrix[i][j]){
                xend  = seq1[i-1] + xend;
                yend = "_" + yend;
                i--;
            }
            else if (matrix[i][j-1] + gap == matrix[i][j]){
                xend = "_" + xend;
                yend = seq2[j-1] + yend;
                j--;
            }   
            else{
                xend = seq1[i-1] + xend;
                yend = seq2[j-1] + yend;
                i--;
                j--;
            }
        }
    }
    cout << "Best Score : " << matrix[x][y] << endl;
    cout << xend << endl;
    cout << yend << endl;
    // for (int i =0; i <= x; i++){
    //     for (int j = 0 ; j <= y ; j ++){
    //         cout << matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }

}

void withNamaFile(string nama1, string nama2, int gap){
    string str1="",str2="";
    ifstream inp(nama1);
    string line;
    if (inp.is_open()){
        getline(inp,line);
        cout << "First sequence : " << line << endl;
        while (getline(inp,line)){
            str1 = str1+line;
        }
    }
    else{
        cout << "File 1 not found" << endl;
    }
    ifstream inp2(nama2);
    if (inp2.is_open()){
        getline(inp2,line);
        cout << "Second sequence : " << line << endl;
        while(getline(inp2,line)){
            // cout << line;
            str2 = str2 + line;
        }
    }
    // cout << str1 << endl;
    // cout << str2 << endl;
    return needleman(str1,str2,nama1,nama2,gap);
}



int main(int argc, char* argv[]){
    if (argc < 2)
        cout << "Maaf kurang argumen, berikan file yang ingin dialign, lalu scoring matrix diakhir, lalu nilai jika terjadi gap" << endl;
    else{
        loadscorematrix(argv[argc-2]);
        int gap = stoi(argv[argc-1]);
        // needleman(argv[1],argv[2],-1);
        withNamaFile(argv[1],argv[2],-1);
    }
}