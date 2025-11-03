
/***********************************************************************

        Copyright (C) 1991,
        Virginia Polytechnic Institute & State University

        This program was originally written by Mr. Hyung K. Lee
        under the supervision of Dr. Dong S. Ha, in the Bradley
        Department of Electrical Engineering, VPI&SU, in 1991.

        This program is released for research use only. This program,
        or any derivative thereof, may not be reproduced nor used
        for any commercial product without the written permission
        of the authors.

        For detailed information, please contact to

        Dr. Dong S. Ha
        Bradley Department of Electrical Engineering
        Virginia Polytechnic Institute & State University
        Blacksburg, VA 24061

        Ph.: (540) 231-4942
        Fax: (540) 231-3362
        E-Mail: ha@vt.edu

        REFERENCE:
           H. K. Lee and D. S. Ha, "On the Generation of Test Patterns
           for Combinational Circuits," Technical Report No. 12_93,
           Dep't of Electrical Eng., Virginia Polytechnic Institute
           and State University.

***********************************************************************/

/**************************** HISTORY **********************************
 
        atalanta: version 1.0        H. K. Lee, 8/15/1991
        atalanta: version 1.1        H. K. Lee, 10/5/1992
        atalanta: version 2.0        H. K. Lee, 6/30/1997
 
***********************************************************************/

/*---------------------------------------------------------------------- 
	testability.c
	Assign controllibility and observability.

	Uses depth of the gate as parameter.
-----------------------------------------------------------------------*/

#include <stdio.h>

#include "parameter.h" 
#include "define.h"    
#include "macro.h"

extern GATEPTR *net;

void set_testability(nog)
int nog;
{
   register int i,j,depth;

   /* cont0 and cont1 */
   for(i=0;i<nog;i++) {
      if(is_free(net[i])||is_head(net[i])) net[i]->cont0=0;
      else {
         depth=(-1);
         for(j=0;j<net[i]->ninput;j++)
	    depth=max(depth,net[i]->inlis[j]->cont0);
	 net[i]->cont0=depth+1;
      }
      net[i]->cont1=net[i]->cont0;
   }

   /* depth from output */
   for(i=nog-1;i>=0;i--)
     if(net[i]->fn==PO) net[i]->dpo=0;
     else {
        depth=(-1);
	for(j=0;j<net[i]->noutput;j++)
	   depth=max(depth,net[i]->outlis[j]->dpo);
	net[i]->dpo=depth+1;
     }
}
