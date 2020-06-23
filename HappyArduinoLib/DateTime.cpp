#include <DateTime.h>

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const uint8_t daysInMonth [] PROGMEM = { 31,28,31,30,31,30,31,31,30,31,30 };

static uint16_t date2days(uint16_t y, uint8_t m, uint8_t d) {
    if (y >= 2000)
        y -= 2000;
    uint16_t days = d;
    for (uint8_t i = 1; i < m; ++i)
        days += pgm_read_byte(daysInMonth + i - 1);
    if (m > 2 && y % 4 == 0)
        ++days;
    return days + 365 * y + (y + 3) / 4 - 1;
}

static long time2long(uint16_t days, uint8_t h, uint8_t m, uint8_t s) {
    return ((days * 24L + h) * 60 + m) * 60 + s;
}

CDateTime::CDateTime (uint32_t t) {
  t -= SECONDS_FROM_1970_TO_2000;    // bring to 2000 timestamp from 1970

  ss = t % 60;
  t /= 60;
  mm = t % 60;
  t /= 60;
  hh = t % 24;
  uint16_t days = t / 24;
  uint8_t leap;
  for (yOff = 0; ; ++yOff) {
    leap = yOff % 4 == 0;
    if (days < 365 + leap)
      break;
    days -= 365 + leap;
  }
  for (m = 1; m < 12; ++m) {
    uint8_t daysPerMonth = pgm_read_byte(daysInMonth + m - 1);
    if (leap && m == 2)
      ++daysPerMonth;
    if (days < daysPerMonth)
      break;
    days -= daysPerMonth;
  }
  d = days + 1;
}

/**************************************************************************/
CDateTime::CDateTime (uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec) {
    if (year >= 2000)
        year -= 2000;
    yOff = year;
    m = month;
    d = day;
    hh = hour;
    mm = min;
    ss = sec;
}

CDateTime::CDateTime (const CDateTime& copy):
  yOff(copy.yOff),
  m(copy.m),
  d(copy.d),
  hh(copy.hh),
  mm(copy.mm),
  ss(copy.ss)
{}

static uint8_t conv2d(const char* p) {
    uint8_t v = 0;
    if ('0' <= *p && *p <= '9')
        v = *p - '0';
    return 10 * v + *++p - '0';
}

CDateTime::CDateTime (const char* date, const char* time) {
    // sample input: date = "Dec 26 2009", time = "12:34:56"
    yOff = conv2d(date + 9);
    // Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
    switch (date[0]) {
        case 'J': m = (date[1] == 'a') ? 1 : ((date[2] == 'n') ? 6 : 7); break;
        case 'F': m = 2; break;
        case 'A': m = date[2] == 'r' ? 4 : 8; break;
        case 'M': m = date[2] == 'r' ? 3 : 5; break;
        case 'S': m = 9; break;
        case 'O': m = 10; break;
        case 'N': m = 11; break;
        case 'D': m = 12; break;
    }
    d = conv2d(date + 4);
    hh = conv2d(time);
    mm = conv2d(time + 3);
    ss = conv2d(time + 6);
}

CDateTime::CDateTime (const __FlashStringHelper* date, const __FlashStringHelper* time) {
    // sample input: date = "Dec 26 2009", time = "12:34:56"
    char buff[11];
    memcpy_P(buff, date, 11);
    yOff = conv2d(buff + 9);
    // Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
    switch (buff[0]) {
        case 'J': m = (buff[1] == 'a') ? 1 : ((buff[2] == 'n') ? 6 : 7); break;
        case 'F': m = 2; break;
        case 'A': m = buff[2] == 'r' ? 4 : 8; break;
        case 'M': m = buff[2] == 'r' ? 3 : 5; break;
        case 'S': m = 9; break;
        case 'O': m = 10; break;
        case 'N': m = 11; break;
        case 'D': m = 12; break;
    }
    d = conv2d(buff + 4);
    memcpy_P(buff, time, 8);
    hh = conv2d(buff);
    mm = conv2d(buff + 3);
    ss = conv2d(buff + 6);
}

