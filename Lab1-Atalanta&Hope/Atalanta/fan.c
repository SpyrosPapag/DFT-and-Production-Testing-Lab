
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
 
	   Add dynamic unique path sensitization, H. K. Lee, 1/20/'94
 
        atalanta: version 2.0        H. K. Lee, 6/30/1997
           Added diagnostic mode, H. K. Lee, 6/30/1997
 
***********************************************************************/

/*-----------------------------------------------------------------
	filename fan.c
	implements the FAN algorithm.
------------------------------------------------------------------*/
#include <stdio.h>
#include "parameter.h" 
#include "define.h"    
#include "macro.h"

extern GATEPTR *net;
extern int *primaryin,*primaryout,*headlines;
extern char learnmode, logmode;
extern level a_truthtbl1[MAXGTYPE][ATALEVEL];
extern level a_truthtbl2[MAXGTYPE][ATALEVEL][ATALEVEL];
extern STACKTYPE unjustified,   /* set of unjustified lines */
          init_obj,             /* set of initial objectives */
          curr_obj,             /* set of current objectives */
          fan_obj,              /* set of fanout objectives */
          head_obj,             /* set of head objectives */
          final_obj,            /* set of final objectives */
          Dfrontier,            /* set of Dfrotiers */
          stack;                /* stack for backtracing */
extern struct ROOTTREE tree;
extern STACKPTR event_list;
extern int mac_i;
extern char gen_all_pat, no_faultsim;
extern int ntest_each;
extern int ntest_each_limit;
extern FILE *test, *logfile;
extern void Dprintio();

int SELECTMODE=0;	/* 0: easiest first, 1: hardest first */

/* constant for the dynamic unique path sensitization */
int dy_id=INFINITY;
GATEPTR dyn_dom[MAXGATE];

/* macros for the gate evaluation using the truthtable */
#define gate_eval1(g,v,f,i) \
	if(g->ninput==1) v=a_truthtbl1[g->fn][g->inlis[0]->output]; \
	else if(g->ninput==2) \
	   v=a_truthtbl2[g->fn][g->inlis[0]->output][g->inlis[1]->output];\
	else { \
	   f = (g->fn==NAND) ? AND : \
	       (g->fn==NOR) ? OR : g->fn; \
	   v=a_truthtbl2[f][g->inlis[0]->output][g->inlis[1]->output];\
	   for(i=2;i<g->ninput;i++) \
	      v=a_truthtbl2[f][v][g->inlis[i]->output]; \
	   v=(g->fn==NAND||g->fn==NOR)? A_NOT(v) : v; \
	}

/*	init_net
	Initialization of flags and data structures.
	changed=0, all set=empty.
	Identifies all reachable gates from the faulty line.
*/
void init_net(nog,faulty_gate,maxdpi)
int nog,maxdpi;
GATEPTR faulty_gate;
{
   register int i,j;
   register GATEPTR p;

   /* clear changed ochange and set freach */
   for(i=0;i<nog;i++) {
      if(is_free(net[i])) set(net[i]->changed);
      else reset(net[i]->changed);
      reset(net[i]->freach);
      net[i]->output=X;
      net[i]->xpath=1;
   }

   /* clear all sets */
   for(i=0;i<maxdpi;i++) clearevent(i);
   clear(Dfrontier);
   clear(unjustified);
   clear(init_obj);
   clear(curr_obj);
   clear(fan_obj);
   clear(head_obj);
   clear(final_obj);
   clear(stack);
   clear(tree);

   /* flag all reachable gates from the faulty gate */
   pushevent(faulty_gate);
   for(i=faulty_gate->dpi;i<maxdpi;i++)
      while(!is_empty(event_list[i])) {
	 p=popevent(i);
	 reset(p->changed);
	 set(p->freach);
	 for(j=0;j<p->noutput;j++)
	    pushevent(p->outlis[j]);
     }
}

/*	set_faulty_gate
	box 1 of the FAN algorithm.
	Defines input and output values of the faulty gate.
	Returns the level of the highest level gate in which
	backward implication is required.
	If a CONFLICT condition (redundant faults) occurs,
	returns (-1).
*/
int set_faulty_gate(fault)
FAULTPTR fault;
{
   register int i,last;
   register GATEPTR p;
   level v1,v2;
   GATEPTR faulty_line;

   last=0;
   p=fault->gate;
   faulty_line = 
      (fault->line==OUTFAULT) ? p : p->inlis[fault->line];
   v2 = (fault->type==SA0) ? D : DBAR;

   /* input stuck-at faults */
   if(fault->line>=0) {			/* input line fault */
      faulty_line->output = (v2==D) ? ONE : ZERO;  /* faulty line */
      push(stack,faulty_line);
      switch(p->fn) {
      case AND: case NAND:
         set(p->changed);
	 for(i=0; i<p->ninput; i++)
	    if(i != fault->line) {
	       if(p->inlis[i]->output==X) {
	          p->inlis[i]->output=ONE;
	          push(stack,p->inlis[i]);
	       }
	       else if(p->inlis[i]->output != ONE) return(-1);
	    }
         p->output = (p->fn==NAND) ? A_NOT(v2) : v2;
	 push(stack,p);
         break;
      case OR: case NOR:
         set(p->changed);
	 for(i=0; i<p->ninput; i++)
	    if(i != fault->line) {
	       if(p->inlis[i]->output==X) {
	          p->inlis[i]->output=ZERO;
	          push(stack,p->inlis[i]);
	       }
	       else if(p->inlis[i]->output != ZERO) return(-1);
	    }
         p->output = (p->fn==NOR) ? A_NOT(v2) : v2;
	 push(stack,p);
         break;
      case NOT:
         p->output = A_NOT(v2);
	 push(stack,p);
	 break;
      case BUFF: case PO:
         p->output = v2;
	 push(stack,p);
	 break;
      case XOR: case XNOR: break;
      }

      /* schedule events */
      if(p->output!=X) {schedule_output(p);}
      for(i=0;i<p->ninput;i++)
	 if(p->inlis[i]->output!=X) {
	    last=max(p->inlis[i]->dpi,last);
	    schedule_input(p,i);
	  }
   }

   else {				/* output line fault */
      p->output=v2;
      push(stack,p);
      schedule_output(p);

      if(is_head(p)) set(p->changed);
      else if(p->ninput==1) {
	 set(p->changed);
	 v1 = (v2==D) ? ONE : ZERO;
	 p->inlis[0]->output = a_truthtbl1[p->fn][v1];
	 push(stack,p->inlis[0]);
	 schedule_input(p,0);
	 last=p->inlis[0]->dpi;
      } else if((v2==D && (p->fn==AND||p->fn==NOR)) ||
	      (v2==DBAR && (p->fn==NAND||p->fn==OR))) {
	 set(p->changed);
         v1=(p->fn==AND || p->fn==NAND) ? ONE : ZERO;
	 for(i=0;i<p->ninput;i++)
	    if(p->inlis[i]->output==X) {
	       p->inlis[i]->output=v1;
	       last=max(p->inlis[i]->dpi,last);
	       push(stack,p->inlis[i]);
	       schedule_input(p,i);
	    }
      }
      else {
	 pushevent(p);
	 last=p->dpi;
      }
   }

   return(last);
}

