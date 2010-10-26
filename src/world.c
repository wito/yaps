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

#include <stdlib.h>
#include <stdio.h>

#include "world.h"

void universeOutput(int frame, particle **particles, void *context) {
  FILE *output = context;
  
  fprintf(output, "frame # %d\n", frame);
  printParticles(output, particles);
  fprintf(output, "\n");
}


struct universe {
  int age;
  FILE *output;

  universe_output_fn_t outputFunction;
  void *outputContext;

  particle **particles;
  graviton **gravity;
};

universe *universeCreate(particle **particles) {
  universe *self = malloc(sizeof(universe));
  
  self->age = 0;
  self->output = stdout;
  
  self->outputFunction = &universeOutput;
  self->outputContext = stdout;
  
  self->particles = particles;
  self->gravity = createGravitons(particles, -1, NULL);
  
  return self;
}

void universeDestroy(universe *self) {
  int i = 0;
  particle *p;
  
  while((p = self->particles[i++])) {
    free(p);
  }
  
  free(self->particles);
  
  destroyGravitons(self->gravity);
  
  if (self->output != stdin) {
    fclose(self->output);
  }
  
  free(self);
}


int universeIterate(universe *self) {
  self->age++;
  
  applyGravitons(self->gravity);
  advanceParticles(self->particles);
  
  universeOutput(self->age, self->particles, self->output);
  
  return self->age;
}

void universeSetOutput(universe *self, FILE *fp) {
  self->output = fp;
  self->outputContext = fp;
}


graviton *gravitonCreate(particle *a, particle *b) {
  graviton *self = malloc(sizeof(graviton));
  
  self->a = a;
  self->b = b;
  
  return self;
}

void gravitonDestroy(graviton *self) {
  return free(self);
}

void gravitonApply(graviton *self) {
  vector *g = particleGravity(self->a,self->b);

  particleApplyForce(self->a, g[0]);
  particleApplyForce(self->b, g[1]);

  free(g);
}

void applyGravitons(graviton **self) {
  while (*self) {
    gravitonApply(*(self++));
  }
}


graviton **createGravitons(particle **particles, int count, int *gCount) {
  if (count < 0) {
    for (int i = 0; ; i++) {
      if (!particles[i]) {
        count = i;
        break;
      }
    }
  }
  
  int g_count = count - 1;
  g_count = (1 + g_count)*(g_count / 2.0);
  
  if (gCount)
    *gCount = g_count;
  
  graviton **retval = calloc(g_count + 1, sizeof(graviton *));
  
  int n = 0;
  for (int i = 0; i < count; i++) {
    for (int j = i + 1; j < count; j++) {
      retval[n++] = gravitonCreate(particles[i], particles[j]);
    }
  }
  retval[n] = NULL;
  
  return retval;
}

void destroyGravitons(graviton **self) {
  int i = 0;
  graviton *g;
  
  while ((g = self[i++])) {
    free(g);
  }
  
  free(self);
}
