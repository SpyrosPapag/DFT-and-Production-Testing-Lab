
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
 
        Changed Parser and added on-line manual: H. K. Lee, 10/5/1992
        Now, atalanta accepts the circuit written in the netlist format
        of ISCAS89 benchmark circuits as well as the netlist format of
        ISCAS85 benchmark circuits.
 
        atalanta: version 2.0        H. K. Lee, 6/30/1997
 
***********************************************************************/

/*--------------------------------------------------------------------- 
	filename io.c
	gettime() returns the CPU time.
-----------------------------------------------------------------------*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/times.h>
#include <time.h>

#include "parameter.h" 
#include "define.h"    
#include "macro.h"

#define NULL 0

extern GATEPTR *net;
extern int *primaryin,*primaryout,*headlines;
extern char *strcpy();
extern void fatalerror();
extern int maxlevel, POlevel;
extern int *depth_array;
extern GATEPTR *dynamic_stack;
extern STACKTYPE free_gates,    /* fault free simulation */
          faulty_gates,         /* list of faulty gates */
          eval_gates,           /* STEM_LIST to be simulated */
          active_stems;         /* list of active stems */
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
extern char gen_all_pat;

#ifdef ISCAS85_NETLIST_MODE

int lineindex[MAXLINE];
char namelist[MAXGATE][10];
char line[MAXSTRING];

/*      circin
        Reads an ISCAS85 benchmark circuit file
        and constructs internal data stuructures.
 
        The following information of the netlist is set in circin:
        1. index field : identification of gates (same as array index)
        2. fn        : gate type
        3. ninput    : number of fan-in lines
        4. inlis     : list of fan-in lines
        5. noutput   : number of fan-out lines
        6. outlis    : list of fan-out lines
        7. po        : set if the gate is a primary output
 
        Inputs: circuit input file (circuit)
        Outputs: data structures and
             nog: number of gate
             nopi: number of primary inputs
             nopout: number of primary outputs
 
        Note: Circuit format is the same as ISCAS85 benchmark circuits.
              The circuit description should be topologically sorted,
              All gates are re-numbered in sequential order from
              0 to nog-1.
*/
boolean circin(nog,nopi,nopout)
int *nog,*nopi,*nopout;
{

   register int i,j;
   int lineno,nfout,nfin;
   int currentline=0;
   int inputs[20];
   char name[10],gtype[5],fromline[10];
 
   *nog = 0;
   *nopi = 0;
   *nopout = 0;
 
   ALLOCATE(net, GATEPTR, MAXGATE);
   ALLOCATE(primaryin, int, MAXPI);
   ALLOCATE(primaryout, int, MAXPO);
   ALLOCATE(headlines, int, MAXPI);
 
   while(fscanf(circuit,"%80s",line) != EOF) {
      if(line[0] == '*') fgets(line,80,circuit); /* comment lines */
      else {
         /* read gate descriptions in the order of
            line_number, label, gtype, # of fanout, # of fanin */
         sscanf(line,"%5d",&lineno);
         fscanf(circuit,"%9s%5s",name,gtype);
         if(strcmp(gtype,"from") == 0)          /* fan-out branch */
            fscanf(circuit,"%9s",fromline);
         else
            fscanf(circuit,"%d%d",&nfout,&nfin);
         while(getc(circuit)!='\n');
 
         /* if gate type is from, search fanin lines
           and skip fanout lines from the gate list */
         if(strcmp(gtype,"from") == 0) {
            for(i=currentline;i>=0;i--)
                if(strcmp(fromline,namelist[i])==0) {
                   lineindex[lineno]=net[i]->index;

                   break;
                }
         }
 
         /* else, construct gate structutes */
         else {
            strcpy(namelist[currentline],name); /* store label */
            net[currentline]=(GATEPTR)malloc(sizeof(GATETYPE));
            lineindex[lineno]=currentline;
            net[currentline]->index = currentline;/* internal netlist */
            net[currentline]->gid = lineno;   /* actual netlist */
            net[currentline]->ninput = nfin;
            if(nfin != 0)
               net[currentline]->inlis=
               (GATEPTR *)malloc((unsigned)(sizeof(GATEPTR)*nfin));
            net[currentline]->noutput = nfout;
#ifdef LEARNFLG
            net[currentline]->plearn=NULL;
#endif
            if(nfout != 0) {
                net[currentline]->outlis=
                (GATEPTR *)malloc((unsigned)(sizeof(GATEPTR)*nfout));
                for(i=0;i<nfout;i++) net[currentline]->outlis[i]=NULL;
            }
            if(strcmp(gtype,"inpt") == 0) {
                net[currentline]->fn = PI;
                primaryin[*nopi] = currentline;
                (*nopi)++;
            }
            else {
                if(strcmp(gtype,"and") == 0) net[currentline]->fn=AND;
                else if(strcmp(gtype,"nand") == 0) net[currentline]->fn=NAND;
                else if(strcmp(gtype,"or")== 0) net[currentline]->fn=OR;
                else if(strcmp(gtype,"nor") == 0) net[currentline]->fn=NOR;

                else if(strcmp(gtype,"not") == 0) net[currentline]->fn=NAND;
                else if(strcmp(gtype,"xor") == 0) net[currentline]->fn=XOR;
                else if(strcmp(gtype,"buff") == 0) net[currentline]->fn=AND;
                else if(strcmp(gtype,"buf") == 0) net[currentline]->fn=AND;
                else { return(FALSE); }
 
                /* get intput list */
                for(i=0;i<nfin;i++) fscanf(circuit,"%6d",&inputs[i]);
                fgets(line,80,circuit);
 
                /* convert input index into internal and check fan-out list */
                for(i=0;i<nfin;i++) {
                   net[currentline]->inlis[i]=net[lineindex[inputs[i]]];
                   for(j=0;j<net[lineindex[inputs[i]]]->noutput;j++)
                      if(net[lineindex[inputs[i]]]->outlis[j]==NULL) {
                         net[lineindex[inputs[i]]]->outlis[j]
                            =net[currentline];
                         break;
                      }
                }
             }
             if(nfout == 0) {
                primaryout[*nopout] = currentline;
/*              net[currentline]->po=TRUE; */
                (*nopout)++;
             }
/*             else net[currentline]->po=FALSE; */
             currentline++;
          }
      }
   }    
   *nog = currentline;
 
   return(TRUE);
}