/*	faulty_gate_eval
	Evaluates the faulty gate function and returns the output value.
*/
level faulty_gate_eval(g,cf)
register GATEPTR g;
FAULTPTR cf;
{
   register int i, j;
   register level val;
   level fval;
   logic f;

   if(g->ninput==0) return(g->output);

   if(cf->line==OUTFAULT) {
      j=0;
      val = g->inlis[0]->output;
   } else {
      j=cf->line;
      val = g->inlis[j]->output;
      if(val==ZERO && cf->type==SA1) val=DBAR;
      else if(val==ONE && cf->type==SA0) val=D;
   }
 
   if(g->ninput==1) val=a_truthtbl1[g->fn][val];
   else {
      f=(g->fn==NAND) ? AND : (g->fn==NOR) ? OR : g->fn;
      for(i=0; i<j; i++)
         val=a_truthtbl2[f][val][g->inlis[i]->output];
      for(++i; i<g->ninput; i++)
         val=a_truthtbl2[f][val][g->inlis[i]->output];
      if(g->fn==NAND||g->fn==NOR) val=A_NOT(val);
   }

   if(cf->line==OUTFAULT) {
      if(val==ZERO && cf->type==SA1) val=DBAR;
      else if(val==ONE && cf->type==SA0) val=D;
   }

   return(val);
}

/*	eval
	Evaluate good circuit in forward and backward completely.
	Set changed flag if the gate is evaluated permanently.
	Push the evaluated gate to stack for backtracking.
	Schedule next events.
*/
status eval(gate,cf)
register GATEPTR gate;
FAULTPTR cf;
{
   register int i,j;
   register level val, v1;
   int num_x;
   logic f;
   GATEPTR *p;

   reset(gate->changed);
   p=gate->inlis;

   /* if a line is a head line, stop */
   if(is_head(gate)) {set(gate->changed); return(FORWARD);}

   /* faulty gate evaluation */
   if(gate==cf->gate) {
      val=faulty_gate_eval(gate,cf);
      if(val==X) {
	 if(gate->output!=X) {
	    for(i=num_x=0;i<gate->ninput;i++)
               if(p[i]->output==X) { num_x++; j=i; }
	    if(num_x==1) {	/* backward implication */
	       val=(gate->output==D) ? ONE :
		   (gate->output==DBAR) ? ZERO : gate->output;
	       val=a_truthtbl1[gate->fn][val];
	       switch(gate->fn) {
	       case XOR: case XNOR:
		  v1 = (j==0) ? p[1]->output : p[0]->output;
		  if(v1==ONE) val=a_truthtbl1[NOT][val];
		  break;
	       }
	       p[j]->output=val;
	       set(gate->changed);
	       push(stack,p[j]);
	       schedule_input(gate,j);
               return(BACKWARD);
	    }
	    else push(unjustified,gate);
	 }
      }
      else if(val==gate->output) set(gate->changed);
      else if(gate->output==X) {	/* forward imp */
	 set(gate->changed);
	 gate->output=val;
	 push(stack,gate);
	 schedule_output(gate);
      }
      else return(CONFLICT);
      return(FORWARD);
   }

   /* fault free gate evaluation */
   gate_eval1(gate,val,f,i);

   if(val==gate->output) {		/* no event */
      if(val!=X)
	 set(gate->changed);
      return(FORWARD);
   }
   if(gate->output==X) {		/* forward implication */
      gate->output=val;
      push(stack,gate);
      set(gate->changed);
      schedule_output(gate);
      return(FORWARD);
   }

   if(val!=X) return(CONFLICT);		/* conflict */

   /* backward implication */
   switch(gate->fn) {
   case AND: case NAND: case OR: case NOR:
      v1 = (gate->fn==AND || gate->fn==NOR) ? ONE : ZERO;
      if(gate->output==v1) {
	 set(gate->changed);
         for(i=0;i<gate->ninput;i++)
	    if(p[i]->output==X) {
	       p[i]->output=a_truthtbl1[gate->fn][v1];
	       push(stack,p[i]);
	       schedule_input(gate,i);
	    }
         i=BACKWARD;
      } else {
         for(i=num_x=0; i<gate->ninput; i++)
            if(p[i]->output==X) { num_x++; j=i; }
         if(num_x==1) {
	    p[j]->output = a_truthtbl1[gate->fn][gate->output];
	    set(gate->changed);
	    push(stack,p[j]);
	    schedule_input(gate,j);
	    i=BACKWARD;
	 } else {
	    push(unjustified,gate);
	    i=FORWARD;
	 }
      }
      break;
   case BUFF: case NOT: case PO:
      p[0]->output=a_truthtbl1[gate->fn][gate->output];
      set(gate->changed);
      push(stack,p[0]);
      schedule_input(gate,0);
      i=BACKWARD;
      break;
   case XOR: case XNOR:
      for(i=num_x=0;i<gate->ninput;i++)
         if(p[i]->output==X) { num_x++; j=i; }
      if(num_x==1) {
	 v1=(j==0) ? p[1]->output : p[0]->output;
	 val=a_truthtbl1[gate->fn][gate->output];
	 if(v1==ONE) val=a_truthtbl1[NOT][val];
	 p[j]->output=val;
	 set(gate->changed);
	 push(stack,p[j]);
	 schedule_input(gate,j);
	 i=BACKWARD;
      } else {
	 push(unjustified,gate);
	 i=FORWARD;
      }
      break;
   }

#ifdef LEARNFLG
   if(learnmode=='y' && gate->plearn!=NULL)
      if(gate->output == ZERO || gate->output==ONE)
         switch(imply_learn(gate,gate->output)) {
	 case BACKWARD: i=BACKWARD; break;
	 case CONFLICT: i=CONFLICT; break;
	 }
#endif
   return(i);
}

