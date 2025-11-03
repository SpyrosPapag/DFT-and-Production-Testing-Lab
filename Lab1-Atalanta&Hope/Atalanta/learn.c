
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
 
        atalanta: version 1.1        H. K. Lee, 10/5/1992
        atalanta: version 2.0        H. K. Lee, 6/30/1997
 
***********************************************************************/

/*-----------------------------------------------------------------
	filename learn.c

	Static Learning procedure
-----------------------------------------------------------------*/
#include <stdio.h>

#include "parameter.h" 
#include "define.h"    
#include "macro.h"

/* #define	DEBUGLEARN	1 */

#define	FAIL	0
#define	PASS	1
#define	PASS1	2

extern GATEPTR *net;
extern void learn_node(), store_learn();
extern void initgood(), fatalerror();
extern level a_truthtbl1[MAXGTYPE][ATALEVEL];
extern level a_truthtbl2[MAXGTYPE][ATALEVEL][ATALEVEL];
extern STACKTYPE stack, *event_list;
extern int mac_i;

int SNODE;
level SVAL;
struct EDEN *impo;
int Lid=0;

#ifdef DEBUGLEARN
int norecord=0, noimpo=0, learnmemory=0;
double slearntime_beg, ulearntime_beg, learntime_beg;
double slearntime_end, ulearntime_end, learntime_end;

char *level2str[4]={"0", "1", "x", "z"};

#endif

/* macros for the gate evaluation using the truthtable */
#define gate_eval1(g,v,f,i) \
	if(g->ninput==1) v=a_truthtbl1[g->fn][g->inlis[0]->output]; \
	else if(g->ninput==2) \
	   v=a_truthtbl2[g->fn][g->inlis[0]->output][g->inlis[1]->output];\
	else if(g->ninput==0) v=g->output; \
        else { \
	   f = (g->fn==NAND) ? AND : \
	       (g->fn==NOR) ? OR : g->fn; \
	   v=a_truthtbl2[f][g->inlis[0]->output][g->inlis[1]->output];\
	   for(i=2;i<g->ninput;i++) \
	      v=a_truthtbl2[f][v][g->inlis[i]->output]; \
	   v=(g->fn==NAND||g->fn==NOR)? A_NOT(v) : v; \
	}

/*------leval---------------------------------------------------
	Evaluate good circuit in forward and backward completely.
	Set changed flag if the gate is evaluated permanently.
	Push the evaluated gate to stack.
	Schedule next events.
---------------------------------------------------------------*/
status leval(gate)
register GATEPTR gate;
{
   register int i,j;
   register level val, v1;
   int num_x;
   logic f;
   GATEPTR *p;

   /* forward gate evaluation */
   reset(gate->changed);
   p=gate->inlis;

   /* if a line is a head line, stop */
   if(is_free(gate)) { return(FORWARD);}

   /* fault free gate evaluation */
   for(i=0; i<gate->ninput; i++)
      if(gate->inlis[i]->numzero==Lid) { gate->numzero=Lid; break; }

   gate_eval1(gate,val,f,i);

   if(val==gate->output) {			/* no event */
      if(val!=X) set(gate->changed);
      return(FORWARD);
   }
   if(gate->output==X) {			/* forward evaluation */
      gate->output=val;				/* update gate output */
      push(stack,gate);
      set(gate->changed);
      schedule_output(gate);
      store_learn(gate,val);
      return(FORWARD);
   }

   if(val!=X) return(CONFLICT);			/* report conflict */

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
         return(BACKWARD);
      } else {
         for(i=num_x=0; i<gate->ninput; i++)
            if(p[i]->output==X) { num_x++; j=i; }
         if(num_x==1) {
            p[j]->output = a_truthtbl1[gate->fn][gate->output];
            set(gate->changed);
            push(stack,p[j]);
            schedule_input(gate,j);
            return(BACKWARD);
         }
      }
      break;

   case BUFF: case NOT: case PO:
      p[0]->output=a_truthtbl1[gate->fn][gate->output];
      set(gate->changed);
      push(stack,p[0]);
      schedule_input(gate,0);
      return(BACKWARD);
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
         return(BACKWARD);
      }
      break;
   }

