
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

/*-----------------------------------------------------------------
	file name: define_fault_list.c
	This file constructs fault list after collapsing equivalent
	faults.
-------------------------------------------------------------------*/
#include <stdio.h>

#include "parameter.h" 
#include "define.h"    
#include "macro.h"

extern GATEPTR *net;
extern STACKTYPE stack;
extern struct FAULT **faultlist;

extern char  rptmode;
extern HASHPTR symbol_tbl[];
extern HASHPTR FindHash();
extern void fatalerror();

/*	set_all_fault_list
	Sets up the fault list data structure.
	Equivalent faults are collapsed.
*/
int set_all_fault_list(nog,no_stem,stem)
int nog,no_stem;
GATEPTR *stem;
{
   register GATEPTR g;
   register FAULTPTR p;
   register int i,j;
   FAULTPTR current;
   fault_type f;
   int nfault,n,nof;
   int	*test, size;
   FAULTTYPE *curr;

   test = (int *)malloc(sizeof(int));
   size = sizeof(FAULTTYPE); 
   nfault=0;
   curr=(FAULTTYPE *)calloc(1,sizeof(FAULTTYPE));
   current=(FAULTPTR)malloc(sizeof(FAULTTYPE));
   current->next=NULL;

   for(i=0;i<nog;i++) {

      /* input line faults */
      g=net[i];
      g->pfault=current;
      g->nfault=0;

      /* if the input of the gate has more than one fanouts, 
	 add a s-a-1 for each AND/NAND,
	     a s-a-0 for each OR/NOR and
	     a s-a-0 and s-a-1 for other gates. */

      if(g->ninput>1) {
	 f=(g->fn==AND||g->fn==NAND) ? SA1 : SA0;
	 for(j=0;j<g->ninput;j++) {
	    if(g->inlis[j]->noutput>1) {
	       p=(FAULTPTR)malloc(sizeof(FAULTTYPE));
	       p->gate=g;
	       p->type=f;
	       p->line=j;
	       p->next=NULL;
	       nfault++; g->nfault++;
	       current->next=p;
	       if(current==g->pfault) p->previous=p;
	       else p->previous=current;
	       current=p;
	       /* case of high level gates */
	       if(g->fn>PI) {
	          ALLOCATE(p,FAULTTYPE,1);
	          p->gate=g;
	          p->type= (f==SA1) ? SA0 : SA1;
	          p->line=j;
	          p->next=NULL;
	          nfault++; g->nfault++;
	          current->next=p;
	          if(current==g->pfault) p->previous=p;
	          else p->previous=current;
	          current=p;
	       }
	    }
         }
      }

      /* output fault assignment:
	 add s-a-1 and s-a-0 faults for each fanout stem or
	 primary output. */
      if((g->noutput==1) && (g->outlis[0]->ninput>1 ||
			     g->outlis[0]->fn==PO) ) {
	 f=(g->outlis[0]->fn==OR||g->outlis[0]->fn==NOR) ? 
	   SA0 : SA1;
	 ALLOCATE(p,FAULTTYPE,1);
	 p->gate=g;
	 p->type=f;
	 p->line=OUTFAULT;
	 p->next=NULL;
	 nfault++; g->nfault++;
	 current->next=p;
	 if(current==g->pfault) p->previous=p;
	 else p->previous=current;
	 current=p;
	 /* case of high level gates */
	 if(g->outlis[0]->fn>PI) {
	    p=(FAULTPTR)malloc(sizeof(FAULTTYPE));
	    p->gate=g;
	    p->type=(f==SA1) ? SA0 : SA1;
	    p->line=OUTFAULT;
	    p->next=NULL;
	    nfault++; g->nfault++;
	    current->next=p;
	    if(current==g->pfault) p->previous=p;
	    else p->previous=current;
	    current=p;
         }
      }
      else if(g->noutput>1) {
	 p=(FAULTPTR)malloc(sizeof(FAULTTYPE));
	 p->gate=g;
	 p->type=SA1;
	 p->line=OUTFAULT;
	 p->next=NULL;
	 nfault++;
	 g->nfault++;
	 current->next=p;
	 if(current==g->pfault) p->previous=p;
	 else p->previous=current;
	 current=p;
	 p=(FAULTPTR)malloc(sizeof(FAULTTYPE));
	 p->gate=g;
	 p->type=SA0;
	 p->line=OUTFAULT;
	 p->next=NULL;
	 nfault++; g->nfault++;
	 current->next=p;
	 if(current==g->pfault) p->previous=p;
	 else p->previous=current;
	 current=p;
      }
      else if(g->fn==PO && g->inlis[0]->noutput>1) {
	 p=(FAULTPTR)malloc(sizeof(FAULTTYPE));
	 p->gate=g;
	 p->type=SA1;
	 p->line=0;
	 p->next=NULL;
	 nfault++; g->nfault++;
	 current->next=p;
	 if(current==g->pfault) p->previous=p;
	 else p->previous=current;
	 current=p;
	 ALLOCATE(p,FAULTTYPE,1);
	 p->gate=g;
	 p->type= SA0;
	 p->line=0;
	 p->next=NULL;
	 nfault++; g->nfault++;
	 current->next=p;
	 if(current==g->pfault) p->previous=p;
	 else p->previous=current;
	 current=p;
      }
         
      current=g->pfault;
      if(g->pfault->next==NULL) g->pfault=NULL;
      else g->pfault=current->next;
      current->next=NULL;
   }	/* end for */

   free((char *)current);

   /* create the fault_list and
      enumerate faults in each fanout free region */
   faultlist=(FAULTPTR *)malloc((unsigned)(sizeof(FAULTPTR)*nfault));
   clear(stack);
   nof=0;
   for(i=no_stem-1;i>=0;i--) {
      push(stack,stem[i]);
      n=1;
      while(!is_empty(stack)) {
	 g=pop(stack);
	 for(p=g->pfault;p!=NULL;p=p->next) 
	    { faultlist[nof++]=p; n++; }
	 for(j=0;j<g->ninput;j++)
	    if(g->inlis[j]->noutput==1) push(stack,g->inlis[j]);
      }
      stem[i]->dfault=(FAULTPTR *)malloc((unsigned)(n*sizeof(FAULTPTR)));
   }

   if(nfault==nof) return(nfault);
   else return(-1);
}

