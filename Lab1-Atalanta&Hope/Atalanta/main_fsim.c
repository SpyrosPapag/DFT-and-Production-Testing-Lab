
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
	fsim.c
	Main program for FSIM.
	FSIM performs fault simulation for combinational circuits.
	Test patterns can be read from a user supplied file or
	generated randomly.
	Collapses the equivalent faults and fault coverage is
	computed based on the collapsed fault set.
-----------------------------------------------------------------------*/
	
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <strings.h>

#include "parameter.h"
#include "define.h"
#include "macro.h"
#include "global.d"

#define DEFAULT_RLIMIT 224
#define is_random_mode(mode) (mode=='y')
#define is_fanout(gate) (gate->noutput>1)
#define output0	output

/* external functions */
extern void GetPRandompattern();
extern void pinit_simulation();
extern void pfault_free_simulation();
extern void printinputs(),print_log_topic(),printoutputs(),printfault();
char *strcpy(), *strcat();
extern void update_all(), update_all1();
extern void gettime();
extern void setfanoutstem();
extern void set_unique_path();
extern caddr_t sbrk();

/* default parameters setting */
char name1[100]="",name2[100]="",name3[100]="",commandfile[100];
char namecct[100]="";
char faultname[100]="";
char inputmode='d';		/* default mode */
char rptmode='y';		/* RPT mode ON */
char logmode='n';		/* LOG off */
char helpmode='q';              /* On-line help mode */
char cctmode=ISCAS89;           /* input circuit format */
int iseed=0;			/* initial random seed */
int randomlimit=DEFAULT_RLIMIT;	/* limit of random patterns */
int maxbit=BITSIZE;		/* number of bits for one operation */
char faultmode='d';
char compact;
int maxcompact;
int msize;
level LFSR[MAXPI];
FILE *faultfile;
int Group_Id;

