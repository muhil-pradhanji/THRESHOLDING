#include <opencv2/opencv.hpp>
#include <iostream>

void customThreshold(const cv::Mat& inputImage, cv::Mat& outputImage, uint16_t thresholdValue, uint16_t maxValue, int thresholdType) {
    // Ensure the image is grayscale
    if (inputImage.channels() != 1) {
        std::cerr << "Input must be a grayscale image." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Create an output image with the same type as the input
    outputImage = cv::Mat::zeros(inputImage.size(), inputImage.type());

    // Apply custom thresholding
    for (int y = 0; y < inputImage.rows; y++) {
        const uint16_t* rowIn = inputImage.ptr<uint16_t>(y);
        uint16_t* rowOut = outputImage.ptr<uint16_t>(y);

        for (int x = 0; x < inputImage.cols; x++) {
            uint16_t pixelValue = rowIn[x];
            if (thresholdType == cv::THRESH_BINARY) {
                rowOut[x] = (pixelValue > thresholdValue) ? maxValue : 0;
            }
            else if (thresholdType == cv::THRESH_BINARY_INV) {
                rowOut[x] = (pixelValue > thresholdValue) ? 0 : maxValue;
            }
            else {
                std::cerr << "Unsupported threshold type!" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
    }
}

int main() {
    // Load your 16-bit grayscale image
    std::string imagePath = "C:\\Users\\Dhvani\\Downloads\\16bit.png";
    cv::Mat inputImage = cv::imread(imagePath, cv::IMREAD_UNCHANGED); // Use UNCHANGED for 16-bit images

    if (inputImage.empty() || inputImage.depth() != CV_16U) {
        std::cerr << "Error: Input must be a valid 16-bit grayscale image." << std::endl;
        return -1;
    }

    cv::Mat thresholdedImage;

    // Threshold parameters
    uint16_t thresholdValue = 30000; // Adjust as needed
    uint16_t maxValue = 65535;       // Maximum value for 16-bit
    int thresholdType = cv::THRESH_BINARY;

    // Apply custom thresholding
    customThreshold(inputImage, thresholdedImage, thresholdValue, maxValue, thresholdType);

    // Save and display the result
    cv::imwrite("thresholded_16bit2_image.png", thresholdedImage);
    std::cout << "Thresholding complete. Image saved as 'thresholded_16bit_image.png'." << std::endl;

    return 0;
}
