#include "../include/CSDist1DTab.hh"

CSDist1DTab::CSDist1DTab(double *energyVec)
{
    enerVec=energyVec;
}

CSDist1DTab::CSDist1DTab(double *energyVec, int numCSEner)
{
    startEner = 1;
    CSVecSize = numCSEner;
    elastic = true;
}

CSDist1DTab::~CSDist1DTab()
{
    delete [] CSVec;
}

void CSDist1DTab::ExtractMCNPData(stringstream &stream, int &count)
{
    int intTemp;
    double temp;

    if(!elastic)
    {
        stream >> intTemp; count++;
        startEner = intTemp;
        stream >> intTemp; count++;
        CSVecSize = intTemp;
    }

    CSVec = new double[CSVecSize];

    for(int j=0; j<CSVecSize; j++, count++)
    {
        stream >> temp;
        CSVec[j] = temp;
    }
}

//Set up for Cross-section data
void CSDist1DTab::WriteG4NDLCSData(stringstream &stream )
{
    stream << std::setw(14) << std::right << CSVecSize;
    stream.precision(6);
    stream.setf(std::ios::scientific);

    for(int i=0; i<CSVecSize; i++)
    {
        if(i%3==0)
            stream << '\n';
        stream << std::setw(14) << std::right << enerVec[i+startEner-1]*1000000;
        stream << std::setw(14) << std::right << CSVec[i];
    }
    stream << '\n';
}

string CSDist1DTab::IdentifyYourSelf()
{
    return "CSDist1DTab";
}

double CSDist1DTab::Interpolate(double x)
{
    int i;
    for(i=0; i<CSVecSize; i++)
    {
        if(enerVec[i+startEner-1]>x)
        {
            i--;
            break;
        }
    }
    if(i<0)
        i=0;

    return CSDist::Interpolate(2, x, enerVec[i+startEner-1], enerVec[i+startEner], CSVec[i+startEner-1], CSVec[i+startEner]);
}