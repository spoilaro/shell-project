
typedef struct Path {
  int path_count;
  char **paths;
} Path;

Path *Path__init(Path *);

void Path__free(Path *);

int Path__count(Path *);

char *Path__get(Path *, int);

char *Path__get_valid(Path *);