#endif
 
/*	set_cct_parameters
	Set several circuit parameters (ltype) of the net data structure.
	Computes the level (dpi) of each gate.
	Allocates space for event_listt and various objectives.
	Inputs	: data structures from circin +
		  nog: number of inputs
		  npi: numeber of primary inputs
	Outputs : ltype (line type among HEAD,BOUND and FREE)
		  dpi (distance from primary inputs)
		  maxdpi: maximum depth of the circuit
	Note	: should be called after circin
*/
#ifdef INCLUDE_HOPE
int set_cct_parameters(nog,npi)
int nog,npi;
{
   register int i,j,depth;
   int head_count=0;

   /* define line type (free,head,bound) and distance from input */
   if(gen_all_pat=='y') {
      for(i=0; i<nog; i++)
         net[i]->ltype = (net[i]->fn==PI) ? HEAD : BOUND;
      head_count=npi;
   } else for(i=0;i<nog;i++) {
      net[i]->ltype=LFREE;
      if(net[i]->fn != PI)
	 for(j=0;j<net[i]->ninput;j++) {
	    if(!is_free(net[i]->inlis[j])) net[i]->ltype=BOUND;
         }
      if(is_free(net[i]) && (net[i]->noutput!=1))
	 net[i]->ltype=HEAD;
      if(is_head(net[i])) head_count++;
      if(is_bound(net[i]))
	 for(j=0;j<net[i]->ninput;j++)
	    if(is_free(net[i]->inlis[j])) {
	       net[i]->inlis[j]->ltype=HEAD;
	       head_count++;
	    }
   }

   for(i=0;i<npi;i++) headlines[i]=(-1);
   j=head_count;
   for(i=nog-1;i>=0;i--) {
      if(is_head(net[i])) headlines[--j]=i;
   }

   /* alloacate space for sets (needed for the fan algorithm) */
   ALLOCATE(unjustified.list,GATEPTR,MAXOBJ);
   ALLOCATE(init_obj.list,GATEPTR,MAXOBJ);
   ALLOCATE(curr_obj.list,GATEPTR,MAXOBJ);
   ALLOCATE(fan_obj.list,GATEPTR,MAXOBJ);
   ALLOCATE(head_obj.list,GATEPTR,head_count);
   ALLOCATE(final_obj.list,GATEPTR,MAXOBJ);
   ALLOCATE(Dfrontier.list,GATEPTR,MAXOBJ);
   if(stack.list==NULL) { ALLOCATE(stack.list,GATEPTR,nog); }
   ALLOCATE(tree.list,TREETYPE,MAXTREE);

   return(maxlevel);
}

