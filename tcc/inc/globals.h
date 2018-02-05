#ifndef GLOBALS_H
#define GLOBALS_H

#define EPS 0.000001

#include <stdio.h>
#include <stdlib.h>

int N, NA;  // number of particles
int ISNOTCUBIC; //if the system in non-cubic or NPT, get box size info from a datafile
int FRAMES; // frames to read from input xmol file
int STARTFROM;  // start reading from this frame in the xmol file
int SAMPLEFREQ; // frequency at which to take frames from the xmol file
int TOTALFRAMES;
double TSTART;
double FRAMETSTEP;
double TFINAL;

char fInputParamsName[1000];    // name of parameters file and r... coordinates file and memsize file
char *fXmolName, *fBoxSizeName; //Name of xyz file, name of file which contains info on box
double *x, *y, *z;  // positions in x y and z directions of N particles
int *rtype; // particle type
double side, halfSide;  // box side length
double sidex, sidey, sidez, halfSidex, halfSidey, halfSidez; //NPT_FIX
double tiltxy,tiltxz,tiltyz;


double rcutAA,rcutAA2,rcutAB,rcutAB2,rcutBB,rcutBB2;    // diameters of AB and BB interactions for binary interactions
double fc;  // Voronoi adjustment parameter
int Vor;    // 0 use simple bond length method Bonds_GetBonds(), 1 use Voronoi method Bonds_GetBondsV()
int PBCs;   // 0 do not impliment periodic boundary conditions, 1 implement periodic boundary conditions
int nB; // max number of bonds per particle
int USELIST;    // 0  do not use cell list, 1 use cell list
int doWriteBonds;   // write bonds files out

int doWriteClus;    // write out indices of each detected cluster
int doWriteRaw; // write raw_*** cluster xmol files out
int do11AcenXmol; // write centres of 11A   
int do13AcenXmol; // write centres of 13A   
int doWritePopPerFrame; // write pop_per_frame file

int initNoStatic;   // initial size of static cluster arrays
int incrStatic; // when full, increment static cluster arrays by this amount
int initNoClustPerPart; // initial size of clusters per part arrays
int incrClustPerPart;   // when full, increment cluster per part arrays by this amount

int doSubClusts; // write sub clusters in tcc files
int PRINTINFO; // print running information about progress

int *cnb; // Current Number of Bonds for particles {1,...,N}
int **bNums;    // list of particles (indices j) bonded to particle at index i
double **bondlengths;   // length of bonds in the bond network and squared
int maxnb; // max number of bonds to one particle
int correctedBonds; // max number of bonds to one particle

int M, ncells;   // number of cells per box length, total number of cells
int *head;   // head of cell array
int *llist; // linked list array
int *map; // list of neighbouring cells for cell i
double cellSide, invcellSide;

int dosp3, dosp3a, dosp3b, dosp3c;
int dosp4, dosp4a, dosp4b, dosp4c;
int dosp5, dosp5a, dosp5b, dosp5c;
int do6Z, do7K, do8A, do8B, do8K, do9A, do9B, do9K, do10A, do10B, do10K, do10W;
int do11A, do11B, do11C, do11E, do11F, do11W, do12A, do12B, do12D, do12E, do12K;
int do13A, do13B, do13K, doFCC, doHCP, doBCC9, doBCC15;

int *nsp3, *nsp3a, *nsp3b, *nsp3c;  // number of sp3a/b/c respectively
int *nsp4, *nsp4a, *nsp4b, *nsp4c;  // number of sp4a/b/c respectively
int *n6A;
int *nsp5, *nsp5a, *nsp5b, *nsp5c;  // number of sp5a/b/c respectively
int *n6Z, *n7K; // number of clusters of particlar type
int *n8A, *n8B, *n8K;   
int *n9A, *n9B, *n9K;
int *n10A, *n10B, *n10K, *n10W;
int *n11A, *n11B, *n11C, *n11E, *n11F, *n11W;   // number of clusters of particlar type
int *n12A, *n12B, *n12D, *n12E, *n12K;
int *n13A, *n13B, *n13K;
int *nFCC, *nHCP, *nBCC_9, *nBCC_15;

