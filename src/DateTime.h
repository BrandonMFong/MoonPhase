#include <time.h>

// time_t t = time(NULL);
// struct tm tm = *localtime(&t);
// printf("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

struct MyDateTime
{
    int Month, Day, Year;
    int Hour, Minute, Second;
};

struct MyDateTime GetDateTime()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    struct MyDateTime dt = {tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec}; // Interesting the year needed to be shifted 
    return dt;
}

long GetEpochSeconds(struct MyDateTime var)
{
    struct tm t;
    time_t t_of_day;

    t.tm_year = var.Year-1900;  // Year - 1900
    t.tm_mon = var.Month;           // Month, where 0 = jan
    t.tm_mday = var.Day;          // Day of the month
    t.tm_hour = var.Hour;
    t.tm_min = var.Minute;
    t.tm_sec = var.Second;
    t.tm_isdst = -1;        // Is DST on? 1 = yes, 0 = no, -1 = unknown

    t_of_day = mktime(&t);

    printf("%d/%d/%d, %d:%d:%d to", var.Month,var.Day,var.Year,var.Hour,var.Minute,var.Second);
    printf(" Epoch seconds: %ld\n", (long) t_of_day);
    return (long) t_of_day;
}

unsigned long  GetHours(double NumberOfHours)
{
    // Seconds * Minutes * Hours
    return 60 * 60 * NumberOfHours;
}

// allows fractional days 
double DayToSeconds(double Days)
{   
    return Days * /* Hours */ 24 * /* Minutes */ 60 * /* Seconds */ 60;
}

// I can manually do it
// I need to worry about the limit of what an int can hold 
int TotalDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31}; // don't forget about leap year for total days on feb
char MonthNames[12][20] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
double GetTotalSeconds(struct MyDateTime dayvar)
{
    printf("\nCalculating seconds\n");
    // Year 
    double SecondsOfYears = DayToSeconds(dayvar.Year * 365);
    printf("Year: %d, Seconds: %lf\n",dayvar.Year,SecondsOfYears);

    // Month
    int Total = 0;
    int i;
    for(i = 0; i < dayvar.Month-1;i++) // I do not want to count current month since that value is in the days part of the struct
    {
        printf("    Adding %s (%d), ",MonthNames + i, TotalDays[i]);
        // i==1 is indexing february
        if((i == 1) && !(dayvar.Year % 4)){Total = Total + TotalDays[i] + 1;} // If we are on leap year 
        else{Total = Total + TotalDays[i];}
        printf("total is %d\n", Total);
    }
    printf("Total days from %s to %s is %d, total seconds ",MonthNames, MonthNames + (i-1), Total);
    double SecondsOfMonths = DayToSeconds(Total);
    printf("%lf\n",dayvar.Month,SecondsOfMonths);

    // Day
    double SecondsOfDays = DayToSeconds(dayvar.Day);
    printf("Day: %d, Seconds: %lf\n",dayvar.Day,SecondsOfDays);

    // Hour
    double SecondsOfHours = dayvar.Hour * /* Minutes */ 60 * /* Seconds */ 60;
    printf("Hour: %d, Seconds: %lf\n",dayvar.Hour,SecondsOfHours);

    // Minute
    double SecondsOfMinutes = dayvar.Minute * /* Seconds */ 60;
    printf("Minute: %d, Seconds: %lf\n",dayvar.Minute,SecondsOfMinutes);

    // Second
    double SecondsOfSeconds = (double)dayvar.Second;
    printf("Seconds: %lf\n",SecondsOfSeconds);

    return SecondsOfYears + SecondsOfMonths + SecondsOfDays + SecondsOfHours + SecondsOfMinutes + SecondsOfSeconds;
}
