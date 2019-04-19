#pragma once

#include "def.h"

namespace dgtl {
	/*
	static void YUV2RGB( ofColor &c ) {
		unsigned char
			y = c.g,
			u = (c.a & 0xF0) >> 4,
			v = c.a & 0xF;

		c.r =	y + 1.13983 * (v - 128),
		c.g =	y - 0.39465 * (u - 128) - 0.5860 * (v - 128),
		c.b =	y + 2.03211 * (u - 128);
	}*/

	static void YUV2RGB( ofPixels &P ) {

		ofPixels newP;
		newP.allocate(P.getWidth(), P.getHeight(), OF_IMAGE_COLOR);
		for (uint i = 0; i < P.getHeight() * P.getWidth() * 2; i += 2) {
			unsigned char
				y = P[i],
				u = P[i + 1] >> 4,
				v = P[i + 1] & 0xF;

			newP[i / 2 * 3 + 0] = y + 1.13983 * (v - 128),
		  newP[i / 2 * 3 + 1] = y - 0.39465 * (u - 128) - 0.5860 * (v - 128),
			newP[i / 2 * 3 + 2] = y + 2.03211 * (u - 128);
			
		}
		P.swap(newP);
		P.setImageType(OF_IMAGE_COLOR);
	}
}