/*	add_fault
	Add a fault to the linked list of each gate.
*/
void add_fault(f)
FAULTPTR f;
{
   GATEPTR gut; FAULTPTR p;

   gut=f->gate;
   if(gut->pfault==NULL) {
      gut->pfault=f;
      f->previous=f;
      gut->nfault=1;
   }
   else {
      p=gut->pfault;
      while(p->next!=NULL) p=p->next;
      p->next=f;
      f->previous=p;
      gut->nfault++;
   }
   f->next=NULL;
}

/*	restore_detected_fault_list
	Restores the fault list for test compaction.
	Does not restore redundant faults.
*/
int restore_detected_fault_list(nof)
int nof;
{
   register FAULTPTR f;
   register int i,n;

   n=0;
   for(i=0;i<nof;i++) {
      f=faultlist[i];
      if(f->detected==DETECTED) {
	 f->detected=UNDETECTED;
	 add_fault(f);
	 n++;
      }
   }
   return(n);
}

/*	check_redundant_faults
	Identifies redundant faults in which more than two inputs of
	a gate are connected to one gate simultaneously and deletes
	the faults from the fault list.

	Input: nog, the number of gates of the circuit
	Output: number of identified redundant faults
	Note: changed flags of all gates should be reset to 0
	      prior to call this function.
*/

/* macro to delete a fault */
#define delete_fault(fal) \
if(fal->previous==fal) { \
   fal->gate->pfault=fal->next; \
   if(fal->next!=NULL) fal->next->previous=fal->next; \
} else { \
   fal->previous->next=fal->next; \
   if(fal->next!=NULL) fal->next->previous=fal->previous; \
}

