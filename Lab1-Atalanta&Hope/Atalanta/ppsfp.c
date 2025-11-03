
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

/*-----------------------------------------------------------------------
	ppsfp.c
	Contains all subroutines for the parallel pattern single
	fault propagation.
	Based on Dominator concept.
------------------------------------------------------------------------*/
#include <stdio.h>

#include "parameter.h" 
#include "define.h"    
#include "macro.h"

#define output0 output

extern GATEPTR *net;
extern STACKPTR event_list;
extern STACKTYPE free_gates,    /* fault free simulation */
          faulty_gates,         /* list of faulty gates */
          eval_gates,           /* STEM_LIST to be simulated */
          active_stems;         /* list of active stems */
extern STACKTYPE stack;
extern GATEPTR *dynamic_stack;
extern int nsstack, ndstack;
extern level all_one;
extern level BITMASK[BITSIZE];
extern status update_flag, update_flag2;

/* macros for parallel gate evaluation */
/* one input gate */
#define pgate_eval1(gate,val) \
val=(gate->fn==NOT || gate->fn==NAND || gate->fn==NOR)?~gate->inlis[0]->output1:gate->inlis[0]->output1

/* two input gates */
#define pgate_eval2(gate,val) \
switch(gate->fn) { \
   case AND: val=gate->inlis[0]->output1&gate->inlis[1]->output1; break; \
   case NAND: val=~(gate->inlis[0]->output1&gate->inlis[1]->output1); break; \
   case OR: val=gate->inlis[0]->output1|gate->inlis[1]->output1; break; \
   case NOR: val=~(gate->inlis[0]->output1|gate->inlis[1]->output1); break; \
   case XOR: val=gate->inlis[0]->output1^gate->inlis[1]->output1; break; \
   case XNOR: val=~(gate->inlis[0]->output1^gate->inlis[1]->output1); break; \
}

/* 3-input gate */
#define pgate_eval3(gate,val) \
switch(gate->fn) { \
   case AND: val=gate->inlis[0]->output1&gate->inlis[1]->output1&gate->inlis[2]->output1; break; \
   case NAND: val=~(gate->inlis[0]->output1&gate->inlis[1]->output1&gate->inlis[2]->output1); break; \
   case OR: val=gate->inlis[0]->output1|gate->inlis[1]->output1|gate->inlis[2]->output1; break; \
   default: val=~(gate->inlis[0]->output1|gate->inlis[1]->output1|gate->inlis[2]->output1); \
}

/* more than 2-inputs */
#define pgate_evalx(gate,val,cnt) \
switch(gate->fn) { \
   case AND: \
      val=gate->inlis[0]->output1&gate->inlis[1]->output1&gate->inlis[2]->output1; \
      for(cnt=3;cnt<gate->ninput;cnt++) val&=gate->inlis[cnt]->output1; break; \
   case NAND: \
      val=gate->inlis[0]->output1&gate->inlis[1]->output1&gate->inlis[2]->output1; \
      for(cnt=3;cnt<gate->ninput;cnt++) val&=gate->inlis[cnt]->output1; \
      val=~val; break; \
   case OR: \
      val=gate->inlis[0]->output1|gate->inlis[1]->output1|gate->inlis[2]->output1; \
      for(cnt=3;cnt<gate->ninput;cnt++) val|=gate->inlis[cnt]->output1; break; \
   case NOR: \
      val=gate->inlis[0]->output1|gate->inlis[1]->output1|gate->inlis[2]->output1; \
      for(cnt=3;cnt<gate->ninput;cnt++) val|=gate->inlis[cnt]->output1; \
      val=~val; \
      break; \
   case XOR: val=gate->inlis[0]->output1^gate->inlis[1]->output1; break; \
   case XNOR: val=~(gate->inlis[0]->output1^gate->inlis[1]->output1); break; \
}

