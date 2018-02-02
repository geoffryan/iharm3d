/******************************************************************************  
 *                                                                            *  
 * PARAMETERS.H                                                               *  
 *                                                                            *  
 * PROBLEM-SPECIFIC CHOICES                                                   *  
 *                                                                            *  
 ******************************************************************************/

/* GLOBAL RESOLUTION */
#define N1TOT 16
#define N2TOT 16
#define N3TOT 16

/* MPI DECOMPOSITION */
/* DECOMPOSE IN N3 FIRST! Small leading array sizes for linear access */
#define N1CPU 1
#define N2CPU 2
#define N3CPU 4

/* METRIC
 *   MINKOWSKI, MKS
 */
#define METRIC MINKOWSKI

#define NMODE 1

#define ELECTRONS 0

#define RADIATION 0

/* RECONSTRUCTION ALGORITHM
 *   LINEAR, PPM, WENO, MP5
 */
#define RECONSTRUCTION LINEAR

/* BOUNDARY CONDITIONS
 *   OUTFLOW PERIODIC POLAR USER
 */
#define X1L_BOUND PERIODIC
#define X1R_BOUND PERIODIC
#define X2L_BOUND PERIODIC
#define X2R_BOUND PERIODIC
#define X3L_BOUND PERIODIC
#define X3R_BOUND PERIODIC
