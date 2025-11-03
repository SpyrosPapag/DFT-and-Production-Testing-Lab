
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

           Major change in log file format, H. K. Lee, 6/30/1997
 
***********************************************************************/

/*---------------------------------------------------------------------
	print.c
	prints head lines of atalanta and
	test pattern generation results.
----------------------------------------------------------------------*/
#include <stdio.h>

#include "parameter.h" 
#include "define.h"    
#include "macro.h"

extern char rptmode;
extern char compact;
extern int randomlimit, iseed,maxcompact, msize;
extern struct FAULT **faultlist;

extern void printfault();
int print_undetected_faults();

char *title=
"******   SUMMARY OF TEST PATTERN GENERATION RESULTS   ******";

/*------print_atpg_head---------------------------------------*/
void print_atpg_head(fp)
FILE *fp;
{
   fprintf(fp,"*********************************************************\n");
   fprintf(fp,"*                                                       *\n");
   fprintf(fp,"*          Welcome to atalanta (version 2.0)            *\n");
   fprintf(fp,"*                                                       *\n");
   fprintf(fp,"*                 Dong S. Ha (ha@vt.edu)                *\n");
   fprintf(fp,"*      Web: http://www.visc.vt.edu/people/ha            *\n");
   fprintf(fp,"*   Virginia Polytechnic Institute & State University   *\n");
   fprintf(fp,"*                                                       *\n");
   fprintf(fp,"*********************************************************\n");
   fprintf(fp,"\n");
}


void print_atpg_result(fp,name,ng,npi,npo,mlev,mback,mback1,ph2,
	nt2,nt3,nof,nd,nred,tback,nshuf,inittime,simtime,fantime,runtime,mode,memory)
FILE *fp;
char *name;	/* circuit name */
int ng;		/* number of gate */
int npi;	/* number of primary inputs */
int npo;	/* number of primary outputs */
int mlev;	/* max level */
int mback;	/* max backtrack limit for phase1*/
int mback1;	/* max backtrack limit for phase2*/
int ph2;	/* phase 2 used */
int nt2;	/* number of test patterns before test compaction */
int nt3;	/* number of test patterns after test compaction */
int nof;	/* number of total faults */
int nd;		/* number of detected faults */
int nred;	/* number of redundant faults */
int tback;	/* number of backtracks (total) */
int nshuf;	/* number of shuffles*/
float inittime,simtime,fantime,runtime;
char mode;	/* If 'y', prints redundant and undetected faults */
int memory;	/* memory used*/
{

   int i;
/* int j; */
   FAULTPTR f;

   fprintf(fp,"%s\n",title);
   fprintf(fp,"1. Circuit structure\n");
   fprintf(fp,"   Name of the circuit                       : %s\n",name);
   fprintf(fp,"   Number of primary inputs                  : %d\n",npi);
   fprintf(fp,"   Number of primary outputs                 : %d\n",npo);
   fprintf(fp,"   Number of gates                           : %d\n",ng-npi-npo);
   fprintf(fp,"   Level of the circuit                      : %d\n",mlev-3);
   fprintf(fp,"\n");
   fprintf(fp,"2. ATPG parameters\n");
   fprintf(fp,"   Test pattern generation mode              : ");
   if(rptmode=='n') fprintf(fp,"DTPG + TC\n");
   else if(rptmode=='y') fprintf(fp,"RPT + DTPG + TC\n");
   if(rptmode=='y') 
   fprintf(fp,"   Limit of random patterns (packets)        : %d\n",randomlimit);
   if(!ph2) {
   fprintf(fp,"   Backtrack limit                           : %d\n",mback);
   } else {
   fprintf(fp,"   Backtrack limit (Phase 1 test generation) : %d\n",mback);
   fprintf(fp,"   Backtrack limit (Phase 2 test generation) : %d\n",mback1);
   }
   fprintf(fp,"   Initial random number generator seed      : %d\n",iseed);
   fprintf(fp,"   Test pattern compaction mode              : ");
   if(compact=='n') fprintf(fp,"NONE \n");
   else if(compact=='r') fprintf(fp,"REVERSE \n");
   else if(compact=='s') fprintf(fp,"REVERSE + SHUFFLE \n");
   if(compact=='s'){
   fprintf(fp,"   Limit of suffling compaction              : %d\n",maxcompact);
   fprintf(fp,"   Number of shuffles                        : %d\n",nshuf);
   }
   fprintf(fp,"\n");
   fprintf(fp,"3. Test pattern generation results\n");
   if(compact=='n') {
   fprintf(fp,"   Number of test patterns                   : %d\n",nt2);
   } else {
   fprintf(fp,"   Number of test patterns before compaction : %d\n",nt2);
   fprintf(fp,"   Number of test patterns after compaction  : %d\n",nt3);
   }
   fprintf(fp,"   Fault coverage                            : %.3f %%\n",(float)nd/(float)nof*100.0);
   fprintf(fp,"   Number of collapsed faults                : %d\n",nof);
   fprintf(fp,"   Number of identified redundant faults     : %d\n",nred);
   fprintf(fp,"   Number of aborted faults                  : %d\n",nof-nd-nred);
   fprintf(fp,"   Total number of backtrackings             : %d\n",tback);
   fprintf(fp,"\n");
   fprintf(fp,"4. Memory used                               : %d Kbytes\n",memory);
   fprintf(fp,"\n");
   fprintf(fp,"5. CPU time\n");
   fprintf(fp,"   Initialization                            : %.3f secs\n",inittime);
   fprintf(fp,"   Fault simulation                          : %.3f secs\n",simtime);
   fprintf(fp,"   FAN                                       : %.3f secs\n",fantime);
   fprintf(fp,"   Total                                     : %.3f secs\n",runtime);

/*
   if(mode=='y' && nd<nof) {
      if(nred > 0)
         fprintf(fp,"\n* List of identified redundant faults:\n");
      for(i=0;i<nof;i++) {
         f=faultlist[i];
         if(f->detected==REDUNDANT) {
	    printfault(fp,f,0);
	 }
      }

      if(nof-nd-nred > 0)
         fprintf(fp,"\n* List of aborted faults:\n");
      for(i=0;i<nof;i++) {
	 f=faultlist[i];
	 if(f->detected==PROCESSED) {
	    printfault(fp,f,0);
         }
      }
   }
*/
   if(mode=='y' && nd<nof)
      print_undetected_faults(fp,'s','y',1);
}

