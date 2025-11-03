
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

/*---------------------------------------------------------------------
	sim.c
	Top level subroutines for fault simulation.
	Called by main().
----------------------------------------------------------------------*/
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <strings.h>

#include "parameter.h"
#include "define.h"
#include "macro.h"

extern GATEPTR *net, *dynamic_stack;
extern level all_one, BITMASK[];
extern level test_vectors[MAXTEST/10][MAXPI+1];
extern level test_vectors1[MAXTEST/10][MAXPI+1];
extern level test_store[MAXTEST/10][MAXPI+1];
extern level test_store1[MAXTEST/10][MAXPI+1];
extern int nsstack,ndstack;
extern status update_flag;
extern level InVal[];
extern char _MODE_SIM, logmode, fillmode;
extern char compact;
extern int maxcompact;
extern FILE *logfile;
extern int *primaryin, *primaryout;
extern FAULTPTR *faultlist;
extern STACKTYPE stack;

#define checkbit(word,nth) ((word&BITMASK[nth])!=ALL0)
#define setbit(word,nth) (word|=BITMASK[nth])
#define resetbit(word,nth) (word&=(~BITMASK[nth]))
#define setb0(W0,W1,nth) W0|=BITMASK[nth]; W1&=(~BITMASK[nth]) 
#define setb1(W0,W1,nth) W0&=(~BITMASK[nth]); W1|=BITMASK[nth]
/*
#define setbx(W0,W1,nth) W0|=(BITMASK[nth]); W1|=(BITMASK[nth])
*/
#define setbx(W0,W1,nth) W0&=(~BITMASK[nth]); W1&=(~BITMASK[nth])

#define delete_fault_fsim(fal) \
if(fal->previous==fal) { \
   fal->gate->pfault=fal->next; \
   if(fal->next!=NULL) fal->next->previous=fal->next; \
} else { \
   fal->previous->next=fal->next; \
   if(fal->next!=NULL) fal->next->previous=fal->previous; \
}

#define output0 output
#define is_checkpoint(gate) (gate->fn>=PI || gate->noutput>1)

int ntest_each;
int ntest_each_limit;
extern char gen_all_pat, no_faultsim;

/*------random_sim-----------------------------------------------------
TASK	Performs random similation until n consecutive packets of
	random patterns do not detect any new fault.
----------------------------------------------------------------------*/
int random_fsim(nog,nopi,nopo,LEVEL,nstem,stem,LFSR,limit,maxbit,maxdetect,
ntest,npacket,nbit,test)
int nog,nopi,nopo,LEVEL,nstem,maxbit;
GATEPTR *stem;
level *LFSR;
int limit;
int *ntest, *npacket, *nbit;
FILE *test;
{
   int iteration=0;
   int i,j;
   int profile[BITSIZE];
   int ndetect=0;

   while(iteration<limit) {
      GetPRandompattern(nopi,LFSR);
      for(i=0;i<nopi;i++)
	 { net[i]->output1=net[i]->output=LFSR[i]; }
      pfault_free_simulation();
      for(i=0;i<maxbit;i++) profile[i]=0;
      if(Fault1_Simulation(nog,LEVEL,nopi,nopo,
            nstem,stem,maxbit,profile)>0) {
         iteration=0;
         for(i=maxbit-1;i>=0;i--)
            if(profile[i]>0) {
	       (*ntest)++;
	       ndetect+=profile[i];
	       for(j=0;j<nopi;j++) 
	          if((net[j]->output1&BITMASK[i])!=ALL0)
	             setbit(test_vectors[*npacket][j],*nbit);
               else resetbit(test_vectors[*npacket][j],*nbit);
               if(++(*nbit)==maxbit) {*nbit=0; (*npacket)++;}
	       if(compact=='n') {
                  printio(test,nopi,nopo,i,*ntest);
                  if(logmode=='y') {
                      fprintf(logfile,"test %4d: ",*ntest);
                      printinputs(logfile,nopi,i);
                      fprintf(logfile," ");
                      printoutputs(logfile,nopo,i);
                      fprintf(logfile," %4d faults detected\n",profile[i]);
                  }
	       }
	    }
	 if(ndetect>=maxdetect) break;
      }
      else iteration++;

      for(i=0;i<=nsstack;i++) dynamic_stack[i]->cobserve=ALL0;
      if(update_flag) {
         update_all1(nopi);
         reset(update_flag);
      }
      else for(i=ndstack;i>nsstack;i--) dynamic_stack[i]->freach=0;
      ndstack=nsstack;
   }

   return(ndetect);
}

