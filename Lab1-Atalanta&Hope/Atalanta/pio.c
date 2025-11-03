
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

/*------------------------------------------------------------------
	filename:  pio.c
	This file contains all subroutines needed for input/output
	of atalanta and fsim results.
--------------------------------------------------------------------*/
#include <stdio.h>

#include "parameter.h" 
#include "define.h"    
#include "macro.h"

extern char cctmode;
extern GATEPTR *net;
extern int *primaryin,*primaryout,*headlines;
extern level BITMASK[BITSIZE];

#define chars_per_line 60
#define chars_per_column 50
#define number_of_spaces 5

/* macros for the bit operation of a computer word */
#define setbit(word,n) word&=BITMASK[n]
#define resetbit(word,n) word|=(~BITMASK[n])
#define checkbit(word,n) ((word&BITMASK[n])!=ALL0)
#define putbit(fp,word,n) if(checkbit(word,n)) putc('1',fp); else putc('0',fp)

/*	printinputs
	print nth bit test pattern of the circuit input
*/
void printinputs(fp,npi,nth_bit)
FILE *fp;
int npi,nth_bit;
{
    register int j;
    for(j=0;j<npi;j++)
       putbit(fp,net[j]->output1,nth_bit);
}

/*	printoutputs
	print nth bit output response of the circuit
*/
void printoutputs(fp,npo,nth_bit)
FILE *fp;
int npo,nth_bit;
{
    register int j;
    for(j=0;j<npo;j++)
       putbit(fp,net[primaryout[j]]->output1,nth_bit);
}

#define TEST_PER_LINE 13

boolean print_test_topic(fp,npi,npo,name)
FILE *fp;
int npi,npo;
char name[];
{
   register int i;
   register GATEPTR gut;

   fprintf(fp,"* Name of circuit:  %s\n",name);
   fprintf(fp,"* Primary inputs :\n  ");
   for(i=0;i<npi;i++) {
#ifdef ISCAS85_NETLIST_MODE
      if(cctmode==ISCAS89) fprintf(fp,"%s ",net[i]->symbol->symbol);
      else fprintf(fp,"%5d ",net[i]->gid);
#else
      fprintf(fp,"%s ",net[i]->symbol->symbol);
#endif
      if(((i+1) mod TEST_PER_LINE == 0) || (i==npi-1))
	 fprintf(fp,"\n  ");
   }
   fprintf(fp,"\n");
   fprintf(fp,"* Primary outputs:\n  ");
   for(i=0;i<npo;i++) {
#ifdef ISCAS85_NETLIST_MODE
      if(cctmode==ISCAS89) {
         gut=net[primaryout[i]];
         if(gut->fn==PO && gut->ninput==1) gut=gut->inlis[0];
         fprintf(fp,"%s ",gut->symbol->symbol);
      }
      else fprintf(fp,"%5d ",net[primaryout[i]]->gid);
#else
/*
      fprintf(fp,"%s ",net[primaryout[i]]->symbol->symbol);
*/
      gut=net[primaryout[i]];
      if(gut->fn==PO && gut->ninput==1) gut=gut->inlis[0];
      fprintf(fp,"%s ",gut->symbol->symbol);
#endif
      if(((i+1) mod TEST_PER_LINE == 0) || (i==npi-1))
	 fprintf(fp,"\n  ");
   }
   fprintf(fp,"\n\n* Test patterns and fault free responses:\n\n");
}

/*	printio
	prints nth bit test patterns and outputs of the circuit
*/
int printio(fp,npi,npo,nth_bit,start)
FILE *fp;
int npi,npo,nth_bit,start;
{
   fprintf(fp,"%4d: ",start);
   printinputs(fp,npi,nth_bit);
   fprintf(fp," ");
   printoutputs(fp,npo,nth_bit);
   fprintf(fp,"\n");
}

