#include <iostream>
#include <fstream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void writeBinaryToFile(const string& data, const string& filename) {
    ofstream file(filename, ios::binary);

    if (file.is_open()) {
        file.write(data.data(), data.size());
        file.close();
        cout << "Binary data written to " << filename << endl;
    } else {
        cerr << "Error opening the file for writing." << endl;
    }
}

string extractFileData(const Mat& videoFrame, int numRows, int numCols) {
    // Extract data from the frame.
    string fileData;

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            fileData.push_back(videoFrame.at<uchar>(i, j));
        }
    }

    return fileData;
}

int main() {
    // Read the image back into a Mat object
    Mat resizedFrame = imread("output.png", IMREAD_GRAYSCALE);

    if (resizedFrame.empty()) {
        cerr << "Error reading the compressed video frame from file." << endl;
        return 1;
    }

    // Extract the data from resizedFrame
    int numRows = resizedFrame.rows;
    int numCols = resizedFrame.cols;
    string extractedFileData = extractFileData(resizedFrame, numRows, numCols);

    // Write the extracted data to a file named "output_bin_data.bin"
    writeBinaryToFile(extractedFileData, "output_bin_data.bin");

    return 0;
}
