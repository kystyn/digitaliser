#pragma once

#include "def.h"

namespace dgtl {
  static void YUV2RGB( unsigned char *B, unsigned char Y1, unsigned char U, unsigned char Y2, unsigned char V ) {
    /*
    B[0] = Y1 + 1.14 * V;
    B[1] = Y1 - 0.395 * U - 0.581 * V;
    B[2] = Y1 + 2.033 * U;
    B[3] = Y2 + 1.14 * V;
    B[4] = Y2 - 0.395 * U - 0.581 * V;
    B[5] = Y2 + 2.033 * U;
    */

    B[0] = std::max(std::min(255, (int)(Y1 + 1.13983 * (V - 128)                     )), 0);
    B[1] = std::max(std::min(255, (int)(Y1 - 0.39465 * (U - 128) - 0.5860 * (V - 128))), 0);
    B[2] = std::max(std::min(255, (int)(Y1 + 2.03211 * (U - 128)                     )), 0);
    B[3] = std::max(std::min(255, (int)(Y2 + 1.13983 * (V - 128)                     )), 0);
    B[4] = std::max(std::min(255, (int)(Y2 - 0.39465 * (U - 128) - 0.5860 * (V - 128))), 0);
    B[5] = std::max(std::min(255, (int)(Y2 + 2.03211 * (U - 128)                     )), 0);
  }

  static void YUV2RGB( ofPixels &P ) {
    ofPixels newP;
    newP.allocate(P.getWidth(), P.getHeight(), OF_IMAGE_COLOR);
    for (uint i = 0; i < P.getHeight() * P.getWidth() * 2; i += 4) {
      unsigned char
        y1 = P[i + 0],
        u = P[i + 1],
        y2 = P[i + 2],
        v = P[i + 3];

      //std::cout << (int)y << " " << (int)u << " " << (int)v << std::endl;

      YUV2RGB(&newP[i / 4 * 3], y1, u, y2, v);
      /*
      newP[i / 4 * 3 + 0] = y1 + 1.14 * v;
      newP[i / 4 * 3 + 1] = y1 - 0.395 * u - 0.581 * v;
      newP[i / 4 * 3 + 2] = y1 + 2.033 * u;
      newP[i / 4 * 3 + 3 + 0] = y2 + 1.14 * v;
      newP[i / 4 * 3 + 3 + 1] = y2 - 0.395 * u - 0.581 * v;
      newP[i / 4 * 3 + 3 + 2] = y2 + 2.033 * u;
      */
    }
    P.swap(newP);
    P.setImageType(OF_IMAGE_COLOR);
  }
}