/* more than 4-inputs */
#define pgate_eval4(gate,val,cnt) \
switch(gate->fn) { \
   case AND: \
      val=gate->inlis[0]->output1&gate->inlis[1]->output1&gate->inlis[2]->output1&gate->inlis[3]->output1; \
      for(cnt=4;cnt<gate->ninput;cnt++) val&=gate->inlis[cnt]->output1; break; \
   case NAND: \
      val=gate->inlis[0]->output1&gate->inlis[1]->output1&gate->inlis[2]->output1&gate->inlis[3]->output1; \
      for(cnt=4;cnt<gate->ninput;cnt++) val&=gate->inlis[cnt]->output1; \
      val=~val; break; \
   case OR: \
      val=gate->inlis[0]->output1|gate->inlis[1]->output1|gate->inlis[2]->output1|gate->inlis[3]->output1; \
      for(cnt=4;cnt<gate->ninput;cnt++) val|=gate->inlis[cnt]->output1; break; \
   default: \
      val=gate->inlis[0]->output1|gate->inlis[1]->output1|gate->inlis[2]->output1|gate->inlis[3]->output1; \
      for(cnt=4;cnt<gate->ninput;cnt++) val|=gate->inlis[cnt]->output1; \
      val=~val; \
}

/* macros for event scheduling */
#define pschedule_output(gate,cnt) \
for(cnt=0;cnt<gate->noutput;cnt++) { \
   tempgate=gate->outlis[cnt]; \
   if(!tempgate->changed) { \
      push(event_list[tempgate->dpi],tempgate); \
      set(tempgate->changed); \
}}

/* macro to delete a fault */
#define delete_fault(fal) \
if(fal->previous==fal) { \
   fal->gate->pfault=fal->next; \
   if(fal->next!=NULL) fal->next->previous=fal->next; \
} else { \
   fal->previous->next=fal->next; \
   if(fal->next!=NULL) fal->next->previous=fal->previous; \
}

GATEPTR tempgate;

/*	update_all
	Dynamically updates all lists
	      --- faulty_gates, free_gates and eval_gates
	Input: current faulty_agtes
	Output: updated faulty_gates
	Note: Gates are stored in the forward levelized order.
*/
void update_all(npi)
int npi;
{
   register int i,j,k;
   register GATEPTR gut;

   /* clear freach */
   for(i=0;i<=free_gates.last;i++) reset(free_gates.list[i]->freach);
   for(i=0;i<npi;i++) reset(net[i]->freach);

   /* faulty gates */
   j=faulty_gates.last+1;
   clear(faulty_gates);
   for(i=0;i<j;i++) {
      gut=faulty_gates.list[i];
      if(gut->nfault>0) {
	 push(faulty_gates,gut);
	 while(!gut->freach) {
	    push(stack,gut);
	    set(gut->freach);
	    if(gut->noutput==1) gut=gut->outlis[0];
	    else if(gut->u_path!=NULL) gut=gut->u_path->ngate;
         }
      }
   }

   /* evaluation gate list */
   j=eval_gates.last+1;
   clear(eval_gates);
   for(i=0;i<j;i++) {
      gut=eval_gates.list[i];
      if(gut->freach) push(eval_gates,gut);
   }

   /* fault free gate list */
   while(!is_empty(stack)) {
      gut=pop(stack);
      for(i=0;i<gut->noutput;i++)
	 if(!gut->outlis[i]->freach) {
	    set(gut->outlis[i]->freach);
	    push(stack,gut->outlis[i]);
	 }
   }

   k=free_gates.last;
   clear(free_gates);
   for(i=0;i<=k;i++) {
      gut=free_gates.list[i];
      if(gut->freach) {
	 reset(gut->freach);
	 push(free_gates,gut);
	 for(j=0;j<gut->ninput;j++) set(gut->inlis[j]->freach);
      }
   }
  
   /* schedule of freach */
   for(i=0;i<npi;i++) reset(net[i]->freach);

   nsstack=(-1);
   for(i=0;i<=faulty_gates.last;i++) {
      gut=faulty_gates.list[i];
      while(!gut->freach) {
	 set(gut->freach);
	 dynamic_stack[++nsstack]=gut;
	 if(gut->noutput==1) gut=gut->outlis[0];
      }
   }
   ndstack=nsstack;
}

