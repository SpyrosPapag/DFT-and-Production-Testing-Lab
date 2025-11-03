
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
	global.d
	Define global variables of atalanta.
-----------------------------------------------------------------------*/

#ifndef __ATALANTA_GLOBAL_D__
#define __ATALANTA_GLOBAL_D__

#include "define.h"

GATEPTR *net;		/* circuit structure */
int *primaryin,*primaryout,*flip_flops,*headlines;
int nog=0,nopi=0,nopo=0,noff=0,nof=0,nodummy=0,lastgate;
int maxlevel,POlevel,PPOlevel;

int *depth_array;
STACKPTR event_list;		/* event list */
struct FAULT **faultlist;	/* fault list */

#ifdef INCLUDE_HOPE
FAULTPTR headfault,tailfault,currentfault;
EVENTPTR head,tail;
#endif

struct ROOTTREE tree;

/* static buffers for fan */
STACKTYPE unjustified,		/* set of unjustified lines */
	  init_obj,		/* set of initial objectives */
	  curr_obj,		/* set of current objectives */
	  fan_obj,		/* set of fanout objectives */
	  head_obj,		/* set of head objectives */
	  final_obj,		/* set of final objectives */
	  Dfrontier,		/* set of Dfrotiers */
	  stack;		/* stack for backtracing */

/* buffers for the fault simulator */
STACKTYPE free_gates,		/* fault free simulation */
	  faulty_gates,		/* list of faulty gates */
	  eval_gates,		/* STEM_LIST to be simulated */
	  active_stems;		/* list of active stems */
GATEPTR *dynamic_stack;
int nsstack,ndstack;

FILE *circuit,*test,*logfile;
int mac_i;

/* global variables for bit operations */
level all_one;
status update_flag, update_flag2;
struct STACK stack1, stack2;

/* Variables for hope */
char initialmode='x';
char xdetectmode='n';

level InVal[MAXPI];

level BITMASK[32]=
        { MASK0, MASK0<<1, MASK0<<2, MASK0<<3,
          MASK0<<4, MASK0<<5, MASK0<<6, MASK0<<7,
          MASK0<<8, MASK0<<9, MASK0<<10, MASK0<<11,
          MASK0<<12, MASK0<<13, MASK0<<14, MASK0<<15,
          MASK0<<16, MASK0<<17, MASK0<<18, MASK0<<19,
          MASK0<<20, MASK0<<21, MASK0<<22, MASK0<<23,
          MASK0<<24, MASK0<<25, MASK0<<26, MASK0<<27,
          MASK0<<28, MASK0<<29, MASK0<<30, MASK0<<31
        };

char *fn_to_string[MAXGTYPE+3]=         /* gate function to string */
{"AND","NAND","OR","NOR","INPUT","XOR","XNOR","DFF","DUMMY","BUFFER","NOT",
 "","","","","","","","","","PO",};
char *level_to_string[MAXLEVEL+1]=      /* level to string */
{"0","1","x","z",};
char *fault_to_string[2]={"/0","/1"};   /* fault type to string */
level parallel_to_level[2][2]=          /* parallel level types to level */
{{X,ONE},{ZERO,Z}};

#endif /* __ATALANTA_GLOBAL_D__ */