void print_log_topic(fp,name)
FILE *fp;
char name[];
{
   fprintf(fp,"* Log file for the circuit %s.\n",name);
   fprintf(fp,"* Number of faults detected by each test pattern:\n\n");
}

/*	pget_test
	Reads test input files and stores in parallel.
	Returns number of test patterns read.
	Returns 0 if EOF is encountered.
*/
int pget_test(fp,input,npi,nbit)
FILE *fp;
level input[];
int npi,nbit;
{
   register int i;
   register int c;
   int ntest;
   unsigned mask1=~(ALL1<<1);
   boolean valid=FALSE;

   i=0;
   for(ntest=0;ntest<nbit;ntest++) {
      while((c=getc(fp))!=EOF) {
         switch(c) {
	 case '*': while((c=getc(fp))!='\n') if(c == EOF) break; break;
	 case ':': valid=TRUE; break;
	 case '0': if(valid) input[i++]<<=1; break;
         case '1': if(valid) {input[i]<<=1; input[i++]|=mask1;} break;
	 }
         if(i==npi) {i=0; valid=FALSE; break;}
      }
      if(c==EOF) break;
   }
   if(i>0 && i<npi) return(0);
   return(ntest);
}

/*	printfault: prints a fault 	*/
char *fault2str[4]={"/0","/1","/0","/1"};
void printfault(fp,f,mode)
FILE *fp;
FAULTPTR f;
boolean mode;
{
   GATEPTR gut;

#ifdef ISCAS85_NETLIST_MODE
   if(cctmode==ISCAS89) {
      if(f->line >= 0) {
	 gut = f->gate->inlis[f->line];
	 fprintf(fp, "%s", gut->symbol->symbol);
         fprintf(fp, "->");
      }
      fprintf(fp,"%s %s",f->gate->symbol->symbol,fault2str[f->type]);
   } else {
      if(f->line<0)
         fprintf(fp,"Output line s-a-%d ",f->type);
      else fprintf(fp,"Input line %d s-a-%d ",f->line+1,f->type);
      fprintf(fp,"of gate %d ",f->gate->gid);
   }
#else
   if(f->line >= 0) {
      gut = f->gate->inlis[f->line];
      fprintf(fp, "%s", gut->symbol->symbol);
      fprintf(fp, "->");
   }
   fprintf(fp,"%s %s",f->gate->symbol->symbol,fault2str[f->type]);
#endif
   if(mode)
      switch(f->detected) {
         case DETECTED: fprintf(fp," detected"); break;
         case UNDETECTED: fprintf(fp," undetected"); break;
         case PROCESSED: fprintf(fp," aborted"); break;
         case REDUNDANT: fprintf(fp," redundant");
      }
   fprintf(fp,"\n");
}


/* The following subroutines are necessary for debugging or
   exteraction of net lists --- not used in normal mode */

#define logic_type(gut) \
switch(gut->fn) { \
case AND: if(gut->ninput==1)printf("buff");else printf("and "); break; \
case NAND: if(gut->ninput==1)printf("not ");else printf("nand"); break; \
case OR: if(gut->ninput==1)printf("buff");else printf("or  "); break; \
case NOR: if(gut->ninput==1)printf("not ");else printf("nor "); break; \
case XOR: if(gut->ninput==1)printf("buff");else printf("xor "); break; \
case PI: printf("input");}

void print_gate(gut)
register GATEPTR gut;
{
   register int i;

/*
   printf("%s: ",gut->symbol->symbol);
*/
   if(gut->fn==PI) 
      printf("input(%d)",gut->index);
   else {
      printf("%d = ",gut->index);
      logic_type(gut); 
      printf("(");
      for(i=0;i<gut->ninput;i++) 
         if(i==0) printf("%d",gut->inlis[i]->index);
         else printf(",%d",gut->inlis[i]->index);
      printf(")");
   }
   printf("\n");
}