int check_redundant_faults(nog)
int nog;
{
   register int i, j;
   int n;
   register GATEPTR gut;
   FAULTPTR f;

   n=0;
   for(i=0;i<nog;i++)
      if(net[i]->noutput>1) {
	 gut=net[i];
	 for(j=0;j<gut->noutput;j++) (gut->outlis[j]->changed)++;
	 for(j=0;j<gut->noutput;j++) {
	    if(gut->outlis[j]->changed>1)
	       for(f=gut->outlis[j]->pfault;f!=NULL;f=f->next)
		  if(f->line>=0)
		     if(f->gate->inlis[f->line]==gut) {
			f->detected=REDUNDANT;
			if(--f->gate->nfault>0) {delete_fault(f);}
			n++;
		     }
	    reset(gut->outlis[j]->changed);
	 }
      }
   return(n);
}


/*******************************************************************
The following routines are used to read fault directory.
The file format is the same as that of ISCAS89 fault list file.
**********************************************************************/

#define is_white_space(c) (c==' ' || c=='-' || c=='\t' || c=='\n')
#define is_head_symbol(c) (c=='/' || c=='>')
#define is_valid(c) ((c>='0' && c<='9') || \
		     (c>='A' && c<='Z') || \
		     (c>='a' && c<='z') || \
		     (c=='[' || c==']') || \
		     (c=='_'))

/*------getfaultsymbol-------------------------------------------------
	reads next symbol from the given fault file
	inputs : file	the name of input file
	outputs: s	symbol string output
        returns head character of s unless EOF is encountered.
-------------------------------------------------------------------*/
#define	EOS	'\0'

char getfaultsymbol(file,s)
FILE *file; char s[];
{
   char c;
   int n=0;
   status valid=FALSE;

   while((c=getc(file))!=EOF) {
      if(is_white_space(c)) { if(valid) break; else continue; }
      if(is_head_symbol(c)) { s[n++]=c; continue; }
      if(is_valid(c)) { s[n++]=c; set(valid); }
      else fatalerror(FAULTERROR);
   }
   s[n]=EOS;
   if(c==EOF) return(c); else return(s[0]);
}


/*------readfaults------------------------------------------------
	reads fault list and constructs fault list data structure
	inputs: file	fault directory file
	outputs: fault list
------------------------------------------------------------------*/
int readfaults(file,nog,no_stem,stem)
FILE *file; int nog,no_stem; GATEPTR *stem;
{
   GATEPTR gut;
   FAULTPTR f;
   int from,to,line,type;
   HASHPTR h;
   int i, j;
   char c;
   char s[MAXSTRING];
   int nfault, n, nof;

   nfault=0;
   for(i=0; i<nog; i++) {
      gut=net[i];
      gut->pfault=(FAULTPTR)NULL;
      gut->nfault=0;
   }

   while(getfaultsymbol(file,s)!=EOF) {
      if(is_valid(s[0])) {
	 if((h=FindHash(symbol_tbl,HASHSIZE,s,0))==NULL) {
	    fprintf(stderr,"Error in fault file:");
	    fprintf(stderr,"%s is not defined\n",s);
	    fatalerror(FAULTERROR);
	 }
	 if((to=h->pnode->index) < 0) fatalerror(FAULTERROR);
	 gut=net[to];
	 line=(-1);
      } else if(s[0]=='>') {
	 from=to;
	 if((h=FindHash(symbol_tbl,HASHSIZE,&s[1],0))==NULL) {
	    fprintf(stderr,"Error in fault file:");
	    fprintf(stderr,"%s is not defined\n",s);
	    fatalerror(FAULTERROR);
	 }
	 if((to=h->pnode->index)<0) fatalerror(FAULTERROR);
	 gut=net[to];
	 for(i=0;i<gut->ninput;i++)
	    if(gut->inlis[i]->index==from) { line=i; break; }
      } else if(s[0]=='/') {
	 if(s[1]=='1') type=SA1; else type=SA0;
	 if(line >= 0)
	    type = (type==SA1) ? SA1 : SA0;

	 ALLOCATE(f,FAULTTYPE,1);
	 f->gate=gut;
	 f->line=line;
	 f->type=type;
	 f->previous=f;
	 if((f->next=gut->pfault) != NULL) f->next->previous=f;
	 gut->pfault=f;
         nfault++;
         gut->nfault++;
/*       while((c=getc(file)) != '\n') if(c==EOF) break; */
      } else fatalerror(FAULTERROR);
   }

   /* create the fault_list and
      enumerate faults in each fanout free region */
   faultlist=(FAULTPTR *)malloc((unsigned)(sizeof(FAULTPTR)*nfault));
   nof=0;
   clear(stack);
   for(i=no_stem-1;i>=0;i--) {
      push(stack,stem[i]);
      n=1;
      while(!is_empty(stack)) {
         gut=pop(stack);
         for(f=gut->pfault;f!=NULL;f=f->next)
            { faultlist[nof++]=f; n++; }
         for(j=0;j<gut->ninput;j++)
            if(gut->inlis[j]->noutput==1) push(stack,gut->inlis[j]);
      }
      stem[i]->dfault=(FAULTPTR *)malloc((unsigned)(n*sizeof(FAULTPTR)));
   }
 
   if(nfault==nof) return(nfault);
   else return(-1);
}

