/* Custom CLI command completion.
 *
 * Copyright (c) 1992, 1993  Simmule Turner and Rich Salz. All rights reserved.
 *
 * This software is not subject to any license of the American Telephone
 * and Telegraph Company or of the Regents of the University of California.
 *
 * Permission is granted to anyone to use this software for any purpose on
 * any computer system, and to alter it and redistribute it freely, subject
 * to the following restrictions:
 * 1. The authors are not responsible for the consequences of use of this
 *    software, no matter how awful, even if they arise from flaws in it.
 * 2. The origin of this software must not be misrepresented, either by
 *    explicit claim or by omission.  Since few users ever read sources,
 *    credits must appear in the documentation.
 * 3. Altered versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.  Since few users
 *    ever read sources, credits must appear in the documentation.
 * 4. This notice may not be removed or altered.
 */

#include "editline.h"
#include <string.h>

#define HISTORY "/tmp/.cli-history"

static char *list[] = {
   "foo ", "bar ", "bsd ", "cli ", "ls ", "cd ", "malloc ", "tee ", NULL
};

/* Attempt to complete the pathname, returning an allocated copy.
 * Fill in *unique if we completed it, or set it to 0 if ambiguous. */
static char *my_rl_complete(char *token, int *match)
{
   int i;
   int index = -1;
   int matchlen = 0;
   int count = 0;

   for (i = 0; list[i]; i++)
   {
      int partlen = strlen (token); /* Part of token */

      if (!strncmp (list[i], token, partlen))
      {
         index = i;
         matchlen = partlen;
         count ++;
      }
   }

   if (count == 1)
   {
      *match = 1;
      return strdup (list[index] + matchlen);
   }

   return NULL;
}

/* Return all possible completions. */
static int my_rl_list_possib(char *token, char ***av)
{
   int i, num, total = 0;
   char **copy;
   
   for (num = 0; list[num]; num++)
      ;
   copy = (char **) malloc (num * sizeof(char *));
   for (i = 0; i < num; i++)
   {
      if (!strncmp (list[i], token, strlen (token)))
      {
         copy[total] = strdup (list[i]);
         total ++;
      }
   }
   *av = copy;

   return total;
}

int main(int ac __attribute__ ((unused)), char *av[] __attribute__ ((unused)))
{
   char *line;
   char	*prompt = "cli> ";

   /* Setup callbacks */
   rl_set_complete_func(&my_rl_complete);
   rl_set_list_possib_func(&my_rl_list_possib);
   read_history(HISTORY);

   while ((line = readline(prompt)) != NULL) {
      printf("\t\t\t|%s|\n", line);
      free(line);
   }

   write_history(HISTORY);

   return 0;
}
