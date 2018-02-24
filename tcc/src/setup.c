#include "setup.h"
#include "tools.h"
#include "iniparser.h"
#include "globals.h"


void Setup_Output_Files() {
    char output_file[200];
    FILE *file_pointer;
    int cluster_number;

    if(do11AcenXyz == 1) {
        make_directory("centers_output");
        for(cluster_number=0; cluster_number < num_cluster_types; cluster_number++) {
            if (*do_cluster_list[cluster_number] == 1) {
                sprintf(output_file, "centers_output/%s.rcAA%lg.rcAB%lg.rcBB%lg.Vor%d.fc%lg.PBCs%d.%s_cen.xyz",
                        fXmolName, rcutAA, rcutAB, rcutBB, Vor, fc, PBCs, cluster_names[24]);
                file_pointer = open_file(output_file, "w");
                fclose(file_pointer);
            }
        }
    }

    if(do13AcenXyz == 1) {
        make_directory("centers_output");
        for(cluster_number=0; cluster_number < num_cluster_types; cluster_number++) {
            if (*do_cluster_list[cluster_number] == 1) {
                sprintf(output_file, "centers_output/%s.rcAA%lg.rcAB%lg.rcBB%lg.Vor%d.fc%lg.PBCs%d.%s_cen.xyz",
                        fXmolName, rcutAA, rcutAB, rcutBB, Vor, fc, PBCs, cluster_names[35]);
                file_pointer = open_file(output_file, "w");
                fclose(file_pointer);
            }
        }
    }

    if(doWriteBonds == 1) {
        sprintf(output_file,"%s.rcAA%lg.rcAB%lg.rcBB%lg.Vor%d.fc%lg.PBCs%d.bonds",fXmolName,rcutAA,rcutAB,rcutBB,Vor,fc,PBCs);
        file_pointer=fopen(output_file, "w");
        fclose(file_pointer);
    }

    if(doWritePopPerFrame == 1) {
        sprintf(output_file,"%s.rcAA%lg.rcAB%lg.rcBB%lg.Vor%d.fc%lg.PBCs%d.pop_per_frame",fXmolName,rcutAA,rcutAB,rcutBB,Vor,fc,PBCs);
        file_pointer=fopen(output_file, "w");
        fclose(file_pointer);
    }

    if(doWriteRaw == 1) {
        make_directory("raw_output");
        for(cluster_number=0; cluster_number < num_cluster_types; cluster_number++) {
            if (*do_cluster_list[cluster_number] == 1) {
                sprintf(output_file, "raw_output/%s.rcAA%lg.rcAB%lg.rcBB%lg.Vor%d.fc%lg.PBCs%d.raw_%s",
                        fXmolName, rcutAA, rcutAB, rcutBB, Vor, fc, PBCs, cluster_names[cluster_number]);
                file_pointer = open_file(output_file, "w");
                fclose(file_pointer);
            }
        }
    }

    if(doWriteClus == 1) {
        make_directory("cluster_output");
        for(cluster_number=0; cluster_number < num_cluster_types; cluster_number++) {
            if (*do_cluster_list[cluster_number] == 1) {
                sprintf(output_file, "cluster_output/%s.rcAA%lg.rcAB%lg.rcBB%lg.Vor%d.fc%lg.PBCs%d.clusts_%s",
                        fXmolName, rcutAA, rcutAB, rcutBB, Vor, fc, PBCs, cluster_names[cluster_number]);
                file_pointer = open_file(output_file, "w");
                fclose(file_pointer);
            }
        }
    }
}

