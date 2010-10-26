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

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "particle.h"
#include "world.h"
#include "parser.h"

#ifndef ITERATIONS
#define ITERATIONS 5
#endif

int main (int argc, const char **argv) {
  int p_count = 0;
  int p_cap = 8;
  particle **particles = malloc(p_cap * sizeof(particle *));
  particles[0] = NULL;

  int iterations = ITERATIONS;
  char *input_path = NULL;
  char *output_path = NULL;
  
  for (int i = 1; i < argc; i++) {
    const char *clswitch = argv[i];
    
    if (!strncmp(clswitch, "-", 1)) {
      const char *argument = argv[++i];
      if (!argument) {
        fprintf(stderr, "setting %s given without argument\n", clswitch);
        exit(1);
      }
      
      if (!strcmp(clswitch, "-i") || !strcmp(clswitch, "--iterations")) {
        iterations = strtol(argument, NULL, 10);
      } else if (!strcmp(clswitch, "-o") || !strcmp(clswitch, "--output")) {
        output_path = strdup(argument);
      }
      
    } else {
      input_path = strdup(clswitch);
      break;
    }
  }
  
  FILE *input = stdin;
  
  if (input_path) {
    input = fopen(input_path,"rb");
    free(input_path);
  }
  
  char *line = NULL;
  while ((line = findline(input))) {
    ConfigAction action = configAction(line);
    
    char **args = NULL;
    
    switch (action) {
      case ParticleAction:
        particles[p_count++] = particleParse(input);
        if (p_count == p_cap) {
          p_cap += 8;
          particles = realloc(particles, p_cap * sizeof(particle *));
        }
        particles[p_count] = NULL;
        break;
      case IterationsConfig:
        args = configArguments(line);
        
        iterations = strtol(args[1], NULL, 10);
        
        break;
      case OutputConfig:
        args = configArguments(line);
        
        free(output_path);
        output_path = strdup(args[1]);
        
        break;
      case UnknownConfigAction:
      default:
        break;
    }
    
    if (args) {
      free(args[0]);
      free(args);
    }
    
    free(line);
  }
    
  fclose(input);

  universe *universe = universeCreate(particles);
  particles = NULL;
  
  FILE *out = stdout;
  
  if (output_path) {
    out = fopen(output_path, "wb");
    free(output_path);
  }
  
  universeSetOutput(universe, out);
  
  for (int t = 0; t < iterations; t++) {
    universeIterate(universe);
  }
  
  universeDestroy(universe);
  universe = NULL;
  
  if (out != stdout) {
    fclose(out);
  }
  
  return 0;
}
