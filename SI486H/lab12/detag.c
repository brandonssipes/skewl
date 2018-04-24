#include <config.h>

#if defined (HAVE_UNISTD_H)
#  include <unistd.h>
#endif
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "loadables.h"

#if !defined (errno)
  extern int errno;
#endif

/*
 * dtag - remove any <tags> from stdin
 */

#define CLEAR 0
#define SETIT 1

char *detag_doc[] = {
  "removes tags from stdin.",
  "Input lines with html-like tags to return the output with no tags.",
};

int 
detag_builtin (list)
  WORD_LIST *list;
{
    int opt, rval;
    rval = EXECUTION_SUCCESS;
    reset_internal_getopt ();
    while ((opt = internal_getopt (list, "")) != -1)
    {
      switch (opt)
      {
        default:
          builtin_usage ();
          return (EX_USAGE);
      }
    }
    list = loptend;

    char *bufr;
    ssize_t bsiz;
    ssize_t red;
    int i, tagflag=0;
    int lineno=0; // set to 1 for line#s

    bsiz=0;  // malloc it the first time; resize thereafter
    while ((red=getline(&bufr, &bsiz, stdin)) > 0){
	if ((lineno) && (bufr[red-1] == '\n')) printf("%5d: ", ++lineno);

	for(i=0; i<red; i++) {
	    if (tagflag) {
		if (bufr[i] == '>') {
		    tagflag=CLEAR;
		}
	    } else {
		if (bufr[i] == '<') {
		    tagflag=SETIT;
		} else {
		    putchar(bufr[i]);
		}
	    }
	}
    }
    free(bufr);

    return (rval);

} // main


struct builtin detag_struct = {
  "detag",
  detag_builtin,
  BUILTIN_ENABLED,
  detag_doc,
  "remove tags",
  0
};