int random_hope(nopi,nopo,LFSR,limit,maxbit,maxdetect,ntest,npacket,nbit,test)
int nopi,nopo,maxbit;
level *LFSR;
int limit;
int *ntest, *npacket, *nbit;
FILE *test;
{
   int iteration=0;
   int i,j,n,n1;
   int ndetect=0;
   int ran_test=0;

   while(iteration<limit) {
      GetPRandompattern(nopi,LFSR);
      for(n=0, i=maxbit-1; i>=0; i--) {
         for(j=0;j<nopi;j++)
	    InVal[j]=((LFSR[j]&BITMASK[i])==ALL0)?ZERO:ONE;
	 GoodSim(++ran_test);
         if((n1=Simulation()) > 0) {
	    n+=n1;
	    (*ntest)++;
	    ndetect+=n1;
	    for(j=0;j<nopi;j++)
	       if(InVal[j]==ONE) {
		  setb1(test_vectors[*npacket][j],
		        test_vectors1[*npacket][j],*nbit);
	       } else {
		  setb0(test_vectors[*npacket][j],
		        test_vectors1[*npacket][j],*nbit);
	       }
            if(++(*nbit)==maxbit) {*nbit=0; (*npacket)++;}

            if(compact=='n'){
               fprintf(test,"test %4d: ",*ntest);
               printiovalues(test,primaryin,nopi,'o','g',0);
               fprintf(test," ");
               printiovalues(test,primaryout,nopo,'o','g',0);
               fprintf(test,"\n");
               if(logmode=='y') {
                  fprintf(logfile,"test %4d: ",*ntest);
                  printiovalues(logfile,primaryin,nopi,'o','g',0);
                  fprintf(logfile," ");
                  printiovalues(logfile,primaryout,nopo,'o','g',0);
                  fprintf(logfile," %4d faults detected",n);
                  fprintf(logfile,"\n");
               }
	    }

	    if(ndetect>=maxdetect) break;
         }
      }
      iteration = (n>0) ? 0 : iteration+1;
      if(ndetect>=maxdetect) break;
   }

   return(ndetect);
}


int random_sim(nog,nopi,nopo,LEVEL,nstem,stem,LFSR,limit,maxbit,maxdetect,
ntest,npacket,nbit,test)
int nog,nopi,nopo,LEVEL,nstem,maxbit;
GATEPTR *stem;
level *LFSR;
int limit;
int *ntest, *npacket, *nbit;
FILE *test;
{
   if(_MODE_SIM=='f')
      return(random_fsim(nog,nopi,nopo,LEVEL,nstem,stem,LFSR,limit,
	     maxbit,maxdetect, ntest,npacket,nbit,test));
   else
      return(random_hope(nopi,nopo,LFSR,limit,maxbit,maxdetect,
	     ntest,npacket,nbit,test));
}


int tgen_sim(nog,LEVEL,nopi,nopo,nstem,stem,ntest,profile)
int nog, LEVEL, nopi, nopo, nstem, profile[],ntest;
GATEPTR *stem;
{
   if(_MODE_SIM=='f')
      return(Fault0_Simulation(nog,LEVEL,nopi,nopo,nstem,stem,1,profile));
   else {
      GoodSim(ntest);
      return(Simulation());
   }
}


void fill_patterns_fsim(mode,npacket,nbit,nopi)
char mode;
int npacket, nbit, nopi;
{
   int j, ran;

   switch(mode) {
   case '0':
      for(j=0;j<nopi;j++)
         switch(net[j]->output) {
         case ONE: setbit(test_vectors[npacket][j],nbit);
                   net[j]->output1=ALL1;
		   break;
         default: resetbit(test_vectors[npacket][j],nbit);
                  net[j]->output1=ALL0;
	  	  break;
         }
      break;
   case '1':
      for(j=0;j<nopi;j++)
         switch(net[j]->output) {
         case ZERO: resetbit(test_vectors[npacket][j],nbit);
                    net[j]->output1=ALL0;
	  	    break;
         default: setbit(test_vectors[npacket][j],nbit);
                  net[j]->output1=ALL1;
		  break;
         }
      break;
   case 'r': case 'x':
      for(j=0;j<nopi;j++)
         switch(net[j]->output) {
         case ZERO: resetbit(test_vectors[npacket][j],nbit);
                    net[j]->output1=ALL0;
	  	    break;
         case ONE: setbit(test_vectors[npacket][j],nbit);
                   net[j]->output1=ALL1;
		   break;
         default: ran=(int)random()&01;
		  if(ran != 0)
		     setbit(test_vectors[npacket][j],nbit);
		  else resetbit(test_vectors[npacket][j],nbit);
		  net[j]->output1=ran;
         }
   break;
   }
}

