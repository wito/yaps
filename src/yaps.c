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

#include "particle.h"
#include "world.h"

int main (int argc, const char **argv) {
  particle **particles = calloc(4, sizeof(particle *));
  
  particles[0] = particleCreate(vectorCreate( 3.0,  0.0, 0.0), vectorCreate( 0.0,  0.005, 0.0), 5.0);
  particles[1] = particleCreate(vectorCreate( 0.0,  0.0, 0.0), vectorCreate( 0.0,  0.0, 0.0), 15.0);
  particles[2] = particleCreate(vectorCreate(-3.0,  0.0, 0.0), vectorCreate( 0.0, -0.005, 0.0), 5.0);
  particles[3] = NULL;
  
  particle *A, *B, *C;
  
  A = particles[0];
  B = particles[1];
  C = particles[2];

  int g_count;
  graviton **G = createGravitons(particles, 3, &g_count);
  
  //printf("%d, g_count\n", g_count);

  for (int t = 0; t < 5; t++) {
    for (int i = 0; i < g_count; i++) {
      gravitonApply(G[i]);
    }
    
    particleAdvance(A);
    particleAdvance(B);
    particleAdvance(C);
  
    fprintf(stdout, "frame # %d\n", t);
    particlePrint(stdout, A, 0);
    particlePrint(stdout, B, 1);
    particlePrint(stdout, C, 2);
    fprintf(stdout, "\n");
  }
  
  printf("\n");
  
  return 0;
}