int maxto3, maxto4, maxto5; // max number of bonds to one particle
int totNclus; // total number of particles identified in clusters

int *nsp3c_spindlebonds, *nsp4c_spindlebonds, *n6A_spindlebonds, *nsp5c_spindlebonds;
int *nsp3_excess_spindles, *nsp4_excess_spindles, *nsp5_excess_spindles;    // number of sp3a/b/c _excess_spindlesed basic clusters

int msp3, msp3a, msp3b, msp3c;  // max size of **sp** arrays in dimension i
int msp4, msp4a, msp4b, msp4c, m6A; // max size of **sp** arrays in dimension i
int msp5, msp5a, msp5b, msp5c;  // max size of **sp** arrays in dimension i
int m6Z, m7K;   // max size of m** arrays in dimension i
int m8A, m8B, m8K;  // max size of m** arrays in dimension i
int m9A, m9B, m9K;  // max size of m** arrays in dimension i
int m10A, m10B, m10K, m10W; // max size of m** arrays in dimension i
int m11A, m11B, m11C, m11E, m11F, m11W; // max size of m** arrays in dimension i
int m12A, m12B, m12D, m12E, m12K;   // max size of m** arrays in dimension i
int m13A, m13B, m13K;   // max size of m** arrays in dimension i
int mFCC, mHCP, mBCC_9, mBCC_15;    // max size of **sp** arrays in dimension i

int **sp3a, **sp3b, **sp3c; // sp3a/b/c arrays (index i denotes number of cluster, j lists particles in cluster)
int **sp4a, **sp4b, **sp4c; // sp5a/b/c arrays (index i denotes number of cluster, j lists particles in cluster)
int **hc6A;
int **sp5a, **sp5b, **sp5c; // sp6a/b/c arrays (index i denotes number of cluster, j lists particles in cluster)
int **hc6Z, **hc7K; // cluster storage arrays (index i denotes number/identifier of cluster, j lists particles in cluster)
int **hc8A, **hc8B, **hc8K;
int **hc9A, **hc9B, **hc9K;
int **hc10A, **hc10B, **hc10K, **hc10W;
int **hc11A, **hc11B, **hc11C, **hc11E, **hc11F, **hc11W;  // cluster storage arrays (index i denotes number/identifier of cluster, j lists particles in cluster)
int **hc12A, **hc12B, **hc12D, **hc12E, **hc12K;
int **hc13A, **hc13B, **hc13K;
int **hcFCC, **hcHCP, **hcBCC_9, **hcBCC_15;

int **mem_sp3b, *nmem_sp3b, mmem_sp3b;
int **mem_sp3c, *nmem_sp3c, mmem_sp3c;
int **mem_sp4b, *nmem_sp4b, mmem_sp4b;
int **mem_sp4c, *nmem_sp4c, mmem_sp4c;
int **mem_sp5b, *nmem_sp5b, mmem_sp5b;
int **mem_sp5c, *nmem_sp5c, mmem_sp5c;

char *ssp3, *ssp3a, *ssp3b, *s5A;
char *ssp4, *ssp4a, *ssp4b, *s6A;
char *ssp5, *ssp5a, *ssp5b, *s7A;
char *s6Z, *s7K;
char *s8A, *s8B, *s8K;
char *s9A, *s9B, *s9K;
char *s10A, *s10B, *s10K, *s10W;
char *s11A, *s11B, *s11C, *s11E, *s11F, *s11W;
char *s12A, *s12B, *s12D, *s12E, *s12K;
char *s13A, *s13B, *s13K;
char*sFCC, *sHCP, *sBCC_9, *sBCC_15;

