#include "sharpening.h"

void Sharpening::Apply(Image &image) const {
    ApplyMatrix(image);
}