void fill_patterns_hope(mode,npacket,nbit,nopi)
char mode;
int npacket,nbit,nopi;
{
   int j;

   switch(mode) {
   case '0':
      for(j=0;j<nopi;j++)
         switch(net[j]->output) {
         case ONE: setb1(test_vectors[npacket][j],
		         test_vectors1[npacket][j],nbit);
                   InVal[j]=ONE;
		   break;
         default: setb0(test_vectors[npacket][j],
		        test_vectors1[npacket][j],nbit);
                  InVal[j]=ZERO;
	  	  break;
         }
      break;
   case '1':
      for(j=0;j<nopi;j++)
         switch(net[j]->output) {
         case ZERO: setb0(test_vectors[npacket][j],
		          test_vectors1[npacket][j],nbit);
                    InVal[j]=ZERO;
		    break;
         default: setb1(test_vectors[npacket][j],
		        test_vectors1[npacket][j],nbit);
                  InVal[j]=ONE;
	  	  break;
         }
      break;
   case 'r':
      for(j=0;j<nopi;j++)
         switch(net[j]->output) {
         case ZERO: setb0(test_vectors[npacket][j],
                          test_vectors1[npacket][j],nbit);
                    InVal[j]=ZERO;
	  	    break;
         case ONE: setb1(test_vectors[npacket][j],
                          test_vectors1[npacket][j],nbit);
		   InVal[j]=ONE;
		   break;
         default: if((InVal[j]=(int)random()&01) != 0) {
		     setb1(test_vectors[npacket][j],
                          test_vectors1[npacket][j],nbit);
		  } else {
		     setb0(test_vectors[npacket][j],
                          test_vectors1[npacket][j],nbit);
		  }
		  break;
         }
      break;
   case 'x':
      for(j=0;j<nopi;j++)
         switch(net[j]->output) {
         case ZERO: setb0(test_vectors[npacket][j],
                          test_vectors1[npacket][j],nbit);
                    InVal[j]=ZERO;
	  	    break;
         case ONE: setb1(test_vectors[npacket][j],
                          test_vectors1[npacket][j],nbit);
		   InVal[j]=ONE;
		   break;
         default: InVal[j]=X;
		  setbx(test_vectors[npacket][j],
                        test_vectors1[npacket][j],nbit);
		  break;
         }
      break;
   }
}


void fill_patterns(mode,npacket,nbit,nopi)
{
   if(_MODE_SIM=='f')
      fill_patterns_fsim(mode,npacket,nbit,nopi);
   else
      fill_patterns_hope(mode,npacket,nbit,nopi);
}

extern int nof;

#define CHECKPOINTMODE 1
#define DEFAULTMODE 0

int testgen(nog,nopi,nopo,LEVEL,maxbits,nstem,stem,maxbacktrack,phase,
            nredundant,noverbacktrack,nbacktrack,ntest,npacket,nbit,fantime,test)