char* CDateTime::toString(char* buffer){
		for(int i=0;i<strlen(buffer)-1;i++){
		if(buffer[i] == 'h' && buffer[i+1] == 'h'){
			buffer[i] = '0'+hh/10;
			buffer[i+1] = '0'+hh%10;
		}
		if(buffer[i] == 'm' && buffer[i+1] == 'm'){
			buffer[i] = '0'+mm/10;
			buffer[i+1] = '0'+mm%10;
		}
		if(buffer[i] == 's' && buffer[i+1] == 's'){
			buffer[i] = '0'+ss/10;
			buffer[i+1] = '0'+ss%10;
		}
    if(buffer[i] == 'D' && buffer[i+1] =='D' && buffer[i+2] =='D'){
      static PROGMEM const char day_names[] = "SunMonTueWedThuFriSat";
      const char *p = &day_names[3*dayOfTheWeek()];
      buffer[i] = pgm_read_byte(p);
      buffer[i+1] = pgm_read_byte(p+1);
      buffer[i+2] = pgm_read_byte(p+2);
    }else
		if(buffer[i] == 'D' && buffer[i+1] == 'D'){
			buffer[i] = '0'+d/10;
			buffer[i+1] = '0'+d%10;
		}
    if(buffer[i] == 'M' && buffer[i+1] =='M' && buffer[i+2] =='M'){
      static PROGMEM const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";
      const char *p = &month_names[3*(m-1)];
      buffer[i] = pgm_read_byte(p);
      buffer[i+1] = pgm_read_byte(p+1);
      buffer[i+2] = pgm_read_byte(p+2);      
    }else
		if(buffer[i] == 'M' && buffer[i+1] == 'M'){
			buffer[i] = '0'+m/10;
			buffer[i+1] = '0'+m%10;
		}
		if(buffer[i] == 'Y'&& buffer[i+1] == 'Y'&& buffer[i+2] == 'Y'&& buffer[i+3] == 'Y'){
			buffer[i] = '2';
			buffer[i+1] = '0';
			buffer[i+2] = '0'+(yOff/10)%10;
			buffer[i+3] = '0'+yOff%10;
		}else
		if(buffer[i] == 'Y'&& buffer[i+1] == 'Y'){
			buffer[i] = '0'+(yOff/10)%10;
			buffer[i+1] = '0'+yOff%10;
		}

	}
	return buffer;
}

uint8_t CDateTime::dayOfTheWeek() const {
    uint16_t day = date2days(yOff, m, d);
    return (day + 6) % 7; // Jan 1, 2000 is a Saturday, i.e. returns 6
}

uint32_t CDateTime::unixtime(void) const {
  uint32_t t;
  uint16_t days = date2days(yOff, m, d);
  t = time2long(days, hh, mm, ss);
  t += SECONDS_FROM_1970_TO_2000;  // seconds from 1970 to 2000

  return t;
}

CDateTime CDateTime::operator+(const CTimeSpan& span) {
  return CDateTime(unixtime()+span.totalseconds());
}

CDateTime CDateTime::operator-(const CTimeSpan& span) {
  return CDateTime(unixtime()-span.totalseconds());
}

CTimeSpan CDateTime::operator-(const CDateTime& right) {
  return CTimeSpan(unixtime()-right.unixtime());
}

bool CDateTime::operator<(const CDateTime& right) const {
  return unixtime() < right.unixtime();
}

bool CDateTime::operator==(const CDateTime& right) const {
  return unixtime() == right.unixtime();
}

String CDateTime::timestamp(timestampOpt opt){
  char buffer[20];

  //Generate timestamp according to opt
  switch(opt){
    case TIMESTAMP_TIME:
    //Only time
    sprintf(buffer, "%02d:%02d:%02d", hh, mm, ss);
    break;
    case TIMESTAMP_DATE:
    //Only date
    sprintf(buffer, "%d-%02d-%02d", 2000+yOff, m, d);
    break;
    default:
    //Full
    sprintf(buffer, "%d-%02d-%02dT%02d:%02d:%02d", 2000+yOff, m, d, hh, mm, ss);
  }
  return String(buffer);
}

CTimeSpan::CTimeSpan (int32_t seconds):
  _seconds(seconds)
{}

CTimeSpan::CTimeSpan (int16_t days, int8_t hours, int8_t minutes, int8_t seconds):
  _seconds((int32_t)days*86400L + (int32_t)hours*3600 + (int32_t)minutes*60 + seconds)
{}

CTimeSpan::CTimeSpan (const CTimeSpan& copy):
  _seconds(copy._seconds)
{}

CTimeSpan CTimeSpan::operator+(const CTimeSpan& right) {
  return CTimeSpan(_seconds+right._seconds);
}

CTimeSpan CTimeSpan::operator-(const CTimeSpan& right) {
  return CTimeSpan(_seconds-right._seconds);
}
