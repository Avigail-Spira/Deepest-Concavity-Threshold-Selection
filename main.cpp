#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
using namespace std;

class Concavity {
public:
  int numRows, numCols, minVal, maxVal;
  int x1, y1, x2, y2;
  double m;
  double b;
  int *histAry;
  int maxHeight;
  int bestThrVal;
  int **displayGraph;

  Concavity(ifstream &inFile1, ifstream &inFile2) {
    std::string line1;
    std::string line2;

    getline(inFile1, line1);
    getline(inFile2, line2);

    stringstream ssin1(line1);
    stringstream ssin2(line2);

    ssin1 >> numRows >> numCols >> minVal >> maxVal;
    ssin2 >> x1 >> y1 >> x2 >> y2;

    histAry = new int[maxVal + 1]{0};

    maxHeight = loadHist(inFile1);
    displayGraph = new int *[maxVal + 1];

    for (int i = 0; i < maxVal+1; i++) {
      displayGraph[i] = new int[maxHeight + 1]{0};
    }

    m = 0.0, b = 0.0;
    bestThrVal = 0;
    
  }

  ~Concavity() {
    delete[] histAry;

    for (int i = 0; i < maxVal + 1; i++) {
      delete[] displayGraph[i];
    }

    delete[] displayGraph;
  }

  int loadHist(ifstream &inFile) {
    std::string line;
    int max = 0;
    while (std::getline(inFile, line)) {
      int index, value;
      while (inFile >> index >> value) {
        histAry[index] = value;
        if (value > max)
          max = value;
      }
    }
    return max;
  }

  void printHist(ofstream &outFile) {
    outFile << numRows << " " << numCols << " " << minVal << " " << maxVal;
    for (int i = 0; i < maxVal+1; i++) {
      outFile << endl << i << " (" << histAry[i] << "): ";
      for (int j = 0; j < histAry[i] && j <= 70; j++) {
        outFile << "+";
      }
    }
    outFile << endl;
  }

  int deepestConcavity(int x1, int x2, int m, int b) {

    m = (double)(y2 - y1) / (double)(x2 - x1);
    b = (double)y1 - (m * (double)x1);

    int max = 0;
    int first = x1;
    int second = x2;
    int x = first;
    int thr = first;

    while (x <= second) {
      int y = (int)(m * x + b);
      plotOneRow(x, y, displayGraph);

      int gap = (abs)(histAry[x] - y);
      if (gap > max) {
        max = gap;
        thr = x;
      }
      x++;
    }

    return thr;
  }

  void plotOneRow(int x, int y, int **displayGraph) {
    int index = min(histAry[x], y);
    int last = max(histAry[x], y);

    while (index <= last) {
      displayGraph[x][index] = 3;
      index++;
    }

    displayGraph[x][histAry[x]] = 1;
    displayGraph[x][last] = 2;
  }

  void printGraph(ofstream &outFile) {
    for (int i = 0; i < maxVal+1; i++) {
      for (int j = 0; j < maxHeight+1; j++) {
        if (displayGraph[i][j] == 0)
          outFile << " ";
        if (displayGraph[i][j] == 1)
          outFile << "*";
        if (displayGraph[i][j] == 2)
          outFile << "+";
        if (displayGraph[i][j] == 3)
          outFile << "=";
      }
      outFile << endl;
    }
  }
};

int main(int argc, char *argv[]) {
  ifstream inFile1(argv[1]);
  ifstream inFile2(argv[2]);
  ofstream outFile(argv[3]);

  Concavity concavity(inFile1, inFile2);

  concavity.printHist(outFile);

  concavity.bestThrVal = concavity.deepestConcavity(concavity.x1, concavity.x2, concavity.m, concavity.b);

  outFile << "The best threshold value is " << concavity.bestThrVal << endl;

  concavity.printGraph(outFile);
  
  inFile1.close();
  inFile2.close();
  outFile.close();
}