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

void encodeFileData(const string& fileData, Mat& videoFrame, int numRows, int numCols) {
    size_t dataSize = fileData.size();
    size_t frameSize = numRows * numCols * videoFrame.channels();

    if (dataSize > frameSize) {
        cerr << "Error: File data size is too large for the video frame." << endl;
        return;
    }

    // Encode file data into the frame.
    cout << "Encoding data: ";
    for (size_t i = 0; i < dataSize; ++i) {
        videoFrame.at<uchar>(i / numCols, i % numCols) = fileData[i]; // Encode data directly as grayscale.

        // Display progress every 10%
        if ((i + 1) % (dataSize / 10) == 0) {
            cout << static_cast<int>((i + 1) * 100 / dataSize) << "% ";
            cout.flush();
        }
    }
    cout << "100%" << endl;
}

int main() {
    // Read binary data from "bin_data_of_zip.bin"
    ifstream inputFile("bin_data_of_zip.bin", ios::binary | ios::ate);
    size_t dataSize = inputFile.tellg();
    inputFile.seekg(0, ios::beg);
    string fileData(dataSize, '\0');
    inputFile.read(&fileData[0], dataSize);
    inputFile.close();

    // Calculate the minimum size required for a black and white frame
    int numRows = static_cast<int>(sqrt(dataSize)) + 1;
    int numCols = static_cast<int>(ceil(static_cast<double>(dataSize) / numRows));

    // Create a black and white frame with the calculated size and initialize it with zeros
    Mat videoFrame(numRows, numCols, CV_8UC1, Scalar(0));

    // Encode binary data into the  frame
    encodeFileData(fileData, videoFrame, numRows, numCols);

    // Write the compressed frame to a PNG file named "output.png"
    vector<int> compression_params;
    compression_params.push_back(IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9); // 0-9, where 9 is the highest compression

    if (!imwrite("output.png", videoFrame, compression_params)) {
        cerr << "Error writing the compressed frame to file." << endl;
        return 1;
    } else {
        cout << "Compressed frame written to output.png" << endl;
    }

    return 0;
}