#else
int set_cct_parameters(nog,npi)
int nog,npi;
{
   register int i,j,depth;
   int maxdpi=0;
   int head_count=0;

   /* define line type (free,head,bound) and distance from input */
   for(i=0;i<nog;i++) {
      net[i]->ltype=LFREE;
      depth=(-1);
      if(net[i]->fn != PI)
	 for(j=0;j<net[i]->ninput;j++) {
	    if(!is_free(net[i]->inlis[j])) net[i]->ltype=BOUND;
	    depth=max(net[i]->inlis[j]->dpi,depth);
         }
      if(is_free(net[i]) && (net[i]->noutput!=1))
	 net[i]->ltype=HEAD;
      net[i]->dpi=depth+1;
      if(is_head(net[i])) head_count++;
      if(is_bound(net[i]))
	 for(j=0;j<net[i]->ninput;j++)
	    if(is_free(net[i]->inlis[j])) {
	       net[i]->inlis[j]->ltype=HEAD;
	       head_count++;
	    }
      maxdpi=max(net[i]->dpi,maxdpi);
   }

   /* allocate memory for event_listt and reset event counter */
   maxdpi++;
   event_list=
      (STACKPTR)malloc((unsigned)(sizeof(STACKTYPE)*maxdpi));
   depth_array=(int *)malloc((unsigned)(sizeof(int)*maxdpi));
   for(i=0;i<maxdpi;i++) event_list[i].last=0;

   for(i=0;i<npi;i++) headlines[i]=(-1);
   j=head_count;
   for(i=nog-1;i>=0;i--) {
      if(is_head(net[i])) headlines[--j]=i;
      /* count the number of gates in each depth */
      (event_list[net[i]->dpi].last)++;
   }

   /* allocate space for each event list */
   for(i=0;i<maxdpi;i++) {
      event_list[i].list=
	 (GATEPTR *)malloc((unsigned)(sizeof(GATEPTR)*event_list[i].last));
      depth_array[i]=event_list[i].last;
      clear(event_list[i]);
   }

   /* alloacate space for sets (needed for the fan algorithm) */
   ALLOCATE(unjustified.list,GATEPTR,MAXOBJ);
   ALLOCATE(init_obj.list,GATEPTR,MAXOBJ);
   ALLOCATE(curr_obj.list,GATEPTR,MAXOBJ);
   ALLOCATE(fan_obj.list,GATEPTR,MAXOBJ);
   ALLOCATE(head_obj.list,GATEPTR,head_count);
   ALLOCATE(final_obj.list,GATEPTR,MAXOBJ);
   ALLOCATE(Dfrontier.list,GATEPTR,MAXOBJ);
   if(stack.list==NULL) { ALLOCATE(stack.list,GATEPTR,nog); }
   ALLOCATE(tree.list,TREETYPE,MAXTREE);

   return(maxdpi);
}
#endif

/*	allocate_dynamic_buffers
	Allocates dynamic buffers needed for fsim.
*/
boolean allocate_dynamic_buffers(nog)
int nog;
{
   if((faulty_gates.list=
	(GATEPTR *)malloc((unsigned)(sizeof(GATEPTR)*nog)))==NULL) 
      return(FALSE);
   if((free_gates.list=
	(GATEPTR *)malloc((unsigned)(sizeof(GATEPTR)*nog)))==NULL) 
      return(FALSE);
   if((eval_gates.list=
	(GATEPTR *)malloc((unsigned)(sizeof(GATEPTR)*nog)))==NULL) 
      return(FALSE);
   if((active_stems.list=
	(GATEPTR *)malloc((unsigned)(sizeof(GATEPTR)*nog)))==NULL) 
      return(FALSE);
   if((dynamic_stack=
	(GATEPTR *)malloc((unsigned)(sizeof(GATEPTR)*nog)))==NULL) 
      return(FALSE);
   return(TRUE);
}

#define Dschedule_output(gut,cnt,Dfrontier,tempgate) \
	for(cnt=0;cnt<gut->noutput;cnt++) { \
	   tempgate=gut->outlis[cnt]; \
	   if(!tempgate->changed) { \
	      push(event_list[tempgate->dpi],tempgate); \
	      Dfrontier++; \
	      set(tempgate->changed); \
	}}