/*	imply
	box 3 of the FAN algorithm.
	Forward and backward implication.
*/
boolean imply(maxdpi,backward,last,cf)
int maxdpi,last;
boolean backward;
FAULTPTR cf;
{
   register int i, start;
   status st;
   GATEPTR g;

   if(backward) start=last;
   else start=0;
   while(TRUE) {
      /* backward implication */
      if(backward)
	 for(i=start;i>=0;i--)
	    while(!is_empty(event_list[i])) {
	       g=pop(event_list[i]);

	       if((st=eval(g,cf))==CONFLICT) return(FALSE);
	    }
      /* forward implication */
      reset(backward);
      for(i=0;i<maxdpi;i++) {
	 while(!is_empty(event_list[i])) {
	    if((st=eval(pop(event_list[i]),cf))==CONFLICT) return(FALSE);
	    else if(st==BACKWARD) {
	       start=i-1;
	       set(backward);
	       break;
	    }
         }
	 if(backward) break;
      }
      if(!backward) break;
   }
   return(TRUE);
}

/*	unique_sensitize
	Box 6 in Fig 9 of the FAN algorithm.
	Predetermines all neccessary inputs of the uniquely
	sensitizable path.
	Returns -1 if no sensitized values exist.
        Otherwise, returns the highest depth for backward implication.
*/

int unique_sensitize(gate,faulty_gate)
register GATEPTR gate; GATEPTR faulty_gate;
{
   register int i;
   register LINKPTR p;
   register GATEPTR curr,next;
   int last;		/* the largest depth of sensitized lines */
   boolean flag;
   level v1;

   last=(-1);

   /* sensitize the current gate */
   if(gate!=faulty_gate) {
      v1=(gate->fn==AND || gate->fn==NAND) ? ONE :
	 (gate->fn==OR || gate->fn==NOR) ? ZERO : X;
      if(v1!=X)
	 for(i=0;i<gate->ninput;i++)
	    if(gate->inlis[i]->output==X) {
	       gate->inlis[i]->output=v1;
	       last=max(gate->inlis[i]->dpi,last);
	       push(stack,gate->inlis[i]);
	       schedule_input(gate,i);
	    }
   }

   /* sensitize next path */
   curr=gate;
   while(curr!=NULL) {
      if(curr->noutput==0) break;
      else if(curr->noutput==1) next=curr->outlis[0];
      else if(curr->u_path==NULL) break;
      else next=curr->u_path->ngate;
      v1=(next->fn==AND || next->fn==NAND) ? ONE :
	 (next->fn==OR || next->fn==NOR) ? ZERO : X;
      if(v1!=X) {
         if(curr->noutput==1) {		/* one fanout */
	    for(i=0;i<next->ninput;i++)
	       if(next->inlis[i]!=curr && next->inlis[i]->output==X) {
	          next->inlis[i]->output=v1;
		  last=max(next->inlis[i]->dpi,last);
		  push(stack,next->inlis[i]);
		  schedule_input(next,i);
	       }
	 }
         else {				/* multiple fanout */
	    for(i=0;i<next->ninput;i++)
	       if(next->inlis[i]->output==X) {
		  set(flag);
		  for(p=curr->u_path->next;p!=NULL;p=p->next)
		     if(next->inlis[i]==p->ngate) {
			reset(flag);
			break;
		     }
		  if(flag) {
		     next->inlis[i]->output=v1;
		     last=max(next->inlis[i]->dpi,last);
		     push(stack,next->inlis[i]);
		     schedule_input(next,i);
		  }
	       }
	 }
      }
      curr=next;
   }
   return(last);
}

/*------dynamic_unique_sensitize---------------------------------
	Dynamic unique path sensitization
	Finds dynamic dominators for the given D-frontier gates
	and assigns mandatory signals.

	Algorithm:
	   This is a three step algorithm finding dynamic dominators.
	   1. Propagate all D-frontier gates in the forward order.
	   2. Trace back in the backward order ---
	      This step finds all X-paths.
	   3. Find dynamic dominators by tracing X-paths.

	   Assigns non-controlling values to inputs of dynamic
	   dominators which can be be reachable from D-frontier gates.

	Implemented by H. K. Lee, 1/20/1994
---------------------------------------------------------------------*/
 
int dynamic_unique_sensitize(Dfront, nod, maxdpi, dom_array, faulty_gate)
int nod,maxdpi;
GATEPTR *Dfront;
GATEPTR *dom_array, faulty_gate;
{
   int ndom=0, ngate;
   int dy_id2;
   register int i,j,k,l,m,n;
   register GATEPTR gut, g, gate, next;
   GATEPTR Dominator;
   int ndominator=0,no_dom=0,new_dom;
   int flag = FALSE;
   int debug=TRUE;
   int v1,send=-1;
   GATEPTR xpo[MAXPO]; int nxpo;

   /* pass 1: D-frontier propagation */
   ++dy_id;
   for(i=nxpo=0; i<=nod; i++) {
      gut = Dfront[i];
      if(gut->freach1 < dy_id) {
	 push(event_list[gut->dpi],gut);
	 gut->freach1=dy_id;
      }
   }
   for(i=0; i<maxdpi; i++) {
      while(!is_empty(event_list[i])) {
	 gut = pop(event_list[i]);
         if(gut->fn==PO) xpo[nxpo++] = gut;
         for(j=0; j<gut->noutput; j++) {
	    next = gut->outlis[j];
	    if((next->output==X) && (next->freach1<dy_id)) {
	       push(event_list[next->dpi],next);
	       next->freach1=dy_id;
	    }
	 }
      }
   }

   /* pass 2: Backward propagation --- X-path */
   dy_id2 = dy_id+1;
   for(i=0; i<nxpo; i++) {
      gut=xpo[i];
      gut->freach1=dy_id2;
      for(j=0; j<gut->ninput; j++) {
         next = gut->inlis[j];
         if(next->freach1==dy_id) {
	    push(event_list[next->dpi],next);
	    next->freach1 = dy_id2;
	 }
      }
   }
   for(i=maxdpi-1; i>=0; i--)
      while(!is_empty(event_list[i])) {
         gut = pop(event_list[i]);
         for(j=0; j<gut->ninput; j++) {
            next = gut->inlis[j];
            if(next->freach1==dy_id) {
               push(event_list[next->dpi],next);
               next->freach1 = dy_id2;
            }
         }
      }

   /* pass 3: Compute dominators */
   dy_id = dy_id2+1;
   for(i=ngate=0; i<=nod; i++) {
      gut = Dfront[i];
      push(event_list[gut->dpi],gut);
      ngate++;
      gut->freach1=dy_id;
   }
   for(i=k=0; i<maxdpi; i++) {
      if(ngate==1 && event_list[i].last==0)
	 dom_array[k++] = event_list[i].list[0];
      while(!is_empty(event_list[i])) {
         gut = pop(event_list[i]);
	 ngate--;
	 if(gut->fn==PO) { ngate=INFINITY; break; }
         for(j=0; j<gut->noutput; j++) {
            next = gut->outlis[j];
            if(next->freach1==dy_id2) {
               push(event_list[next->dpi],next);
               next->freach1=dy_id;
	       ngate++;
            }
	 }
      }
      if(ngate==INFINITY) break;
   }

   /* Assign non-controlling values to dominators */
   send=(-1);
   while(--k >= 0) {
      gut=dom_array[k];
/*
printf("dominator: gut=%d #Dfrontier=%d\n",gut->index,nod+1);
*/
      if(gut==faulty_gate) continue;
      v1=(gut->fn==AND || gut->fn==NAND) ? ONE :
         (gut->fn==OR || gut->fn==NOR) ? ZERO : X;
      if(v1 != X) {
         for(i=0; i<gut->ninput; i++){
	    next = gut->inlis[i];
            if(next->freach1<dy_id && next->output==X) {
               next->output=v1;
/*
printf("\tmandatory signal assignment: gut=%d val=%d\n", next->index, v1);
*/
               send=max(next->dpi,send);
               push(stack,next);
               schedule_input(gut,i);
            }
         }
      }
   }

   return(send);
}
 

