#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#define INVALID_DATE (-1)
#endif /* __PROGTEST__ */
#include <math.h>
#define FULLMOON 29.5305902777777777

int leapYear(int y){
    if ( y == 1){
        return 1;
    }
    else if (y % 4 == 0 && y % 100 != 0)
    {
        return 1;
    }
    else if (y % 400 == 0 && y % 100 == 0)
    {
        return 1;
    }
    else if (y % 4 == 0 && y % 100 == 0)
    {
        return 0;
    }

    return 0;
}

int validateDate(int y, int m, int d)
{
    switch (m)
    {
        case 1://January
        case 3://March
        case 5://May
        case 7://July
        case 8://August
        case 10://October
        case 12://December
            if (d > 31)
            {
                return INVALID_DATE;
            }
            break;
        case 4://April
        case 6://June
        case 9://September
        case 11://November
            if (d > 30)
            {
                return INVALID_DATE;
            }
            break;
        case 2://February
            if (leapYear(y/*,m,d*/) && d > 29)
            {
                return INVALID_DATE;
            }
            else if (!(leapYear(y/*,m,d*/)) && d > 28)
            {
                return INVALID_DATE;
            }
            break;
        default:
            return INVALID_DATE;
    }

    return 1;
}

int month(int m, int y){
    int month[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    int res = 0;
    for (int i = 0; i < m-1; ++i) {
        if(i == 1){
            if(leapYear(y) == 1){
                res += 29;
            } else {
                res += 28;
            }
        } else {
            res += month[i];
        }
    }
    return res;
}

int dayDifference(int y1,int y2,int m1,int m2,int d1,int d2){
    int count = 0;
    for (int i = y1; i < y2; i++) {
        if( leapYear(i) == 1){
            count += 366;
        } else {
            count += 365;
        }
    }
    count -= month(m1,y1);
    count -= d1;
    count += month(m2, y2);
    count += d2;

    if(count < 0){
        count = count * -1;
    }

    return count;
}

void daysToDate(int days, int y, int m, int d ){
    int rem1, rem2, rem3, rem4, rem5;
    int year = 365;
    int year_4 = year * 4 +1;// 1461
    int year_100 = year_4 * 25 -1;// 36524
    int year_400 = year_100 * 4 + 1;// 146097
    int year_4000 = year_400 * 10 -1;// 1460969

    d = days;
    rem1 = d % year_4000;
    y = ((d - rem1)/year_4000) * 4000;

    d = rem1;

    if( rem1 > year_4000 - 365){
        y+=3999;
        d -= (year_4000-365);
    }

    rem2 = d % year_400;
    y += ((d - rem2)/year_400) * 400;

    d = rem2;
    if( rem2 > year_400 - 366){
        y+=399;
        d -= (year_400-366);
    }

    rem3 = d % year_100;
    y += ((d - rem3)/year_100) * 100;

    d = rem3;

    if( rem3 > year_100 - 365){
        y+=99;
        d -= (year_100-365);
    }

    rem4 = d % year_4;
    y += ((d - rem4)/year_4) * 4;

    d = rem4;

    if( rem4 > year_4 - 366){
        y+=3;
        d -= (year_4-366);
    }

    rem5 = (d % year);
    y += ((d - rem5)/year);

    d = rem5 - 1;

    if(d == 0){
        y -= 1;
        m = 12;
        d = 31;
    }

    y += 1;

    if (d <= 31) {
        m=1;
    } else if (d <= 59 + leapYear(y)) {
        m = 2;
        d-= 31;
    } else if (d <= 90 + leapYear(y)) {
        m = 3;
        d-= (59 + leapYear(y));
    } else if (d <= 120 + leapYear(y)) {
        m = 4;
        d-= (90 + leapYear(y));
    } else if (d <= 151 + leapYear(y)) {
        m = 5;
        d-= (120 + leapYear(y));
    } else if (d <= 181 + leapYear(y)) {
        m = 6;
        d-= (151 + leapYear(y));
    } else if (d <= 212 + leapYear(y)) {
        m = 7;
        d-= (181 + leapYear(y));
    } else if (d <= 242 + leapYear(y)) {
        m = 8;
        d-= (212 + leapYear(y));
    } else if (d <= 273 + leapYear(y)) {
        m = 9;
        d-= (242 + leapYear(y));
    } else if (d <= 303 + leapYear(y)) {
        m = 10;
        d-= (273 + leapYear(y));
    } else if (d <= 334 + leapYear(y)) {
        m = 11;
        d-= (303 + leapYear(y));
    } else if (d <= 364 + leapYear(y)) {
        m = 12;
        d-= (334 + leapYear(y));
    }
   //printf("Date: %d/%d/%d\n", y,m,d);


}


int isFullMoon ( int y, int m, int d )
{
    int diff = 0, tmp = 0;
    int refY = 2000, refM = 7, refD= 16;
    //double refH = 13, refMin = 55, refS = 12;
    double day,/*time,*/ res;
    double time = 0.86586811;

    if( validateDate(y,m,d) == INVALID_DATE){
        return INVALID_DATE;
    }

    if ( y >= refY){
        diff = dayDifference(refY, y, refM, m, refD, d);
    } else {
        diff = dayDifference(y, refY, m, refM, d, refD);
    }



    if(diff > 0)

        day = diff + time;
    else
         day = diff;


    res = floor(day / FULLMOON) * FULLMOON ;
    tmp = res;


    if ( round(res) == diff)
        return 1;
    else if( ( res - tmp ) > 0.40000 && ( res - tmp ) < 0.49999 )
        return 1;
    else
        return 0;
}


int prevFullMoon ( int y, int m, int d,
                   int * prevY, int * prevM, int * prevD )
{
    int refY = 1, refM = 1, refD = 1, diff = 0, days = 0;
    double res;

    if( validateDate(y,m,d) == INVALID_DATE){
        return INVALID_DATE;
    }
    diff = dayDifference(refY, y, refM, m, refD, d);
    diff+=1;

    if(isFullMoon(y,m,d) == 1){
        d-=1;
        while (isFullMoon(y,m,d) != 1){
            d--;
            if(d == 0){
                if (m == 1){
                    d=31;
                    m=12;
                    y--;
                } else if ( m == 11){
                    d=31 + leapYear(y);
                    m--;
                } else if ( m == 12){
                    d=30 + leapYear(y);
                    m--;
                } else if ( m == 2){
                    d=31;
                    m--;
                } else if ( m == 3){
                    d= 28 + leapYear(y);
                    m--;
                } else if ( m == 4){
                    d=31 + leapYear(y);
                    m--;
                }  else if ( m == 5){
                    d=30 + leapYear(y);
                    m--;
                } else if ( m == 6){
                    d= 31 + leapYear(y);
                    m--;
                } else if ( m == 7){
                    d=30 + leapYear(y);
                    m--;
                } else if ( m == 8){
                    d=31 + leapYear(y);
                    m--;
                } else if ( m == 9){
                    d=31+ leapYear(y);
                    m--;
                } else if ( m == 10){
                    d=30+ leapYear(y);
                    m--;
                }
            }
        }
        res = diff;

    } else {
        while (isFullMoon(y,m,d) != 1){
            d--;
            if(d == 0){
                if (m == 1){
                    d=31;
                    m=12;
                    y--;
                } else if ( m == 11){
                    d=31 + leapYear(y);
                    m--;
                } else if ( m == 12){
                    d=30 + leapYear(y);
                    m--;
                } else if ( m == 2){
                    d=31;
                    m--;
                } else if ( m == 3){
                    d= 28 + leapYear(y);
                    m--;
                } else if ( m == 4){
                    d=31 + leapYear(y);
                    m--;
                }  else if ( m == 5){
                    d=30 + leapYear(y);
                    m--;
                } else if ( m == 6){
                    d= 31 + leapYear(y);
                    m--;
                } else if ( m == 7){
                    d=30 + leapYear(y);
                    m--;
                } else if ( m == 8){
                    d=31 + leapYear(y);
                    m--;
                } else if ( m == 9){
                    d=31+ leapYear(y);
                    m--;
                } else if ( m == 10){
                    d=30+ leapYear(y);
                    m--;
                }
            }
        }
        res = diff;
        //res = round(diff-(2*FULLMOON));
    }
    days = res;
    daysToDate(days, y, m, d);
    *prevY = y;
    *prevM = m;
    *prevD = d;
    if(isFullMoon(*prevY, *prevM, *prevD) == 1)
        return 1;
    else
        return 0;


}

int nextFullMoon ( int y, int m, int d,
                   int * nextY, int * nextM, int * nextD )
{
    int refY = 1, refM = 1, refD = 1, diff = 0, days = 0;
    double res;

    if( validateDate(y,m,d) == INVALID_DATE){
        return INVALID_DATE;
    }

    diff = dayDifference(refY, y, refM, m, refD, d);
    diff+=1;

    if(isFullMoon(y,m,d) == 1){
        d+=1;
        while (isFullMoon(y,m,d) != 1){
            d++;
            if(d == 31 || d == 30){
                d=0;
                if(m==12){
                    m=1;
                    y++;
                }
                else{
                    m++;
                }
            }
        }
        res = diff;

    } else {
        while (isFullMoon(y,m,d) != 1){
            d++;
            if(d == 31 || d == 30){
                d=0;
                if(m==12){
                    m=1;
                    y++;
                }
                else{
                    m++;
                }
            }
        }
        res = diff;
    }

    days = res;
    daysToDate(days, y, m, d);
    *nextY = y;
    *nextM = m;
    *nextD = d;
    if(isFullMoon(*nextY, *nextM, *nextD) == 1)
        return 1;
    else
        return 0;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    int y, m, d;

    assert ( isFullMoon ( 2000, 7, 16 ) == 1 );
    assert ( isFullMoon ( 2017, 1, 11 ) == 0 );
    assert ( isFullMoon ( 2017, 1, 12 ) == 1 );
    assert ( isFullMoon ( 2017, 1, 13 ) == 0 );
    assert ( isFullMoon ( 2017, 11, 3 ) == 0 );
    assert ( isFullMoon ( 2017, 11, 4 ) == 1 );
    assert ( isFullMoon ( 2017, 11, 5 ) == 0 );
    assert ( isFullMoon ( 2019, 12, 11 ) == 1 );
    assert ( isFullMoon ( 2019, 12, 12 ) == 0 );
    assert ( isFullMoon ( 2019, 12, 13 ) == 0 );
    assert ( prevFullMoon ( 2017, 1, 11, &y, &m, &d ) == 1 && y == 2016 && m == 12 && d == 14 );
    assert ( prevFullMoon ( 2017, 1, 12, &y, &m, &d ) == 1 && y == 2016 && m == 12 && d == 14 );
    assert ( prevFullMoon ( 2017, 1, 13, &y, &m, &d ) == 1 && y == 2017 && m == 1 && d == 12 );
    assert ( prevFullMoon ( 2017, 11, 3, &y, &m, &d ) == 1 && y == 2017 && m == 10 && d == 5 );
    assert ( prevFullMoon ( 2017, 11, 4, &y, &m, &d ) == 1 && y == 2017 && m == 10 && d == 5 );
    assert ( prevFullMoon ( 2017, 11, 5, &y, &m, &d ) == 1 && y == 2017 && m == 11 && d == 4 );
    assert ( prevFullMoon ( 2019, 12, 11, &y, &m, &d ) == 1 && y == 2019 && m == 11 && d == 12 );
    assert ( prevFullMoon ( 2019, 12, 12, &y, &m, &d ) == 1 && y == 2019 && m == 12 && d == 11 );
    assert ( prevFullMoon ( 2019, 12, 13, &y, &m, &d ) == 1 && y == 2019 && m == 12 && d == 11 );
    assert ( nextFullMoon ( 2017, 1, 11, &y, &m, &d ) == 1 && y == 2017 && m == 1 && d == 12 );
    assert ( nextFullMoon ( 2017, 1, 12, &y, &m, &d ) == 1 && y == 2017 && m == 2 && d == 11 );
    assert ( nextFullMoon ( 2017, 1, 13, &y, &m, &d ) == 1 && y == 2017 && m == 2 && d == 11 );
    assert ( nextFullMoon ( 2017, 11, 3, &y, &m, &d ) == 1 && y == 2017 && m == 11 && d == 4 );
    assert ( nextFullMoon ( 2017, 11, 4, &y, &m, &d ) == 1 && y == 2017 && m == 12 && d == 3 );
    assert ( nextFullMoon ( 2017, 11, 5, &y, &m, &d ) == 1 && y == 2017 && m == 12 && d == 3 );
    assert ( nextFullMoon ( 2019, 12, 11, &y, &m, &d ) == 1 && y == 2020 && m == 1 && d == 10 );
    assert ( nextFullMoon ( 2019, 12, 12, &y, &m, &d ) == 1 && y == 2020 && m == 1 && d == 10 );
    assert ( nextFullMoon ( 2019, 12, 13, &y, &m, &d ) == 1 && y == 2020 && m == 1 && d == 10 );
    assert ( isFullMoon ( 2017, 1, 12 ) == 1 );
    assert ( isFullMoon ( 2017, 2, 11 ) == 1 );
    assert ( isFullMoon ( 2017, 3, 12 ) == 1 );
    assert ( isFullMoon ( 2017, 4, 11 ) == 1 );
    assert ( isFullMoon ( 2017, 5, 10 ) == 1 );
    assert ( isFullMoon ( 2017, 6, 9 ) == 1 );
    assert ( isFullMoon ( 2017, 7, 9 ) == 1 );
    assert ( isFullMoon ( 2017, 8, 7 ) == 1 );
    assert ( isFullMoon ( 2017, 9, 6 ) == 1 );
    assert ( isFullMoon ( 2017, 10, 5 ) == 1 );
    assert ( isFullMoon ( 2017, 11, 4 ) == 1 );
    assert ( isFullMoon ( 2017, 12, 3 ) == 1 );
    assert ( isFullMoon ( 2018, 1, 2 ) == 1 );
    assert ( isFullMoon ( 2018, 1, 31 ) == 1 );
    assert ( isFullMoon ( 2018, 3, 2 ) == 1 );
    assert ( isFullMoon ( 2018, 3, 31 ) == 1 );
    assert ( isFullMoon ( 2018, 4, 30 ) == 1 );
    assert ( isFullMoon ( 2018, 5, 29 ) == 1 );
    assert ( isFullMoon ( 2018, 6, 28 ) == 1 );
    assert ( isFullMoon ( 2018, 7, 27 ) == 1 );
    assert ( isFullMoon ( 2018, 8, 26 ) == 1 );
    assert ( isFullMoon ( 2018, 9, 25 ) == 0 );
    assert ( isFullMoon ( 2018, 10, 24 ) == 1 );
    assert ( isFullMoon ( 2018, 11, 23 ) == 1 );
    assert ( isFullMoon ( 2018, 12, 22 ) == 1 );
    assert ( isFullMoon ( 2019, 1, 21 ) == 1 );
    assert ( isFullMoon ( 2019, 2, 19 ) == 1 );
    assert ( isFullMoon ( 2019, 3, 21 ) == 1 );
    assert ( isFullMoon ( 2019, 4, 19 ) == 1 );
    assert ( isFullMoon ( 2019, 5, 18 ) == 0 );
    assert ( isFullMoon ( 2019, 6, 17 ) == 1 );
    assert ( isFullMoon ( 2019, 7, 16 ) == 0 );
    assert ( isFullMoon ( 2019, 8, 15 ) == 1 );
    assert ( isFullMoon ( 2019, 9, 14 ) == 1 );
    assert ( isFullMoon ( 2019, 10, 13 ) == 1 );
    assert ( isFullMoon ( 2019, 11, 12 ) == 1 );
    assert ( isFullMoon ( 2019, 12, 12 ) == 0 );
    assert ( isFullMoon ( 2000, 14, 10 ) == INVALID_DATE );
    assert ( prevFullMoon ( 2000, 11, 31, &y, &m, &d ) == INVALID_DATE );
    assert ( nextFullMoon ( 2001, 2, 29, &y, &m, &d ) == INVALID_DATE );
    assert ( isFullMoon ( 2004, 2, 29 ) == 0 );
    assert ( prevFullMoon ( 2100, 2, 29, &y, &m, &d ) == INVALID_DATE );
    assert ( nextFullMoon ( 2000, 2, 29, &y, &m, &d ) == 1 && y == 2000 && m == 3 && d == 20 );

    return 0;
}
#endif /* __PROGTEST__ */
