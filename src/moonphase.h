
#include <stdio.h>
#include <math.h>
#include "DateTime.h"

// States
enum MoonState{NEW, WANINGCRESCENT, THIRDQTR, WANINGGIBBOUS, FULL, WAXINGGIBBOUS, FIRSTQTR, WAXINGCRESCENT};

struct MoonDays
{
    double New;
    double ThirdQ;
    double Full;
    double FirstQ;
    double Max;
} MoonDays;
// struct MoonDays
// {
    MoonDays.New = 0;
    MoonDays.ThirdQ = 7;
    MoonDays.Full = 15;
    MoonDays.FirstQ = 22;
    MoonDays.Max = 29.53;
// } MoonDays;


double GetJulianDay(struct DateTime Date)
{
    // struct DateTime Date = GetDateTime;

    // Get Julian Day data
    double A = Date.Year / 100;
    double B = A / 4;
    double C = 2 - A + B;
    double E = 365.25 * (Date.Year + 4716);
    double F = 30.6001 * (Date.Month + 1);
    double JulianDay = C+Date.Day+E+F-1524.5;
    return JulianDay;
}

double GetFraction()
{
    struct DateTime LastKnownNewMoon = {1, 6, 2000, 12, 24, 1};
    double Julian_Today = GetJulianDay(GetDateTime());
    double Julian_LastKnownNewMoon = GetJulianDay(LastKnownNewMoon);
    double DaysSinceNewMoon = Julian_Today - Julian_LastKnownNewMoon; // In Julians

    double NumberOfNewMoons = DaysSinceNewMoon / MoonDays.Max; // Get the number of new moons since last known new moon
    double integral;
    double fractional = modf(some_double, &integral); // Get the fraction of the whole number

    // Use the fractional to get how far you are in the phase 
    double MoonCycleFraction = fractional * MoonDays.Max;

    return MoonCycleFraction;
}

int GetMoonState(double Days)
{
    switch(Days)
    {
        case (NEW): return NEW;
        case (THIRDQTR): return THIRDQTR;
        case (FULL): return FULL;
        case (FIRSTQTR): return FIRSTQTR;
        default:
            if(MoonDays.New < Days < MoonDays.ThirdQ) return WANINGCRESCENT;
            else if (MoonDays.ThirdQ < Days < MoonDays.Full) return WANINGGIBBOUS;
            else if (MoonDays.Full < Days < MoonDays.FirstQ) return WAXINGGIBBOUS;
            else if (MoonDays.FirstQ < Days < MoonDays.Max) return WAXINGCRESCENT;
            else return NEW; // See if this throws an error
    }
}