/*	closest_po
	Finds the gate closiest from a primary output.
*/
GATEPTR closest_po(objective,pclose)
struct STACK objective;
int *pclose;
{
   register int i,distance;
   register GATEPTR p;

   if(is_empty(objective)) return(NULL);
   *pclose=objective.last;
   distance=objective.list[*pclose]->dpo;
   for(i=(objective.last)-1;i>=0;i--)
      if(objective.list[i]->dpo<distance) {
	 distance=objective.list[i]->dpo;
	 *pclose=i;
      }
   p=objective.list[*pclose];
   return(p);
}

/*	select_hardest
	Finds the hardest gate to satisfy
*/
GATEPTR select_hardest(objective,pclose)
struct STACK objective;
int *pclose;
{
   register int i,distance;
   register GATEPTR p;

   if(is_empty(objective)) return(NULL);
   *pclose=objective.last;
   distance=objective.list[*pclose]->dpo;
   for(i=(objective.last)-1;i>=0;i--)
      if(objective.list[i]->dpo>distance) {
	 distance=objective.list[i]->dpo;
	 *pclose=i;
      }
   p=objective.list[*pclose];
   return(p);
}

/*	backtrace
	Fiqure 8, of the FAN algorithm.
	Multiple backtrace.
*/
status backtrace(state)
status state;
{
   int i;
   register int j;
   register level v1;
   GATEPTR a_curr_obj,*input;
   int n0,n1,nn0,nn1;
   int easiest,easy_cont;

   /* box 1: Initialization of objective and its logic level */
   if(state==81) {
      copy(init_obj,curr_obj,i);
      for(i=0;i<=init_obj.last;i++) {
	 a_curr_obj=init_obj.list[i];
	 switch(a_curr_obj->output) {
	    case ZERO: case DBAR: 
		setline(a_curr_obj,1,0); break;	/* unjustified lines */
	    case ONE: case D: 
		setline(a_curr_obj,0,1); break;
	    default:				/* Dfrontier */
	       switch(a_curr_obj->fn) {
		  case AND: case NOR: setline(a_curr_obj,0,1); break;
		  case NAND: case OR: setline(a_curr_obj,1,0); break;
		  case XOR: case XNOR: setline(a_curr_obj,1,0); break;
	       }
	 }
      }
      state=82;
   }

   while(TRUE) {
      switch(state) {

	 /* Box 2,3,4 of figure 8 */
	 case 82:
	    if(is_empty(curr_obj)) 		/* box 2 */
	       if(is_empty(fan_obj)) state=103;	/* box 4 */
	       else state=86;
	    else {
	       a_curr_obj=pop(curr_obj);	/* box 3 */
	       state=85;
	    }
	    break;

	 /* Box 5,9,10,11,12 of figure 8 */
	 case 85:
	    if(is_head(a_curr_obj)) {		/* box 5 */
	       push(head_obj,a_curr_obj);	/* box 12 */
	    } else {				/* box 9,10,11 */
	       switch(a_curr_obj->fn) {
		  case AND:
		  	n0=a_curr_obj->numzero;
			n1=a_curr_obj->numone;
			v1=ZERO;
			break;
		  case OR:
		  	n0=a_curr_obj->numzero;
			n1=a_curr_obj->numone;
			v1=ONE;
			break;
		  case NAND:
			n0=a_curr_obj->numone;
			n1=a_curr_obj->numzero;
			v1=ZERO;
			break;
		  case NOR:
			n0=a_curr_obj->numone;
			n1=a_curr_obj->numzero;
			v1=ONE;
			break;
		  case NOT:
			n0=a_curr_obj->numone;
		        n1=a_curr_obj->numzero;
			v1=X;
		        break;
		  case XOR:
			j=0;
			if((v1=a_curr_obj->inlis[j]->output) == X)
			   v1=a_curr_obj->inlis[++j]->output;
			if(v1==ONE) {
			   n0=a_curr_obj->numone;
			   n1=a_curr_obj->numzero; }
			else {
			   n0=a_curr_obj->numzero;
			   n1=a_curr_obj->numone;
			}
			v1=X;
			break;
		  case XNOR:
			j=0;
			if((v1=a_curr_obj->inlis[j]->output) == X)
			   v1=a_curr_obj->inlis[++j]->output;
			if(v1==ZERO) {
			   n0=a_curr_obj->numone;
			   n1=a_curr_obj->numzero; }
			else {
			   n0=a_curr_obj->numzero;
			   n1=a_curr_obj->numone;
			}
			v1=X;
			break;
		  default: /* BUFF, PO, PI */
			n0=a_curr_obj->numzero;
			n1=a_curr_obj->numone;
			v1=X;
			break;
	       }

	       /* Find the easiest input. */
	       input=a_curr_obj->inlis;
	       easy_cont=INFINITY;
	       easiest=0;
	       if(v1==ZERO) {  	/* and, nand */
		  for(i=0;i<a_curr_obj->ninput;i++)
		     if(input[i]->output==X)
			if(easy_cont>input[i]->cont0) {
			   easy_cont=input[i]->cont0;
			   easiest=i;
			}
	       }
	       else {		/* or, nor, xor,xnor */
		  for(i=0;i<a_curr_obj->ninput;i++)
		     if(input[i]->output==X)
			if(easy_cont>input[i]->cont1) {
			   easy_cont=input[i]->cont1;
			   easiest=i;
			}
	       }

	       for(i=0;i<a_curr_obj->ninput;i++) {
		  if(input[i]->output==X) {

		     if(i==easiest) { nn0=n0; nn1=n1; }
		     else if(v1==ZERO) { nn0=0; nn1=n1; }
		     else if(v1==ONE) { nn0=n0; nn1=0; }
		     else {	/* xor,xnor */
		        if(n0>n1) { nn0=n0; nn1=n1; }
			else { nn0=n1; nn1=n0; }
		     }

		     if(nn0>0 || nn1>0)
		        if(is_fanout(input[i])) {
			   if(input[i]->numzero==0 && input[i]->numone==0)
			      push(fan_obj,input[i]);
		 	   input[i]->numzero+=nn0;
			   input[i]->numone+=nn1;
		        } else {
			   setline(input[i],nn0,nn1);
			   push(curr_obj,input[i]);
		        }
		  }
	       } /* for */
	    }

	    state=82;
	    break;

	 /* Box 6,7,8 of figure 8 */
	 case 86:
	    a_curr_obj=closest_po(fan_obj,&i);	/* box 6 */
	    delete(fan_obj,i);
	    if(a_curr_obj->output!=X) { state=82; break; }
	    if(is_reachable_from_fault(a_curr_obj)) {/* box 7 */
	       state=85; break;}
	    if(!is_conflict(a_curr_obj)) {	/* box 8 */
	       state=85; break;}
	    push(final_obj,a_curr_obj);		/* box 12 in figure 10 */
	    state=93;
	    break;

	 default:
	    return(state);
      }
   }
}