char *s9B_cen, *s9K_cen;
char *s10B_cen, *s10K_cen, *s10W_cen;
char *s11A_cen, *s11B_cen, *s11C_cen, *s11W_cen;
char *s12A_cen, *s12B_cen, *s12K_cen;
char *s13A_cen, *s13B_cen, *s13K_cen;
char *sFCC_cen, *sHCP_cen, *sBCC_9_cen, *sBCC_15_cen;

char *s9B_shell, *s9K_shell;
char *s10B_shell, *s10K_shell, *s10W_shell;
char *s11A_shell, *s11B_shell, *s11C_shell, *s11W_shell;
char *s12A_shell, *s12B_shell, *s12K_shell;
char *s13A_shell, *s13B_shell, *s13K_shell;
char *sFCC_shell, *sHCP_shell, *sBCC_9_shell, *sBCC_15_shell;

double *pop_per_frame_sp3, *pop_per_frame_sp3a, *pop_per_frame_sp3b, *pop_per_frame_sp3c;
double *pop_per_frame_sp4, *pop_per_frame_sp4a, *pop_per_frame_sp4b, *pop_per_frame_6A;
double *pop_per_frame_sp5, *pop_per_frame_sp5a, *pop_per_frame_sp5b, *pop_per_frame_sp5c;
double *pop_per_frame_6Z, *pop_per_frame_7K;
double *pop_per_frame_8A, *pop_per_frame_8B, *pop_per_frame_8K;
double *pop_per_frame_9A, *pop_per_frame_9B, *pop_per_frame_9K;
double *pop_per_frame_10A, *pop_per_frame_10B, *pop_per_frame_10K, *pop_per_frame_10W;
double *pop_per_frame_11A, *pop_per_frame_11B, *pop_per_frame_11C, *pop_per_frame_11E, *pop_per_frame_11F, *pop_per_frame_11W;
double *pop_per_frame_12A, *pop_per_frame_12B, *pop_per_frame_12D, *pop_per_frame_12E, *pop_per_frame_12K;
double *pop_per_frame_13A, *pop_per_frame_13B, *pop_per_frame_13K;
double *pop_per_frame_FCC, *pop_per_frame_HCP, *pop_per_frame_BCC_9, *pop_per_frame_BCC_15;

double mean_pop_per_frame_sp3, mean_pop_per_frame_sp3a, mean_pop_per_frame_sp3b, mean_pop_per_frame_sp3c;
double mean_pop_per_frame_sp4, mean_pop_per_frame_sp4a, mean_pop_per_frame_sp4b, mean_pop_per_frame_6A;
double mean_pop_per_frame_sp5, mean_pop_per_frame_sp5a, mean_pop_per_frame_sp5b, mean_pop_per_frame_sp5c;
double mean_pop_per_frame_6Z, mean_pop_per_frame_7K;
double mean_pop_per_frame_8A, mean_pop_per_frame_8B, mean_pop_per_frame_8K;
double mean_pop_per_frame_9A, mean_pop_per_frame_9B, mean_pop_per_frame_9K;
double mean_pop_per_frame_10A, mean_pop_per_frame_10B, mean_pop_per_frame_10K, mean_pop_per_frame_10W;
double mean_pop_per_frame_11A, mean_pop_per_frame_11B, mean_pop_per_frame_11C, mean_pop_per_frame_11E, mean_pop_per_frame_11F, mean_pop_per_frame_11W;
double mean_pop_per_frame_12A, mean_pop_per_frame_12B, mean_pop_per_frame_12D, mean_pop_per_frame_12E, mean_pop_per_frame_12K;
double mean_pop_per_frame_13A, mean_pop_per_frame_13B, mean_pop_per_frame_13K;
double mean_pop_per_frame_FCC, mean_pop_per_frame_HCP, mean_pop_per_frame_BCC_9, mean_pop_per_frame_BCC_15;