#ifdef INCLUDE_HOPE

/*----------------------------------------------------------------- 
	The following routines creates the fault list for HOPE
-------------------------------------------------------------------*/
extern int nog,nopi,nopo,noff,maxlevel,nof;
extern int *primaryin,*primaryout,*flip_flops;
extern GATEPTR *net;
extern STACKTYPE stack1,stack2,*event_list;
extern FAULTPTR headfault,currentfault,tailfault,*faultlist;
extern HASHPTR symbol_tbl[];
extern HASHPTR FindHash();
extern void fatalerror();

FAULTPTR evenhead, eventail, oddhead, oddtail;
int parity_of_gate[MAXGTYPE]={0,1,0,1,0,0,0,0,0,0,1,};
int inverseparity[2][2]={{0,1},{1,0}};

/*------init_fault_list--------------------------------------------
	initializes fault list including headfault,tailfault
	headfault indicates one dummy fault
-------------------------------------------------------------------*/
void init_fault_list()
{
   ALLOCATE(headfault,FAULTTYPE,1);
   headfault->gate=NULL;
   headfault->next=NULL;
   headfault->event=NULL;
   evenhead=eventail=oddhead=oddtail=NULL;
   tailfault=headfault;
}

/*------insert_fault------------------------------------------------
	inserts a fault at the end of the fault list
	used for fault ordering. Parity of each fault is
	checked and stored in even and odd fault list.
	inputs: gut; faulty gate
		line; faulty line, if (-1), output fault
		type; fault type
	outputs: evenhead,eventail,oddhead,oddtail
-------------------------------------------------------------------*/
void insert_fault(gut,line,type)
GATEPTR gut; int line; fault_type type;
{
   int parity;
   FAULTPTR f;

   parity = (gut->changed>=2) ? gut->changed-2 : gut->changed;
   if(line<0) parity = inverseparity[parity_of_gate[gut->fn]][parity];

   ALLOCATE(f,FAULTTYPE,1);
   f->gate=gut;
   f->line=line;
   f->type=type;
   f->next=NULL;
   f->event=NULL;
   f->npot=0;

   nof++;

   if((parity==0 && type==SA0) || (parity==1 && type==SA1))
      if(eventail==NULL) evenhead=eventail=f;
      else { eventail->next=f; eventail=f; }
   else if(oddtail==NULL) oddhead=oddtail=f;
      else { oddtail->next=f; oddtail=f; }
}