/*	find_final_objective
	Figure 10 of the FAN algorithm.
	Finds a final objective.
*/

void 
find_final_objective(backtrace_flag,fault_propagated_to_po,nog,last_Dfrontier)
boolean *backtrace_flag;
boolean fault_propagated_to_po;
int nog;
GATEPTR *last_Dfrontier;
{
   int i;
   register GATEPTR p;
   register status state;


   if(*backtrace_flag) state=107;	/* box 1 */
   else 
      if(is_empty(fan_obj)) state=103;	/* box 2 */
      else state=86;
   while(TRUE)
      switch(state) {
	 case 103: 			/* box 3,4,5,6 */
	    if(is_empty(head_obj)) state=107;	/* box 3 */
	    else {
	       p=head_obj.list[0];
	       for(i=1;i<=head_obj.last;i++)
		  head_obj.list[i-1]=head_obj.list[i];
	       delete_last(head_obj);
	       if(p->output==X) {		/* box 4,5 */
		  push(final_obj,p);		/* box 6 */
		  state=93;
	       }
	       else state=103;
	    }
	    break;
	 case 107:			/* box 7,8,9,10,11 */
	    reset(*backtrace_flag);	/* box 7 */
	    for(i=0;i<nog;i++) {	/* initialization */
	       net[i]->numzero=0;
	       net[i]->numone=0;
	    }
	    clear(init_obj);
	    clear(curr_obj);
	    clear(fan_obj);
	    clear(head_obj);
	    clear(final_obj);
	    if(!is_empty(unjustified)) {	/* box 8 */
	       copy(unjustified,init_obj,i);	/* box 9 */
	       if(fault_propagated_to_po) {	/* box 10 */
		  (*last_Dfrontier)=NULL;
		  state=81;
		  break;
	       }
	    }
	    switch(SELECTMODE) {
	    case 0:		/* easiest D first */
	       (*last_Dfrontier) = closest_po(Dfrontier,&i);
	       push(init_obj,(*last_Dfrontier));
	       break;
	    case 1:
	       (*last_Dfrontier) = select_hardest(Dfrontier,&i);
	       push(init_obj,(*last_Dfrontier));
	       break;
	    case 2:
	       (*last_Dfrontier) = closest_po(Dfrontier,&i);
	       if(is_empty(unjustified)) { push(init_obj,(*last_Dfrontier)); }
	       break;
	    case 3: 
	       (*last_Dfrontier) = select_hardest(Dfrontier,&i);
	       if(is_empty(unjustified)) { push(init_obj,(*last_Dfrontier)); }
	       break;
	    }

	    state=81;
	    break;
	 case 86: case 81:
	    state=backtrace(state);
	    break;
	 default:
	    return;				/* exit */
      }
}

/*	Xpath
	Finds the existence of an X-path recursively.
	Returns 0 if no X-path exist,
		1 if unknown (not checked yet) and
		2 if an X-path exist.
*/
boolean Xpath(gate)
register GATEPTR gate;
{
   register int i;

   /* base step --- if no X-path exist, return FALSE  */
   if(gate->output!=X || gate->xpath==0) {
      gate->xpath=0;
      return(FALSE);
   }

   /* base step --- if an X-path exist, return TRUE */
   if((gate->fn==PO) || (gate->xpath==2)) {
      gate->xpath=2;
      return(TRUE);
   }

   /* induction step --- else, go to next step */
   for(i=0;i<gate->noutput;i++)
      if(Xpath(gate->outlis[i])) {
	 gate->xpath=2;
	 return(TRUE);
      }
   gate->xpath=0;
   return(FALSE);
} 

/*	update_Dfrontier
	Updates Dfrontier and checks X-path exist or not.
*/
void update_Dfrontier()
{
   register int i,j;
   register GATEPTR g;
   int first;

   first=INFINITY;
   for(i=0;i<=Dfrontier.last;) {
      g=Dfrontier.list[i];
      switch(g->output) {
	 case D: case DBAR:
	    for(j=0;j<g->noutput;j++)
	       push(Dfrontier,g->outlis[j]);
            delete(Dfrontier,i);
	    break;
	 case X:
	    if(g->index<first) first=g->index;
	    i++;
	    break;
	 default:			/* 1 or 0 */
	    delete(Dfrontier,i);
      }
   }
}