void Setup_InitStaticVars() { // Initialize lots of important variables for static TCC algorithm
    int i, f, j;
    char errMsg[1000];

    dosp3=dosp3a=dosp3b=dosp3c=1;
    dosp4=dosp4a=dosp4b=dosp4c=1;
    dosp5=dosp5a=dosp5b=dosp5c=1;
    do6Z=do7K=do8A=do8B=do8K=do9A=do9B=do9K=do10A=do10B=do10K=do10W=1;
    do11A=do11B=do11C=do11E=do11F=do11W=do12A=do12B=do12D=do12E=do12K=1;
    do13A=do13B=do13K=doFCC=doHCP=doBCC9=1;
    doBCC15=0;
    
    msp3a=msp3b=msp3c=initNoStatic; // max size of **sp** arrays in dimension i
    msp4a=msp4b=msp4c=initNoStatic; // max size of **sp** arrays in dimension i
    msp5a=msp5b=msp5c=initNoStatic; // max size of **sp** arrays in dimension i
    m6Z=m7K=initNoStatic;   // max size of m** arrays in dimension i
    m8A=m8B=m8K=initNoStatic;   // max size of m** arrays in dimension i
    m9A=m9B=m9K=initNoStatic;   // max size of m** arrays in dimension i
    m10A=m10B=m10K=m10W=initNoStatic;   // max size of m** arrays in dimension i
    m11A=m11B=m11C=m11E=m11F=m11W=initNoStatic; // max size of m** arrays in dimension i
    m12A=m12B=m12D=m12E=m12K=initNoStatic;  // max size of m** arrays in dimension i
    m13A=m13B=m13K=initNoStatic;    // max size of m** arrays in dimension i
    mFCC=mHCP=mBCC_9=mBCC_15=initNoStatic;  // max size of **sp** arrays in dimension i

    mmem_sp3b=mmem_sp3c=mmem_sp4b=mmem_sp4c=mmem_sp5b=mmem_sp5c=initNoClustPerPart;
    
    mean_pop_per_frame = malloc(num_cluster_types*sizeof(double));
    for(i=0; i<num_cluster_types; i++) {
        mean_pop_per_frame[i] = 0.0;
    }

    x = malloc(N*sizeof(double));   if (x==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): x[] malloc out of memory\n");    Error_no_free(errMsg); }    // positions of particles in a configuration
    y = malloc(N*sizeof(double));   if (y==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): y[] malloc out of memory\n");    Error_no_free(errMsg); }
    z = malloc(N*sizeof(double));   if (z==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): z[] malloc out of memory\n");    Error_no_free(errMsg); }
    
    particle_type=malloc(N*sizeof(int)); if (particle_type==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): particle_type[] malloc out of memory\n");   Error_no_free(errMsg); }    // type of species

    cnb = malloc(N*sizeof(int));    if (cnb==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): cnb[] malloc out of memory\n");    Error_no_free(errMsg); }    // number of "bonded" neighbours of a particle

    bNums = malloc(N*sizeof(int *));    if (bNums==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): bNums[] malloc out of memory\n");    Error_no_free(errMsg); }    // list of bonded particles to each particle
    for (j=0; j<N; ++j) { bNums[j] = malloc(nB*sizeof(int));    if (bNums[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): bNums[][] malloc out of memory\n");   Error_no_free(errMsg); } }

    bondlengths = malloc(N*sizeof(double *));   if (bondlengths==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): bondlengths[] malloc out of memory\n");    Error_no_free(errMsg); }    // array of bond lengths
    for (j=0; j<N; ++j) { bondlengths[j] = malloc(nB*sizeof(double));   if (bondlengths[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): bondlengths[][] malloc out of memory\n");   Error_no_free(errMsg); } }  
    

    // arrays for the clusters found in each frame
    hcsp3a = malloc(msp3a*sizeof(int *)); if (hcsp3a==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): sp3a[] malloc out of memory\n");  Error_no_free(errMsg); }
    for (j=0; j<msp3a; ++j) { hcsp3a[j] = malloc(3*sizeof(int));  if (hcsp3a[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): sp3a[][] malloc out of memory\n"); Error_no_free(errMsg); } }
    hcsp3b = malloc(msp3b*sizeof(int *)); if (hcsp3b==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): sp3b[] malloc out of memory\n");  Error_no_free(errMsg); }
    for (j=0; j<msp3b; ++j) { hcsp3b[j] = malloc(4*sizeof(int));  if (hcsp3b[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): sp3b[][] malloc out of memory\n"); Error_no_free(errMsg); } }
    hcsp3c = malloc(msp3c*sizeof(int *)); if (hcsp3c==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): sp3c[] malloc out of memory\n");  Error_no_free(errMsg); }
    for (j=0; j<msp3c; ++j) { hcsp3c[j] = malloc(5*sizeof(int));  if (hcsp3c[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): sp3c[][] malloc out of memory\n"); Error_no_free(errMsg); } }
    hcsp4a = malloc(msp4a*sizeof(int *)); if (hcsp4a==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): sp4a[] malloc out of memory\n");  Error_no_free(errMsg); }
    for (j=0; j<msp4a; ++j) { hcsp4a[j] = malloc(4*sizeof(int));  if (hcsp4a[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): sp4a[][] malloc out of memory\n"); Error_no_free(errMsg); } }
    hcsp4b = malloc(msp4b*sizeof(int *)); if (hcsp4b==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): sp4b[] malloc out of memory\n");  Error_no_free(errMsg); }
    for (j=0; j<msp4b; ++j) { hcsp4b[j] = malloc(5*sizeof(int));  if (hcsp4b[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): sp4b[][] malloc out of memory\n"); Error_no_free(errMsg); } }
    hcsp4c = malloc(msp4c*sizeof(int *)); if (hcsp4c==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): sp4c[] malloc out of memory\n");  Error_no_free(errMsg); }
    for (j=0; j<msp4c; ++j) { hcsp4c[j] = malloc(6*sizeof(int));  if (hcsp4c[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): sp4c[][] malloc out of memory\n"); Error_no_free(errMsg); } }
    hcsp5a = malloc(msp5a*sizeof(int *)); if (hcsp5a==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): sp5a[] malloc out of memory\n");  Error_no_free(errMsg); }
    for (j=0; j<msp5a; ++j) { hcsp5a[j] = malloc(5*sizeof(int));  if (hcsp5a[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): sp5a[][] malloc out of memory\n"); Error_no_free(errMsg); } }
    hcsp5b = malloc(msp5b*sizeof(int *)); if (hcsp5b==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): sp5b[] malloc out of memory\n");  Error_no_free(errMsg); }
    for (j=0; j<msp5b; ++j) { hcsp5b[j] = malloc(6*sizeof(int));  if (hcsp5b[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): sp5b[][] malloc out of memory\n"); Error_no_free(errMsg); } }
    hcsp5c = malloc(msp5c*sizeof(int *)); if (hcsp5c==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): sp5c[] malloc out of memory\n");  Error_no_free(errMsg); }
    for (j=0; j<msp5c; ++j) { hcsp5c[j] = malloc(7*sizeof(int));  if (hcsp5c[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): sp5c[][] malloc out of memory\n"); Error_no_free(errMsg); } }
    
    // arrays for the number of clusters of each type bonded to each particle
    mem_sp3b = malloc(N*sizeof(int *)); if (mem_sp3b==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): mem_sp3b[] malloc out of memory\n");  Error_no_free(errMsg); }
    for (j=0; j<N; ++j) { mem_sp3b[j] = malloc(mmem_sp3b*sizeof(int));  if (mem_sp3b[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): mem_sp3b[][] malloc out of memory\n"); Error_no_free(errMsg); } }
    nmem_sp3b = malloc(N*sizeof(int));  if (nmem_sp3b==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): nmem_sp3b[] malloc out of memory\n");    Error_no_free(errMsg); }
    mem_sp3c = malloc(N*sizeof(int *)); if (mem_sp3c==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): mem_sp3c[] malloc out of memory\n");  Error_no_free(errMsg); }
    for (j=0; j<N; ++j) { mem_sp3c[j] = malloc(mmem_sp3c*sizeof(int));  if (mem_sp3c[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): mem_sp3c[][] malloc out of memory\n"); Error_no_free(errMsg); } }
    nmem_sp3c = malloc(N*sizeof(int));  if (nmem_sp3c==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): nmem_sp3c[] malloc out of memory\n");    Error_no_free(errMsg); }
    mem_sp4b = malloc(N*sizeof(int *)); if (mem_sp4b==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): mem_sp4b[] malloc out of memory\n");  Error_no_free(errMsg); }
    for (j=0; j<N; ++j) { mem_sp4b[j] = malloc(mmem_sp4b*sizeof(int));  if (mem_sp4b[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): mem_sp4b[][] malloc out of memory\n"); Error_no_free(errMsg); } }
    nmem_sp4b = malloc(N*sizeof(int));  if (nmem_sp4b==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): nmem_sp4b[] malloc out of memory\n");    Error_no_free(errMsg); }
    mem_sp4c = malloc(N*sizeof(int *)); if (mem_sp4c==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): mem_sp4c[] malloc out of memory\n");  Error_no_free(errMsg); }
    for (j=0; j<N; ++j) { mem_sp4c[j] = malloc(mmem_sp4c*sizeof(int));  if (mem_sp4c[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): mem_sp4c[][] malloc out of memory\n"); Error_no_free(errMsg); } }
    nmem_sp4c = malloc(N*sizeof(int));  if (nmem_sp4c==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): nmem_sp4c[] malloc out of memory\n");    Error_no_free(errMsg); }
    mem_sp5b = malloc(N*sizeof(int *)); if (mem_sp5b==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): mem_sp5b[] malloc out of memory\n");  Error_no_free(errMsg); }
    for (j=0; j<N; ++j) { mem_sp5b[j] = malloc(mmem_sp5b*sizeof(int));  if (mem_sp5b[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): mem_sp5b[][] malloc out of memory\n"); Error_no_free(errMsg); } }
    nmem_sp5b = malloc(N*sizeof(int));  if (nmem_sp5b==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): nmem_sp5b[] malloc out of memory\n");    Error_no_free(errMsg); }
    mem_sp5c = malloc(N*sizeof(int *)); if (mem_sp5c==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): mem_sp5c[] malloc out of memory\n");  Error_no_free(errMsg); }
    for (j=0; j<N; ++j) { mem_sp5c[j] = malloc(mmem_sp5c*sizeof(int));  if (mem_sp5c[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): mem_sp5c[][] malloc out of memory\n"); Error_no_free(errMsg); } }
    nmem_sp5c = malloc(N*sizeof(int));  if (nmem_sp5c==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): nmem_sp5c[] malloc out of memory\n");    Error_no_free(errMsg); }

    // arrays for the clusters found in each frame
    hc6Z = malloc(m6Z*sizeof(int *));   if (hc6Z==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc6Z[] malloc out of memory\n");  Error_no_free(errMsg); }
    for (j=0; j<m6Z; ++j) { hc6Z[j] = malloc(6*sizeof(int));    if (hc6Z[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc6Z[][] malloc out of memory\n"); Error_no_free(errMsg); } }
    
    hc7K = malloc(m7K*sizeof(int *));   if (hc7K==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc7K[] malloc out of memory\n");  Error_no_free(errMsg); }
    for (j=0; j<m7K; ++j) { hc7K[j] = malloc(7*sizeof(int));    if (hc7K[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc7K[][] malloc out of memory\n"); Error_no_free(errMsg); } }
    
    hc8A = malloc(m8A*sizeof(int *));   if (hc8A==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc8A[] malloc out of memory\n");  Error_no_free(errMsg); }
    for (j=0; j<m8A; ++j) { hc8A[j] = malloc(8*sizeof(int));    if (hc8A[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc8A[][] malloc out of memory\n"); Error_no_free(errMsg); } }
    hc8B = malloc(m8B*sizeof(int *));   if (hc8B==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc8B[] malloc out of memory\n");  Error_no_free(errMsg); }
    for (j=0; j<m8B; ++j) { hc8B[j] = malloc(8*sizeof(int));    if (hc8B[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc8B[][] malloc out of memory\n"); Error_no_free(errMsg); } }
    hc8K = malloc(m8K*sizeof(int *));   if (hc8K==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc8K[] malloc out of memory\n");  Error_no_free(errMsg); }
    for (j=0; j<m8K; ++j) { hc8K[j] = malloc(8*sizeof(int));    if (hc8K[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc8K[][] malloc out of memory\n"); Error_no_free(errMsg); } }
    
    hc9A = malloc(m9A*sizeof(int *));   if (hc9A==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc9A[] malloc out of memory\n");  Error_no_free(errMsg); }
    for (j=0; j<m9A; ++j) { hc9A[j] = malloc(9*sizeof(int));    if (hc9A[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc9A[][] malloc out of memory\n"); Error_no_free(errMsg); } }
    hc9B = malloc(m9B*sizeof(int *));   if (hc9B==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc9B[] malloc out of memory\n");  Error_no_free(errMsg); }
    for (j=0; j<m9B; ++j) { hc9B[j] = malloc(9*sizeof(int));    if (hc9B[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc9B[][] malloc out of memory\n"); Error_no_free(errMsg); } }
    hc9K = malloc(m9K*sizeof(int *));   if (hc9K==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc9K[] malloc out of memory\n");  Error_no_free(errMsg); }
    for (j=0; j<m9K; ++j) { hc9K[j] = malloc(9*sizeof(int));    if (hc9K[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc9K[][] malloc out of memory\n"); Error_no_free(errMsg); } }
    
    hc10A = malloc(m10A*sizeof(int *)); if (hc10A==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc10A[] malloc out of memory\n");    Error_no_free(errMsg); }
    for (j=0; j<m10A; ++j) { hc10A[j] = malloc(10*sizeof(int)); if (hc10A[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc10A[][] malloc out of memory\n");   Error_no_free(errMsg); } }
    hc10B = malloc(m10B*sizeof(int *)); if (hc10B==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc10B[] malloc out of memory\n");    Error_no_free(errMsg); }
    for (j=0; j<m10B; ++j) { hc10B[j] = malloc(10*sizeof(int)); if (hc10B[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc10B[][] malloc out of memory\n");   Error_no_free(errMsg); } }
    hc10K = malloc(m10K*sizeof(int *)); if (hc10K==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc10K[] malloc out of memory\n");    Error_no_free(errMsg); }
    for (j=0; j<m10K; ++j) { hc10K[j] = malloc(10*sizeof(int)); if (hc10K[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc10K[][] malloc out of memory\n");   Error_no_free(errMsg); } }
    hc10W = malloc(m10W*sizeof(int *)); if (hc10W==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc10W[] malloc out of memory\n");    Error_no_free(errMsg); }
    for (j=0; j<m10W; ++j) { hc10W[j] = malloc(10*sizeof(int)); if (hc10W[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc10W[][] malloc out of memory\n");   Error_no_free(errMsg); } }
    
    hc11A = malloc(m11A*sizeof(int *)); if (hc11A==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc11A[] malloc out of memory\n");    Error_no_free(errMsg); }
    for (j=0; j<m11A; ++j) { hc11A[j] = malloc(11*sizeof(int)); if (hc11A[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc11A[][] malloc out of memory\n");   Error_no_free(errMsg); } }
    hc11B = malloc(m11B*sizeof(int *)); if (hc11B==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc11B[] malloc out of memory\n");    Error_no_free(errMsg); }
    for (j=0; j<m11B; ++j) { hc11B[j] = malloc(11*sizeof(int)); if (hc11B[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc11B[][] malloc out of memory\n");   Error_no_free(errMsg); } }
    hc11C = malloc(m11C*sizeof(int *)); if (hc11C==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc11C[] malloc out of memory\n");    Error_no_free(errMsg); }
    for (j=0; j<m11C; ++j) { hc11C[j] = malloc(11*sizeof(int)); if (hc11C[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc11C[][] malloc out of memory\n");   Error_no_free(errMsg); } }
    hc11E = malloc(m11E*sizeof(int *)); if (hc11E==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc11E[] malloc out of memory\n");    Error_no_free(errMsg); }
    for (j=0; j<m11E; ++j) { hc11E[j] = malloc(11*sizeof(int)); if (hc11E[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc11E[][] malloc out of memory\n");   Error_no_free(errMsg); } }
    hc11F = malloc(m11F*sizeof(int *)); if (hc11F==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc11F[] malloc out of memory\n");    Error_no_free(errMsg); }
    for (j=0; j<m11F; ++j) { hc11F[j] = malloc(11*sizeof(int)); if (hc11F[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc11F[][] malloc out of memory\n");   Error_no_free(errMsg); } }
    hc11W = malloc(m11W*sizeof(int *)); if (hc11W==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc11W[] malloc out of memory\n");    Error_no_free(errMsg); }
    for (j=0; j<m11W; ++j) { hc11W[j] = malloc(11*sizeof(int)); if (hc11W[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc11W[][] malloc out of memory\n");   Error_no_free(errMsg); } }
    
    hc12A = malloc(m12A*sizeof(int *)); if (hc12A==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc12A[] malloc out of memory\n");    Error_no_free(errMsg); }
    for (j=0; j<m12A; ++j) { hc12A[j] = malloc(12*sizeof(int)); if (hc12A[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc12A[][] malloc out of memory\n");   Error_no_free(errMsg); } }
    hc12B = malloc(m12B*sizeof(int *)); if (hc12B==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc12B[] malloc out of memory\n");    Error_no_free(errMsg); }
    for (j=0; j<m12B; ++j) { hc12B[j] = malloc(12*sizeof(int)); if (hc12B[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc12B[][] malloc out of memory\n");   Error_no_free(errMsg); } }
    hc12D = malloc(m12D*sizeof(int *)); if (hc12D==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc12D[] malloc out of memory\n");    Error_no_free(errMsg); }
    for (j=0; j<m12D; ++j) { hc12D[j] = malloc(12*sizeof(int)); if (hc12D[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc12D[][] malloc out of memory\n");   Error_no_free(errMsg); } }
    hc12E = malloc(m12E*sizeof(int *)); if (hc12E==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc12E[] malloc out of memory\n");    Error_no_free(errMsg); }
    for (j=0; j<m12E; ++j) { hc12E[j] = malloc(12*sizeof(int)); if (hc12E[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc12E[][] malloc out of memory\n");   Error_no_free(errMsg); } }
    hc12K = malloc(m12K*sizeof(int *)); if (hc12K==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc12K[] malloc out of memory\n");    Error_no_free(errMsg); }
    for (j=0; j<m12K; ++j) { hc12K[j] = malloc(12*sizeof(int)); if (hc12K[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc12K[][] malloc out of memory\n");   Error_no_free(errMsg); } }
        
    hc13A = malloc(m13A*sizeof(int *)); if (hc13A==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc13A[] malloc out of memory\n");    Error_no_free(errMsg); }
    for (j=0; j<m13A; ++j) { hc13A[j] = malloc(13*sizeof(int)); if (hc13A[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc13A[][] malloc out of memory\n");   Error_no_free(errMsg); } }
    hc13B = malloc(m13B*sizeof(int *)); if (hc13B==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc13B[] malloc out of memory\n");    Error_no_free(errMsg); }
    for (j=0; j<m13B; ++j) { hc13B[j] = malloc(13*sizeof(int)); if (hc13B[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc13B[][] malloc out of memory\n");   Error_no_free(errMsg); } }
    hc13K = malloc(m13K*sizeof(int *)); if (hc13K==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc13K[] malloc out of memory\n");    Error_no_free(errMsg); }
    for (j=0; j<m13K; ++j) { hc13K[j] = malloc(13*sizeof(int)); if (hc13K[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hc13K[][] malloc out of memory\n");   Error_no_free(errMsg); } }
    
    hcFCC = malloc(mFCC*sizeof(int *)); if (hcFCC==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hcFCC[] malloc out of memory\n");    Error_no_free(errMsg); }
    for (j=0; j<mFCC; ++j) { hcFCC[j] = malloc(13*sizeof(int)); if (hcFCC[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hcFCC[][] malloc out of memory\n");   Error_no_free(errMsg); } }
    hcHCP = malloc(mHCP*sizeof(int *)); if (hcHCP==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hcHCP[] malloc out of memory\n");    Error_no_free(errMsg); }
    for (j=0; j<mHCP; ++j) { hcHCP[j] = malloc(13*sizeof(int)); if (hcHCP[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hcHCP[][] malloc out of memory\n");   Error_no_free(errMsg); } }
    hcBCC_9 = malloc(mBCC_9*sizeof(int *)); if (hcBCC_9==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hcBCC_9[] malloc out of memory\n");    Error_no_free(errMsg); }
    for (j=0; j<mBCC_9; ++j) { hcBCC_9[j] = malloc(9*sizeof(int));  if (hcBCC_9[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hcBCC_9[][] malloc out of memory\n");   Error_no_free(errMsg); } }
    hcBCC_15 = malloc(mBCC_15*sizeof(int *));   if (hcBCC_15==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hcBCC_15[] malloc out of memory\n");  Error_no_free(errMsg); }
    for (j=0; j<mBCC_15; ++j) { hcBCC_15[j] = malloc(15*sizeof(int));   if (hcBCC_15[j]==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): hcBCC_15[][] malloc out of memory\n"); Error_no_free(errMsg); } }
    
    // character arrays listing what type each particle is when found in a cluster
    ssp3a=malloc(N*sizeof(char)); if (ssp3a==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): ssp3a[] malloc out of memory\n"); Error_no_free(errMsg); }
    ssp3b=malloc(N*sizeof(char)); if (ssp3b==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): ssp3b[] malloc out of memory\n"); Error_no_free(errMsg); }
    ssp3c=malloc(N*sizeof(char)); if (ssp3c==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): ssp3c[] malloc out of memory\n"); Error_no_free(errMsg); }
    
    ssp4a=malloc(N*sizeof(char)); if (ssp4a==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): ssp4a[] malloc out of memory\n"); Error_no_free(errMsg); }
    ssp4b=malloc(N*sizeof(char)); if (ssp4b==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): ssp4b[] malloc out of memory\n"); Error_no_free(errMsg); }
    ssp4c=malloc(N*sizeof(char)); if (ssp4c==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): ssp4c[] malloc out of memory\n"); Error_no_free(errMsg); }
    
    ssp5a=malloc(N*sizeof(char)); if (ssp5a==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): ssp5a[] malloc out of memory\n"); Error_no_free(errMsg); }
    ssp5b=malloc(N*sizeof(char)); if (ssp5b==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): ssp5b[] malloc out of memory\n"); Error_no_free(errMsg); }
    ssp5c=malloc(N*sizeof(char)); if (ssp5c==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): ssp5c[] malloc out of memory\n"); Error_no_free(errMsg); }

    s6Z=malloc(N*sizeof(char)); if (s6Z==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): s6Z[] malloc out of memory\n"); Error_no_free(errMsg); }
    s7K=malloc(N*sizeof(char)); if (s7K==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): s7K[] malloc out of memory\n"); Error_no_free(errMsg); }
    s8A=malloc(N*sizeof(char)); if (s8A==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): s8A[] malloc out of memory\n"); Error_no_free(errMsg); }
    s8B=malloc(N*sizeof(char)); if (s8B==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): s8B[] malloc out of memory\n"); Error_no_free(errMsg); }
    s8K=malloc(N*sizeof(char)); if (s8K==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): s8K[] malloc out of memory\n"); Error_no_free(errMsg); }
    s9A=malloc(N*sizeof(char)); if (s9A==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): s9A[] malloc out of memory\n"); Error_no_free(errMsg); }
    s9B=malloc(N*sizeof(char)); if (s9B==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): s9B[] malloc out of memory\n"); Error_no_free(errMsg); }
    s9K=malloc(N*sizeof(char)); if (s9K==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): s9K[] malloc out of memory\n"); Error_no_free(errMsg); }
    s10A=malloc(N*sizeof(char)); if (s10A==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): s10A[] malloc out of memory\n"); Error_no_free(errMsg); }
    s10B=malloc(N*sizeof(char)); if (s10B==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): s10B[] malloc out of memory\n"); Error_no_free(errMsg); }
    s10K=malloc(N*sizeof(char)); if (s10K==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): s10K[] malloc out of memory\n"); Error_no_free(errMsg); }
    s10W=malloc(N*sizeof(char)); if (s10W==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): s10W[] malloc out of memory\n"); Error_no_free(errMsg); }
    s11A=malloc(N*sizeof(char)); if (s11A==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): s11A[] malloc out of memory\n"); Error_no_free(errMsg); }
    s11B=malloc(N*sizeof(char)); if (s11B==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): s11B[] malloc out of memory\n"); Error_no_free(errMsg); }
    s11C=malloc(N*sizeof(char)); if (s11C==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): s11C[] malloc out of memory\n"); Error_no_free(errMsg); }
    s11E=malloc(N*sizeof(char)); if (s11E==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): s11E[] malloc out of memory\n"); Error_no_free(errMsg); }
    s11F=malloc(N*sizeof(char)); if (s11F==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): s11F[] malloc out of memory\n"); Error_no_free(errMsg); }
    s11W=malloc(N*sizeof(char)); if (s11W==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): s11W[] malloc out of memory\n"); Error_no_free(errMsg); }
    s12A=malloc(N*sizeof(char)); if (s12A==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): s12A[] malloc out of memory\n"); Error_no_free(errMsg); }
    s12B=malloc(N*sizeof(char)); if (s12B==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): s12B[] malloc out of memory\n"); Error_no_free(errMsg); }
    s12D=malloc(N*sizeof(char)); if (s12D==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): s12D[] malloc out of memory\n"); Error_no_free(errMsg); }
    s12E=malloc(N*sizeof(char)); if (s12E==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): s12E[] malloc out of memory\n"); Error_no_free(errMsg); }
    s12K=malloc(N*sizeof(char)); if (s12K==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): s12K[] malloc out of memory\n"); Error_no_free(errMsg); }
    s13A=malloc(N*sizeof(char)); if (s13A==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): s13A[] malloc out of memory\n"); Error_no_free(errMsg); }
    s13B=malloc(N*sizeof(char)); if (s13B==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): s13B[] malloc out of memory\n"); Error_no_free(errMsg); }
    s13K=malloc(N*sizeof(char)); if (s13K==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): s13K[] malloc out of memory\n"); Error_no_free(errMsg); }
    sFCC=malloc(N*sizeof(char)); if (sFCC==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): sFCC[] malloc out of memory\n"); Error_no_free(errMsg); }
    sHCP=malloc(N*sizeof(char)); if (sHCP==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): sHCP[] malloc out of memory\n"); Error_no_free(errMsg); }
    sBCC_9=malloc(N*sizeof(char)); if (sBCC_9==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): sBCC_9[] malloc out of memory\n"); Error_no_free(errMsg); }
    sBCC_15=malloc(N*sizeof(char)); if (sBCC_15==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): sBCC_15[] malloc out of memory\n"); Error_no_free(errMsg); }

    // particle fraction of particles in each cluster in each frame
    pop_per_frame = malloc(num_cluster_types*sizeof(double *));

    for(i=0; i<num_cluster_types; i++) {
        pop_per_frame[i] = malloc(FRAMES*sizeof(double));
        if (pop_per_frame[i]==NULL) {
            sprintf(errMsg,"Setup_InitStaticVars(): pop_per_frame malloc out of memory\n");
            Error_no_free(errMsg);
        }
    }

    // Zero the pop per frame arrays
    for(i=0; i<num_cluster_types; i++) {
        for (f=0; f<FRAMES; f++) {
            pop_per_frame[i][f] = 0;
        }
    }
}

void Setup_ResetStaticVars() { // Reset static variables in each frame
    int i, j, k;

    nsp3a=nsp3b=nsp3c=0;
    nsp4a=nsp4b=nsp4c=0;
    nsp5a=nsp5b=nsp5c=0;
    n6Z=n7K=0;
    n8A=n8B=n8K=0;
    n9A=n9B=n9K=0;
    n10A=n10B=n10K=n10W=0;
    n11A=n11B=n11C=n11E=n11F=n11W=0;
    n12A=n12B=n12D=n12E=n12K=0;
    n13A=n13B=n13K=0;
    nFCC=nHCP=nBCC_9=nBCC_15=0;

    for (i=0; i<N; ++i) {
        x[i]=y[i]=z[i]=-1000.0;
        for (j=0;j<nB;++j) {
            bNums[i][j]=-1;
            bondlengths[i][j]=-1.0;
        }
        cnb[i]=0;
    }

    for (i=0; i<msp3a; ++i) {
        for (j=0;j<3;++j) hcsp3a[i][j]=-1;
    }
    for (i=0; i<msp3b; ++i) {
        for (j=0;j<4;++j) hcsp3b[i][j]=-1;
    }
    for (i=0; i<msp3c; ++i) {
        for (j=0;j<5;++j) hcsp3c[i][j]=-1;
    }
    for (j=0; j<N; ++j) { 
        for (k=0; k<mmem_sp3b; k++) mem_sp3b[j][k]=-1; 
        for (k=0; k<mmem_sp3c; k++) mem_sp3c[j][k]=-1; 
        for (k=0; k<mmem_sp4b; k++) mem_sp4b[j][k]=-1; 
        for (k=0; k<mmem_sp4c; k++) mem_sp4c[j][k]=-1;
        for (k=0; k<mmem_sp5b; k++) mem_sp5b[j][k]=-1; 
        for (k=0; k<mmem_sp5c; k++) mem_sp5c[j][k]=-1;
        nmem_sp3b[j]=0;
        nmem_sp3c[j]=0;
        nmem_sp4b[j]=0;
        nmem_sp4c[j]=0;
        nmem_sp5b[j]=0;
        nmem_sp5c[j]=0;
    }

    for (i=0; i<msp4a; ++i) {
        for (j=0;j<4;++j) hcsp4a[i][j]=-1;
    }
    for (i=0; i<msp4b; ++i) {
        for (j=0;j<5;++j) hcsp4b[i][j]=-1;
    }
    for (i=0; i<msp4c; ++i) {
        for (j=0;j<6;++j) hcsp4c[i][j]=-1;
    }
    for (i=0; i<msp5a; ++i) {
        for (j=0;j<5;++j) {
            hcsp5a[i][j]=-1;
        }
    }
    for (i=0; i<msp5b; ++i) {
        for (j=0;j<6;++j) hcsp5b[i][j]=-1;
    }
    for (i=0; i<msp5c; ++i) {
        for (j=0;j<7;++j) hcsp5c[i][j]=-1;
    }
    for (i=0; i<m6Z; ++i) {
        for (j=0;j<6;++j) hc6Z[i][j]=-1;
    }
    
    for (i=0; i<m7K; ++i) {
        for (j=0;j<7;++j) hc7K[i][j]=-1;
    }
    
    for (i=0; i<m8A; ++i) {
        for (j=0;j<8;++j) hc8A[i][j]=-1;
    }
    for (i=0; i<m8B; ++i) {
        for (j=0;j<8;++j) hc8B[i][j]=-1;
    }
    for (i=0; i<m8K; ++i) {
        for (j=0;j<8;++j) hc8K[i][j]=-1;
    }
    
    for (i=0; i<m9A; ++i) {
        for (j=0;j<9;++j) hc9A[i][j]=-1;
    }
    for (i=0; i<m9B; ++i) {
        for (j=0;j<9;++j) hc9B[i][j]=-1;
    }
    for (i=0; i<m9K; ++i) {
        for (j=0;j<9;++j) hc9K[i][j]=-1;
    }
    
    for (i=0; i<m10A; ++i) {
        for (j=0;j<10;++j) hc10A[i][j]=-1;
    }
    for (i=0; i<m10B; ++i) {
        for (j=0;j<10;++j) hc10B[i][j]=-1;
    }
    for (i=0; i<m10K; ++i) {
        for (j=0;j<10;++j) hc10K[i][j]=-1;
    }
    for (i=0; i<m10W; ++i) {
        for (j=0;j<10;++j) hc10W[i][j]=-1;
    }
    
    for (i=0; i<m11A; ++i) {
        for (j=0;j<11;++j) hc11A[i][j]=-1;
    }
    for (i=0; i<m11B; ++i) {
        for (j=0;j<11;++j) hc11B[i][j]=-1;
    }
    for (i=0; i<m11C; ++i) {
        for (j=0;j<11;++j) hc11C[i][j]=-1;
    }
    for (i=0; i<m11E; ++i) {
        for (j=0;j<11;++j) hc11E[i][j]=-1;
    }
    for (i=0; i<m11F; ++i) {
        for (j=0;j<11;++j) hc11F[i][j]=-1;
    }
    for (i=0; i<m11W; ++i) {
        for (j=0;j<11;++j) hc11W[i][j]=-1;
    }
    
    for (i=0; i<m12A; ++i) {
        for (j=0;j<12;++j) hc12A[i][j]=-1;
    }
    for (i=0; i<m12B; ++i) {
        for (j=0;j<12;++j) hc12B[i][j]=-1;
    }
    for (i=0; i<m12D; ++i) {
        for (j=0;j<12;++j) hc12D[i][j]=-1;
    }
    for (i=0; i<m12E; ++i) {
        for (j=0;j<12;++j) hc12E[i][j]=-1;
    }
    for (i=0; i<m12K; ++i) {
        for (j=0;j<12;++j) hc12K[i][j]=-1;
    }
    
    for (i=0; i<m13A; ++i) {
        for (j=0;j<13;++j) hc13A[i][j]=-1;
    }
    for (i=0; i<m13B; ++i) {
        for (j=0;j<13;++j) hc13B[i][j]=-1;
    }
    for (i=0; i<m13K; ++i) {
        for (j=0;j<13;++j) hc13K[i][j]=-1;
    }
    
    for (i=0; i<mFCC; ++i) {
        for (j=0;j<13;++j) hcFCC[i][j]=-1;
    }
    for (i=0; i<mHCP; ++i) {
        for (j=0;j<13;++j) hcHCP[i][j]=-1;
    }
    for (i=0; i<mBCC_9; ++i) {
        for (j=0;j<9;++j) hcBCC_9[i][j]=-1;
    }
    for (i=0; i<mBCC_15; ++i) {
        for (j=0;j<15;++j) hcBCC_15[i][j]=-1;
    }
    
    for (i=0; i<N; ++i) {
        ssp3a[i]=ssp3b[i]=ssp3c[i]='C';
        ssp4a[i]=ssp4b[i]=ssp4c[i]='C';
        s6Z[i]=s7K[i]='C';
        ssp5a[i]=ssp5b[i]=ssp5c[i]='C';
        s8A[i]=s8B[i]=s8K[i]='C';
        s9A[i]=s9B[i]=s9K[i]='C';
        s10A[i]=s10B[i]=s10K[i]=s10W[i]='C';
        s11A[i]=s11B[i]=s11C[i]=s11E[i]=s11F[i]=s11W[i]='C';
        s12A[i]=s12B[i]=s12D[i]=s12E[i]=s12K[i]='C';
        s13A[i]=s13B[i]=s13K[i]='C';
        sFCC[i]=sHCP[i]=sBCC_9[i]=sBCC_15[i]='C';
    }
}

void Setup_FreeStaticVars()  {  // Free bond detection variables
    int i;

    free(mean_pop_per_frame);

    free(particle_type);
    free(fXmolName);
    free(fBoxSizeName);
    free(x); free(y); free(z);

    for (i=0; i<N; ++i) {
        free(bNums[i]); 
        free(bondlengths[i]);
    }
    free(bNums); free(bondlengths); free(cnb);
    
    if (USELIST==1) {
        free(map);
        free(head);
        free(llist);
    }

    for (i=0; i<num_cluster_types; ++i) {
        free(pop_per_frame[i]);
    }
    free(pop_per_frame);

    for (i=0; i<msp3a; ++i) free(hcsp3a[i]);
    for (i=0; i<msp3b; ++i) free(hcsp3b[i]);
    for (i=0; i<msp3c; ++i) free(hcsp3c[i]);
    for (i=0; i<msp4a; ++i) free(hcsp4a[i]);
    for (i=0; i<msp4b; ++i) free(hcsp4b[i]);
    for (i=0; i<msp4c; ++i) free(hcsp4c[i]);
    for (i=0; i<msp5a; ++i) free(hcsp5a[i]);
    for (i=0; i<msp5b; ++i) free(hcsp5b[i]);
    for (i=0; i<msp5c; ++i) free(hcsp5c[i]);
    for (i=0; i<m6Z; ++i) free(hc6Z[i]);
    for (i=0; i<m7K; ++i) free(hc7K[i]);
    for (i=0; i<m8A; ++i) free(hc8A[i]);
    for (i=0; i<m8B; ++i) free(hc8B[i]);
    for (i=0; i<m8K; ++i) free(hc8K[i]);
    for (i=0; i<m9A; ++i) free(hc9A[i]);
    for (i=0; i<m9B; ++i) free(hc9B[i]);
    for (i=0; i<m9K; ++i) free(hc9K[i]);
    for (i=0; i<m10A; ++i) free(hc10A[i]);
    for (i=0; i<m10B; ++i) free(hc10B[i]);
    for (i=0; i<m10K; ++i) free(hc10K[i]);
    for (i=0; i<m10W; ++i) free(hc10W[i]);
    for (i=0; i<m11A; ++i) free(hc11A[i]);
    for (i=0; i<m11B; ++i) free(hc11B[i]);
    for (i=0; i<m11C; ++i) free(hc11C[i]);
    for (i=0; i<m11E; ++i) free(hc11E[i]);
    for (i=0; i<m11F; ++i) free(hc11F[i]);
    for (i=0; i<m11W; ++i) free(hc11W[i]);
    for (i=0; i<m12A; ++i) free(hc12A[i]);
    for (i=0; i<m12B; ++i) free(hc12B[i]);
    for (i=0; i<m12D; ++i) free(hc12D[i]);
    for (i=0; i<m12E; ++i) free(hc12E[i]);
    for (i=0; i<m12K; ++i) free(hc12K[i]);
    for (i=0; i<m13A; ++i) free(hc13A[i]);
    for (i=0; i<m13B; ++i) free(hc13B[i]);
    for (i=0; i<m13K; ++i) free(hc13K[i]);
    for (i=0; i<mFCC; ++i) free(hcFCC[i]);
    for (i=0; i<mHCP; ++i) free(hcHCP[i]);
    for (i=0; i<mBCC_9; ++i) free(hcBCC_9[i]);
    for (i=0; i<mBCC_15; ++i) free(hcBCC_15[i]);
    
    for (i=0; i<N; ++i) free(mem_sp3b[i]);
    for (i=0; i<N; ++i) free(mem_sp3c[i]);
    for (i=0; i<N; ++i) free(mem_sp4b[i]);
    for (i=0; i<N; ++i) free(mem_sp4c[i]);
    for (i=0; i<N; ++i) free(mem_sp5b[i]);
    for (i=0; i<N; ++i) free(mem_sp5c[i]);
    
    free(mem_sp3b);
    free(mem_sp3c);
    free(mem_sp4b);
    free(mem_sp4c);
    free(mem_sp5b);
    free(mem_sp5c);

    free(nmem_sp3b);
    free(nmem_sp3c);
    free(nmem_sp4b);
    free(nmem_sp4c);
    free(nmem_sp5b);
    free(nmem_sp5c);

    free(hcsp3a); free(hcsp3b); free(hcsp3c);
    free(hcsp4a); free(hcsp4b); free(hcsp4c);
    free(hcsp5a); free(hcsp5b); free(hcsp5c);
    free(hc6Z); free(hc7K);
    free(hc8A); free(hc8B); free(hc8K);
    free(hc9A); free(hc9B); free(hc9K);
    free(hc10A); free(hc10B); free(hc10K); free(hc10W);
    free(hc11A); free(hc11B); free(hc11C); free(hc11E); free(hc11F); free(hc11W);
    free(hc12A); free(hc12B); free(hc12D); free(hc12E); free(hc12K);
    free(hc13A); free(hc13B); free(hc13K);
    free(hcFCC); free(hcHCP); free(hcBCC_9); free(hcBCC_15);

    free(ssp3a); free(ssp3b); free(ssp3c);
    free(ssp4a); free(ssp4b); free(ssp4c);
    free(s6Z); free(s7K);
    free(ssp5a); free(ssp5b); free(ssp5c);
    free(s8A); free(s8B); free(s8K);
    free(s9A); free(s9B); free(s9K);
    free(s10A); free(s10B); free(s10K); free(s10W);
    free(s11A); free(s11B); free(s11C); free(s11E); free(s11F); free(s11W);
    free(s12A); free(s12B); free(s12D); free(s12E); free(s12K);
    free(s13A); free(s13B); free(s13K);
    free(sFCC);free(sHCP); free(sBCC_9); free(sBCC_15);
    
}

int icell(int tix, int tiy, int tiz) { 	// returns cell number (from 1 to ncells) for given (tix,tiy,tiz) coordinate
    return 1 + (tix-1+M)%M + M*((tiy-1+M)%M) + M*M*((tiz-1+M)%M);
}

void Setup_Cell_List() {

    int i;
    int ix, iy, iz;
    int imap;
    char errMsg[1000];

    head=malloc((ncells+1)*sizeof(int));    if (head==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): head[] malloc out of memory\n");  Error_no_free(errMsg); }
    map=malloc((13*ncells+1)*sizeof(int));  if (map==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): map[] malloc out of memory\n");    Error_no_free(errMsg); }
    llist=malloc((N+1)*sizeof(int));    if (llist==NULL) { sprintf(errMsg,"Setup_InitStaticVars(): llist[] malloc out of memory\n");    Error_no_free(errMsg); }

    for (i=0; i<ncells+1; i++) head[i]=0;
    for (i=0; i<13*ncells+1; i++) map[i]=0;
    for (i=0; i<N+1; i++) llist[i]=0;


    M = (int)(side/rcutAA);	// number of cells along box side
    if (M<3) Error_no_free("main(): M<3, too few cells");
    ncells = M*M*M;	// total number of cells
    cellSide = side/M;	// length of cells
    invcellSide = 1.0/cellSide;	// invcellSide
    printf("m %d ncells %d cellside %.15lg\n", M, ncells, cellSide);
    // routine to create the thirteen nearest neighbours array map[] of each cell
    for (iz=1; iz<=M; iz++) {
        for (iy=1; iy<=M; iy++) {
            for (ix=1; ix<=M; ix++) {
                imap = (icell(ix,iy,iz)-1)*13;
                map[imap+1 ]=icell(ix+1,iy	,iz	);
                map[imap+2 ]=icell(ix+1,iy+1,iz	);
                map[imap+3 ]=icell(ix	 ,iy+1,iz	);
                map[imap+4 ]=icell(ix-1 ,iy+1,iz	);
                map[imap+5 ]=icell(ix+1,iy	,iz-1	);
                map[imap+6 ]=icell(ix+1,iy+1,iz-1	);
                map[imap+7 ]=icell(ix	 ,iy+1,iz-1	);
                map[imap+8 ]=icell(ix-1 ,iy+1,iz-1	);
                map[imap+9 ]=icell(ix+1,iy	,iz+1	);
                map[imap+10]=icell(ix+1,iy+1,iz+1	);
                map[imap+11]=icell(ix	 ,iy+1,iz+1	);
                map[imap+12]=icell(ix-1 ,iy+1,iz+1);
                map[imap+13]=icell(ix	 ,iy	,iz+1	);
            }
        }
    }
}