int nog, nopi, nopo, LEVEL, maxbits, nstem, maxbacktrack;
int phase; 	/* 0: static, 1:dynamic unique path sensitization */
GATEPTR *stem;
int *nredundant,*noverbacktrack,*nbacktrack,*npacket,*nbit,*ntest;
double *fantime;
FILE *test;
{

   int j,nback;
   status fault_selection_mode;
   int lastfault;
   int state;
   int ndetect=0;
   FAULTTYPE *pcurrentfault;
   boolean done;
   GATEPTR gut;
   int profile[BITSIZE];
   double seconds,minutes,runtime1,runtime2;

   fault_selection_mode=DEFAULTMODE;
   lastfault=nof;
   all_one=~(ALL1<<1);
   done=FALSE;

   while(!done) {
      if(maxbacktrack==0) break;

      /* select any undetected and untried fault */
      pcurrentfault=NULL;
      switch(fault_selection_mode) {
	 case CHECKPOINTMODE:
	    while(--lastfault>=0)
	       if(is_undetected(faultlist[lastfault])) {
		  pcurrentfault=faultlist[lastfault];
		  gut=pcurrentfault->gate;
		  if(pcurrentfault->line!=OUTFAULT)
		     gut=gut->inlis[pcurrentfault->line];
		  if(is_checkpoint(gut)) break;
		  pcurrentfault=NULL;
	       }
	    if(pcurrentfault==NULL) {
		fault_selection_mode=DEFAULTMODE;
		lastfault=nof;
	    }
	    break;

         default:
	    while(--lastfault>=0)
               if(is_undetected(faultlist[lastfault])) {
	          pcurrentfault=faultlist[lastfault];
	          break;
	       }
	    if(pcurrentfault==NULL) set(done);
      }

      if(pcurrentfault==NULL) continue;
      gut=pcurrentfault->gate;

      ntest_each=0;
      if(no_faultsim=='y') {
         printfault(test,pcurrentfault,0);
         if(logmode=='y') printfault(logfile,pcurrentfault,0);
      }

      gettime(&minutes,&seconds,&runtime1);

      /* test pattern generation using fan */
      state = (phase==FALSE) ? 
	 fan(nog,LEVEL,nopi,nopo,pcurrentfault,maxbacktrack,&nback) :
	 fan1(nog,LEVEL,nopi,nopo,pcurrentfault,maxbacktrack,&nback);
      (*nbacktrack)+=nback;

      gettime(&minutes,&seconds,&runtime2);
      (*fantime)+=(runtime2-runtime1);

      if(no_faultsim=='y') {
	 (*ntest)+=ntest_each;
	 if(ntest_each > 0) {
	    pcurrentfault->detected=DETECTED;
	    ndetect++;
	 } else if(state==NO_TEST) {
            /* redundant faults */
            pcurrentfault->detected=REDUNDANT;
            (*nredundant)++;
         } else {
            /* over backtracking */
            (*noverbacktrack)++;
            pcurrentfault->detected=PROCESSED;
         }
      } else if(state==TEST_FOUND) {
	 /* fault is detected, delete the detected fault from fault list */
	 pcurrentfault->detected=PROCESSED;

/*	 pcurrentfault->detected=DETECTED;
	 gut->nfault--;
	 ndetect++;
*/
	 /* assign random zero and ones to the unassigned bits */
         (*ntest)++;
	 fill_patterns(fillmode,*npacket,*nbit,nopi);
	 if(_MODE_SIM=='f')
	    for(j=0;j<nopi;j++) {
	       reset(net[j]->changed);
	       reset(net[j]->freach);
	       net[j]->cobserve=ALL0;
	       net[j]->output0=net[j]->output1;
	    }
	 else
	    for(j=0;j<nog;j++) {
	       reset(net[j]->changed);
	       reset(net[j]->freach);
	    }
	 if(++(*nbit)==maxbits) {*nbit=0; (*npacket)++;}
	 clear(stack);

	 /* fault simulation */
	 profile[0]=0;
	 profile[0] =
	    tgen_sim(nog,LEVEL,nopi,nopo,nstem,stem,*ntest,profile);
         ndetect += profile[0];

	 if(compact=='n') {
	    if(_MODE_SIM=='f') {
               /*printio(test,nopi,nopo,j,*ntest);KHB*/
               printio(test,nopi,nopo,0,*ntest);
               if(logmode=='y') {
                   fprintf(logfile,"test %4d: ",*ntest);
                   printinputs(logfile,nopi,0);
                   fprintf(logfile," ");
                   printoutputs(logfile,nopo,0);
                   fprintf(logfile," %4d faults detected\n",profile[0]);
               }
	    }
	    else {
               fprintf(test,"test %4d: ",*ntest);
               printiovalues(test,primaryin,nopi,'o','g',0);
               fprintf(test," ");
               printiovalues(test,primaryout,nopo,'o','g',0);
               fprintf(test,"\n");
               if(logmode=='y') {
                  fprintf(logfile,"test %4d: ",*ntest);
                  printiovalues(logfile,primaryin,nopi,'o','g',0);
                  fprintf(logfile," ");
                  printiovalues(logfile,primaryout,nopo,'o','g',0);
                  fprintf(logfile," %4d faults detected",profile[0]);
                  fprintf(logfile,"\n");
               }
            }
         }

	 if(pcurrentfault->detected!=DETECTED) {
	    printf("Error in test generation\n");
	 }
      }

      else if(state==NO_TEST) {
	 /* redundant faults */
	 pcurrentfault->detected=REDUNDANT;
	 (*nredundant)++;
         if(_MODE_SIM=='f') {
	    delete_fault_fsim(pcurrentfault);
	    if(--gut->nfault==0) set(update_flag);
	 }
      }

      else {
	 /* over backtracking */
	 (*noverbacktrack)++;
	 pcurrentfault->detected=PROCESSED;
      }
   }

   return(ndetect);
}



