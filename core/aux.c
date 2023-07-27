/******************************************************************************
 *                                                                            *
 * AUX.C                                                                      *
 *                                                                            *
 * MANAGES AUXILLARY (TABULATED) DATA                                         * 
 *                                                                            *
 ******************************************************************************/

#include "decs.h"
#include "hdf5_utils.h"

void make_buffer(const char name[], int ndim, hsize_t dims[], double **buf) {
  //Reads a dataset (of known rank "ndim").  Returns the dimensionality in
  //"dims" and allocates a buffer "buf", fills with the dataset.
  //
  //Returned buffer must be freed by caller

  hdf5_read_array_dims(name, dims, ndim);
  
  size_t size = 1;
  int i;
  hsize_t start[ndim];

  for(i=0; i<ndim; i++)
  {
      size *= (size_t)dims[i];
      start[i] = 0;
  }

  *buf = (double *)malloc(size * sizeof(double));

  hdf5_read_array(*buf, name, ndim, dims, start, dims,
                  dims, start, H5T_IEEE_F64LE);
}

int searchsorted(double x, double *arr, int N)
{
  if(x <= arr[0])
    return 0;
  else if(x >= arr[N-1])
    return N-2;

  unsigned int i = ((unsigned int) N) >> 1;
  unsigned int a = 0;
  unsigned int b = N-1;

  while(b-a > 1u)
  {
    i = (b+a) >> 1;
    if(arr[i] > x)
      b = i;
    else
      a = i;
  }

  return (int) a;
}

void init_aux(struct AuxillaryData *D) {
#if DARK_PHOTON

  //Open up Dark Photon Amu file, read in table.
  hdf5_open("Amu.h5");
  hdf5_set_directory("/");

  double *r_grid = NULL;
  double *th_grid = NULL;
  double *Ac = NULL;
  double *As = NULL;
  hsize_t Nr;
  hsize_t Nth;
  hsize_t Acdims[3];
  hsize_t Asdims[3];

  make_buffer("r", 1, &Nr, &r_grid);
  make_buffer("th", 1, &Nth, &th_grid);
  make_buffer("Ac", 3, Acdims, &Ac);
  make_buffer("As", 3, Asdims, &As);

  hdf5_close();

  ZLOOP {
    double X[NDIM];
    coord(i, j, k, CENT, X);
    double r, th;
    bl_coord(X, &r, &th);

    int idx_r = searchsorted(r, r_grid, Nr);
    int idx_th = searchsorted(th, th_grid, Nth);

    int Nrth = Nr*Nth;
    int idx = Nr*idx_th + idx_r;

    DLOOP1 {
        D->Ac[mu][k][j][i] = 0.01*Ac[mu*Nrth + idx];
        D->As[mu][k][j][i] = 0.01*As[mu*Nrth + idx];
    }
  }

  free(r_grid);
  free(th_grid);
  free(Ac);
  free(As);

#endif
}

