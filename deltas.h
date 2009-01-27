#if !defined( DELTAS_H )
#define DELTAS_H

#define Xmax            (200)   /**< number of cells in x (cross-shore) direction */
#define Ymax            (500)   /**< number of cells in y (longshore) direction */
#define MaxBeachLength  (8*Ymax)/**< maximum length of arrays that contain beach data at each time step */
#define TimeStep     (0.2)  /**< days - reflects rate of sediment transport per
                             time step */

typedef struct
{
   float SedRate; /**< Sedimentation rate as percent per time step. */

   /** Input/output file names. */
   char* savefilename; /**< Name of save file. */
   char* readfilename; /**< Namve of file to read input from. */

   /** Overall Shoreface Configuration Arrays - Data file information */
   char AllBeach[Xmax][2*Ymax]; /**< Flag indicating of cell is entirely beach */
   float PercentFull[Xmax][2*Ymax]; /**< Fractional amount of shore cell full of
                                       sediment */
   int Age[Xmax][2*Ymax]; /**< Age since cell was deposited */
   float CellDepth[Xmax][2*Ymax]; /**< Depth array (m) (ADA 6/3) */

   /** Computational Arrays (determined for each time step) */
   int X[MaxBeachLength]; /**< X Position of ith beach element */
   int Y[MaxBeachLength]; /**< Y Position of ith beach element */
   char	InShadow[MaxBeachLength];	 /**< Is ith beach element in shadow? */
   float ShorelineAngle[MaxBeachLength]; /**< Angle between cell and right (z+1)
                                            neighbor */
   float SurroundingAngle[MaxBeachLength];/**< Cell-orientated angle based upon
                                             left and right neighbor */
   char UpWind[MaxBeachLength]; /**< Upwind or downwind condition used to
                                   calculate sediment transport */
   float VolumeIn[MaxBeachLength];  /**< Sediment volume into ith beach
                                       element */	
   float VolumeOut[MaxBeachLength]; /**< Sediment volume out of ith beach
                                       element */

   /** Miscellaneous State Variables */
   int CurrentTimeStep; /**< Time step of current calculation */ 

   int NextX; /**< used to iterate FindNextCell in global array - */
   int NextY;

   int TotalBeachCells; /**< Number of cells describing beach at particular iteration */
   int ShadowXMax; /**< used to determine maximum extent of beach cells */
   float WaveAngle; /**< wave angle for current time step */	

   int FindStart; /**< Used to tell FindBeach at what Y value to start looking */

   char FellOffArray; /**< Flag used to determine if accidentally went off array */

   float MassInitial; /**< For conservation of mass calcs */
   float MassCurrent;

   int NumWaveBins;    /**< For Input Wave - number of bins */
   float WaveMax[36];  /**< Max Angle for specific bin */
   float WaveProb[36]; /**< Probability of Certain Bin */


   /** Graphics variables. */
   float xcellwidth;
   float ycellwidth;
   int   xplotoff;
   int   yplotoff;

   char state[256];
}
State;

int initialize( State* s );
int run_until ( State* s, int until );
int finalize  ( State* s );

void deltas_init_state( State* s );
void deltas_free_state( State* s );

#endif
