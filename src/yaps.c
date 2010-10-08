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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "particle.h"
#include "world.h"

#ifndef ITERATIONS
#define ITERATIONS 5
#endif

int main (int argc, const char **argv) {
  int iterations = ITERATIONS;
  
  if (argc > 2 && !strncmp(argv[1], "-i", 2)) {
    iterations = strtol(argv[2], NULL, 10);
  }
  
  particle **particles = calloc(4, sizeof(particle *));
  
  particles[0] = particleCreate(vectorCreate( 3.0,  0.0, 0.0), vectorCreate( 0.0,  0.005, 0.0), 5.0);
  particles[1] = particleCreate(vectorCreate( 0.0,  0.0, 0.0), vectorCreate( 0.0,  0.0, 0.0), 15.0);
  particles[2] = particleCreate(vectorCreate(-3.0,  0.0, 0.0), vectorCreate( 0.0, -0.005, 0.0), 5.0);
  particles[3] = NULL;
  
  universe *universe = universeCreate(particles);
  
  for (int t = 0; t < iterations; t++) {
    universeIterate(universe);
  }
  
  return 0;
}