/*
   v1=(gate->fn==AND || gate->fn==NOR) ? ONE :
      (gate->fn==NAND || gate->fn==OR) ? ZERO : X;
   if(gate->output==v1) {
      set(gate->changed);
      if(gate->fn==NAND || gate->fn==NOR) v1=A_NOT(v1);
      for(i=0;i<gate->ninput;i++)
	 if(p[i]->output==X) {
	    p[i]->output=v1;
	    push(stack,p[i]);
	    schedule_input(gate,i);
	 }
      return(BACKWARD);
   }
   else {
      num_x=0;
      for(i=0;i<gate->ninput;i++)
         if(p[i]->output==X) {
	  num_x++;
	  j=i;
         }
      if(num_x==1) {
	 if(v1!=X)
	    p[j]->output = (gate->fn==NAND||gate->fn==NOR) ?
			   A_NOT(gate->output) : gate->output;
         else {
	    v1=(j==0) ? p[1]->output : p[0]->output;
	    p[j]->output=(v1==gate->output)?ZERO:ONE;
	 }
	 set(gate->changed);
	 push(stack,p[j]);
	 schedule_input(gate,j);
         return(BACKWARD);
      }
   }

*/

   return(FORWARD);
}

/*	impval
	Forward and backward implication.
*/
boolean impval(maxdpi,backward,last)
int maxdpi,last;
boolean backward;
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
	       if((st=leval(g))==CONFLICT) return(FALSE);
	    }
      /* forward implication */
      reset(backward);
      for(i=0;i<maxdpi;i++) {
	 while(!is_empty(event_list[i])) {
	    if((st=leval(pop(event_list[i])))==CONFLICT) return(FALSE);
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

/*------learn---------------------------------------------
	preprocessing for static learning
	Good cct only
----------------------------------------------------------*/
void learn(nog,maxdpi)
int nog, maxdpi;
{
   register int ix;
   GATEPTR gut;
   struct EDEN *temp;
   struct LEARN *record;

#ifdef DEBUGLEARN
   gettime(&slearntime_beg,&ulearntime_beg,&learntime_beg);
   printf("DEBUG: Start learn(nog,maxdpi), nog=%d, maxdpi=%d\n",nog,maxdpi);
#endif

   for(temp=impo; temp!=NULL; ) {
      impo=temp->next;
      MFREE(temp);
      temp=impo->next;
   }
   for(ix=0; ix<nog; ix++) {
      gut=net[ix];
      reset(gut->changed);
      gut->numzero=(-1);
      gut->output=X;
      for(record=gut->plearn; record!=NULL; ) {
	 gut->plearn=record->next;
         MFREE(record);
         record=gut->plearn;
      }
   }
 
   for(ix=0; ix<nog; ix++) {
      gut=net[ix];
      if(is_free(gut)) continue;
      if(gut->ninput==1) continue;

#ifdef DEBUGLEARN
      printf("** Learn node %d: symbol=%s fi=%d fo=%d\n",
                 gut->index, gut->symbol->symbol, gut->ninput, gut->noutput);
#endif
      switch(gut->fn) {
      case AND: case NOR:
         learn_node(maxdpi,ix,ONE);
	 if(gut->noutput>1) learn_node(maxdpi,ix,ZERO);
	 break;
      case OR: case NAND:
         learn_node(maxdpi,ix,ZERO);
	 if(gut->noutput>1) learn_node(maxdpi,ix,ONE);
	 break;
      default:
	 if(gut->noutput > 1) {
	    learn_node(maxdpi,ix,ZERO);
	    learn_node(maxdpi,ix,ONE);
	 }
      }
   }

   clear(stack);

#ifdef DEBUGLEARN
   gettime(&slearntime_end,&ulearntime_end,&learntime_end);
   printf("\n*** End of learning\n");
   printf("*** Number of redundant nodes = %d\n",noimpo);
   printf("*** Number of learning records = %d\n",norecord);
   printf("*** Memory required = %d bytes\n",learnmemory);
   printf("*** CPU time spent = %.2f seconds\n",learntime_end-learntime_beg);
#endif
}


/*------learn_node: learning procedure for a node------*/
void learn_node(maxdpi,node,val)
int maxdpi; int node; level val;
{

   register int ix;
   struct EDEN *tmp;
   GATEPTR gut=net[node], tg;

   SNODE=node;
   gut->output=val;
   push(stack,gut);
   SVAL=A_NOT(val);

   pushevent(gut);
   gut->numzero=++Lid;
   schedule_output(gut);

   if(impval(maxdpi,FORWARD,0) == FALSE) {
      ALLOCATE(tmp,struct EDEN,1);
      tmp->node=node;
      tmp->val=A_NOT(val);
      tmp->next=impo;
      impo=tmp;
#ifdef DEBUGLEARN
      noimpo++;
      learnmemory+=sizeof(struct EDEN);
      printf("learn: impo: node %d = %s\n",tmp->node,level2str[tmp->val]);
#endif
      for(ix=0; ix<maxdpi; ix++)
         while(!is_empty(event_list[ix])) {
	    gut=pop(event_list[ix]);
	    reset(gut->changed);
         }
   }

   /* restore good values */
   for(ix=stack.last; ix>=0; ix--) {
      tg=stack.list[ix];
      tg->output=X;
      reset(tg->changed);
   }
   clear(stack);
}

/*------store_learn: gather info from learning------*/
void store_learn(gut,val)
GATEPTR gut; level val;
{
   struct LEARN *tmp;

   if(gut->ninput < 2) return;
   if(gut->numzero != Lid) return;

   switch(gut->fn) {
   case AND: case NOR: if(val==ZERO) return; break;
   case OR: case NAND: if(val==ONE) return; break;
   case XOR: case XNOR: break;
   default: return;
   }

   ALLOCATE(tmp,struct LEARN,1);
   tmp->node=SNODE;
   tmp->tval=SVAL;
   tmp->sval=A_NOT(val);
   tmp->next=gut->plearn;
   gut->plearn=tmp;

#ifdef DEBUGLEARN
   norecord++;
   learnmemory+=sizeof(struct LEARN);
   printf("learn: (node %d = %s) from ",tmp->node,level2str[tmp->tval]);
   printf("(node %d = %s)\n",gut->index,level2str[tmp->sval]);
#endif
}

int conflict_tbl[3][5]=
/*	0	1	x	d	dbar	        old/new	*/
{{	PASS,	FAIL,	PASS1,	FAIL,	PASS	},	/* 0 */
 {	FAIL,	PASS,	PASS1,	PASS,	FAIL	},	/* 1 */
 {	PASS,	PASS,	PASS,	PASS,	PASS	}	/* x */
};

/*------imply_learn--------------------------------------*/
status imply_learn(gut,val)
register GATEPTR gut; register level val;
{
   register struct LEARN *tmp;
   register GATEPTR tg;
   int state;

   switch(gut->fn) {
   case AND: case NOR: if(val==ONE) return(FORWARD); break;
   case OR: case NAND: if(val==ZERO) return(FORWARD); break;
   }

   state=FORWARD;
   for(tmp=gut->plearn; tmp!=NULL; tmp=tmp->next)
      if(tmp->sval==val) {
         tg=net[tmp->node];
	 switch(conflict_tbl[tg->output][tmp->tval]) {
	 case PASS: break;
         case FAIL: 
#ifdef DEBUGLEARN
	    printf("Learned: conflict at node=%d old=%s new=%s from node=%d val=%s\n",
                    tg->index, level2str[tg->output], level2str[tmp->tval],
		    gut->index, level2str[val]);
#endif
	    return(CONFLICT);
	 case PASS1:
	    tg->output=tmp->tval;
	    push(stack,tg);
	    pushevent(tg);
	    schedule_output(tg);
#ifdef DEBUGLEARN
	    printf("Learned: node=%d val=%s from node=%d val=%s\n",
		    tg->index, level2str[tg->output], gut->index, level2str[val]);
#endif
 	    state=BACKWARD;
	    break;
         }
      }

   return(state);
}

/*------imply_learn1-------------------------------------*/
status imply_learn1(gut,val)
register GATEPTR gut; register level val;
{
   register struct LEARN *tmp;
   register GATEPTR tg;
   int state;

   if(val==D) val=1;
   else if(val==DBAR) val=0;

   switch(gut->fn) {
   case AND: case NOR: if(val==ONE) return(FORWARD); break;
   case OR: case NAND: if(val==ZERO) return(FORWARD); break;
   }

   state=FORWARD;
   for(tmp=gut->plearn; tmp!=NULL; tmp=tmp->next)
      if(tmp->sval==val) {
         tg=net[tmp->node];
	 if(tg->freach) continue;
	 switch(conflict_tbl[tg->output][tmp->tval]) {
	 case PASS: break;
         case FAIL:
#ifdef DEBUGLEARN
	    printf("Learned: conflict at node=%d old=%s new=%s from node=%d val=%s\n",
                    tg->index, level2str[tg->output], level2str[tmp->tval],
		    gut->index, level2str[val]);
#endif
	    return(CONFLICT);
	 case PASS1:
	    tg->output=tmp->tval;
	    push(stack,tg);
	    pushevent(tg);
	    schedule_output(tg);
#ifdef DEBUGLEARN
	    printf("Learned: node=%d val=%s from node=%d val=%s\n",
		    tg->index, level2str[tg->output], gut->index, level2str[val]);
#endif
 	    state=BACKWARD;
	    break;
         }
      }

   return(state);
}