/*	pinit_simulation
	Initializes necessary flags and counters.
	changed=0, observe=ALL0 clear event_list 
*/
void pinit_simulation(nog,maxdpi,npi)
int nog,maxdpi,npi;
{
   register int i;
   register GATEPTR p;

   /* clear changed ochange and set freach */
   for(i=0;i<nog;i++) { 
      reset(net[i]->changed); 
      reset(net[i]->freach);
      net[i]->cobserve=ALL0;
      net[i]->observe=ALL0;
   }

   /* clear all sets */
   for(i=0;i<maxdpi;i++) clear(event_list[i]);
   clear(stack);
   clear(free_gates);
   clear(faulty_gates);
   clear(eval_gates);
   clear(active_stems);

   /* initialize all stacks */
   for(i=0;i<nog;i++) {
      p=net[i];
      if(p->nfault>0) push(faulty_gates,p);
      if(p->noutput != 1) push(eval_gates,p);
   }
   for(i=nog-1;i>=npi;i--) push(free_gates,net[i]);

   /* schedule freach */
   nsstack=(-1);
   for(i=0;i<=faulty_gates.last;i++) {
      p=faulty_gates.list[i];
      while(!p->freach) {
	 set(p->freach);
	 dynamic_stack[++nsstack]=p;
	 if(p->noutput==1) p=p->outlis[0];
      }
   }
   ndstack=nsstack;
}

/* restore_fault_free_value: Restores fault free values */
void restore_fault_free_value()
{
   register GATEPTR p;

   while(!is_empty(stack)) {
      p=pop(stack);
      p->output1=p->output0;
   }
}

/*	pfault_free_simulation
	Perform fault free simulation.
	Only gates in free_gates are evaluated
	Inputs: test vectors should be put to output1 and output0
	Outputs: output0 and output1
	Notes: Resets freach flag for the fault dropping
*/
void pfault_free_simulation()
{
   register int i,j;
   register GATEPTR gut;
   register level val;

   for(i=free_gates.last;i>=0;i--) {
      gut=free_gates.list[i];
      switch(gut->ninput) {
	 case 2: pgate_eval2(gut,gut->output1); break;
	 case 1: pgate_eval1(gut,gut->output1); break;
	 case 3: pgate_eval3(gut,gut->output1); break;
	 default: pgate_eval4(gut,val,j) gut->output1=val; break;
      }
      gut->output0=gut->output1;
   }
}

/*	pfault_simulation
	Performs fault simulation of the stem fault to the Dominator.
	
	Inputs:
	    gut: gate under test
	    observe: observability of the gate under test
	    Dominator: Dominator gate
	    maxdpi: depth of evaluation stack (circuit)
	Output: observe word of fault simulation

	Notes:
	    1. If observe=ALL0, no simulation.
	       If observe=ALL1, simulates both s-a-1 and s-a-0
	       If observe=~free_value, simulates s-a-1
	       If observe=free_value, simulates s-a-0
	       Else, simulates observe^free_value
	    2. If Dominator=NULL, simulates upto primary outputs.
*/
level pfault_simulation(gut,observe,Dominator,maxdpi)
register GATEPTR gut;		/* faulty gate */
level observe;		/* determines faulty value of the gut */
GATEPTR Dominator;
int maxdpi;		/* depth of event list, number of output */
{
   register int i,j;
   register level val;

   if(observe==ALL0) return(observe);
   gut->output1^=observe;
   push(stack,gut);
   pschedule_output(gut,i);
   if(gut->fn!=PO) observe=ALL0;
   if(Dominator!=NULL) maxdpi=Dominator->dpi+1;

   /* evaluate event list */
   for(i=gut->dpi+1;i<maxdpi;i++) {
      while(!is_empty(event_list[i])) {
	 gut=pop(event_list[i]);
	 reset(gut->changed);
	 switch(gut->ninput) {
	    case 2: pgate_eval2(gut,val) break;
	    case 1: pgate_eval1(gut,val); break;
	    default: pgate_evalx(gut,val,j)
	 }
	 if(gut==Dominator) {
	    restore_fault_free_value();
	    return(observe|(val^gut->output1));
	 }
	 if(gut->fn==PO) observe|=(val^gut->output1);
	 if(val!=gut->output1) {
	    pschedule_output(gut,j);
	    gut->output1=val;
	    push(stack,gut);
	 }
      }
   }
   restore_fault_free_value();
   return(observe);
}

