
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
 
        atalanta: version 2.0        H. K. Lee, 6/30/1997

           Linked HOPE with ATALANTA
 
***********************************************************************/

/*----------------------------------------------------------------- 
	lsim.c
	contains all subroutines necessary for 
	zero gate delay event driven logic simulation.

	list all modifications below:
	original: 8/15/1991	Hyung K. Lee   compiled and checked
-------------------------------------------------------------------*/
#include <stdio.h>
#include "parameter.h"
#include "define.h"
#include "macro.h"

extern int nog,nopi,nopo,noff,maxlevel,POlevel,PPOlevel;
extern int *primaryin,*primaryout,*flip_flops;
extern GATEPTR *net;
extern STACKTYPE *event_list;
extern level InVal[];
extern char initialmode;

#define cmplevel(V1,V2) (V1[0]!=V2[0] || V1[1]!=V2[1])
#define cpylevel(Dest,Sour) Dest[0]=Sour[0]; Dest[1]=Sour[1]
level TABLE[Z+1][2]={{ALL1,ALL0},{ALL0,ALL1},{ALL0,ALL0},{ALL1,ALL1}};

extern level truthtbl1[MAXGTYPE][MAXLEVEL];
extern level truthtbl2[MAXGTYPE][MAXLEVEL][MAXLEVEL];
#define scmplevel(V1,V2) (V1!=V2)
#define scpylevel(Dest,Sour) Dest=Sour

/*-----GoodSim------------------------------------------------------
	Performs good circuit logic simulation.
	Input patterns are stored in InVal[i].
	Current Flip-Flop values in inputs of each FF.
	Logic values in GVs of each gate structure are
	updated and old values are eliminated.
------------------------------------------------------------------*/
void GoodSim(ntest)
int ntest;
{
   register int i,j;
   register GATEPTR gut,temp;
   level Val;

   /* schedule events in flip-flops 
      --- FFs are modeled as Delay Elements */
   if(ntest==1) {
      for(i=0;i<noff;i++) {
         gut=net[flip_flops[i]];
	 Val=(initialmode=='0')?ZERO:(initialmode=='1')?ONE:X;
         if(scmplevel(gut->SGV,Val)) {
	    scpylevel(gut->SGV,Val);
	    cpylevel(gut->GV,TABLE[Val]);
	    schedulegate(gut,j,temp);
         }
      }
   } else for(i=0;i<noff;i++) {
      gut=net[flip_flops[i]];
      scpylevel(Val,gut->inlis[0]->SGV);
      if(scmplevel(gut->SGV,Val)) {
	 scpylevel(gut->SGV,Val);
	 cpylevel(gut->GV,TABLE[Val]);
	 schedulegate(gut,j,temp);
      }
   }

   /* schedule event in primary inputs */
   for(i=0;i<nopi;i++) {
      gut=net[primaryin[i]];
      if(scmplevel(gut->SGV,InVal[i])) {
	 scpylevel(gut->SGV,InVal[i]);
	 cpylevel(gut->GV,TABLE[InVal[i]]);
	 schedulegate(gut,j,temp);
      }
   }

   for(i=0;i<PPOlevel;i++) {
      while(!is_empty(event_list[i])) {
	 gut=pop(event_list[i]);
	 reset(gut->changed);

	 /* gate evaluation */
	 if(gut->ninput==1) {
	    gut->SGV=Val=truthtbl1[gut->fn][gut->inlis[0]->SGV];
	    cpylevel(gut->GV,TABLE[Val]);
	    schedulegate(gut,j,temp);
	 } else {
	    Val=truthtbl1[gut->fn][gut->inlis[0]->SGV];
	    for(j=1;j<gut->ninput;j++)
	       Val=truthtbl2[gut->fn][Val][gut->inlis[j]->SGV];
	    if(scmplevel(gut->SGV,Val)) {
	       scpylevel(gut->SGV,Val);
	       cpylevel(gut->GV,TABLE[Val]);
	       schedulegate(gut,j,temp);
	    }
	 }
      }
   }

   /* Pseudo-Primary outputs */
   while(!is_empty(event_list[PPOlevel])) {
      gut=pop(event_list[PPOlevel]);
      reset(gut->changed);
   }
}