void random_test_fsim(test_st,test_vect,pack,no_bit,no_pi)
level test_st[][MAXPI+1];
level test_vect[][MAXPI+1];
int pack,no_bit,no_pi;
{
   int array[40*BITSIZE];
   int array1[40*BITSIZE];
   int i,j,x,bits,k,B,nbit=0,npacket=0;
   int maxbits=BITSIZE;
 
   bits=32*pack+no_bit;
   for(i=0;i<bits;i++)array[i]=i;
 
   j=0;
   for(i=bits-1;i>=0;i--){
      x=random()%(i+1);
      array1[j]=array[x];
      array[x]=array[i];
      j++;
   }
   for(i=0;i<bits;i++){
      x=array1[i];
      k=x/32;
      B=x%32;
      for(j=0;j<no_pi;j++)
         if((test_st[k][j]&BITMASK[B])!=ALL0)
            setbit(test_vect[npacket][j],nbit);
         else resetbit(test_vect[npacket][j],nbit);
      if(++nbit==maxbits){nbit=0;npacket++;}
   }
}


int reverse_fsim(nog,nopi,nopo,LEVEL,nstem,stem,nof,
	         ndet,npacket,nbit,maxbits,test)
int nog,nopi,LEVEL,nstem,nof;
int npacket, nbit, maxbits;
GATEPTR *stem;
FILE *test;
int *ndet;
{
   int i, j, k, n;
   int nrestoredfault;
   int ndetect=0;
   int no_test=0;
   int ncomp=INFINITY, stop=ONE;
   int bit=0, packet=0;
   int profile[BITSIZE];
   int narray[MAXTEST], store=0;
   int done, flag_bit;

   for(i=0;i<nog;i++) {
      net[i]->nfault=0;
      net[i]->pfault=NULL;
   }
   if((nrestoredfault=restore_detected_fault_list(nof))<0) {
      printf("error occurred in restoration of fault list\n");
      exit(0);
   }

   pinit_simulation(nog,LEVEL,nopi);

   reset(update_flag);
   if(nbit==0) {--npacket; nbit=maxbits;}

   /* reverse fault simulation */
   k=npacket+1;
   while(--k>=0) {
      if(ndetect>=nrestoredfault) break;
      if(k<npacket) nbit=maxbits;
      if(nbit==BITSIZE) all_one=ALL1;
      else all_one=~(ALL1<<nbit);
 
      for(j=0;j<nopi;j++)
         net[j]->output1=net[j]->output0=test_vectors[k][j];
      pfault_free_simulation();
 
      for(i=0;i<nbit;i++) profile[i]=0;
      if((n = Fault1_Simulation(nog,LEVEL,nopi,nopo,
	    nstem,stem,nbit,profile))>0) {
         ndetect+=n;
 
         /* print out test files */
         for(i=nbit-1;i>=0;i--)
            if(profile[i]>0) {
               no_test++;
               if(compact=='r'){
                  printio(test,nopi,nopo,i,no_test);
                  if(logmode=='y') {
                     fprintf(logfile,"test %4d: ",no_test);
                     printinputs(logfile,nopi,i);
                     fprintf(logfile," ");
                     printoutputs(logfile,nopo,i);
                     fprintf(logfile," %4d faults detected\n",profile[i]);
                  }
	       }
            }
      }
 
      for(i=0;i<=nsstack;i++) dynamic_stack[i]->cobserve=ALL0;
      if(update_flag) {
         update_all1(nopi);
         reset(update_flag);
      }
      else for(i=ndstack;i>nsstack;i--) dynamic_stack[i]->freach=0;
      ndstack=nsstack;
   }

   *ndet=ndetect;
   return(no_test);
}


