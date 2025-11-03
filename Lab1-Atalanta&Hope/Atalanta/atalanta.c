
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
	Added shuffle compaction:  T. Chandra, 12/11/1993

	Now, atalanta accepts the circuit written in the netlist format
	of ISCAS89 benchmark circuits as well as the netlist format of
	ISCAS85 benchmark circuits.

        atalanta: version 2.0        H. K. Lee, 6/30/1997

***********************************************************************/

/*---------------------------------------------------------------------
	atalanta.c
	Main program for atalanta.
	An automatic test pattern generator for single stuck-at
	fault in combinational logic circuits.
	Generates test patterns detecting stuck-at faults in
	combinational circuits.
----------------------------------------------------------------------*/
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <strings.h>

#include "parameter.h"
#include "define.h"
#include "macro.h"
#include "truthtable.h"

#include "global.d"

#define CHECKPOINTMODE 1
#define DEFAULTMODE 0

extern caddr_t sbrk();
extern long random();
extern int  init_fault();
extern void print_atpg_head(), print_atpg_result(),
	    help(), exit(), fatalerror(), learn();
extern int print_undetected_faults();

#define valid_test(i) test_vectors[i][nopi]=ONE
#define invalid_test(i) test_vectors[i][nopi]=ZERO
#define is_valid(i) (test_vectors[i][nopi]==ONE)
#define is_invalid(i) (test_vectors[i][nopi]==ZERO)
#define is_random_mode(mode) (mode=='y')
#define delete_fault(fal) \
if(fal->previous==fal) { \
   fal->gate->pfault=fal->next; \
   if(fal->next!=NULL) fal->next->previous=fal->next; \
} else { \
   fal->previous->next=fal->next; \
   if(fal->next!=NULL) fal->next->previous=fal->previous; \
}

#define is_checkpoint(gate) (gate->fn>=PI || gate->noutput>1)
#define output0 output

#define checkbit(word,nth) ((word&BITMASK[nth])!=ALL0)
#define setbit(word,nth) (word|=BITMASK[nth])
#define resetbit(word,nth) (word&=(~BITMASK[nth]))

/* external variables */
extern void setfanoutstem();
extern void set_unique_path();
extern void pinit_simulation();
extern void GetPRandompattern();
extern void pfault_free_simulation();
extern void update_all1();
extern char *strcpy(), *strcat();
extern void GetRandompattern();
extern void print_log_topic();
extern void gettime();
extern void printinputs(), printoutputs(), printfault();
extern void set_testability();

/* variables for main program */
level test_vectors[MAXTEST/10][MAXPI+1];
level test_vectors1[MAXTEST/10][MAXPI+1];
level test_store[MAXTEST/10][MAXPI+1];
level test_store1[MAXTEST/10][MAXPI+1];


/* default parameters setting */
char name1[100]="",name2[100]="",name3[100]="";
char faultname[100]="";
char cctname[100]="";
char nameufaults[MAXSTRING]="";
char inputmode='d';		/* default mode */
char rptmode='y';		/* RPT mode ON */
char logmode='n';		/* LOG off */
char fillmode='r';		/* 0, 1, x, r */
char compact='s';		/* n: no compaction, r: reverse, s: shuffle */
char helpmode='q';		/* On-line help mode */
char learnmode='n';
char cctmode=ISCAS89;		/* input circuit format*/
int iseed=0;			/* initial random seed */
int randomlimit=16;		/* condition for RPT stopping */
int maxbacktrack=10;		/* maximum backtracking of FAN */
int maxbacktrack1=0;		/* maximum backtracking of FAN */
int maxcompact=2;		/* maximum limit for compaction*/
char _MODE_SIM='f';		/* 'f': FSIM, 'h': HOPE */
char faultmode='d';
char gen_all_pat='n';		/* 'y': generates all patterns for each fault */
int ntest_each_limit=(-1);      /* no of patterns to be generated for each fault */
char no_faultsim='n';		/* 'y': no fault simulation */
char ufaultmode='n';            /* Write out undetected faults */
char rfaultmode='n';            /* Write out redundant faults */