void sprint_gate(gut)
register GATEPTR gut;
{
   register int i;

/*
   printf("%s: ",gut->symbol->symbol);
*/
   if(gut->fn==PI) 
      printf("input(%s)",gut->symbol->symbol);
   else {
      printf("%s = ",gut->symbol->symbol);
      logic_type(gut); 
      printf("(");
      for(i=0;i<gut->ninput;i++) 
         if(i==0) printf("%s",gut->inlis[i]->symbol->symbol);
         else printf(",%s",gut->inlis[i]->symbol->symbol);
      printf(")");
   }
   printf("\n");
}

void print_faultlist(fp,flist,no,mode)
FILE *fp;
FAULTPTR *flist; int no;
int mode;
{
   register int i;

   for(i=0; i<no; i++) {
      printfault(fp,flist[i],mode);
   }
}

/*
void print_output_cone(gut,maxdpi,mode)
register GATEPTR gut; int maxdpi;
char mode;
{
   register int i,j;

   push(event_list[gut->dpi],gut);
   set(gut->changed);
   for(i=gut->dpi;i<maxdpi;i++)
      while(!is_empty(event_list[i])) {
	 gut=pop(event_list[i]);
	 reset(gut->changed);
	 if(mode=='s') sprint_gate(gut);
	 else print_gate(gut);
	 for(j=0;j<gut->noutput;j++) {
	    if(!gut->outlis[j]->changed) {
	       push(event_list[gut->outlis[j]->dpi],gut->outlis[j]);
	       set(gut->outlis[j]->changed);
	    }
	 }
      }
}

void print_input_cone(gut,mode)
register GATEPTR gut;
char mode;
{
   register int i,j;

   push(event_list[gut->dpi],gut);
   set(gut->changed);
   for(i=gut->dpi;i>=0;i--)
      while(!is_empty(event_list[i])) {
	 gut=pop(event_list[i]);
	 reset(gut->changed);
	 if(mode=='s') sprint_gate(gut);
	 else print_gate(gut);
	 for(j=0;j<gut->ninput;j++) {
	    if(!gut->inlis[j]->changed) {
	       push(event_list[gut->inlis[j]->dpi],gut->inlis[j]);
	       set(gut->inlis[j]->changed);
	    }
	 }
      }
}
*/


/*----------------------------------------------------------------- 
	filename print.c
	This file contains all subroutines necessary to print out
	circuit structure, fault list and test patterns to the
	standard output. --- will be changed to report to a file.
-------------------------------------------------------------------*/

extern int nog,nopi,nopo,noff,maxlevel;
extern int *primaryin,*primaryout,*flip_flops;
extern GATEPTR *net;
extern level BITMASK[];
extern char *fn_to_string[],*level_to_string[],*fault_to_string[];
extern level parallel_to_level[][2];
extern FAULTPTR headfault;
extern int Group_Id;

#define printgatetype(file,type) fprintf(file,"%s",fn_to_string[type])
#define printfaulttype(file,type) fprintf(file,"%s",fault_to_string[type])
#define printlevel(file,type) fprintf(file,"%s",level_to_string[type])
#define aprintgate(file,gate) \
{ printgate(file,gate,'s'); fprintf(file," ; "); printgate(file,gate,'n'); }

/*------prints gate symbol or index--------------------------------*/
void printgatename(fp,gate,wmode)
FILE *fp; register GATEPTR gate; char wmode;
{
    if(wmode=='s') {
       if(gate->symbol==NULL) fprintf(fp,"TEMP%d",gate->index);
       else fprintf(fp,"%s",gate->symbol->symbol);
    } else fprintf(fp,"%d",gate->index);
}

/*------prints PI,PO,PPI or PPO gatenames--------------------------*/
void printionames(fp,array,n,head,wmode,iomode)
FILE *fp; int array[]; register int n;
register char wmode,iomode;
char *head;
{
    GATEPTR gut; int i;

    for(i=0;i<n;i++) {
       gut=net[array[i]];
       if(iomode=='i') if(gut->ninput>0) gut=gut->inlis[0];
       printgatename(fp,gut,wmode);
       fprintf(fp," ");
       if(((i+1) mod TEST_PER_LINE == 0) || (i==n-1)) {
	  fprintf(fp,"\n");
	  if(i<n-1) fprintf(fp,"%s",head);
       }
    }
} 