int shuffle_fsim(nog,nopi,nopo,LEVEL,nstem,stem,nof,
	         nshuf,ndet,npacket,nbit,maxbits,test)
int nog,nopi,LEVEL,nstem,nof;
int npacket, nbit, maxbits;
GATEPTR *stem;
FILE *test;
int *nshuf,*ndet;
{
   int i, j, k, n;
   int nrestoredfault;
   int ndetect=0;
   int no_test=0;
   int ncomp=INFINITY, stop=ONE;
   int bit=0, packet=0;
   int profile[BITSIZE];
   int narray[MAXTEST], store=0;
   int done, flag_bit;

   for(i=0;i<=maxcompact;i++) narray[i]=0;
   reset(done);
   flag_bit=FALSE;
   *nshuf=0;

   /* shufle fault simulation */
   if(compact=='s'){
      while((!done)){
         (*nshuf)++;
         for(i=0;i<nog;i++) {
            net[i]->nfault=0;
            net[i]->pfault=NULL;
         }
         if((nrestoredfault=restore_detected_fault_list(nof))<0) {
            printf("error occurred in restoration of fault list\n");
            exit(0);
         }

         pinit_simulation(nog,LEVEL,nopi);

         reset(update_flag);
         if(flag_bit == TRUE){
            nbit=bit;   
            npacket=packet;
            /*shuffles the test patterns and stores it back in the random fashion*/
            random_test_fsim(test_store,test_vectors,packet,bit,nopi);
            bit=packet=0;
            for(ncomp=0;ncomp<=maxcompact-1;ncomp++){
               stop=STOP;
	       if(narray[ncomp]!=narray[ncomp+1]){
	          stop=TWO;
		  break;
	       }
            }
         }

         no_test=0;
         ndetect=0;
 
         if(nbit==0) {--npacket; nbit=maxbits;}
         k=npacket+1;
         while(--k>=0) {
            if(ndetect>=nrestoredfault) break;
            if(k<npacket) nbit=maxbits;
            if(nbit==BITSIZE) all_one=ALL1;
            else all_one=~(ALL1<<nbit);

            for(j=0;j<nopi;j++)
               net[j]->output1=net[j]->output0=test_vectors[k][j];
            pfault_free_simulation();
 
            for(i=0;i<nbit;i++) profile[i]=0;
            if((n = Fault1_Simulation(nog,LEVEL,nopi,nopo,
	       nstem,stem,nbit,profile))>0) {
               ndetect+=n;
 
               /* print out test files */
               for(i=nbit-1;i>=0;i--)
                  if(profile[i]>0) {
                     no_test++;
                     if(stop==STOP){
                        printio(test,nopi,nopo,i,no_test);
                        if(logmode=='y') {
                           fprintf(logfile,"test %4d: ",no_test);
                           printinputs(logfile,nopi,i);
                           fprintf(logfile," ");
                           printoutputs(logfile,nopo,i);
                           fprintf(logfile," %4d faults detected\n",profile[i]);
                        }
	                set(done);
	             }
                     flag_bit=TRUE;
                     for(j=0;j<nopi;j++)
                        if((net[j]->output1&BITMASK[i])!=ALL0)
                            setbit(test_store[packet][j],bit);
                        else resetbit(test_store[packet][j],bit);
                     if(++bit==maxbits) {bit=0; packet++;}
                  }
            }
 
 
            for(i=0;i<=nsstack;i++) dynamic_stack[i]->cobserve=ALL0;
            if(update_flag) {
               update_all1(nopi);
               reset(update_flag);
            }
            else for(i=ndstack;i>nsstack;i--) dynamic_stack[i]->freach=0;
            ndstack=nsstack;
         }
         if(store==maxcompact+1)store=0;
         narray[store]=no_test;
         store++;
      }
   }

   *ndet=ndetect;
   return(no_test);
}