int ngsp3, ngsp3a, ngsp3b, ng5A;
int ngsp4, ngsp4a, ngsp4b, ng6A;
int ngsp5, ngsp5a, ngsp5b, ng7A;
int ng6Z, ng7K;
int ng8A, ng8B, ng8K;
int ng9A, ng9B, ng9K;
int ng10A, ng10B, ng10K, ng10W;
int ng11A, ng11B, ng11C, ng11E, ng11F, ng11W;
int ng12A, ng12B, ng12D, ng12E, ng12K;
int ng13A, ng13B, ng13K;
int ngFCC, ngHCP, ngBCC_9, ngBCC_15;

int nn5A;
int nn6A, nn6Z, nn7K;
int nn7A;
int nn8A, nn8B, nn8K;
int nn9A, nn9B, nn9K;
int nn10A, nn10B, nn10K, nn10W;
int nn11A, nn11B, nn11C, nn11E, nn11F, nn11W;   // number of particles in clusers net
int nn12A, nn12B, nn12D, nn12E, nn12K;
int nn13A, nn13B, nn13K;
int nnFCC, nnHCP, nnBCC_9, nnBCC_15;

int ncsp3, ncsp3a, ncsp3b, nc5A;
int ncsp4, ncsp4a, ncsp4b, ncsp4c, nc6A;
int ncsp5, ncsp5a, ncsp5b, nc7A;    // total number of clusers
int nc6Z, nc7K;
int nc8A, nc8B, nc8K;
int nc9A, nc9B, nc9K;
int nc10A, nc10B, nc10K, nc10W;
int nc11A, nc11B, nc11C, nc11E, nc11F, nc11W;   // total number of clusers
int nc12A, nc12B, nc12D, nc12E, nc12K;
int nc13A, nc13B, nc13K;
int ncFCC, ncHCP, ncBCC_9, ncBCC_15;    // total number of clusers

int ncsp3_excess_spindles, ncsp4_excess_spindles, ncsp5_excess_spindles;    // total number of _excess_spindlesed basic clusters
int ncsp3c_spindlebonds, ncsp4c_spindlebonds, nc6A_spindlebonds, ncsp5c_spindlebonds;   // total number of spindle bonds

int *a5, *a6, *a7, *a8, *a9, *a10, *a11, *a12, *a13, *a15;

FILE *wsp3, *wsp3a, *wsp3b, *w5A;
FILE *wsp4, *wsp4a, *wsp4b, *wsp4c, *w6A, *w6Z, *w7K;
FILE *wsp5, *wsp5a, *wsp5b, *w7A;
FILE *w8A, *w8B, *w8K;
FILE *w9A, *w9B, *w9K;
FILE *w10A, *w10B, *w10K, *w10W;
FILE *w11A, *w11B, *w11C, *w11E, *w11F, *w11W;
FILE *w12A, *w12B, *w12D, *w12E, *w12K;
FILE *w13A, *w13B, *w13K;
FILE *wFCC, *wHCP, *wBCC_9, *wBCC_15;

FILE *bondsout;
FILE *fPopPerFrame;

FILE *file_raw_sp3, *file_raw_sp3a, *file_raw_sp3b, *file_raw_5A;
FILE *file_raw_sp4, *file_raw_sp4a, *file_raw_sp4b, *file_raw_6A;
FILE *file_raw_sp5, *file_raw_sp5a, *file_raw_sp5b, *file_raw_7A;
FILE *file_raw_6Z, *file_raw_7K;
FILE *file_raw_8A, *file_raw_8B, *file_raw_8K;  
FILE *file_raw_9A, *file_raw_9B, *file_raw_9K;
FILE *file_raw_10A, *file_raw_10B, *file_raw_10K, *file_raw_10W;
FILE *file_raw_11A, *file_raw_11B, *file_raw_11C, *file_raw_11E, *file_raw_11F, *file_raw_11W;
FILE *file_raw_12A, *file_raw_12B, *file_raw_12D, *file_raw_12E, *file_raw_12K;
FILE *file_raw_13A, *file_raw_13B, *file_raw_13K;
FILE *file_raw_FCC, *file_raw_HCP, *file_raw_BCC_9, *file_raw_BCC_15;

FILE *file_11A_cen_xmol;
FILE *file_13A_cen_xmol;

#endif 