/*------default_line_fault-----------------------------------------
	defines default stuck-at faults for the given line
	inputs: gut; gate under consideration
		line; faulty line of the gate, if (-1), output fault
	outputs: none
-------------------------------------------------------------------*/
void default_line_fault(gut,line)
GATEPTR gut; int line;
{
   GATEPTR from,to;

   if(line<0) {			/* output line fault */
      if(gut->fn==DUMMY || gut->fn==PO) return;
      if(gut->noutput!=1) {
	 insert_fault(gut,OUTFAULT,SA0);
	 insert_fault(gut,OUTFAULT,SA1);
      } else {
	 to=gut->outlis[0];
         if(to->fn==DUMMY) to=to->outlis[0];
	 switch(to->fn) {
	 case AND: case NAND:
	    if(to->ninput>1) insert_fault(gut,OUTFAULT,SA1);
	    break;
	 case OR: case NOR:
	    if(to->ninput>1) insert_fault(gut,OUTFAULT,SA0);
	    break;
	 case XOR: case XNOR: case DFF: case PO:
	    insert_fault(gut,OUTFAULT,SA0);
	    insert_fault(gut,OUTFAULT,SA1);
	    break;
	 default: break;	/* dummy, not, buff */
         }
      }
   } else { /* input line fault */
      from = gut->inlis[line];
      if(from->fn==DUMMY || from->fn==PO) from=from->inlis[0];
      if(from->noutput>1) switch(gut->fn) {
	 case AND: case NAND: 
	    if(gut->ninput>1) insert_fault(gut,line,SA1);
	    break;
         case OR: case NOR:
	    if(gut->ninput>1) insert_fault(gut,line,SA0);
	    break;
	 case XOR: case XNOR: case DFF: case PO:
	    insert_fault(gut,line,SA0);
	    insert_fault(gut,line,SA1);
	    break;
         default: break;	/* dummy, not, buffer */
      }
   }
}

#define setparity(gut,par) \
gut->changed=inverseparity[parity_of_gate[gut->fn]][par]
#define mark(gut) gut->changed+=2
#define is_not_marked(gut) gut->changed<2
#define is_stem(gut) \
((gut->noutput != 1) || (gut->outlis[0]->fn==DFF))

/*------ Sets fault list for the given FFRs ------*/
void FFR_Fault(gut)
GATEPTR gut;
{
   register GATEPTR temp;
   register int ix;

   clear(stack1);
   evenhead=eventail=oddhead=oddtail=NULL;

   push(stack1,gut);
   while(!is_empty(stack1)) {
      gut=pop(stack1);
      default_line_fault(gut,OUTFAULT);
      for(ix=0; ix<gut->ninput; ix++) {
         temp=gut->inlis[ix];
         if(is_stem(temp)) default_line_fault(gut,ix);
         else push(stack1,temp);
      }
   }

   if(eventail==NULL) { evenhead=oddhead; eventail=oddtail; }
   else { eventail->next=oddhead; }
   if((eventail=(oddtail==NULL)?eventail:oddtail) != NULL) {
      tailfault->next=evenhead;
      tailfault=eventail;
   }
}

/*------DFS_po--------------------------------------------------------
	Subroutine of DFS search from primary outputs
---------------------------------------------------------------------*/
void DFS_po(parent,child)
GATEPTR parent,child; 
{
   int i;

   /* preWORK */
   setparity(child,(parent==NULL?0:parent->changed-2));
   mark(child);

   if(is_stem(child)) FFR_Fault(child);

   /* Go into children */
   for(i=0;i<child->ninput;i++) {
      /* preWORK for input lines */
      if(is_not_marked(child->inlis[i]))
	 DFS_po(child,child->inlis[i]);
   }
}