void random_test_hope(test_st0,test_st1,test_vec0,test_vec1,pack,no_bit,no_pi)
level test_st0[][MAXPI+1];
level test_st1[][MAXPI+1];
level test_vec0[][MAXPI+1];
level test_vec1[][MAXPI+1];
int pack,no_bit,no_pi;
{
   int array[40*BITSIZE];
   int array1[40*BITSIZE];
   int i,j,x,bits,k,B,nbit=0,npacket=0;
   int maxbits=BITSIZE;
 
   bits=32*pack+no_bit;
   for(i=0;i<bits;i++) array[i]=i;
 
   j=0;
   for(i=bits-1;i>=0;i--){
      x=random()%(i+1);
      array1[j]=array[x];
      array[x]=array[i];
      j++;
   }
   for(i=0;i<bits;i++){
      x=array1[i];
      k=x/32;
      B=x%32;
      for(j=0;j<no_pi;j++) {
         if((test_st0[k][j]&BITMASK[B])!=ALL0)
            { setbit(test_vec0[npacket][j],nbit); }
         else { resetbit(test_vec0[npacket][j],nbit); }
         if((test_st1[k][j]&BITMASK[B])!=ALL0)
            { setbit(test_vec1[npacket][j],nbit); }
         else { resetbit(test_vec1[npacket][j],nbit); }
      }
      if(++nbit==maxbits){nbit=0;npacket++;}
   }
}


extern FAULTPTR potentialfault, tailfault;

int reverse_hope(nog,nopi,nopo,nof,ndet,npacket,nbit,maxbits,test)
int nog,nopi,nof;
int npacket, nbit, maxbits;
FILE *test;
int *ndet;
{
   int i, j, k, n;
   level v1, v2;
   int nrestoredfault;
   int ndetect=0;
   int no_test=0;
   int ncomp=INFINITY, stop=ONE;
   int bit=0, packet=0;
   int narray[MAXTEST], store=0;
   int done, flag_bit;

   if((nrestoredfault=restore_hope_fault_list(nof))<0) {
      printf("error occurred in restoration of fault list\n");
      exit(0);
   }
   potentialfault=tailfault;
   for(i=0; i<nog; i++) { reset(net[i]->changed); }

   if(nbit==0) {--npacket; nbit=maxbits;}

   /* reverse fault simulation */
   k=npacket+1;
   while(--k>=0) {
      if(ndetect>=nrestoredfault) break;
      if(k<npacket) nbit=maxbits;
      for(i=nbit-1; i>=0; i--) {

         for(j=0;j<nopi;j++) {
            v1=((test_vectors[k][j]&BITMASK[i])==ALL0)?ZERO:ONE;
            v2=((test_vectors1[k][j]&BITMASK[i])==ALL0)?ZERO:ONE;
            InVal[j]=(v1==ONE)?ZERO:(v2==ONE)?ONE:X;
         }
         GoodSim(2);
         if((n=Simulation()) > 0) {
            ndetect+=n;
            no_test++;
            if(compact=='r'){
	       fprintf(test,"test %4d: ",no_test);
	       printiovalues(test,primaryin,nopi,'o','g',0);
	       fprintf(test," ");
	       printiovalues(test,primaryout,nopo,'o','g',0);
	       fprintf(test,"\n");
               if(logmode=='y') {
                  fprintf(logfile,"test %4d: ",no_test);
                  printiovalues(logfile,primaryin,nopi,'o','g',0);
                  fprintf(logfile," ");
                  printiovalues(logfile,primaryout,nopo,'o','g',0);
                  fprintf(logfile," %4d faults detected",n);
                  fprintf(logfile,"\n");
               }
	    }
            if(ndetect>=nrestoredfault) break;
         }
      }
   }

   *ndet=ndetect;
   return(no_test);
}


