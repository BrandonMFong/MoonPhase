
#include <time.h>

// time_t t = time(NULL);
// struct tm tm = *localtime(&t);
// printf("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

struct DateTime
{
    int Month, Day, Year;
    int Hour, Minute, Second;
};

DateTime GetDateTime()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    struct DateTime dt = {tm.tm_mon, tm.tm_mday, tm.tm_year, tm.tm_hour, tm.tm_min, tm.tm_sec};
    return dt;
}