/* feval: faulty gate evaluation */
level feval(pf,gut)
FAULTPTR pf; register GATEPTR gut;
{
   register level val;
   register int i;
   GATEPTR g;

   g=gut->inlis[pf->line];
   if((val=g->output1^(pf->type==SA0?ALL0:ALL1))==ALL0) return(val);
   if(gut->ninput==2) {
      if(gut->fn<=NAND)
         return(val&(pf->line==0?gut->inlis[1]->output1:gut->inlis[0]->output1));
      else if(gut->fn<=NOR)
         return(val&(pf->line==0?~gut->inlis[1]->output1:~gut->inlis[0]->output1));
      else return(val);
   }
   g->output1=gut->inlis[0]->output;
   switch(gut->fn) {
      case AND: case NAND:
         for(i=1;i<gut->ninput;i++) 
	    val&=gut->inlis[i]->output1;
	 break;
      case OR: case NOR:
         for(i=1;i<gut->ninput;i++) 
	    val&=(~gut->inlis[i]->output1);
	 break;
   }
   g->output1=g->output0;
   return(val);
}

/*	pcheck_fault
	Determine the detectability of a fault at the stem  of the gate.
	If stem is a PO, enumerates number of detected faults

	Inputs: gut->observe: detectability array of gut
	Outputs: cumulative detectability of the faults
	Note: Pushes detectable faults to stem buffer
*/

level pcheck_fault(gut,pf,stemobs)
register GATEPTR gut;
FAULTPTR **pf;		/* pointer of stem buffer */
level stemobs;		/* cumulative detectability of the stem */
{
   register FAULTPTR f;
   level observe;

   for(f=gut->pfault;f!=NULL;f=f->next) {
      if(f->line==OUTFAULT)
	 observe=gut->observe&((f->type==SA0)?gut->output1:~gut->output1);
      else  			/* input fault */
	 observe=gut->observe&feval(f,gut);
      f->observe=observe;
      if(observe!=ALL0) {
	 **pf=f;
	 (*pf)++;
	 stemobs|=observe;
      }
   }
   return(stemobs);
}

/*	pcheck_po
	Enumerates number of detected faults.

	Inputs: gut->observe: grobal detectability array of gut
	Outputs: number of detected faults
	Note:
	    gut->observe should contain grobal detectability wrt
	    primary outputs of the circuit.
*/
int pcheck_po(gut,flag,nbit,tarray)
register GATEPTR gut;
status *flag;
int nbit,tarray[];
{
   FAULTPTR f;
   register unsigned observe;
   register int i;
   int ndetect=0;

   for(f=gut->pfault;f!=NULL;f=f->next) {
      observe=gut->observe;
      if(f->line==OUTFAULT)
	 observe&=((f->type==SA0)?gut->output1:~gut->output1);
      else observe&=feval(f,gut);
      if(observe!=ALL0) {
	 f->detected=DETECTED;
	 ndetect++;
	 for(i=nbit-1;i>=0;i--)
	    if((observe&BITMASK[i])!=ALL0) {++tarray[i]; break;}
	 if(--gut->nfault==0) set(*flag);
	 else { delete_fault(f); }
      }
   }
   return(ndetect);
}

