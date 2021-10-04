/* --------------------------------------------------------------------------
 * File:    demosaic.cpp
 * Created: 2015-10-01
 * --------------------------------------------------------------------------
 *
 *
 *
 * ------------------------------------------------------------------------*/

#include "demosaic.h"
#include <cmath>

using namespace std;

Image basicGreen(const Image &raw, int offset) {
  // --------- HANDOUT  PS03 ------------------------------
  // Takes as input a raw image and returns a single-channel
  // 2D image corresponding to the green channel using simple interpolation
  Image output(raw.width(), raw.height(), 1); // Initialize 1 channel output image

  for (int h = 0; h < output.height(); h++) {
    output(0, h, 0) = raw(0, h, 1);                                   // Copy Left edge column
    output(output.width() - 1, h, 0) = raw(output.width() - 1, h, 1); // Copy Right edge column
  }
  for (int w = 0; w < output.width(); w++) {
    output(w, 0, 0) = raw(w, 0, 1);                                     // Copy Top edge row
    output(w, output.height() - 1, 0) = raw(w, output.height() - 1, 1); // Copy Bottom edge row
  }

  if (offset = 0) {
    for (int h = 1; h < output.height() - 1; h++) {  // Iterate over pixels in row-major order
      for (int w = 1; w < output.width() - 1; w++) {
        if (w % 2 == h % 2) {
          output(w, h, 0) = raw(w, h, 1); // Top left corner is green
        }
        else {
          output(w, h, 0) = (raw(w, h+1, 1) + raw(w, h-1, 1) + raw(w-1, h, 1) + raw(w+1, h, 1)) / 4.0f;
        }
      }
    }
  }
  else {
    for (int h = 1; h < output.height() - 1; h++) {  // Iterate over pixels in row-major order
      for (int w = 1; w < output.width() - 1; w++) {
        if (w % 2 == h % 2) { // One to right of top left corner
           output(w, h, 0) = (raw(w, h+1, 1) + raw(w, h-1, 1) + raw(w-1, h, 1) + raw(w+1, h, 1)) / 4.0f;
        }
        else {
          output(w, h, 0) = raw(w, h, 1);
        }
      }
    }
  }
  return output; // Return output image
}

Image basicRorB(const Image &raw, int offsetX, int offsetY) {
  // --------- HANDOUT  PS03 ------------------------------
  //  Takes as input a raw image and returns a single-channel
  //  2D image corresponding to the red or blue channel using simple
  //  interpolation
  return raw;
}

Image basicDemosaic(const Image &raw, int offsetGreen, int offsetRedX,
                    int offsetRedY, int offsetBlueX, int offsetBlueY) {
  // --------- HANDOUT  PS03 ------------------------------
  // takes as input a raw image and returns an rgb image
  // using simple interpolation to demosaic each of the channels
  return raw;
}

Image edgeBasedGreen(const Image &raw, int offset) {
  // --------- HANDOUT  PS03 ------------------------------
  // Takes a raw image and outputs a single-channel
  // image corresponding to the green channel taking into account edges
  return raw;
}

Image edgeBasedGreenDemosaic(const Image &raw, int offsetGreen, int offsetRedX,
                             int offsetRedY, int offsetBlueX, int offsetBlueY) {
  // --------- HANDOUT  PS03 ------------------------------
  // Takes as input a raw image and returns an rgb image
  // using edge-based green demosaicing for the green channel and
  // simple interpolation to demosaic the red and blue channels
  return raw;
}

Image greenBasedRorB(const Image &raw, Image &green, int offsetX, int offsetY) {
  // --------- HANDOUT  PS03 ------------------------------
  // Takes as input a raw image and returns a single-channel
  // 2D image corresponding to the red or blue channel using green based
  // interpolation
  return raw;
}

Image improvedDemosaic(const Image &raw, int offsetGreen, int offsetRedX,
                       int offsetRedY, int offsetBlueX, int offsetBlueY) {
  // // --------- HANDOUT  PS03 ------------------------------
  // Takes as input a raw image and returns an rgb image
  // using edge-based green demosaicing for the green channel and
  // simple green based demosaicing of the red and blue channels
  return raw;
}
