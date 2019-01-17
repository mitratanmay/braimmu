#ifndef BRAIN_H
#define BRAIN_H

#include <vector>
#include "stdio.h"
#include "stdlib.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>

#include "nifti1.h"
#include "nifti1_io.h"
#include "znzlib.h"

#include "pointers.h"
#include "input.h"
#include "memory.h"
#include "init.h"
#include "run.h"
#include "comm.h"
#include "output.h"
#include "region.h"

namespace brain_NS {

class Brain {
 public:
  Brain(int, char **, int, int);
  ~Brain();

  void allocations();
  void destroy();

  // classes
  Input *input;
  Memory *memory;
  Init *init;
  Run *run;
  Comm *comm;
  Output *output;
  Region *region;

  int me,nproc;

  friend class Input;

  //Run *run;
  //Output *output;

  int *npart;
  int *nv;
  tagint nvoxel; // total number of voxels
  int nlocal, nghost, nall; // number of voxels for each core, local/ghost/all

  int step, Nrun, Nlog; // step, number of steps, log output

  double dt;  // timestep
  int nevery; // period of neural activity = nevery timesteps
  double *boxlo,*boxhi,*lbox; // box boundaries, and size
  double *xlo,*xhi; // boundaries for each partition

  double **x; // voxel position
  double vlen, vlen_1, vlen_2, vvol, vvol_1; // voxel size

  int *type, *group;

  //int nbondlist, **bondlist;

  tagint *tag; // tag of each voxel
  int *map; // mapping from tag to voxel id

  int num_neigh_max, num_conn_max; // maximum number of neighbors/connections
  int *num_neigh, *num_conn; // number of neighbors, number of long-range connections
  int **neigh; // neighbor ids for each voxel
  tagint **conn; // connection tags for each voxel

  /// MRI image variables
  nifti_image *nim;

  /// model parameters
  double ***agent; // agents
  //double ***grad; // gradients
  double init_val[num_agents];
  double D_sAb, diff_sAb; // diffusivity of sAb
  double D_mic, diff_mic; // diffusivity of microglia
  double cs, sens_s, cf, sens_f; // microglia chemotaxis sensitivity
  double kp, kn; // rate of polymerization and nucleation
  double ds,df; // clearance rate of sAb and fAb by microglia
  double es; // rate of sAb efflux in CSF
  double c_mic, vel_mic; // velocity of microglia (speed of chemotaxis)
  double dn; // neuronal death rate due to astogliosis
  double Ha; // Michaelis-Menten constant for astrogliosis

  MPI_Comm world;

};

}

#endif