/*------print out gate structure in symbolic or neumeric notations---*/
void printgate(fp,gate,wmode)
FILE *fp;register GATEPTR gate;char wmode;
{
   register int i;

   if(gate->fn==PI) {
      printgatetype(fp,gate->fn);
      fprintf(fp,"(");
      printgatename(fp,gate,wmode);
      fprintf(fp,")");
   } else {
      printgatename(fp,gate,wmode);
      fprintf(fp," = ");
      if(gate->ninput==1)
	 if(gate->fn==AND || gate->fn==OR) fprintf(fp,"BUFF");
	 else if(gate->fn==NAND || gate->fn==NOR) fprintf(fp,"NOT");
	 else printgatetype(fp,gate->fn);
      else printgatetype(fp,gate->fn);
      putc('(',fp);
      for(i=0;i<gate->ninput;i++) {
	 printgatename(fp,gate->inlis[i],wmode);
	 if(i<gate->ninput-1) putc(',',fp);
      }
      putc(')',fp);
   }
}

/*------converts a parallel logic format to a single logic level------*/
level logiclevel(V0,V1,n)
register level V0,V1; register int n;
{
   V0=((V0 & BITMASK[n]) == ALL0) ? ZERO : ONE;
   V1=((V1 & BITMASK[n]) == ALL0) ? ZERO : ONE;
   return(parallel_to_level[V0][V1]);
}

/*------prints values of PIs,POs,PPIs or PPOs-------------------------
	if iomode=='i', prints input values
	else prints output values.
---------------------------------------------------------------------*/
void printiovalues(fp,array,n,iomode,gmode,bit)
FILE *fp; int array[]; int n; char iomode,gmode; int bit;
{
    register int j;
    register GATEPTR gut;

    for(j=0;j<n;j++) {
       gut=net[array[j]];
       if(iomode=='i') if(gut->ninput>0) gut=gut->inlis[0];
       if(gmode=='g' || gut->Gid!=Group_Id)
	  printlevel(fp,logiclevel(gut->GV[0],gut->GV[1],bit));
       else printlevel(fp,logiclevel(gut->FV[0],gut->FV[1],bit));
    }
}

/*------prints inputs and outputs of a given gate--------------------*/
void printgatevalues(fp,gut,n,gmode)
FILE *fp; register GATEPTR gut; char gmode;
{
   register int i;
   register GATEPTR g;

   if(gmode=='g'|| gut->Gid!=Group_Id)
      printlevel(fp,logiclevel(gut->GV[0],gut->GV[1],n));
   else printlevel(fp,logiclevel(gut->FV[0],gut->FV[1],n));
   fprintf(fp," = ");
   printgatetype(fp,gut->fn);
   fprintf(fp,"(");
   for(i=0;i<gut->ninput;i++) {
      g=gut->inlis[i];
      if(gmode=='g' || g->Gid!=Group_Id)
         printlevel(fp,logiclevel(g->GV[0],g->GV[1],n));
      else printlevel(fp,logiclevel(g->FV[0],g->FV[1],n));
      if(i<gut->ninput-1) putc(',',fp);
   }
   putc(')',fp);
}