FILE *faultfile;
FILE *ufaultfile;
int msize;

/*------main: Main program of atalanta---------------------------*/

void main(argc,argv)
int argc;
char *argv[];
{
   register int i,j;
   int shuf;
   boolean done=FALSE;
   int number;
   int LEVEL=0;
   int nrestoredfault,maxdetect;
   FAULTTYPE *pcurrentfault,*f;
   GATEPTR gut,*stem;
   int nstem;
   int k,n,iteration;
   status state,fault_selection_mode;
   int nbacktrack;
   int ndetect=0, nredundant=0, noverbacktrack=0, ntest=0;
   int ntest1=0, ntest2=0, ntest3=0;
   int ndetect3=0;
   int narray[MAXTEST],store=0;
   int tbacktrack=0;
   int lastfault;
   int ncomp=INFINITY,stop=ONE;
   double minutes,seconds,starttime,inittime,runtime1,runtime2;
   double fantime,fan1time,simtime1,simtime2,simtime3;

   int maxbits=BITSIZE;
   int fault_profile[BITSIZE];
   int nbit=0,npacket=0;
   char c;
   level LFSR[MAXPI],ran;
   int bit=0,packet=0;
   int phase2,nd;

   /*****************************************************************
    *                                                               *
    *          step 0: preprocess ---                               *
    *                input and output file interface                *
    *                                                               *
    *****************************************************************/

/*
   if(argc==1) {
      helpmode='d';
   } else for(i=1;i<argc;i++) {
           if(argv[i][0]=='-') {
	      if((i=option_set(argv[i][1],argv,i,argc))<0) {
	         helpmode='d'; break;
	   }}
	   else strcpy(name1,argv[i]);
        }

   if(helpmode!='q') { help(helpmode); exit(0); }
*/
   option_set(argc,argv);

   if((circuit = fopen(name1,"r")) == NULL) {
      fprintf(stderr,"Fatal error: no such file exists %s\n",name1);
      exit(0);
   }

   strcpy(cctname,name1);

   i=0; j=0;
   if(name2[0]=='\0') {
      while((c=name1[i++])!='\0') {
         if(c=='/') j=0;
         else if(c=='.') break;
         else name2[j++]=c;
      }
      name2[j]='\0';
      strcat(name2,".test");
   }

   i=0; j=0;
   if(name3[0]=='\0') {
      while((c=name1[i++])!='\0') {
         if(c=='/') j=0;
         else if(c=='.') break;
         else name3[j++]=c;
      }
      name3[j]='\0';
      strcat(name3,".log");
   }

   if((test = fopen(name2,"w")) == NULL) {
      fprintf(stderr,"Fatal error: %s file open error\n",name2);
      exit(0);
   }

   if(logmode=='y') 
      if((logfile = fopen(name3,"w")) == NULL) {
	 fprintf(stderr,"Fatal error: %s file open error\n",name3);
	 exit(0);
      }

#ifdef DEBUG
   fprintf(stderr,"##########################################################\n");
   fprintf(stderr,"Warning: Atalanta is compiled in debug mode.\n");
   fprintf(stderr,"Warning: This mode may create an incorrect result or a wrong output file.\n");
   fprintf(stderr,"Warning: To avoid it, please comment out DEBUG flag in \"define.h\",\n");
   fprintf(stderr,"Warning: and recompile the program.\n");
   fprintf(stderr,"##########################################################\n");
#else
   if(logmode=='y') print_log_topic(logfile,cctname);
#endif

#ifdef ISCAS85_NETLIST_MODE
   if(cctmode==ISCAS85 && faultmode=='f') {
      fprintf(stderr,"Fatal error in options:\n");
      fprintf(stderr,"The option -f can not combined with the option -I.\n");
      exit(0);
   }
#endif

   if(faultmode=='f')
      if((faultfile = fopen(faultname,"r")) == NULL) {
	 fprintf(stderr,"Fatal error: %s file open error\n",faultname);
	 exit(0);
      }

   iseed=Seed(iseed);

   gettime(&minutes,&seconds,&runtime1);
   starttime=runtime1;

   /**************************************************************
    *                                                            *
    *          step 1: preprocess ---                            *
    *                  construction of data structures           *
    *                                                            *
    **************************************************************/

   if(read_circuit(circuit,cctname) < 0) fatalerror(CIRCUITERROR);
   fclose(circuit);

   if(nog<=0 || nopi<=0 || nopo<=0) {
      fprintf(stderr,"Error: #pi=%d, #po=%d, #gate=%d\n",nopi,nopo,nog);
      fatalerror(CIRCUITERROR);
   }
   if(noff > 0) {
      fprintf(stderr,"Error: %d flip-flop exists in the circuit.\n",noff);
      fatalerror(CIRCUITERROR);
   }
   nodummy=add_PO();

   if(cctmode==ISCAS89) {
      ALLOCATE(stack.list,GATEPTR,nog+10);
      clear(stack);

#ifdef INCLUDE_HOPE
      allocate_stacks();
      maxlevel=compute_level();
      allocate_event_list();
      levelize();
      add_sparegates();
      lastgate=nog-1;

      i=SetFFR();
      j=SetDominator();
#else
      if(levelize(net,nog,nopi,nopo,noff,stack.list) <0) {      
         fprintf(stderr,"Fatal error: Invalid circuit file.\n");
         exit(0);
      }
#endif

      if(noff > 0) {
         fprintf(stderr,"Error: Invalid type DFF is defined.\n");
         exit(0);
      }
   } else stack.list=NULL;

   maxlevel=set_cct_parameters(nog,nopi);

#ifdef INCLUDE_HOPE
   LEVEL=maxlevel+2;
#else
   LEVEL=maxlevel;
#endif

   if(_MODE_SIM=='f') { /* FSIM */
      if(!allocate_dynamic_buffers(nog)) {
         fprintf(stderr,"Fatal error: memory allocation error\n");
         exit(0);
      }

      nstem=0;
      for(i=0;i<nog;i++)
         if(is_fanout(net[i]) || net[i]->fn==PO) nstem++;
      stem=(GATEPTR *)malloc((unsigned)(sizeof(GATEPTR)*nstem));
      setfanoutstem(nog,stem,nstem);

      nof = (faultmode=='f') ?
            readfaults(faultfile,nog,nstem,stem) :
	    set_all_fault_list(nog,nstem,stem);
   }

#ifdef INCLUDE_HOPE
   else { /* HOPE */
      if(faultmode=='d') FWD_faults();
      else readfaults_hope(faultfile);
   }
#endif

   if(nof<0) {
      fprintf(stderr,"Fatal error: error in setting fault list\n");
      exit(0);
   }

   set_testability(nog);

   for(i=0;i<nog;i++) {
      reset(net[i]->changed);
      net[i]->freach=nog;
      if(net[i]->dpi>=PPOlevel)
         printf("Error: gut=%s dpi=%d\n",net[i]->symbol->symbol, net[i]->dpi);

   }
   set_dominator(nog,LEVEL);
   set_unique_path(nog,LEVEL);

   print_test_topic(test,nopi,nopo,name1);
   if(learnmode=='y') learn(nog,LEVEL);

   for(i=0;i<nof;i++) {
      faultlist[i]->detected=UNDETECTED;
      faultlist[i]->observe=ALL0;
   }

   if(_MODE_SIM=='f') {
      nredundant=check_redundant_faults(nog);
      pinit_simulation(nog,LEVEL,nopi);
   } else {
     InitFaultSim();
   }

   maxdetect=nof;

   all_one=ALL1;

   gettime(&minutes,&seconds,&runtime2);
   inittime=runtime2-runtime1;
   runtime1=runtime2;
   simtime1=0.0;

   /*****************************************************************
    *                                                               *
    *         step 2: Random pattern testing session                *
    *              1. generate 32 random patterns                   *
    *              2. fault free simulation                         *
    *              3. fault simulation                              *
    *              4. fault dropping                                *
    *                                                               *
    *****************************************************************/

   if(is_random_mode(rptmode)) {

      ndetect=random_sim(nog,nopi,nopo,LEVEL,nstem,stem,LFSR,randomlimit,
	          maxbits,maxdetect,&ntest,&npacket,&nbit,test);

      ntest1=ntest;
      gettime(&minutes,&seconds,&runtime2);
      simtime1=runtime2-runtime1;
      runtime1=runtime2;
   }

   /******************************************************************
    *                                                                *
    *    step 3: Deterministic Test Pattern Generation Session       *
    *            (fan with unique path sensitization                 *
    *                                                                *
    ******************************************************************/
   reset(phase2);
   fantime=0;
   ndetect+=testgen(nog,nopi,nopo,LEVEL,maxbits,nstem,stem,maxbacktrack,
	            phase2,&nredundant,&noverbacktrack,&tbacktrack,
	            &ntest,&npacket,&nbit,&fantime,test);
   ntest2=ntest;

   /******************************************************************
    *                                                                *
    *    step 4: Deterministic Test Pattern Generation Session       *
    *            Phase 2: Employs dynamic unique path sensitization  *
    *                                                                *
    ******************************************************************/

   state=NO_TEST; 
   if(maxbacktrack1>0 && nof-ndetect-nredundant>0) {
      set(phase2);
      for(i=0;i<nof;i++) {
         f=faultlist[i];
         if(f->detected==PROCESSED) { f->detected=UNDETECTED; }
      }
      fan1time=0;
      ndetect+=testgen(nog,nopi,nopo,LEVEL,maxbits,nstem,stem,maxbacktrack1,
                       phase2,&nredundant,&noverbacktrack,&tbacktrack,
	               &ntest,&npacket,&nbit,&fan1time,test);
      fantime+=fan1time;
   }
 
   ntest2=ntest;
   gettime(&minutes,&seconds,&runtime2);
   simtime2=runtime2-fantime-runtime1;
   runtime1=runtime2;

 
   /********************************************************************
    *                                                                  *
    *       step 5: Test compaction session                            *
    *               32-bit reverse fault simulation                    *
    *               + shuffling compaction   	                       *
    *                                                                  *
    ********************************************************************/

   if(ntest==0) {
      ntest3=0;
      ndetect3=0;
   } else if(compact=='n') {
      ntest3=ntest;
      ndetect3=ndetect;
   } else {
      if(maxcompact==0) compact='r';
      ntest3=
         compact_test(nog,nopi,nopo,LEVEL,nstem,stem,nof,&shuf,&ndetect3,npacket,nbit,maxbits,test);
      if(ndetect3 != ndetect) {
         printf("Error in test compaction: ndetect=%d, ndetect3=%d\n",ndetect,ndetect3);
         exit(0);
      }
   }

   gettime(&minutes,&seconds,&runtime2);
   simtime3=runtime2-runtime1;
   runtime1=runtime2;
   msize = (int)sbrk(0)/1000;

   /* print out the results */
   print_atpg_head(stdout);
   print_atpg_result(stdout,cctname,nog,nopi,nopo,LEVEL,
		     maxbacktrack,maxbacktrack1,phase2,ntest2,ntest3,nof,ndetect,
		     nredundant,tbacktrack,shuf,inittime,
		     simtime1+simtime2+simtime3,fantime,runtime2-starttime,'n',msize);

#ifndef DEBUG
   if(logmode=='y') {
      fprintf(logfile,"\nEnd of test pattern generation.\n\n");
      print_atpg_head(logfile);
      print_atpg_result(logfile,cctname,nog,nopi,nopo,LEVEL,
		     maxbacktrack,maxbacktrack1,phase2,ntest2,ntest3,nof,ndetect,
		     nredundant,tbacktrack,shuf,inittime,
		     simtime1+simtime2+simtime3,fantime,runtime2-starttime,'y',msize);
   }
#endif

   if(ufaultmode=='y') {
      if((rfaultmode=='y' && ndetect<nof) ||
         (rfaultmode=='n' && ndetect+nredundant<nof)) {
         i=j=0;
         if(nameufaults[0]=='\0') {
            while((c=name1[i++])!='\0') {
               if(c=='/') j=0;
               else if(c=='.') break;
               else nameufaults[j++]=c;
            }
            nameufaults[j]='\0';
            strcat(nameufaults,".ufaults");
         }
         if((ufaultfile = fopen(nameufaults,"r")) != NULL) {
            fprintf(stderr,"Warning: %s file already exists in the run directory\n" ,nameufaults);
            fprintf(stderr,"Warning: The undetected fault list file is not created.\n");
         } else {
            if((ufaultfile = fopen(nameufaults,"w")) == NULL) {
               fprintf(stderr,"Fatal error: %s file open error\n",nameufaults);
               exit(0);
            }
            print_undetected_faults(ufaultfile,'s',rfaultmode,0);
         }
         fclose(ufaultfile);
      }
   }

   fclose(test);
   if(logmode=='y') fclose(logfile);
}