/*	restore_faults
	Sets up primary inputs of free faults.
*/
void restore_faults(fal)
FAULTPTR fal;
{
   register int i,j;
   register GATEPTR p;
   int k;
   level value,gtype;

   clear(fan_obj);
   p=fal->gate;
   if(fal->line!=OUTFAULT) p=p->inlis[fal->line];
   push(fan_obj,p);

   while(TRUE) {
      p=p->outlis[0];
      for(i=0;i<p->ninput;i++)
         if(p->inlis[i]->output==ZERO || p->inlis[i]->output==ONE)
	    push(fan_obj,p->inlis[i]);
      if(is_head(p)) break;
   }

   while(!is_empty(fan_obj)) {
      p=pop(fan_obj);    
      if(p->output==D) p->output=ONE;
      else if(p->output==DBAR) p->output=ZERO;
      if(!(p->fn==PI || p->output==X)) { 
         clear(curr_obj);
	 push(curr_obj,p);
	 while(!is_empty(curr_obj)) {
	    p=pop(curr_obj);
	    switch(p->fn) {
	       case PI: break;
	       case XOR:
		  p->inlis[0]->output=ZERO;
		  push(curr_obj,p->inlis[0]);
		  for(j=1;j<p->ninput;j++) {
		     p->inlis[j]->output=p->output;
		     push(curr_obj,p->inlis[j]);
		  }
		  break;
	       case XNOR:
		  p->inlis[0]->output=ONE;
		  push(curr_obj,p->inlis[0]);
		  for(j=1;j<p->ninput;j++) {
		     p->inlis[j]->output=p->output;
		     push(curr_obj,p->inlis[j]);
		  }
		  break;
	       case PO: case BUFF: case NOT:
		  p->inlis[0]->output=a_truthtbl1[p->fn][p->output];
		  push(curr_obj,p->inlis[0]);
		  break;
	       default:		/* and,or,nor,nand */
		  value=a_truthtbl1[p->fn][p->output];
		  gtype=(p->fn==AND ||p->fn==NAND) ? ONE : ZERO;
		  if(value==gtype)
		     for(j=0;j<p->ninput;j++) {
			p->inlis[j]->output=value;
			push(curr_obj,p->inlis[j]);
		     }
		  else {
		     k=0;
		     for(j=1;j<p->ninput;j++)
			if(p->inlis[j]->dpi<p->inlis[k]->dpi) k=j;
		     p->inlis[k]->output=value;
		     push(curr_obj,p->inlis[k]);
		  } 
		  break;
	    } /* switch */
	 } /* while */
      } /* if */
   } /* while */
}

/*	justify_free_lines
	Justifies free lines of the circuit.
*/
void justify_free_lines(npi,of,cf)
int npi;
FAULTPTR of,cf;
{
   register int i,j,k;
   register GATEPTR p;
   level value,gtype;

   for(i=0;i<npi;i++) {
      if(headlines[i]<0) break;
      p=net[headlines[i]];
      if(p==cf->gate && of != NULL) {
	 restore_faults(of);
	 continue;
      }
      if(p->output==D) p->output=ONE;
      else if(p->output==DBAR) p->output=ZERO;
      if(!(p->fn==PI || p->output==X)) { 
         clear(curr_obj);
	 push(curr_obj,p);
	 while(!is_empty(curr_obj)) {
	    p=pop(curr_obj);
	    switch(p->fn) {
	       case PI: break;
	       case XOR:
		  p->inlis[0]->output=ZERO;
		  push(curr_obj,p->inlis[0]);
		  for(j=1;j<p->ninput;j++) {
		     p->inlis[j]->output=p->output;
		     push(curr_obj,p->inlis[j]);
		  }
		  break;
	       case XNOR:
		  p->inlis[0]->output=ONE;
		  push(curr_obj,p->inlis[0]);
		  for(j=1;j<p->ninput;j++) {
		     p->inlis[j]->output=p->output;
		     push(curr_obj,p->inlis[j]);
		  }
		  break;
	       case PO: case BUFF: case NOT:
		  p->inlis[0]->output=a_truthtbl1[p->fn][p->output];
		  push(curr_obj,p->inlis[0]);
		  break;
	       default:		/* and,or,nor,nand */
		  value=a_truthtbl1[p->fn][p->output];
		  gtype = (p->fn==AND ||p->fn==NAND) ? ONE : ZERO;
		  if(value==gtype)
		     for(j=0;j<p->ninput;j++) {
			p->inlis[j]->output=value;
			push(curr_obj,p->inlis[j]);
		     }
		  else {
		     k=0;
		     for(j=1;j<p->ninput;j++)
			if(p->inlis[j]->dpi<p->inlis[k]->dpi) k=j;
		     p->inlis[k]->output=value;
		     push(curr_obj,p->inlis[k]);
		  } 
		  break;
	    } /* switch */
	 } /* while */
      } /* if */
   } /* for */
}


/*	backtrack
	Backtracs from current tree node.
	Returns FALSE if the tree is empty.
*/
boolean backtrack(faulty_gate,last,nog)
GATEPTR faulty_gate;
int *last,nog;
{

   register GATEPTR p;
   register int i,j;
   level value;

   while(!is_empty(tree))
      if(is_flagged(current_node)) delete_last(tree);
      else {

	 /* update & remove duplicate unjustified lines */
         for(i=unjustified.last;i>=0;i--) {
	    p=unjustified.list[i];
	    if(is_justified(p)) delete(unjustified,i);
	    else {
	       set(p->changed);
	       push(final_obj,p);
	    }
	 }
	 while(!is_empty(final_obj)) reset(pop(final_obj)->changed);

	 /* restore and schedule events */
	 value=A_NOT(current_node.gate->output);
	 set(current_node.flag);
	 for(i=current_node.pstack;i<=stack.last;i++) {
	    p=stack.list[i];
	    p->output=X;
	    reset(p->changed);
	    for(j=0;j<p->noutput;j++) reset(p->outlis[j]->changed);
	 }
	 *last=0;
	 for(i=current_node.pstack+1;i<=stack.last;i++) {
	    p=stack.list[i];
	    for(j=0;j<p->noutput;j++) {
	       if(p->outlis[j]->output!=X) {
		  if(!is_justified(p->outlis[j]))
		     push(unjustified,p->outlis[j]);
		  pushevent(p->outlis[j]);
	       }
	       if(*last<p->outlis[j]->dpi) *last=p->outlis[j]->dpi;
	    }
	 }
	 stack.last=current_node.pstack;
	 current_node.gate->output=value;
	 if(is_head(current_node.gate)) set(current_node.gate->changed);
	 else {pushevent(current_node.gate);}
	 schedule_output(current_node.gate);

	 /* update Dfrontier */
	 clear(Dfrontier);
	 push(Dfrontier,faulty_gate);
	 update_Dfrontier();

	 /* update unjustified set */
	 for(i=unjustified.last;i>=0; i--)
	    if(unjustified.list[i]->output==X) delete(unjustified,i);

	 /* reset xpath */
	 for(i=faulty_gate->index;i<nog;i++) net[i]->xpath=1;
	 return(TRUE);
      }
   return(FALSE);
}
   

