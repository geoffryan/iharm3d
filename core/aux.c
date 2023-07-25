/******************************************************************************
 *                                                                            *
 * AUX.C                                                                      *
 *                                                                            *
 * MANAGES AUXILLARY (TABULATED) DATA                                         * 
 *                                                                            *
 ******************************************************************************/

#include "decs.h"

void init_aux(struct AuxillaryData *D)
{
#if DARK_PHOTON
  ZLOOP {
      D->Ac[UU][k][j][i] = 1.0e-2;
      D->As[U2][k][j][i] = -1.0e-2;
  }
#endif
}

