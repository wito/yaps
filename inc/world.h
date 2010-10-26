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

#ifndef WORLD_H
#define WORLD_H

#include "particle.h"

typedef struct universe universe;
typedef void (*universe_output_fn_t)(int, particle **, void *);

typedef struct {
  particle *a;
  particle *b;
} graviton;

universe *universeCreate(particle **);
void universeDestroy(universe *);

void universeSetOutput(universe *, FILE *);
void universeSetOutputFunction(universe *, universe_output_fn_t, void *);

int universeIterate(universe *);

graviton *gravitonCreate(particle *, particle *);
void gravitonDestroy(graviton *);

graviton **createGravitons(particle **, int, int *);
void destroyGravitons(graviton **);

void gravitonApply(graviton *);
void applyGravitons(graviton **);

#endif // WORLD_H