extern int nof;
int print_undetected_faults(fp,symbol,rfaultmode,flag)
FILE *fp;
char symbol;
char rfaultmode;
int flag;
{
   int i;
   int no_red, no_det, no_abort;
   FAULTPTR f;

   no_red = no_det = no_abort = 0;
   for(i=0;i<nof;i++) {
      f=faultlist[i];
      switch(f->detected) {
         case REDUNDANT: no_red++; break;
         case PROCESSED: no_abort++; break;
         default: no_det++; break;
      }
   }
   if(rfaultmode=='y' && no_red>0) {
      if(flag) fprintf(fp,"\n* List of identified redundant faults:\n");
      /* j=0; */
      for(i=0;i<nof;i++) {
         f=faultlist[i];
         if(f->detected==REDUNDANT) {
	    /* if(flag) fprintf(fp,"%4d. ",++j); */
	    printfault(fp,f,0);
	 }
      }
   }
   if(no_abort>0) {
      if(flag)   fprintf(fp,"\n* List of aborted faults:\n");
      /* j=0; */
      for(i=0;i<nof;i++) {
	 f=faultlist[i];
	 if(f->detected==PROCESSED) {
	    /* if(flag) fprintf(fp,"%4d. ",++j); */
	    printfault(fp,f,0);
         }
      }
   }
}

char *titlesim=
"******       SUMMARY OF FAULT SIMULATION RESULTS      ******";

/*------print_sim_head---------------------------------------*/
void print_sim_head(fp)
FILE *fp;
{
   fprintf(fp,"*********************************************************\n");
   fprintf(fp,"*                                                       *\n");
   fprintf(fp,"*            Welcome to fsim (version 1.1)              *\n");
   fprintf(fp,"*                                                       *\n");
   fprintf(fp,"*                 Copyright (C) 1991,                   *\n");
   fprintf(fp,"*   Virginia Polytechnic Institute & State University   *\n");
   fprintf(fp,"*                                                       *\n");
   fprintf(fp,"*********************************************************\n");
   fprintf(fp,"\n");
}


void print_sim_result(fp,name,ng,npi,npo,mlev,nametest,
	nt,nof,nd,inittime,simtime,runtime,mode)
FILE *fp;
char *name;	/* circuit name */
int ng;		/* number of gate */
int npi;	/* number of primary inputs */
int npo;	/* number of primary outputs */
int mlev;	/* max level */
char *nametest;	/* name of test cct */
int nt;		/* number of test patterns */
int nof;	/* number of total faults */
int nd;		/* number of detected faults */
float inittime,simtime,runtime;
char mode;	/* If 'y', prints redundant and undetected faults */
{

   int i;
/* int j; */
   FAULTPTR f;

   fprintf(fp,"%s\n",titlesim);
   fprintf(fp,"1. Circuit structure\n");
   fprintf(fp,"   Name of the circuit                       : %s\n",name);
   fprintf(fp,"   Number of primary inputs                  : %d\n",npi);
   fprintf(fp,"   Number of primary outputs                 : %d\n",npo);
   fprintf(fp,"   Number of gates                           : %d\n",ng-npi-npo);
   fprintf(fp,"   Level of the circuit                      : %d\n",mlev-3);
   fprintf(fp,"\n");
   fprintf(fp,"2. Simulation parameters\n");
   fprintf(fp,"   Simulation mode                           : ");
   if(rptmode=='n') fprintf(fp,"file (%s)\n",nametest);
   else if(rptmode=='y') fprintf(fp,"random\n");
   if(rptmode=='y') 
   fprintf(fp,"   Initial random number generator seed      : %d\n",iseed);
   fprintf(fp,"\n");
   fprintf(fp,"3. Simulation results\n");
   fprintf(fp,"   Number of test patterns applied           : %d\n",nt);
   fprintf(fp,"   Fault coverage                            : %.3f %%\n",(float)nd/(float)nof*100.0);
   fprintf(fp,"   Number of collapsed faults                : %d\n",nof);
   fprintf(fp,"   Number of detected faults                 : %d\n",nd);
   fprintf(fp,"   Number of undetected faults               : %d\n",nof-nd);

   fprintf(fp,"\n4. Memory used                               : %d Kbytes\n",msize);

   fprintf(fp,"\n5. CPU time\n");
   fprintf(fp,"   Initialization                            : %.3f secs\n",inittime);
   fprintf(fp,"   Fault simulation                          : %.3f secs\n",simtime);
   fprintf(fp,"   Total                                     : %.3f secs\n",runtime);

   if(mode=='y' && nd<nof) {
      fprintf(fp,"\n* List of undetected faults:\n");
/*    j=0; */
      for(i=0;i<nof;i++) {
         f=faultlist[i];
         if(f->detected!=DETECTED) {
/*	    fprintf(fp,"%4d. ",++j); */
	    printfault(fp,f,0);
	 }
      }
   }
}
