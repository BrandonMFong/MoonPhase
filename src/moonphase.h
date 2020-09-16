
#include <stdio.h>
#include <math.h>
#include "DateTime.h"
// use this formula https://minkukel.com/en/various/calculating-moon-phase/
// TODO Stop using julian days
// WHOEVER IS READING THIS the moonphase.pdf from subsystem.us has incorrect data and is very misleading

// This struct is to hold the values for Moon Phase days
struct Bounds
{
    double New_From,New_To; // New
    double WaxingCrescent_From,WaxingCrescent_To; // Waxing Crescent
    double FirstQ_From,FirstQ_To; // First Quarter
    double WaxingGibbous_From,WaxingGibbous_To; // Waxing Gibbous
    double Full_From,Full_To; // Full
    double WaningGibbous_From,WaningGibbous_To; // Waning Gibbous
    double LastQ_From,LastQ_To; // Last Quarter
    double WaningCrescent_From,WaningCrescent_To; // Waning Crescent
    double Max_From,Max_To; // New
} Bounds;

// Set bounds
struct Bounds Bounds = 
{
    0,	0.033863193308711, // New
    0.033863193308711, 	0.216136806691289, // Waxing Crescent
    0.216136806691289, 	0.283863193308711, // First Quarter
    0.283863193308711, 	0.466136806691289, // Waxing Gibbous
    0.466136806691289, 	0.533863193308711, // Full
    0.533863193308711, 	0.716136806691289, // Waning Gibbous
    0.716136806691289, 	0.783863193308711, // Last Quarter
    0.783863193308711, 	0.966136806691289, // Waning Crescent
    0.966136806691289, 1 // New
}; 

// This fraction represents how far you are into the moon phase
/* Last Known New Moon */
#define MONTH 1
#define DAY 6
#define YEAR 2019
#define HOUR 17
#define MINUTE 28
#define SECOND 0

#define LunarCycleConstant 29.53058770576
double GetDaysIntoCycle()
{
    struct MyDateTime LastKnownNewMoon = {MONTH, DAY, YEAR, HOUR, MINUTE, SECOND}; // Last know full moon
    printf("LastKnownNewMoon's date: %d/%d/%d, %d:%d:%d\n", LastKnownNewMoon.Month,LastKnownNewMoon.Day,LastKnownNewMoon.Year,LastKnownNewMoon.Hour,LastKnownNewMoon.Minute,LastKnownNewMoon.Second);

    struct MyDateTime Today = GetDateTime(); // Today
    printf("Today's date: %d/%d/%d, %d:%d:%d\n", Today.Month,Today.Day,Today.Year,Today.Hour,Today.Minute,Today.Second);

    double lunarsecs = DayToSeconds(LunarCycleConstant);
    printf("Lunar constant in seconds: %lf\n", lunarsecs);

    printf("\nConverting Last known new moon to seconds\n");
    double LastKnownNewMoon_secs = GetTotalSeconds(LastKnownNewMoon);
    printf("\nConverting Today's date to seconds\n");
    double Today_secs = GetTotalSeconds(Today);

    printf("\nLast known new moon in seconds: %lf\n", LastKnownNewMoon_secs);
    printf("Today in seconds: %lf\n", Today_secs);

    double totalsecs = Today_secs - LastKnownNewMoon_secs;
    printf("Time between today and last new moon %lf\n", totalsecs);

    // To compile this, use -lm switch 
    double currentsecs = fmod(totalsecs,lunarsecs); // This function is not known 
    printf("Seconds into cycle (modulus, %lf %% %lf) %lf\n",totalsecs, lunarsecs, currentsecs);

    // If this is negative number (in case a date was selected before 2000) we add 1 cycle (add ‘lunarsecs’ to ‘currentsecs’).

    double currentfrac = currentsecs / lunarsecs;
    printf("Fraction we are into the cycle (%lf / %lf) %lf\n",currentsecs, lunarsecs, currentfrac);
    printf("\n");

    // // Testing Epoch
    // printf("TESTING EPOCH\n");
    // long EpochToday = GetEpochSeconds(Today);
    // long EpochLastNew = GetEpochSeconds(LastKnownNewMoon);
    // long Epochtotalsecs = EpochToday - EpochLastNew;
    // printf("Epoch total secs since new moon: %ld\n", Epochtotalsecs);

    // // Error here 
    // double Epochcurrentsecs = fmod(Epochtotalsecs,lunarsecs); // This function is not known
    // printf("Epoch days into cycle: %ld\n", Epochcurrentsecs);
    // double Epochcurrentfrac = (double)Epochcurrentsecs / (double)lunarsecs; 
    // printf("Epoch fraction  %ld", Epochcurrentfrac);


    printf("\n");
    return currentfrac; // temp
}

// States
enum MoonState{NEW, WAXINGCRESCENT, FIRSTQTR, WAXINGGIBBOUS, FULL, WANINGGIBBOUS, LASTQTR, WANINGCRESCENT};
int GetMoonState()
{
    double Fraction = GetDaysIntoCycle();
    printf("Into cycle: %lf\n", Fraction);
    if ((Bounds.New_From < Fraction) && (Fraction < Bounds.New_To)) return NEW;
    else if ((Bounds.WaxingCrescent_From < Fraction) && (Fraction < Bounds.WaxingCrescent_To)) return WAXINGCRESCENT;
    else if ((Bounds.FirstQ_From < Fraction) && (Fraction < Bounds.FirstQ_From)) return FIRSTQTR;
    else if ((Bounds.WaxingGibbous_From < Fraction) && (Fraction < Bounds.WaxingGibbous_From)) return WAXINGGIBBOUS;
    else if ((Bounds.Full_From < Fraction) && (Fraction < Bounds.Full_To)) return FULL;
    else if ((Bounds.WaningGibbous_From < Fraction) && (Fraction < Bounds.WaningGibbous_To)) return WANINGGIBBOUS;
    else if ((Bounds.LastQ_From < Fraction) && (Fraction < Bounds.LastQ_To)) return LASTQTR;
    else if ((Bounds.WaningCrescent_From < Fraction) && (Fraction < Bounds.WaningCrescent_To)) return WANINGCRESCENT;
    else if ((Bounds.Max_From < Fraction) && (Fraction < Bounds.Max_To)) return NEW;
    else return NEW; // See if this throws an error
}