/*	ftp_reverse
	Simulates fan-out free regions using critical path tracing.

	Inputs:
	    stem: a fan-out stem to be evaluated
	Outputs:
	    sets observe of each fault, each gate and dominator of the stem.
	    observe: cumulative observability of the stem, i.e.,
		     ORs of each fault detectability and dominator obserbility.
		     If, stem is a primary output, returns detected faults.

	Notes:
	    1. freach should be set before calling,
	       the ftp_reverse is performed for only those gates
	    2. Try to use buffers instead of flags
	    3. stem->observe should be set before calling
*/
int ftp_reverse(stem,flag,flag2,nbit,tarray)
GATEPTR stem;
status *flag,flag2;
int nbit,tarray[];
{
   register int i,j;
   register GATEPTR gut, g;
   register level observe,val;
   int ndetect=0;
   FAULTPTR *pf;

   observe=ALL0;
   pf=stem->dfault;

   push(stack,stem);
   while(!is_empty(stack)) {
      gut=pop(stack);
      if(gut->nfault>0)
	 if(flag2) ndetect+=pcheck_po(gut,flag,nbit,tarray);
	 else observe=pcheck_fault(gut,&pf,observe);
      if(gut->cobserve!=ALL0) observe|=(gut->observe&gut->cobserve);
      if(gut->ninput==1) {
	 g=gut->inlis[0];
	 if((g->noutput==1) && g->freach) {
	    g->observe=gut->observe;
	    push(stack,g);
	 }
      }
      else if(gut->ninput==2) {
	 g=gut->inlis[0];
	 if((g->noutput==1) && g->freach) {
	    switch(gut->fn) {
	       case AND: case NAND:
		  g->observe=gut->observe&gut->inlis[1]->output1; break;
	       case OR: case NOR:
		  g->observe=gut->observe&~(gut->inlis[1]->output1); break;
	       default: g->observe=gut->observe;
	    }
	    if(g->observe!=ALL0) push(stack,g);
	 }
	 g=gut->inlis[1];
	 if((g->noutput==1) && g->freach) {
	    switch(gut->fn) {
	       case AND: case NAND:
		  g->observe=gut->observe&gut->inlis[0]->output1; break;
	       case OR: case NOR:
		  g->observe=gut->observe&~(gut->inlis[0]->output1); break;
	       default: g->observe=gut->observe;
	    }
	    if(g->observe!=ALL0) push(stack,g);
	 }
      }
      else 
         for(i=0;i<gut->ninput;i++) {
	    g=gut->inlis[i];
	    if((g->noutput==1) && g->freach) {
	       g->output1=~g->output1;
	       if(gut->ninput==1) {
		  pgate_eval1(gut,val);
	       } else {
	          pgate_evalx(gut,val,j);
	       }
	       g->observe=(val^gut->output1)&gut->observe;
	       g->output1=g->output0;
	       if(g->observe!=ALL0) push(stack,g);
	    }
         }
   }
   *pf=NULL;
   if(flag2) return(ndetect);
   else return(observe);
}

/*	Fault1_Simulation
	Main routine for the fault simulation
	Simulates each gates strictly in the forward order
	Uses dominator information to avoid duplicate calculation
	of gate profiles
	Inputs: circuit structure
	Outputs: number of detected faults
	Notes:
	    1. Input patterns should be set in the output0 
	       and output1 of primary input gates.
	    2. ALL1 should be set according to number of bits used
*/
int Fault1_Simulation(nog,maxdpi,npi,npo,nstem,stem,nbit,tarray)
int nog,maxdpi,npi,npo,nstem,nbit,tarray[];
GATEPTR stem[];
{
   register int i;
   register GATEPTR gut,g;
   FAULTPTR f,*pf;
   int ndetect=0;

   ndetect=0;

   /* step 3: fault simulation in the forward order */
   clear(active_stems);
   for(i=0;i<=eval_gates.last;i++) {
      gut=eval_gates.list[i];
      if(!gut->freach) continue;
      gut->observe=all_one;
      if(gut->fn==PO)
	 ndetect+=ftp_reverse(gut,&update_flag,TRUE,nbit,tarray);
      else 
	 if((gut->observe=ftp_reverse(gut,&update_flag,FALSE,nbit,tarray))!=ALL0) {
	 g=(gut->u_path==NULL)?NULL: gut->u_path->ngate;
	 if((gut->observe=pfault_simulation(gut,gut->observe,g,maxdpi))!=ALL0) {
	    push(active_stems,gut);
	    if(g!=NULL) {
	       g->observe=ALL0;
	       if(g->freach) g->cobserve|=gut->observe;
	       else {
		  set(g->freach);
		  dynamic_stack[++ndstack]=g;
		  g->cobserve=gut->observe;
		  if(g->noutput==1) {
		     g=g->outlis[0];
		     while(!g->freach) {
		        set(g->freach);
		        dynamic_stack[++ndstack]=g;
			g->cobserve=ALL0;
		        if(g->noutput==1) g=g->outlis[0];
	             }
		  }
	       }
	    }
	 }
      }
   }

   /* step 4: Determine grobal detectability and detected faults */
   while(!is_empty(active_stems)) {
      gut=pop(active_stems);
      if(gut->u_path!=NULL) {
	 g=gut->u_path->ngate;
	 gut->observe&=(g->observe&net[g->fos]->observe);
      }
      if(gut->observe!=ALL0) {
	 pf=gut->dfault;
	 while((f=(*pf))!=NULL) {
	    if((f->observe&gut->observe)!=ALL0) {
		f->observe&=gut->observe;
		for(i=nbit-1;i>=0;i--)
		   if((f->observe&BITMASK[i])!=ALL0) {++tarray[i];break;}
		f->detected=DETECTED;
		ndetect++;
		if(--(f->gate->nfault)==0) set(update_flag);
		else {delete_fault(f)}
	    }
	    pf++;
	 }
      }
   }

   return(ndetect);
}