int read_option(option,array,i,n)
char option,*array[];
int i,n;
{
   if(i+1 >= n) return((-1));

   switch(option) {
      case 'd': inputmode='d'; break;
#ifdef ISCAS85_NETLIST_MODE
      case 'I': cctmode=ISCAS85; break;
#endif
      case 'r': sscanf(array[++i],"%d",&randomlimit);
	        if(randomlimit==0) rptmode='n'; break;
      case 's': sscanf(array[++i],"%d",&iseed); break;
      case 'N': compact='n'; maxcompact=0; break;
      case 'c': sscanf(array[++i],"%d",&maxcompact); break;
      case 'b': sscanf(array[++i],"%d",&maxbacktrack); break;
      case 'B': sscanf(array[++i],"%d",&maxbacktrack1); break;
      case 't': strcpy(name2,array[++i]); break;
      case 'l': logmode='y'; strcpy(name3,array[++i]); break;
      case 'n': strcpy(name1,array[++i]); break;
      case 'h': helpmode=*(array[++i]); break;
      case 'L': learnmode='y'; break;
      case 'f': faultmode='f'; strcpy(faultname,array[++i]); break;
      case 'H': _MODE_SIM='h'; break;
      case '0': fillmode='0'; break;
      case '1': fillmode='1'; break;
      case 'X': fillmode='x'; break;
      case 'R': fillmode='r'; break;
      case 'A': gen_all_pat='y'; break;
      case 'D': sscanf(array[++i],"%d",&ntest_each_limit);
                gen_all_pat='y'; break;
      case 'Z': no_faultsim='y'; break;
      case 'u': ufaultmode='y'; break;
      case 'U': ufaultmode='y'; strcpy(nameufaults,array[++i]); break;
      case 'v': ufaultmode='y'; rfaultmode='y'; break;
      default:  i=(-1);
   }
   return(i);
}

int option_set(argc,argv)
int argc; char *argv[];
{
   int i;

   if(argc==1) {
      helpmode='d';
   } else 
      for(i=1;i<argc;i++) {
         if(argv[i][0]=='-') {
            if((i=read_option(argv[i][1],argv,i,argc))<0)
	       { helpmode='d'; break; }
	 }
	 else strcpy(name1,argv[i]);
      }

   if(helpmode!='q') { help(helpmode); exit(0); }
   if(fillmode=='x') _MODE_SIM='h';
   if(gen_all_pat=='y') {
      randomlimit=0;
      rptmode='n';
      maxbacktrack1=0;
      fillmode='x';
      compact='n';
      maxcompact=0;
      _MODE_SIM='h';
      no_faultsim='y';
   }

   if(no_faultsim=='y') {
      randomlimit=0;
      rptmode='n';
      fillmode='x';
      compact='n';
      maxcompact=0;
      _MODE_SIM='h';
   }
}

