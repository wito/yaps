/*
 * Part of YAPS (Yet Another Particle Simulation)
 *
 * Copyright 2010 Williham Totland. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 * 
 *    1. Redistributions of source code must retain the above copyright notice, this list of
 *       conditions and the following disclaimer.
 * 
 *    2. Redistributions in binary form must reproduce the above copyright notice, this list
 *       of conditions and the following disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY WILLIHAM TOTLAND ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL WILLIHAM TOTLAND OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "vector.h"

#include <math.h>

vector vectorCreate(double x, double y, double z) {
  return (vector){ x, y, z };
}


double vectorLength(vector self) {
  return sqrt(vectorDotProduct(self,self));
}

vector vectorUnit(vector self) {
  return vectorDivide(self, vectorLength(self));
}


vector vectorAddition(vector a,vector b) {
  return vectorCreate(a.x + b.x, a.y + b.y, a.z + b.z);
}

vector vectorSubtraction(vector a, vector b) {
  return vectorCreate(a.x - b.x, a.y - b.y, a.z - b.z);
}

vector vectorMultiply(vector self, double r) {
  return vectorCreate(self.x * r, self.y * r, self.z * r);
}

vector vectorDivide(vector self, double r) {
  return vectorCreate(self.x / r, self.y / r, self.z / r);
}


vector vectorXProduct(vector a, vector b) {
  return vectorCreate(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

double vectorDotProduct(vector a,vector b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}