/*
	main
	Main program of FSIM.
*/
main(argc,argv)
int argc; char *argv[];
{
   register int i, j;
   int nbit;
   int maxdpi,nstem,ndominator,LEVEL;
   int nof,ndetect,maxdetect,nredundant;
   int ntest;
   FAULTPTR f;
   GATEPTR *stem;
   int fault_profile[BITSIZE];
   double inittime,runtime;
   double runtime1,minutes,seconds;
   double coverage;
   char c;

   nbit=maxbit;
   update_flag=FALSE;
   update_flag2=FALSE;

/********************************************************************
 *                                                                  *
 *                  preprocess ---                                  *
 *                  input and output file interface                 *
 *                                                                  *
 ********************************************************************/

   if(argc==1) {
      helpmode='d';
   }
   else for(i=1;i<argc;i++) {
           if(argv[i][0]=='-') {
	      if((i=option_set(argv[i][1],argv,i,argc))<0) {
                 helpmode='d'; break;
	   }}
	   else strcpy(name1,argv[i]);
        }

   if(helpmode!='q') { help(helpmode); exit(0); }

   if((circuit = fopen(name1,"r")) == NULL) {
      fprintf(stderr,"Fatal error: no such file exists %s\n",name1);
      exit(0);
   }

   strcpy(namecct,name1);

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

   if(rptmode=='n') if((test = fopen(name2,"r")) == NULL) {
      fprintf(stderr,"Fatal error: %s file open error\n",name2);
      exit(0);
   }

   if(logmode=='y') 
      if((logfile = fopen(name3,"w")) == NULL) {
	 fprintf(stderr,"Fatal error: %s file open error\n",name3);
	 exit(0);
      }
/*
   if(logmode=='y') print_log_topic(logfile,namecct);
*/

   if(cctmode==ISCAS85 && faultmode=='f') {
      fprintf(stderr,"Fatal error in options:\n");
      fprintf(stderr,"The option -f can not combined with the option -I.\n");
      exit(0);
   }

   if(faultmode=='f')
      if((faultfile = fopen(faultname,"r")) == NULL) {
         fprintf(stderr,"Fatal error: %s file open error\n",faultname);
         exit(0);
      }

   if(rptmode=='y') iseed=Seed(iseed);

   gettime(&minutes,&seconds,&runtime1);

/*****************************************************************
 *                                                               *
 *                  preprocess ---                               *
 *                  construction of data structures              *
 *                                                               *
 *****************************************************************/

   if(cctmode==ISCAS89) {
      if(read_circuit(circuit,namecct) <0) {
         fprintf(stderr,"Fatal error: Invalid circuit file.\n");
         exit(0);
      }
   }

#ifdef ISCAS85_NETLIST_MODE
   else if(!circin(&nog,&nopi,&nopo)) {
      fprintf(stderr,"Fatal error: Invalid circuit file\n");
      exit(0);
   }
#endif

   fclose(circuit);
   nodummy=add_PO();

   if(nog<=0 || nopi<=0 || nopo<=0) {
      fprintf(stderr,"Fatal error: Invalid circuit file\n");
      exit(0);
   }
 
   if(cctmode==ISCAS89) {
      ALLOCATE(stack.list,GATEPTR,nog);
      clear(stack);

#ifdef INCLUDE_HOPE
      allocate_stacks();
      maxdpi=compute_level();
      allocate_event_list();
      levelize();
      lastgate=nog-1;
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

#ifdef INCLUDE_HOPE
   set_cct_parameters(nog,nopi);
   maxdpi=POlevel+1;
#else
   maxdpi=set_cct_parameters(nog,nopi);
#endif

   if(!allocate_dynamic_buffers(nog)) {
      fprintf(stderr,"Fatal error: memory allocation error\n");
      exit(0);
   }

   nstem=0;
   for(i=0; i<nog; i++)
      if(net[i]->noutput != 1) nstem++;
   stem=(GATEPTR *)malloc((unsigned)((sizeof(GATEPTR))*nstem));
   setfanoutstem(nog,stem,nstem);

   nof = (faultmode=='f') ?
         readfaults(faultfile,nog,nstem,stem) :
         set_all_fault_list(nog,nstem,stem);

   if(nof<0) {
      fprintf(stderr,"Fatal error: error in setting fault list\n");
      exit(0);
   }

   for(i=0;i<nog;i++) {
      reset(net[i]->changed);
      net[i]->freach=nog;
   }
   ndominator=set_dominator(nog,maxdpi);
   set_unique_path(nog,maxdpi);

/*****************************************************************
 *                                                               *
 *                 Initialization of circuit parameters          *
 *                                                               *
 *****************************************************************/

   for(i=0;i<nof;i++) {
      faultlist[i]->detected=UNDETECTED;
      faultlist[i]->observe=ALL0;
   }

   nredundant=check_redundant_faults(nog);

   pinit_simulation(nog,maxdpi,nopi);
   ntest=0;
   ndetect=0;
   maxdetect=nof;

   all_one= (maxbit==BITSIZE) ? ALL1 : ~(ALL1<<maxbit);

   gettime(&minutes,&seconds,&runtime1);
   inittime=runtime1;

/*******************************************************************
*                                                                  *
*		Main loop for the fault simulaiton.                *
*		1. Read test patterns.                             *
*		2. Fault free simulation.                          *
*		3. Fault Simulation.				   *
*		4. Update flags.				   *
*                                                                  *
********************************************************************/

   while(ntest<randomlimit) {

      /* Get a test pattern */
      if(rptmode=='y') GetPRandompattern(nopi,LFSR);
      else {
	 if((nbit=pget_test(test,LFSR,nopi,maxbit))==0) break;
	 all_one=(nbit==BITSIZE) ? ALL1 : ~(ALL1<<nbit);
      }

      /* fault free simulation */
      for(i=0;i<nopi;i++)
	 net[i]->output1=net[i]->output0=LFSR[i];

      pfault_free_simulation();

      /* fault simulation */
      for(i=0;i<nbit;i++) fault_profile[i]=0;
      ndetect +=
	 Fault1_Simulation(nog,maxdpi,nopi,nopo,nstem,stem,nbit,fault_profile);
      ntest+=nbit;

      if(logmode=='y') {
	 ntest-=nbit;
	 for(i=nbit-1;i>=0;i--) {
	    fprintf(logfile,"test %4d: ",++ntest);
	    printinputs(logfile,nopi,i);
	    fprintf(logfile," ");
	    printoutputs(logfile,nopo,i);
	    fprintf(logfile," %4d faults detected",fault_profile[i]);

	    fprintf(logfile,"\n");
	 }
      }

      if(ndetect>=maxdetect) break;

      /* dynamic scheduling of network flags */
      for(i=0;i<=nsstack;i++) dynamic_stack[i]->cobserve=ALL0;
      if(update_flag) {
	 if(logmode=='y') update_all1(nopi);
	 else update_all(nopi);
	 reset(update_flag);
      }
      else for(i=ndstack;i>nsstack;i--) dynamic_stack[i]->freach=0;
      ndstack=nsstack;
   }

   gettime(&minutes,&seconds,&runtime);
   coverage=(double)ndetect/(double)nof*100.00;
   msize = (int)sbrk(0)/1000;

   /* print out the results */
   print_sim_head(stdout);
   print_sim_result(stdout,namecct,nog,nopi,nopo,maxdpi,name2,
      ntest,nof,ndetect,inittime,runtime-inittime,runtime,'n');
   if(logmode=='y') {
/*
      fprintf(logfile,"\nEnd of fault simulation.\n\n");
      print_sim_head(logfile);
      print_sim_result(logfile,namecct,nog,nopi,nopo,maxdpi,name2,
         ntest,nof,ndetect,inittime,runtime-inittime,runtime,'y');
*/
      fclose(logfile);
   }
 
   if(rptmode=='n') fclose(test);
}


int option_set(option,array,i,n)
char option,*array[];
register int i,n;
{
   if(i+1 >= n) return((-1));

   switch(option) {
      case 'd': inputmode='d'; break;
      case 'I': cctmode=ISCAS85; break;
      case 'r': sscanf(array[++i],"%d",&randomlimit); 
		if(randomlimit==0) randomlimit=DEFAULT_RLIMIT; break;
      case 's': sscanf(array[++i],"%d",&iseed); break;
      case 't': rptmode='n'; randomlimit=INFINITY;
		strcpy(name2,array[++i]); break;
      case 'l': logmode='y'; strcpy(name3,array[++i]); break;
      case 'n': strcpy(name1,array[++i]); break;
      case 'h': helpmode=*(array[++i]); break;
      case 'f': faultmode='f'; strcpy(faultname,array[++i]); break;
      default:  i=(-1);
   }
   return(i);
}

