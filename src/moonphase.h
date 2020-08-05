
#include <stdio.h>
#include <DateTime.h>

double GetJulianDay(struct DateTime Date)
{
    // struct DateTime Date = GetDateTime;

    // Get Julian Day data
    double A = Date.Year / 100;
    double B = A / 4;
    double C = 2 - A + B;
    double E = 365.25 * (Date.Year + 4716);
    double F = 30.6001 * (Date.Month + 1);
    double JulianDay = C+D+E+F-1524.5;
    return JulianDay;
}

void InitMoonPhase()
{
    // struct DateTime LastKnownNewMoon = {1, 6, 2000, 12, 24, 1};
    double Julian_Today = GetJulianDay(GetDateTime);
    double Julian_LastKnownNewMoon = GetJulianDay({1, 6, 2000, 12, 24, 1});
    double DaysSinceNewMoon = Julian_Today - Julian_LastKnownNewMoon; // In Julians
}

