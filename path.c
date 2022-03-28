#include "path.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

Path *Path__init(Path *self) {
  char *paths[10] = {"/bin/"};
  self = (Path *)malloc(sizeof(Path));

  if (self == NULL) {
    // TODO Error
  }

  self->path_count = 0;
  self->paths = paths;

  return self;
}

void Path__free(Path *self) {
  // TODO Free
}

int Path__count(Path *self){
  // TODO Count
  return 1;
}

char *Path__get(Path *self, int i){
  return self->paths[i];
}


char *Path__get_valid(Path *self){
 char *p = NULL;
 int p_count = Path__count(self);

 for (int i=0; i<p_count; i++){
   if (access(self->paths[i], F_OK) == 0){
     p = self->paths[i];
   }
 }
  
 return p;
}
