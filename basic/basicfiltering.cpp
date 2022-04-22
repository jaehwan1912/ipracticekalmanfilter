#include <iostream>
#include <vector>

using namespace std;


int main() {
    double initEst = 68;
    double initErr = 2;

    vector<vector<double>> mea = {
        {75, 4},
        {71, 4},
        {70, 4},
        {74, 4},
    };

    double est = initEst;
    double err = initErr;

    for (int i=0;i<4;i++) {
        double KG = err / (err + mea[i][1]);
        est = est + KG * (mea[i][0] - est);
        err = (1-KG) * err;
        cout << "Iter " << i << "\t\tKG: " << KG << "\tEST: " << est <<
                "\tErr: " << err << endl;
    }

    return 0;
}