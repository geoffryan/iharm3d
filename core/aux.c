/******************************************************************************
 *                                                                            *
 * AUX.C                                                                      *
 *                                                                            *
 * MANAGES AUXILLARY (TABULATED) DATA                                         * 
 *                                                                            *
 ******************************************************************************/

#include "decs.h"
#include "hdf5_utils.h"

void init_aux(struct AuxillaryData *D)
{
#if DARK_PHOTON
  hdf5_open("test.h5");
  hdf5_set_directory("");
  int ndim = hdf5_read_array_ndim("data");
  hsize_t dims[ndim];
  hdf5_read_array_dims("data", dims, ndim);
  size_t size = 1;
  int i;
  hsize_t start[ndim];

  printf("ndim: %d\n", ndim);
  for(i=0; i<ndim; i++)
  {
      size *= (size_t)dims[i];
      start[i] = 0;
      printf("dims[%d] = %d\n", i, (int)dims[i]);
  }
  printf("size: %zu\n", size);


  double *data = (double *)malloc(size * sizeof(double));

  hdf5_read_array(data, "data", ndim, dims, start, dims,
                  dims, start, H5T_IEEE_F64LE); 

  hdf5_close();

  for(i=0; i<size; i++)
      printf("%.0f\n", data[i]);

  ZLOOP {
      D->Ac[UU][k][j][i] = 1.0e-2;
      D->As[U2][k][j][i] = -1.0e-2;
  }
  free(data);
#endif
}