/*------prints head lines of the log file----------------------------*/
/*
void print_log_topic(fp,name,wmode)
FILE *fp; char name[], wmode;
{
   fprintf(fp,"* Log files for test pattern generation.\n");
   fprintf(fp,"* name of the circuit: %s\n",name);
   fprintf(fp,"* primary inputs: ");
   printionames(fp,primaryin,nopi,"                  ",wmode,'o');
   fprintf(fp,"* pseudo-primary inputs: ");
   printionames(fp,flip_flops,noff,"                         ",wmode,'o');
   fprintf(fp,"* primary outputs: ");
   printionames(fp,primaryout,nopo,"                   ",wmode,'o');
   fprintf(fp,"* pseudo-primary outputs: ");
   printionames(fp,flip_flops,noff,"                          ",wmode,'i');
   fprintf(fp,"number of faults detected by each test pattern.\n\n");
}

void printfault(fp,f,wmode)
FILE *fp;
register FAULTPTR f;
char wmode;
{
   register GATEPTR gut;

   if(f->line>=0) {
      for(gut=f->gate->inlis[f->line];gut->symbol==NULL;gut=gut->inlis[1]);
      printgatename(fp,gut,wmode);
      fprintf(fp,"->");
   }
   printgatename(fp,f->gate,wmode);
   fprintf(fp," ");
   printfaulttype(fp,f->type);
}
*/

void printfaultlist(fp,wmode)
FILE *fp; char wmode;
{
   register FAULTPTR f;

   for(f=headfault->next;f!=NULL;f=f->next) {
      printfault(fp,f,wmode);
      fprintf(fp,"\n");
   }
}

#define TEST_PER_L 13

/*
void print_test_topic(fp,npi,npo,name)
FILE *fp;
int npi,npo;
char name[];
{
   int i;
   GATEPTR gut;

   fprintf(fp,"* Name of circuit: %s\n",name);
   fprintf(fp,"* Primary inputs :\n  ");
   for(i=0;i<npi;i++) {
      gut=net[primaryin[i]];
      printgatename(fp,gut,'s'); fprintf(fp," ");
      if(((i+1) mod TEST_PER_L == 0) || (i==npi-1))
	 fprintf(fp,"\n  ");
   }
   fprintf(fp,"\n");
   fprintf(fp,"* Primary outputs:\n  ");
   for(i=0;i<npo;i++) {
      gut=net[primaryout[i]];
      printgatename(fp,gut,'s'); fprintf(fp," ");
      if(((i+1) mod TEST_PER_L == 0) || (i==npi-1))
	 fprintf(fp,"\n  ");
   }
   fprintf(fp,"\n\n* Test patterns and fault free responses:\n\n");
}
*/

/*------print_net------------------------------------------------------
	prints the circuit structure
	if wmode=='a', prints in both symbolic and neumeric notations.
	if wmode=='s', prints in symbolic notations.
	else prints in neumeric notations.
-----------------------------------------------------------------------*/
void print_net(fp,name,wmode)
FILE *fp; char name[]; char wmode;
{
   register int i,j;
   int number_of_gates[MAXGTYPE],nonot=0;

   for(i=0;i<MAXGTYPE;i++) number_of_gates[i]=0;
   for(i=0;i<nog;i++) 
      if(net[i]->ninput==1) 
	 if(net[i]->fn==AND || net[i]->fn==OR) number_of_gates[BUFF]++;
         else if(net[i]->fn==NAND || net[i]->fn==NOR) nonot++;
         else number_of_gates[net[i]->fn]++;
      else number_of_gates[net[i]->fn]++;

   fprintf(fp,"# %s\n",name);		/* name */
   fprintf(fp,"# %d inputs\n",nopi);
   fprintf(fp,"# %d outputs\n",nopo);
   fprintf(fp,"# %d D-type flipflops\n",noff);
   fprintf(fp,"# %d inverters\n",nonot);
   fprintf(fp,"# %d gates",nog-nopi-noff-nonot);
   j=0;
   for(i=0;i<MAXGTYPE;i++)
      if(number_of_gates[i]>0) 
         if(j==0) {
	    fprintf(fp," (%d %ss",number_of_gates[i],fn_to_string[i]);
	    j++;
	 } else fprintf(fp," + %d %ss",number_of_gates[i],fn_to_string[i]);
   fprintf(fp,")\n\n");

   for(i=0;i<nopi;i++)
      if(wmode=='a') {
	 printgate(fp,net[primaryin[i]],'s'); fprintf(fp," ; ");
	 printgate(fp,net[primaryin[i]],'n'); putc(CR,fp);
      } else { printgate(fp,net[primaryin[i]],wmode); putc(CR,fp); }
   putc(CR,fp);
   for(i=0;i<nopo;i++) {
      fprintf(fp,"OUTPUT(");
      if(wmode=='a') {
	 printgatename(fp,net[primaryout[i]],'s');
	 fprintf(fp,") ; OUTPUT(");
	 printgatename(fp,net[primaryout[i]],'n');
      } else printgatename(fp,net[primaryout[i]],wmode);
      fprintf(fp,")\n");
   }
   putc(CR,fp);

   for(i=0;i<nog;i++) if(net[i]->fn!=PI) {
      if(wmode=='a') {
	 printgate(fp,net[i],'s'); fprintf(fp," ; ");
	 printgate(fp,net[i],'n');
      } else printgate(fp,net[i],wmode);
      putc(CR,fp);
   }
}