int shuffle_hope(nog,nopi,nopo,nof,nshuf,ndet,npacket,nbit,maxbits,test)
int nog,nopi,nof;
int npacket, nbit, maxbits;
FILE *test;
int *nshuf, *ndet;
{
   int i, j, k, n;
   level v1, v2;
   int nrestoredfault;
   int ndetect=0;
   int no_test=0;
   int ncomp=INFINITY, stop=ONE;
   int bit=0, packet=0;
   int narray[MAXTEST], store=0;
   int done, flag_bit;

   for(i=0;i<=maxcompact;i++) narray[i]=0;
   reset(done);
   flag_bit=FALSE;
   *nshuf=0;

   /* shufle fault simulation */
   if(compact=='s'){
      while((!done)){
         (*nshuf)++;
         if((nrestoredfault=restore_hope_fault_list(nof))<0) {
            printf("error occurred in restoration of fault list\n");
            exit(0);
         }
         potentialfault=tailfault;
         for(i=0; i<nog; i++) { reset(net[i]->changed); }

         if(flag_bit == TRUE){
            nbit=bit;   
            npacket=packet;
            /*shuffles the test patterns and stores it back in the random fashion*/
            random_test_hope(test_store,test_store1,test_vectors,test_vectors1,
		             packet,bit,nopi);
            bit=packet=0;
            for(ncomp=0;ncomp<=maxcompact-1;ncomp++){
               stop=STOP;
	       if(narray[ncomp]!=narray[ncomp+1]){
	          stop=TWO;
		  break;
	       }
            }
         }

         no_test=0;
         ndetect=0;
 
         if(nbit==0) {--npacket; nbit=maxbits;}
         k=npacket+1;
         while(--k>=0) {
            if(ndetect>=nrestoredfault) break;
            if(k<npacket) nbit=maxbits;
            for(i=nbit-1; i>=0; i--) {
 
               for(j=0;j<nopi;j++) {
                  v1=((test_vectors[k][j]&BITMASK[i])==ALL0)?ZERO:ONE;
                  v2=((test_vectors1[k][j]&BITMASK[i])==ALL0)?ZERO:ONE;
                  InVal[j]=(v1==ONE)?ZERO:(v2==ONE)?ONE:X;
               }
               GoodSim(2);
               if((n=Simulation()) > 0) {
                  ndetect+=n;
                  no_test++;
                  if(stop==STOP){
                     fprintf(test,"test %4d: ",no_test);
                     printiovalues(test,primaryin,nopi,'o','g',0);
                     fprintf(test," ");
                     printiovalues(test,primaryout,nopo,'o','g',0);
                     fprintf(test,"\n");
                     if(logmode=='y') {
                        fprintf(logfile,"test %4d: ",no_test);
                        printiovalues(logfile,primaryin,nopi,'o','g',0);
                        fprintf(logfile," ");
                        printiovalues(logfile,primaryout,nopo,'o','g',0);
                        fprintf(logfile," %4d faults detected",n);
                        fprintf(logfile,"\n");
                     }
	  	     set(done);
	          }
                  flag_bit=TRUE;
                  for(j=0;j<nopi;j++) {
		     switch(InVal[j]) {
		     case ONE:
                        setb1(test_store[packet][j],
                              test_store1[packet][j],bit);
			break;
		     case ZERO:
                        setb0(test_store[packet][j],
                              test_store1[packet][j],bit);
		        break;
		     default:
                        setbx(test_store[packet][j],
                              test_store1[packet][j],bit);
			break;
                     }
		  }
                  if(++bit==maxbits) {bit=0; packet++;}
               }
               if(ndetect>=nrestoredfault) break;
            }
         }
         if(store==maxcompact+1) store=0;
         narray[store]=no_test;
         store++;
      }
   }

   *ndet=ndetect;
   return(no_test);
}

int compact_test(nog,nopi,nopo,LEVEL,nstem,stem,nof,
	         nshuf,ndet,npacket,nbit,maxbits,test)
int nog,nopi,LEVEL,nstem,nof;
int npacket, nbit, maxbits;
GATEPTR *stem;
FILE *test;
int *nshuf, *ndet;
{
   *nshuf=0;
   if(_MODE_SIM=='f') {
      if(compact=='s')
         return(shuffle_fsim(nog,nopi,nopo,LEVEL,nstem,stem,nof,
		          nshuf,ndet,npacket,nbit,maxbits,test));
      else
         return(reverse_fsim(nog,nopi,nopo,LEVEL,nstem,stem,nof,
		          ndet,npacket,nbit,maxbits,test));
   } else {
      if(compact=='s')
         return(shuffle_hope(nog,nopi,nopo,nof,nshuf,
	                  ndet,npacket,nbit,maxbits,test));
      else
         return(reverse_hope(nog,nopi,nopo,nof,
	                  ndet,npacket,nbit,maxbits,test));
   }
}


extern FILE *test;
char *Dlevel_to_string[5]={"0","1","x","1","0"};
void Dprintio(test,nopi,nopo,no)
FILE *test;
int nopi, nopo, no;
{
   int i;

   fprintf(test,"   %4d: ",no);
   for(i=0; i<nopi; i++) {
      fprintf(test,"%s",Dlevel_to_string[net[primaryin[i]]->output]);
   }
   fprintf(test," ");
   for(i=0; i<nopo; i++) {
      fprintf(test,"%s",Dlevel_to_string[net[primaryout[i]]->output]);
   }
   fprintf(test,"\n");
}

