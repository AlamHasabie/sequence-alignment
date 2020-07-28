#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

#include "dnc.cpp"
#include "readFile.cpp"
#include <fstream>
#include <cstdlib> // for exit function


int main(){
    vector<vector<int>> simMatrix;
    simMatrix = readScoreMatrix("scoringMatrix/PAM250.txt");

    vector<char> alfabet;
    alfabet = readAlfabet("alfabet sekuens/protein.txt");
    map<char, int> alphEnum;
    alphEnum = initAlphaEnum(alfabet);

    cout << "===============SEQUENCE ALIGNMENT==============" << endl;
    cout << "Which sequence do you want to allign?" << endl;
    cout << "1. Nucleoid" << endl;
    cout << "2. Protein" << endl;

    int choice;
    cin >> choice;

    string in1, in2;
    string seq1, seq2;
    cout << "enter first sequence (.fasta)" << endl;
    cin >> in1;
    cout << "" << endl;
    cout << "enter second sequence (.fasta)" << endl;
    cin >> in2;

    seq1 = readSequence(in1);
    seq2 = readSequence(in2);


    vector<string> hasil;
    int gapPenalty;

    if(choice == 1){
        gapPenalty = -1;
    }
    else{
        gapPenalty = -8;
    }

    hasil = dnc(choice, seq1, seq2, simMatrix, alphEnum, gapPenalty);
    

    ofstream outdata; // outdata is like cin

    string sub1 = in1.substr(in1.length()-16, in1.length());
    string sub2 = in2.substr(in2.length()-16, in2.length());

    outdata.open("result/"+sub1+"_"+sub2+"/"+sub1+".txt"); // opens the file
    outdata << hasil[0] << endl;
    outdata.close();

    ofstream outdata2; // outdata is like cin
    outdata2.open("result/"+sub1+"_"+sub2+"/"+sub2+".txt"); // opens the file
    outdata2 << hasil[1] << endl;
    outdata.close();

    ofstream outdata3; // outdata is like cin
    outdata3.open("result/"+sub1+"_"+sub2+"/score.txt"); // opens the file
    outdata3 << hasil[2] << endl;
    outdata.close();

    cout << hasil[0] << endl;
    cout << hasil[1] << endl;
    cout << hasil[2] << endl;
}