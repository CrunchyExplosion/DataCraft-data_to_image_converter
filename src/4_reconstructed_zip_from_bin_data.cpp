#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    // Open the binary file for reading
    ifstream inputFile("output_bin_data.bin", ios::binary);

    if (!inputFile.is_open()) {
        cerr << "Error opening binary file." << endl;
        return 1;
    }

    // Read the binary data from the file into a vector
    vector<char> binaryData((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());

    // Close the input file
    inputFile.close();

    // Open a new zip file for writing
    ofstream outputFile("zip_reconstructed.zip", ios::binary);

    if (!outputFile.is_open()) {
        cerr << "Error opening output zip file." << endl;
        return 1;
    }

    // Write the binary data to the new zip file
    outputFile.write(binaryData.data(), binaryData.size());

    // Close the output file
    outputFile.close();

    cout << "Zip file successfully reconstructed." << endl;

    return 0;
}