/*	update_faulty_gates
	updates the list, faulty_gates, which contains faulty gates
	Input: current faulty_agtes
	Output: updated faulty_gates
	Notes: gates are stored in the forward levelized order
*/
void update_faulty_gates()
{
   register int i,j;
   register GATEPTR gut;

   j=faulty_gates.last;
   clear(faulty_gates);
   for(i=0;i<=j;i++) {
      gut=faulty_gates.list[i];
      if(gut->nfault>0) push(faulty_gates,gut);
   }
}

/*	update_free_gates
	Update the list free_gates which contains gates to be evaluated.
	Input: faulty_gates, list of faulty gates
	       free_gates, current list
	Output: free_gates, list is updated
	Notes: Gates are in the reverse levelized order.
	       Primary inputs are not included in free_gates.
*/

void update_free_gates(npi)
int npi;
{
   int j,k;
   register int i;
   register GATEPTR gut;

   for(i=faulty_gates.last;i>=0;i--) {
      stack.list[i]=faulty_gates.list[i];
      set(stack.list[i]->changed);
   }
   stack.last=faulty_gates.last;

   while(!is_empty(stack)) {
      gut=pop(stack);
      for(i=0;i<gut->noutput;i++)
	 if(!gut->outlis[i]->changed) {
	    set(gut->outlis[i]->changed);
	    push(stack,gut->outlis[i]);
	 }
   }

   k=free_gates.last;
   clear(free_gates);
   for(i=0;i<=k;i++) {
      gut=free_gates.list[i];
      if(gut->changed) {
	 push(free_gates,gut);
	 reset(gut->changed);
	 for(j=0;j<gut->ninput;j++) set(gut->inlis[j]->changed);
      }
   }
   for(i=0;i<npi;i++) reset(net[i]->changed);
}

/*	update_eval_gates
	Updates stem_list which contains stems to be evaluated.
	Inputs: faulty_gates, eval_gates
	Outputs: eval_gates updated
*/
void update_eval_gates()
{
   register int i,j;
   register GATEPTR gut;

   /* set freach from each faulty gate to its stem */
   for(i=0;i<=faulty_gates.last;i++) {
      gut=net[faulty_gates.list[i]->fos];
      while(!gut->changed) {
	 set(gut->changed);
	 if(gut->u_path!=NULL) gut=net[gut->u_path->ngate->fos];
      }
   }

   /* set eval_gates based on previous stacks */
   j=eval_gates.last;
   clear(eval_gates);
   for(i=0;i<=j;i++) {
      gut=eval_gates.list[i];
      if(gut->changed) {
	 push(eval_gates,gut);
	 reset(gut->changed);
      }
   }
}

/*	update_all1
	updates all lists --- faulty_gates and eval_gates

	Input: current faulty_agtes
	Output: updated faulty_gates

	Notes: gates are stored in the forward levelized order
*/

void update_all1(npi)
int npi;
{
   register int i,j;
   register GATEPTR gut;

   /* clear freach */
   for(i=0;i<=free_gates.last;i++) reset(free_gates.list[i]->freach);
   for(i=0;i<npi;i++) reset(net[i]->freach);

   /* faulty gates */
   j=faulty_gates.last+1;
   clear(faulty_gates);
   nsstack=(-1);
   for(i=0;i<j;i++) {
      gut=faulty_gates.list[i];
      if(gut->nfault>0) {
	 push(faulty_gates,gut);
	 while(!gut->freach) {
	    set(gut->freach);
	    dynamic_stack[++nsstack]=gut;
	    if(gut->noutput==1) gut=gut->outlis[0];
         }
      }
   }

   /* evaluation gate list */
   update_eval_gates();
   ndstack=nsstack;
}

