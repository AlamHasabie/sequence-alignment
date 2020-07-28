#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

string readSequence(string file){
    string myText;
    string sequence;
    ifstream MyReadFile(file);

    // Use a while loop together with the getline() function to read the file line by line
    int i = 0;
    while (getline (MyReadFile, myText)){
    // Output the text from the file
        if(i != 0){
            sequence.append(myText);
        }
        i++;
        
    }

    MyReadFile.close();
    return sequence;
}

vector<char> readAlfabet(string file){
    string myText;
    string temp;
    ifstream MyReadFile(file);

    // Use a while loop together with the getline() function to read the file line by line
    getline(MyReadFile, myText);

    vector<char> alfabet;
    for (auto x : myText){ 
       if (x != ' '){  
           alfabet.push_back(x);
       } 
   }  
   

    MyReadFile.close();
    return alfabet;   
}

vector<vector<int>> readScoreMatrix(string file){
    string myText;
    string sequence;
    ifstream MyReadFile(file);

    vector<vector<int>> mat(20, std::vector<int>(20, 0));

    // Use a while loop together with the getline() function to read the file line by line
    int i = 0;
    while (getline (MyReadFile, myText)){
    // Output the text from the file
        string word = "";
        int j=0;
        for (auto x : myText){ 
            if (x == ' '){
                if(word != ""){
                    mat[i][j] = mat[j][i] = stoi(word);
                    word = "";
                    j++;
                }  
            } 
            else{
                word = word + x;
            }

        }
        i++;
    }

    return mat;
}