/*------count_events-----------------------------------------------------
	Counts numbers of next events (PPIs which are different from
	fault free circuits).
	Input:	f; fault
	Output: returns the number of events
------------------------------------------------------------------------*/
int count_events(f)
register FAULTPTR f;
{
   int i=0;
   EVENTPTR e;

   for(e=f->event;e!=NULL;e=e->next) i++;
   return(i);
}

void print_event(file,f,mode)
FILE *file; FAULTPTR f; char mode;
{
   EVENTPTR e;

   if(count_events(f)>0)
      for(e=f->event;e!=NULL;e=e->next) {
	 printgate(file,net[e->node],mode);
	 fprintf(file,":");
	 switch(e->value) {
	 case 0: fprintf(file,"x  "); break;
	 case 1: fprintf(file,"0  "); break;
	 case 2: fprintf(file,"1  "); break;
	 }
      }
   fprintf(file,"\n");
}

void print_event_tree(file,event,mode)
FILE *file; EVENTPTR event; char mode;
{
   EVENTPTR e;

   if(event!=NULL)
      for(e=event;e!=NULL;e=e->next) {
	 printgatename(file,net[e->node],mode);
	 fprintf(file,"=");
	 switch(e->value) {
	 case 0: fprintf(file,"x "); break;
	 case 1: fprintf(file,"0 "); break;
	 case 2: fprintf(file,"1 "); break;
	 }
      }
   fprintf(file,"\n");
}

void DFSWalk(child,iomode)
GATEPTR child; char iomode;
{
   int i;

   set(child->changed);

   /* Go into children */
   if(iomode=='i') for(i=0;i<child->noutput;i++) {
      if(!child->outlis[i]->changed) DFSWalk(child->outlis[i],iomode); }
   else for(i=0;i<child->ninput;i++) {
      if(!child->inlis[i]->changed) DFSWalk(child->inlis[i],iomode); }
}
      
int FindUnobservableGates(fp,wflag,iomode)
FILE *fp; status wflag,iomode;
{
   register int i,count=0;

   for(i=0;i<nog;i++) reset(net[i]->changed);
   if(iomode=='i') for(i=0;i<nopi;i++) DFSWalk(net[primaryin[i]],iomode);
   else for(i=0;i<nopo;i++) DFSWalk(net[primaryout[i]],iomode);

   for(i=0;i<nog;i++) if(!net[i]->changed) count++;

   if(fp!=NULL && count>0) {
      if(iomode=='i') fprintf(fp,"Number of gates which are unreachable from PI = %d\n",count);
      else fprintf(fp,"Number of gates which are unreachable to any PO = %d\n",count);
      for(i=0; i<nog; i++)
	 if(net[i]->changed==0 && net[i]->fn==DFF) 
	    { printgate(fp,net[i],wflag); fprintf(fp,"\n"); }
   }

   for(i=0;i<nog;i++) reset(net[i]->changed);

   return(count);
}