/*	faulty_line_is_free
	Propagates the fault into a head line.
	Changes the fault into equivalent fault in the head line.
*/
void faulty_line_is_free(cf)
FAULTPTR cf;
{
   register int i;
   register level value;
   register GATEPTR p;

   p=cf->gate;
   if(cf->line!=OUTFAULT) p=p->inlis[cf->line];
   p->output=(cf->type==SA0) ? D : DBAR;
   push(stack,p->outlis[0]);
   while(!is_empty(stack)) {
      p=pop(stack);
      value=(p->fn==AND||p->fn==NAND) ? ONE : ZERO;
      for(i=0;i<p->ninput;i++)
	 if(p->inlis[i]->output==X) p->inlis[i]->output=value;
         else p->output=a_truthtbl1[p->fn][p->inlis[i]->output];
      if(is_free(p)) push(stack,p->outlis[0]);
   }
   set(p->changed);
   push(stack,p);
   schedule_output(p);
   cf->gate=p;
   cf->line=OUTFAULT;
   cf->type= (p->output==D) ? SA0 : SA1;
}

/*	fan
	Fig 9 main flowchart of the FAN algorithm.
	Main for the FAN algorithm.
*/
status fan(nog,maxdpi,npi,npo,cf,maxbacktrack,nbacktrack)
int nog,maxdpi,npi,npo,maxbacktrack,*nbacktrack;
FAULTPTR cf;
{
   register int i;
   register GATEPTR gut, g;
   int last_dpi;
   GATEPTR last_Dfrontier;
   boolean backward_flag,backtrace_flag,fault_propagated_to_po;
   boolean Dfrontier_changed,done;
   status state;
   FAULTPTR original=NULL;

   *nbacktrack=0;
   reset(done);
   reset(backward_flag);
   set(backtrace_flag);
   reset(fault_propagated_to_po);
   last_Dfrontier=NULL;

   gut=cf->gate;

   init_net(nog,gut,maxdpi);		/* initializaiton */

   if(cf->line!=OUTFAULT) gut=gut->inlis[cf->line];
   if(is_free(gut)) {			/* box 1 */
      original=(FAULTPTR)malloc(sizeof(FAULTTYPE));
      original->gate=cf->gate;
      original->line=cf->line;
      original->type=cf->type;
      faulty_line_is_free(cf);
      last_dpi=0;
   }
   else last_dpi=set_faulty_gate(cf);
   if(last_dpi==(-1)) return(NO_TEST);

   gut=cf->gate;
#ifdef LEARNFLG
   if(gut->plearn!=NULL && gut->output!=X)
      switch(imply_learn1(gut,gut->output)) {
      case CONFLICT: return(NO_TEST); break;
      case BACKWARD: last_dpi=gut->dpi; break;
      }
#endif

   push(Dfrontier,gut);
   i=unique_sensitize(gut,gut);
   if((last_dpi=max(i,last_dpi))>0) set(backward_flag);
   state=93;

   /* main loop of fan algorithm */
   while(done==FALSE) {
      switch(state) {

	 case 93:	/* box 3,4,5,6 */

	    if(!imply(maxdpi,backward_flag,last_dpi,cf)){/* box 3 */
	       state=98;
	       break;
	    }
	    if(gut->output==ZERO || gut->output==ONE) { state=98; break;}

	    /* update unjustified lines and delete duplicated lines 
		final_obj should be empty */
	    for(i=unjustified.last;i>=0;i--) {
	       g=unjustified.list[i];
	       if(is_justified(g)) delete(unjustified,i);
	       else {
		  set(g->changed);
		  push(final_obj,g);
	       }
	    }
	    while(!is_empty(final_obj)) reset(pop(final_obj)->changed);

	    /* check for backtrace */
	    for(i=init_obj.last;i>=0;i--)
	       if(is_justified(init_obj.list[i])) delete(init_obj,i);

	    reset(fault_propagated_to_po);
	    for(i=0;i<npo;i++)
	       if( net[primaryout[i]]->output==D ||
		   net[primaryout[i]]->output==DBAR) {
		  set(fault_propagated_to_po);
		  break;
	       }

	    if(last_Dfrontier!=NULL)
	       if(last_Dfrontier->output==X) 
		  reset(Dfrontier_changed);
	       else set(Dfrontier_changed);
	    else set(Dfrontier_changed);

	    if(is_empty(init_obj) && Dfrontier_changed)	/* box 4, 4-1 */ 
	       set(backtrace_flag);

	    if(fault_propagated_to_po) {
	       state=99;				/* box 4-3 */
	       for(i=unjustified.last;i>=0;i--)
		  if(is_unjustified(unjustified.list[i]) &&
		     is_bound(unjustified.list[i])) {
		     state=97;
		     break;
		  }
	    }
	    else {					/* box 5 */
	       /* update Dfrontier */
	       if(!is_empty(Dfrontier)) update_Dfrontier();
	       for(i=gut->index;i<nog;i++) if(net[i]->xpath==2) net[i]->xpath=1;
	       for(i=Dfrontier.last;i>=0;i--)
	          if(!Xpath(Dfrontier.list[i]))
		     delete(Dfrontier,i);

	       if(is_empty(Dfrontier)) state=98;
	       else if(Dfrontier.last==0) {		/* box 6 */
		  if((last_dpi=unique_sensitize(Dfrontier.list[0],gut))>0) {
		     set(backward_flag);
		     state=93;
		  }
		  else if(last_dpi==0) state=93;
		  else state=97;
	       }
	       else state=97;
	    }
	    break;

	 case 97:					/* box 7 */

	    find_final_objective(&backtrace_flag,fault_propagated_to_po,nog,&last_Dfrontier);

	    while(!is_empty(final_obj)) {
	       g=pop(final_obj);
	       if(g->numzero>g->numone) g->output=ZERO;
	       else g->output=ONE;
	       (tree.last)++;
	       current_node.gate=g;
	       reset(current_node.flag);
	       push(stack,g);
	       if(is_head(g)) set(g->changed);
	       else pushevent(g);		/**** study ****/
	       schedule_output(g);
	       current_node.pstack=stack.last;
	    }

	    reset(backward_flag);
	    state=93;
	    break;

	 case 98:					/* box 8 */

	    if(is_flagged(current_node)) (*nbacktrack)++;
	    for(i=0;i<maxdpi;i++)
	       while(!is_empty(event_list[i])) reset(pop(event_list[i])->changed);
	    if(*nbacktrack>maxbacktrack) state=OVER_BACKTRACK;
	    else if(backtrack(gut,&last_dpi,nog)) {
	       if(last_dpi>0) set(backward_flag);
	       else reset(backward_flag);
	       set(backtrace_flag);
	       last_Dfrontier=NULL;
	       state=93;
	    }
	    else state=NO_TEST;
	    break;

	 case 99:
	    justify_free_lines(npi,original,cf);
	    state=TEST_FOUND;
	    if(no_faultsim=='y') {
	       Dprintio(test,npi,npo,++ntest_each);
	       if(logmode=='y') Dprintio(logfile,npi,npo,ntest_each);
	       if(gen_all_pat=='y') {
                  if(ntest_each_limit<=0 || ntest_each<ntest_each_limit) {
	             *nbacktrack=0;
	             state=98;
                  }
	       }
	    }
	    break;
	 default:
	    set(done);
      }

   }

   if(original!=NULL) {
      cf->gate=original->gate;
      cf->line=original->line;
      cf->type=original->type;
      free((char *)original);
   }
   return(state);
}