/*------DFS_faults----------------------------------------------------
	defines fault list in the order of DFS from primary outputs
	use recursive version DFS routines.
	main of DFS_po.
---------------------------------------------------------------------*/
void FWD_faults()
{

   register int i;
   register GATEPTR gut;

   for(i=0;i<nog;i++) reset(net[i]->changed);

   init_fault_list();

   /* Primary Outputs */
   for(i=0;i<nopo;i++) {
      gut=net[primaryout[i]];
      DFS_po((GATEPTR)NULL,gut);
   }

   /* count faults and copy */
   nof=0;
   currentfault=headfault;
   while(currentfault->next!=NULL) { 
      nof++;
      currentfault=currentfault->next;
   }

   ALLOCATE(faultlist,FAULTPTR,nof);
   i=0;
   currentfault=headfault;

   while(currentfault->next!=NULL) {
      faultlist[i++]=currentfault->next;
      currentfault=currentfault->next;
   }
   tailfault=faultlist[nof-1];
}

/*------readfaults_hope-------------------------------------------
	reads fault list and constructs fault list data structure
	inputs: file	fault directory file
	outputs: fault list
------------------------------------------------------------------*/
void readfaults_hope(file)
FILE *file;
{
   GATEPTR gut;
   FAULTPTR f;
   int from,to,line,type;
   HASHPTR h;
   int i;
   char s[MAXSTRING];

   init_fault_list();

   while(getfaultsymbol(file,s)!=EOF) {
      if(is_valid(s[0])) {
	 if((h=FindHash(symbol_tbl,HASHSIZE,s,0))==NULL) {
	    fprintf(stderr,"Error in fault file:");
	    fprintf(stderr,"%s is not defined\n",s);
	    fatalerror(FAULTERROR);
	 }
	 if((to=h->pnode->index)<0) fatalerror(FAULTERROR);
	 gut=net[to];
	 line=OUTFAULT;
      } else if(s[0]=='>') {
	 from=to;
	 if((h=FindHash(symbol_tbl,HASHSIZE,&s[1],0))==NULL) {
	    fprintf(stderr,"Error in fault file:");
	    fprintf(stderr,"%s is not defined\n",s);
	    fatalerror(FAULTERROR);
	 }
	 if((to=h->pnode->index)<0) fatalerror(FAULTERROR);
	 gut=net[to];
	 for(i=0;i<gut->ninput;i++)
	    if(gut->inlis[i]->index==from) { line=i; break; }
      } else if(s[0]=='/') {
	 if(s[1]=='1') type=SA1; else type=SA0;
	 ALLOCATE(f,FAULTTYPE,1);
	 f->gate=gut;
	 f->line=line;
	 f->type=type;
	 f->event=NULL;
	 f->next=headfault->next;
	 headfault->next=f;
      } else fatalerror(FAULTERROR);
   }

   /* count faults and copy */
   nof=0;
   currentfault=headfault;
   while(currentfault->next!=NULL)
      { nof++; currentfault=currentfault->next; }

   ALLOCATE(faultlist,FAULTPTR,nof);
   i=0;
   currentfault=headfault;
   while(currentfault->next!=NULL) {
      faultlist[i++]=currentfault->next;
      currentfault=currentfault->next;
   }
}

/*	restore_hope_fault_list
	Restores the fault list for test compaction.
	Does not restore redundant faults.
*/
extern EVENTPTR head, tail;

int restore_hope_fault_list(nof)
int nof;
{
   register FAULTPTR f,papa;
   register int i,n;
   EVENTPTR e1;

   n=0;
   papa=headfault;
   for(i=0;i<nof;i++) {
      f=faultlist[i];
      if(f->detected==DETECTED) {
	 f->detected=UNDETECTED;
	 papa->next=f;
	 papa=f;
	 n++;
      }
      if(f->event != (EVENTPTR)NULL) {
         tail->next=f->event;
	 while(tail->next!=(EVENTPTR)NULL) tail=tail->next;
         f->event=(EVENTPTR)NULL;
      }
   }
   papa->next=(FAULTPTR)NULL;
   tailfault=papa;
   return(n);
}

#endif
