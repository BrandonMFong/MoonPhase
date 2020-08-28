
#include <stdio.h>
#include <math.h>
#include "DateTime.h"

// States
enum MoonState{NEW, WANINGCRESCENT, THIRDQTR, WANINGGIBBOUS, FULL, WAXINGGIBBOUS, FIRSTQTR, WAXINGCRESCENT};

// This struct is to hold the values for Moon Phase days
struct MoonDays
{
    double New;
    double ThirdQ;
    double Full;
    double FirstQ;
    double Max;
} MoonDays;
struct MoonDays MoonDays = {0,7,15,22,29.53}; // Day per phase

// Get julian day number
double GetJulianDay(struct DateTime Date)
{
    double A = Date.Year / 100;
    double B = A / 4;
    double C = 2 - A + B;
    double E = 365.25 * (Date.Year + 4716);
    double F = 30.6001 * (Date.Month + 1);
    double JulianDay = C+Date.Day+E+F-1524.5;
    return JulianDay;
}

// This fraction represents how far you are into the moon phase
/* Last Known New Moon */
#define MONTH 8
#define DAY 18
#define YEAR 2020
#define HOUR 22
#define MINUTE 41
#define SECOND 0
double GetFraction()
{
    struct DateTime LastKnownNewMoon = {MONTH, DAY, YEAR, HOUR, MINUTE, SECOND};
    struct DateTime Date = GetDateTime();
    printf("Last Known New Moon date: %d/%d/%d, %d:%d:%d\n", LastKnownNewMoon.Month,LastKnownNewMoon.Day,LastKnownNewMoon.Year,LastKnownNewMoon.Hour,LastKnownNewMoon.Minute,LastKnownNewMoon.Second);
    printf("Today's date: %d/%d/%d, %d:%d:%d\n", Date.Month,Date.Day,Date.Year,Date.Hour,Date.Minute,Date.Second);
    double Julian_Today = GetJulianDay(Date); // Get current day
    double Julian_LastKnownNewMoon = GetJulianDay(LastKnownNewMoon); // Get a known recorded new moon day
    printf("Today's julian day: %lf\nNewMoon julian day: %lf\n",Julian_Today,Julian_LastKnownNewMoon);
    double DaysSinceNewMoon = Julian_Today - Julian_LastKnownNewMoon; // In Julians

    double NumberOfNewMoons = DaysSinceNewMoon / MoonDays.Max; // Get the number of new moons since Julian_LastKnownNewMoon date
    printf("Days since last new moon: %lf\n",NumberOfNewMoons);
    double integral;
    double fractional = modf(NumberOfNewMoons, &integral); // Get the fraction of the whole number
    printf("Fractional: %lf\n", fractional);

    // Use the fractional to get how far you are in the phase 
    double DaysIntoMoonphase = fractional * MoonDays.Max;

    // There is more to this because the results are not accurate 

    return DaysIntoMoonphase;
}

// Pass in the julian day number and it will tell you which phase you are on
// TODO make sure Days is julian day number
int GetMoonState()
{
    double Days = GetFraction();
    printf("Days into cycle: %lf\n", Days);
    if (Days == NEW) return NEW;
    else if (Days == THIRDQTR) return THIRDQTR;
    else if (Days == FULL) return FULL;
    else if (Days == FIRSTQTR) return FIRSTQTR;
    else if ((MoonDays.New < Days) && (Days < MoonDays.ThirdQ)) return WANINGCRESCENT;
    else if ((MoonDays.ThirdQ < Days) && (Days < MoonDays.Full)) return WANINGGIBBOUS;
    else if ((MoonDays.Full < Days) && (Days < MoonDays.FirstQ)) return WAXINGGIBBOUS;
    else if ((MoonDays.FirstQ < Days) && (Days < MoonDays.Max)) return WAXINGCRESCENT;
    else return NEW; // See if this throws an error
}


