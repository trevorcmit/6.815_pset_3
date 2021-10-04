/* --------------------------------------------------------------------------
 * File:    align.cpp
 * Created: 2015-10-01
 * --------------------------------------------------------------------------
 *
 *
 *
 * ------------------------------------------------------------------------*/

#include "align.h"

using namespace std;

Image denoiseSeq(const vector<Image> &imSeq) {
  // // --------- HANDOUT  PS03 ------------------------------
  // Basic denoising by computing the average of a sequence of images
  Image output(imSeq.at(0).width(), imSeq.at(0).height(), imSeq.at(0).channels()); // Initialize output image
  for (int h = 0; h < output.height(); h++) {
    for (int w = 0; w < output.width(); w++) {
      for (int c = 0; c < output.channels(); c++) { // Iterate over pixels in row-major order
        for (int n = 0; n < imSeq.size(); n++) {
          output(w, h, c) = output(w, h, c) + (imSeq.at(n)(w, h, c) / imSeq.size()); // Add all values at that pixel
        }
      }
    }
  }
  return output; // Return output image
}

Image logSNR(const vector<Image> &imSeq, float scale) {
  // // --------- HANDOUT  PS03 ------------------------------
  // returns an image visualizing the per-pixel and
  // per-channel log of the signal-to-noise ratio scaled by scale.
  Image avg = denoiseSeq(imSeq); // Get the Expected Value (E[i]) of each pixel
  Image output(avg.width(), avg.height(), avg.channels()); // Initialize output image

  for (int h = 0; h < output.height(); h++) {  // Iterate over pixels in row-major order
    for (int w = 0; w < output.width(); w++) {
      for (int c = 0; c < output.channels(); c++) {

        float sigma_sqr = 0.0f;                   // Initialize value for sigma squared (variance)
        for (int n = 0; n < imSeq.size(); n++) {
          sigma_sqr += pow(imSeq.at(n)(w, h, c) - avg(w, h, c), 2); // square difference between pixel and the avg
        }
        sigma_sqr /= (imSeq.size() - 1 + 0.000001); // Divide by n-1, sigma_sqr is now equal to variance

        output(w, h, c) = scale * 10.0f * log10(avg(w, h, c) * avg(w, h, c) / (sigma_sqr + 0.000001)); // Add log SNR to image
      }
    }
  }
  return output; // Return output image
}

vector<int> align(const Image &im1, const Image &im2, int maxOffset) {
  // // --------- HANDOUT  PS03 ------------------------------
  // returns the (x,y) offset that best aligns im2 to match im1.
  vector<int> output;

  float best_diff = im1.height() * im1.width() * im1.channels() * 2.0f; // Initialize best sum of squared pixel difference counter
  int best_offset_x = 0, best_offset_y = 0; // Initialize best offset counters

  for (int y = -1 * maxOffset; y <= maxOffset; y++) { // Brute force over all offset values
    for (int x = -1 * maxOffset; x <= maxOffset; x++) {
      
      float difference = 0.0f; // Initialize variable to hold sum of squared pixel differences
      for (int h = maxOffset; h < im1.height() + maxOffset; h++) {  // Iterate over pixels in row-major order
        for (int w = maxOffset; w < im1.width() + maxOffset; w++) {
          for (int c = 0; c < im1.channels(); c++) {
            difference += pow(im1.smartAccessor(w, h, c) - im2.smartAccessor(w + x, h + y, c), 2); // squared pixel difference
          }
        }
      }
      if (difference < best_diff) {
        best_diff = difference;     // Keep track of the best option so far
        best_offset_x = x;
        best_offset_y = y; 
      }
    }
  }
  output.push_back(best_offset_x);
  output.push_back(best_offset_y);
  return output; // Return vector of the best x and y translations
}

Image alignAndDenoise(const vector<Image> &imSeq, int maxOffset) {
  // // --------- HANDOUT  PS03 ------------------------------
  // Registers all images to the first one in a sequence and outputs
  // a denoised image even when the input sequence is not perfectly aligned.
  return Image(1, 1, 1);
}

Image split(const Image &sergeyImg) {
  // --------- HANDOUT  PS03 ------------------------------
  // 6.865 only:
  // split a Sergey images to turn it into one 3-channel image.
  return Image(1, 1, 1);
}

Image sergeyRGB(const Image &sergeyImg, int maxOffset) {
  // // --------- HANDOUT  PS03 ------------------------------
  // 6.865 only:
  // aligns the green and blue channels of your rgb channel of a sergey
  // image to the red channel. This should return an aligned RGB image
  return Image(1, 1, 1);
}

/**************************************************************
 //               DON'T EDIT BELOW THIS LINE                //
 *************************************************************/

// This circularly shifts an image by xRoll in the x direction and
// yRoll in the y direction. xRoll and yRoll can be negative or postive
Image roll(const Image &im, int xRoll, int yRoll) {

  int xNew, yNew;
  Image imRoll(im.width(), im.height(), im.channels());

  // for each pixel in the original image find where its corresponding
  // location is in the rolled image
  for (int x = 0; x < im.width(); x++) {
    for (int y = 0; y < im.height(); y++) {

      // use modulo to figure out where the new location is in the
      // rolled image. Then take care of when this returns a negative
      // number
      xNew = (x + xRoll) % im.width();
      yNew = (y + yRoll) % im.height();
      xNew = (xNew < 0) * (imRoll.width() + xNew) + (xNew >= 0) * xNew;
      yNew = (yNew < 0) * (imRoll.height() + yNew) + (yNew >= 0) * yNew;

      // assign the rgb values for each pixel in the original image to
      // the location in the new image
      for (int z = 0; z < im.channels(); z++) {
        imRoll(xNew, yNew, z) = im(x, y, z);
      }
    }
  }

  // return the rolled image
  return imRoll;
}
