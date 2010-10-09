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

#include "particle.h"
#include "parser.h"

particle *particleCreate (vector p, vector v, double m) {
  particle *self = malloc(sizeof(particle));
  
  self->position = p;
  self->velocity = v;
  self->mass     = m;
  
  return self;
}

void particleDestroy (particle *self) {
  return free(self);
}


particle *particleParse (FILE *stream) {
  vector p, v;
  double m;
  
  char *line = findline(stream);
  p = vectorParse(line);
  free(line);
  
  line = findline(stream);
  v = vectorParse(line);
  free(line);
  
  line = findline(stream);
  sscanf(line, " %lf", &m);
  free(line);
  
  return particleCreate(p,v,m);
}


double particleMass(particle *self) {
  return self->mass;
}


void particleApplyForce (particle *self, vector f) {
  self->velocity = vectorAddition(self->velocity, vectorDivide(f, particleMass(self)));
}

void particleAdvance (particle *self) {
  self->position = vectorAddition(self->position, self->velocity);
}


vector *particleGravity(particle *a, particle *b) {
  vector *retval = calloc(2,sizeof(vector));
  
  double G = 0.00001;
  
  /// experimental - accounts for relativistic effects of relative velocities
  // double x = vectorLength(vectorSubtraction(a->velocity, b->velocity));
  // double X = x * x;
  
  double M = particleMass(a) * particleMass(b);
  double r = particleDistance(a,b);
  double R = r * r;
  
  // double F = -G * M * X / R;
  double F = -G * M / R;
  
  vector vec_r = vectorUnit(vectorSubtraction(a->position, b->position));
  retval[0] = vectorMultiply(vec_r, F);
  retval[1] = vectorMultiply(vec_r, -F);
  
  return retval;
}

double particleDistance(particle *a, particle *b) {
  return vectorLength(vectorSubtraction(a->position, b->position));
}

void particlePrint(FILE *fp, particle *self, int id) {
  fprintf(fp, "particle # %d\n", id);
  fprintf(fp, "# position\n    %10.5f %10.5f %10.5f\n", self->position.x, self->position.y, self->position.z);
  fprintf(fp, "# velocity\n    %10.5f %10.5f %10.5f\n", self->velocity.x, self->velocity.y, self->velocity.z);
  fprintf(fp, "# mass\n    %10.5f\n", particleMass(self));
}

void advanceParticles(particle **self) {
  while (*self) {
    particleAdvance(*(self++));
  }
}

void printParticles(FILE *fp, particle **self) {
  for (int i = 0;; i++) {
    if (self[i]) {
      particlePrint(fp, self[i], i);
    } else {
      return;
    }
  }
}
