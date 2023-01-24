#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fts.h>
#include <string.h>

int compare (const FTSENT**, const FTSENT**);

int walk (char* const* root);

int
main (int argc, char** argv, char** env) {
  if (argc > 1) {
    return walk (argv + 1);
  }

  char* def [] =  {".", NULL};
  return walk (def);
}

int
compare (const FTSENT** lhs, const FTSENT** rhs) {
  return (strcmp ( (*lhs)->fts_name, (*rhs)->fts_name) );
}

int
walk (char* const* root) {
  FTS* file_system = NULL;
  FTSENT* node = NULL;
  file_system = fts_open (  root, FTS_COMFOLLOW | FTS_NOCHDIR, &compare);

  if (NULL == file_system) {
    fprintf (stderr, "fts_open failed\n");
    return 1;
  }

  while ( (node = fts_read (file_system) ) != NULL) {
    switch (node->fts_info) {
    case FTS_D:
      if (strcmp (node->fts_name, ".git") == 0) {
        char* parent = strndup (node->fts_path, node->fts_pathlen - 4);
        fprintf (stdout, "%s\n", parent);
        free (parent);
      }

      break;

    default:
      break;
    }
  }

  return 0;
}
