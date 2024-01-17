// 1. zip to bin
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    // Open the zip file in binary mode
    ifstream zipFile("input.zip", ios::binary);

    if (!zipFile.is_open()) {
        cerr << "Error opening zip file." << endl;
        return 1;
    }

    // Read the binary data from the zip file into a vector
    vector<char> zipData((istreambuf_iterator<char>(zipFile)), istreambuf_iterator<char>());

    // Close the zip file
    zipFile.close();

    // Open the output binary file for writing
    ofstream outputFile("bin_data_of_zip.bin", ios::binary);

    if (!outputFile.is_open()) {
        cerr << "Error opening output file." << endl;
        return 1;
    }

    // Write the binary data to the output file
    outputFile.write(zipData.data(), zipData.size());

    // Close the output file
    outputFile.close();

    cout << "Binary data successfully written to bin_data_of_zip.bin." << endl;

    return 0;
}