/*	fan1
	Fig 10 main flowchart of the FAN algorithm.
	Main for the FAN algorithm with the dynamic unique path sensitization.
*/
status fan1(nog,maxdpi,npi,npo,cf,maxbacktrack,nbacktrack)
int nog,maxdpi,npi,npo,maxbacktrack,*nbacktrack;
FAULTPTR cf;
{
   register int i;
   register GATEPTR gut, g;
   int last_dpi;
   GATEPTR last_Dfrontier;
   boolean backward_flag,backtrace_flag,fault_propagated_to_po;
   boolean Dfrontier_changed,done;
   status state;
   FAULTPTR original=NULL;

   *nbacktrack=0;
   reset(done);
   reset(backward_flag);
   set(backtrace_flag);
   reset(fault_propagated_to_po);
   last_Dfrontier=NULL;

   gut=cf->gate;

   init_net(nog,gut,maxdpi);		/* initializaiton */

   if(cf->line!=OUTFAULT) gut=gut->inlis[cf->line];
   if(is_free(gut)) {			/* box 1 */
      original=(FAULTPTR)malloc(sizeof(FAULTTYPE));
      original->gate=cf->gate;
      original->line=cf->line;
      original->type=cf->type;
      faulty_line_is_free(cf);
      last_dpi=0;
   }
   else last_dpi=set_faulty_gate(cf);
   if(last_dpi==(-1)) return(NO_TEST);

   gut=cf->gate;
#ifdef LEARNFLG
   if(gut->plearn!=NULL && gut->output!=X)
      switch(imply_learn1(gut,gut->output)) {
      case CONFLICT: return(NO_TEST); break;
      case BACKWARD: last_dpi=gut->dpi; break;
      }
#endif

   push(Dfrontier,gut);
   i=unique_sensitize(gut,gut);
   if((last_dpi=max(i,last_dpi))>0) set(backward_flag);
   state=93;

   /* main loop of fan algorithm */
   while(done==FALSE) {
      switch(state) {

	 case 93:	/* box 3,4,5,6 */

	    if(!imply(maxdpi,backward_flag,last_dpi,cf)){/* box 3 */
	       state=98;
	       break;
	    }
	    if(gut->output==ZERO || gut->output==ONE) { state=98; break;}

	    /* update unjustified lines and delete duplicated lines 
		final_obj should be empty */
	    for(i=unjustified.last;i>=0;i--) {
	       g=unjustified.list[i];
	       if(is_justified(g)) delete(unjustified,i);
	       else {
		  set(g->changed);
		  push(final_obj,g);
	       }
	    }
	    while(!is_empty(final_obj)) reset(pop(final_obj)->changed);

	    /* check for backtrace */
	    for(i=init_obj.last;i>=0;i--)
	       if(is_justified(init_obj.list[i])) delete(init_obj,i);

	    reset(fault_propagated_to_po);
	    for(i=0;i<npo;i++)
	       if( net[primaryout[i]]->output==D ||
		   net[primaryout[i]]->output==DBAR) {
		  set(fault_propagated_to_po);
		  break;
	       }

	    if(last_Dfrontier!=NULL)
	       if(last_Dfrontier->output==X) 
		  reset(Dfrontier_changed);
	       else set(Dfrontier_changed);
	    else set(Dfrontier_changed);

	    if(is_empty(init_obj) && Dfrontier_changed)	/* box 4, 4-1 */ 
	       set(backtrace_flag);

	    if(fault_propagated_to_po) {
	       state=99;				/* box 4-3 */
	       for(i=unjustified.last;i>=0;i--)
		  if(is_unjustified(unjustified.list[i]) &&
		     is_bound(unjustified.list[i])) {
		     state=97;
		     break;
		  }
	    }
	    else {					/* box 5 */
	       /* update Dfrontier */
	       if(!is_empty(Dfrontier)) update_Dfrontier();
	       for(i=gut->index;i<nog;i++) if(net[i]->xpath==2) net[i]->xpath=1;
	       for(i=Dfrontier.last;i>=0;i--)
	          if(!Xpath(Dfrontier.list[i]))
		     delete(Dfrontier,i);

	       if(is_empty(Dfrontier)) state=98;
               /*when dfrontier is not zero*/
	       else {		/* box 6 */
	          if(dy_id>=INFINITY-3) {
		     for(i=0; i<nog; i++) net[i]->freach1=0;
		     dy_id=0;
		  }
		  if((last_dpi=dynamic_unique_sensitize(Dfrontier.list,
			            Dfrontier.last,maxdpi,dyn_dom,gut))>0) {
		     set(backward_flag);
		     state=93;
		  }
		  else if(last_dpi==0) state=93;
		  else state=97;
	       }
	    }
	    break;

	 case 97:					/* box 7 */

	    find_final_objective(&backtrace_flag,fault_propagated_to_po,nog,&last_Dfrontier);

	    while(!is_empty(final_obj)) {
	       g=pop(final_obj);
	       if(g->numzero>g->numone) g->output=ZERO;
	       else g->output=ONE;
	       (tree.last)++;
	       current_node.gate=g;
	       reset(current_node.flag);
	       push(stack,g);
	       if(is_head(g)) set(g->changed);
	       else pushevent(g);		/**** study ****/
	       schedule_output(g);
	       current_node.pstack=stack.last;
	    }

	    reset(backward_flag);
	    state=93;
	    break;

	 case 98:					/* box 8 */

	    if(is_flagged(current_node)) (*nbacktrack)++;
	    for(i=0;i<maxdpi;i++)
	       while(!is_empty(event_list[i])) reset(pop(event_list[i])->changed);
	    if(*nbacktrack>maxbacktrack) state=OVER_BACKTRACK;
	    else if(backtrack(gut,&last_dpi,nog)) {
	       if(last_dpi>0) set(backward_flag);
	       else reset(backward_flag);
	       set(backtrace_flag);
	       last_Dfrontier=NULL;
	       state=93;
	    }
	    else state=NO_TEST;
	    break;

	 case 99:
	    justify_free_lines(npi,original,cf);
	    state=TEST_FOUND;
	 default:
	    set(done);

      }

   }

   if(original!=NULL) {
      cf->gate=original->gate;
      cf->line=original->line;
      cf->type=original->type;
      free((char *)original);
   }
   return(state);
}
