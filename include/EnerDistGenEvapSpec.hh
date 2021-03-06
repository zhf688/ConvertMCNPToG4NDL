#ifndef ENERDISTGENEVAPSPEC_HH
#define ENERDISTGENEVAPSPEC_HH

#include "EnergyDist.hh"

/*
Created By: Wesley Ford June 17, 2015

This class is responsible for the extraction of the general evaporation out-going neutron energy distribution data from MCNP
and the writing of this data into the applicable G4NDL files.

To better understand the MCNP format that this class is built to extract from please refer to MCNP5 Manual Vol III
To better understand the G4NDL format that this class is built to write to, please refer to G4NDL Final State Decryption
*/

class EnerDistGenEvapSpec: public EnergyDist
{
    public:
        EnerDistGenEvapSpec();
        virtual ~EnerDistGenEvapSpec();
        void ExtractMCNPData(stringstream &stream, int &count);
        void WriteG4NDLData(stringstream &stream);
        string IdentifyYourSelf()
        {
            return "EnerDistGenEvapSpec";
        }

        int numRegs, numIncEner, numNormOutEnerDistPoints;
        int *regEndPos, *intScheme;
        double *incEner, *outEnerMulti, *normOutEnerDist;

    protected:
    private:
};

#endif // ENERDISTGENEVAPSPEC_HH
