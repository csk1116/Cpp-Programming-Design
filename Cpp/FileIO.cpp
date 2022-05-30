#include<iostream>
#include<fstream> //ifstream and ofstream
#include<string>
using namespace std;

int main()
{    
    //ofstream
    ofstream myOFile;
    string myPath = "C:\\Users\\CSK\\git\\Some-Basic-Practice\\File\\test.txt"; //or C:/Users/CSK/git/Some-Basic-Practice/File
    myOFile.open(myPath, ios::app); //open mode 1.out 2.app 3.ate, regardless of extension name, we are creating/opening a plain text file.
    myOFile << "1 abc\n lasijdoi" << 145.89 << endl;
    myOFile.close();

    ofstream scoreFile("C:\\Users\\CSK\\git\\Some-Basic-Practice\\File\\score.txt", ios::app);
    if(!scoreFile)
        exit(1);
    string name = "";
    int score = 0;
    char con;
    do
    {
        cin >> name >> score;
        scoreFile << name << ":" << score << endl;
        cout << "Continue (Y/N)? ";
        cin >> con;
    } while (con == 'Y' || con == 'y');
    scoreFile.close();  


    //ifstream
    ifstream myIFile("C:\\Users\\CSK\\git\\Some-Basic-Practice\\File\\score.txt");
    if(myIFile)
    {
        string name = "";
        int score = 0;
        int scoreSum = 0;
        int scoreCount = 0;

        while(!myIFile.eof())
        {
            getline(myIFile, name, ':');
            cout << name;
            myIFile >> score;
            scoreSum += score;
            scoreCount ++;
        }

        if(scoreCount != 0)
            cout << static_cast<double>(scoreSum) / scoreCount << endl;
        else
            cout << "no grades" << endl;              
    }
    myIFile.close();  

    return 0;
}