/*	set_dominator
	Finds the immediate dominators of all fanout stems.
	Inputs	: circuit structure +
		  nog (number of gates), maxdpi(maximum depth)
	Outputs	: dominators (u_path)
*/
int set_dominator(nog,maxdpi)
int nog,maxdpi;		/* depth of event list, number of output */
{
   register int i,j;
   register GATEPTR gut, g;
   GATEPTR Dominator;
   int gate_count;
   int ndominator=0;

   for(i=nog-1;i>=0;i--) {
      gut=net[i];
      if(gut->noutput<=1) gut->u_path=NULL;
      else {
         gate_count=0;
         Dschedule_output(gut,j,gate_count,g);
	 for(j=gut->dpi+1;j<maxdpi;j++)
	    while(!is_empty(event_list[j])) {
	       Dominator=pop(event_list[j]);
	       reset(Dominator->changed);
	       if(gate_count<=0) continue;
	       gate_count--;
	       if(gate_count==0) {
		  gut->u_path=(LINKPTR)malloc(sizeof(LINKTYPE));
	          gut->u_path->ngate=Dominator;
	          ndominator++;
		  break;
	       }
	       if(Dominator->noutput==0) {
		  gut->u_path=NULL;
		  gate_count=0;
	       }
	       else if(Dominator->noutput>1) {
		  if(Dominator->u_path==NULL) {
		     gut->u_path=NULL;
		     gate_count=0;
		  }
		  else {
		     g=Dominator->u_path->ngate;
		     if(!g->changed) {
			push(event_list[g->dpi],g);
			set(g->changed);
			gate_count++;
		     }
		  }
	       }
	       else if(!Dominator->outlis[0]->changed) {
		  g=Dominator->outlis[0];
		  push(event_list[g->dpi],g);
		  set(g->changed);
		  gate_count++;
	       }
           }
     }
   }
   return(ndominator);
}

/*	set_unique_path
	For every fanout stem which has a dominator,
	this routine finds the unique path and property of the dominator.
	Used in FAN.
	Should be called after setting dominators.
*/

#define setfreach(gate,number) gate->freach=number
#define is_reached(gate,number) gate->freach==number

void set_unique_path(nog,maxdpi)
int nog,maxdpi;		/* depth of event list, number of output */
{
   register int i,j;
   register GATEPTR gut,g;
   LINKPTR p;
   int count, k;

   for(i=nog-1;i>=0;i--) {
      gut=net[i];
      if(gut->u_path==NULL) continue;
      count=0;
      setfreach(gut,i);

      for(j=0;j<gut->noutput;j++) {
	 g=gut->outlis[j];
	 if(!g->changed) {
	    push(event_list[g->dpi],g);
	    set(g->changed);
	    count++;
	 }
      }
      for(j=gut->dpi+1;j<maxdpi;j++)
	 while(!is_empty(event_list[j])) {
	    gut=pop(event_list[j]);
	    reset(gut->changed);
	    setfreach(gut,i);
	    count--;
	    if(count==0) {
	       p=net[i]->u_path;
	       for(k=0;k<gut->ninput;k++) {
		  g=gut->inlis[k];
		  if(is_reached(g,i)) {
		     p->next=(LINKPTR)malloc(sizeof(LINKTYPE));
		     p=p->next;
		     p->ngate=g;
		     p->next=NULL;
		  }
	       }
	       break;
	    }
	    for(k=0;k<gut->noutput;k++) {
	       g=gut->outlis[k];
	       if(!g->changed) {
		  push(event_list[g->dpi],g);
		  set(g->changed);
		  count++;
	       }
	    }
	 }
   }
}

/*	setfanoutstem
	For fault simulation.
	Identifies fanout stems and builds fanout free region.
*/
void setfanoutstem(nog,stem,nstem)
int nog,nstem;
GATEPTR *stem;
{
   register int i,j;
   register GATEPTR p;

   j=0;
   for(i=0;i<nog;i++)
      if(net[i]->noutput != 1) stem[j++]=net[i];
   clear(stack);
   for(i=0;i<nstem;i++) {
      push(stack,stem[i]);
      while(!is_empty(stack)) {
	 p=pop(stack);
	 p->fos=stem[i]->index;
	 for(j=0;j<p->ninput;j++)
	    if(p->inlis[j]->noutput==1) push(stack,p->inlis[j]);
      }
   }
}

/*	gettime: Gets CPU time used by the program. */
void gettime(usertime,systemtime,total)
double *usertime;
double *systemtime;
double *total;
{
   struct tms timesbuffer;
   time_t totaltime;
   time_t utime;
   time_t stime;

   times(&timesbuffer);
   utime=timesbuffer.tms_utime;
   stime=timesbuffer.tms_stime;
   totaltime=timesbuffer.tms_utime+timesbuffer.tms_stime;/* In 60th seconds */
   *usertime=(double)utime/60.0;
   *systemtime=(double)stime/60.0;
   *total=(double)totaltime/60.0;
}