/*	Fault0_Simulation
	Main routine for the fault simulation.
	Simulates each gates strictly in the forward order.
	Uses dominator information to avoid duplicate calculation
	of gate profiles.
	Inputs: circuit structure
	Outputs: number of detected faults
	Notes:
	    1. Input patterns should be set in the output0 
	       and output1 of primary input gates.
	    2. ALL1 should be set according to number of bits used
	    3. Modified for the atalanta
*/

int Fault0_Simulation(nog,maxdpi,npi,npo,nstem,stem,nbit,tarray)
int nog,maxdpi,npi,npo,nstem,nbit,tarray[];
GATEPTR stem[];
{
   register int i,j;
   register GATEPTR gut,g;
   FAULTPTR f,*pf;
   level val;
   int ndetect=0;

   ndetect=0;

   /* step 1: fault free simulation */
   for(i=free_gates.last;i>=0;i--) {
      gut=free_gates.list[i];
      switch(gut->ninput) {
	 case 2: pgate_eval2(gut,gut->output1) break;
	 case 1: pgate_eval1(gut,gut->output1); break;
	 case 3: pgate_eval3(gut,gut->output1) break;
	 default: pgate_eval4(gut,val,j)
		  gut->output1=val;
      }
      gut->output0=gut->output1;
      reset(gut->freach);
      reset(gut->changed);
   }

   /* step 2: fault dropping */
   for(i=0;i<=faulty_gates.last;i++) {
      gut=faulty_gates.list[i];
      while(!gut->freach) {
         set(gut->freach);
	 gut->cobserve=ALL0;
	 if(gut->noutput==1) gut=gut->outlis[0];
      }
   }

   /* step 3: fault simulation in the forward order */
   clear(active_stems);
   for(i=0;i<=eval_gates.last;i++) {
      gut=eval_gates.list[i];
      if(!gut->freach) continue;
      gut->observe=all_one;
      if(gut->fn==PO)
	 ndetect+=ftp_reverse(gut,&update_flag,TRUE,nbit,tarray);
      else
	 if((gut->observe=ftp_reverse(gut,&update_flag,FALSE,nbit,tarray))!=ALL0) {
	 g=(gut->u_path==NULL)?NULL:gut->u_path->ngate;
	 if((gut->observe=pfault_simulation(gut,gut->observe,g,maxdpi))!=ALL0) {
	    push(active_stems,gut);
	    if(g!=NULL) {
	       g->observe=ALL0;
	       if(g->freach) g->cobserve|=gut->observe;
	       else {
		  set(g->freach);
		  g->cobserve=gut->observe;
		  if(g->noutput==1) {
		     g=g->outlis[0];
		     while(!g->freach) {
		        set(g->freach);
		        if(g->noutput==1) g=g->outlis[0];
	             }
		  }
	       }
	    }
	 }
      }
   }

   /* step 4: determine grobal detectability and detected faults */
   while(!is_empty(active_stems)) {
      gut=pop(active_stems);
      if(gut->u_path!=NULL) {
	 g=gut->u_path->ngate;
	 gut->observe&=(g->observe&net[g->fos]->observe);
      }
      if(gut->observe!=ALL0) {
	 pf=gut->dfault;
	 while((f=(*pf))!=NULL) {
	    if((f->observe&gut->observe)!=ALL0) {
		f->observe&=gut->observe;
		for(i=nbit-1;i>=0;i--)
		   if((f->observe&BITMASK[i])!=ALL0) {++tarray[i];break;}
		f->detected=DETECTED;
		ndetect++;
		if(--(f->gate->nfault)==0) set(update_flag);
		else {delete_fault(f)}
	    }
	    pf++;
	 }
      }
   }

   /* if event occurs, update fault free lines */
   if(update_flag) {
      update_faulty_gates();
      update_eval_gates();
/*      update_free_gates(npi); */
      reset(update_flag);
   }
   return(ndetect);
}
