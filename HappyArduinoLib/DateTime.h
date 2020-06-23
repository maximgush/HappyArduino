#pragma once

#include <Arduino.h>

#define SECONDS_PER_DAY       86400L  ///< 60 * 60 * 24
#define SECONDS_FROM_1970_TO_2000 946684800  ///< Unixtime for 2000-01-01 00:00:00, useful for initialization

class CTimeSpan {
public:
  CTimeSpan (int32_t seconds = 0);
  CTimeSpan (int16_t days, int8_t hours, int8_t minutes, int8_t seconds);
  CTimeSpan (const CTimeSpan& copy);

  int16_t days() const         { return _seconds / 86400L; }
  int8_t  hours() const        { return _seconds / 3600 % 24; }
  int8_t  minutes() const      { return _seconds / 60 % 60; }
  int8_t  seconds() const      { return _seconds % 60; }
  int32_t totalseconds() const { return _seconds; }

  CTimeSpan operator+(const CTimeSpan& right);
  CTimeSpan operator-(const CTimeSpan& right);

protected:
  int32_t _seconds;   ///< Actual CTimeSpan value is stored as seconds
};


class CDateTime {
public:
  CDateTime (uint32_t t = SECONDS_FROM_1970_TO_2000);
  CDateTime (uint16_t year, uint8_t month, uint8_t day,
              uint8_t hour = 0, uint8_t min = 0, uint8_t sec = 0);
  CDateTime (const CDateTime& copy);
  CDateTime (const char* date, const char* time);
  CDateTime (const __FlashStringHelper* date, const __FlashStringHelper* time);
  char* toString(char* buffer);

  uint16_t year() const       { return 2000 + yOff; }
  uint8_t month() const       { return m; }
  uint8_t day() const         { return d; }
  uint8_t hour() const        { return hh; }
  uint8_t minute() const      { return mm; }
  uint8_t second() const      { return ss; }
  uint8_t dayOfTheWeek() const;

  /** ISO 8601 Timestamp function */
  enum timestampOpt{
    TIMESTAMP_FULL, // YYYY-MM-DDTHH:MM:SS
    TIMESTAMP_TIME, // HH:MM:SS
    TIMESTAMP_DATE  // YYYY-MM-DD
  };
  String timestamp(timestampOpt opt = TIMESTAMP_FULL);

  CDateTime operator+(const CTimeSpan& span);
  CDateTime operator-(const CTimeSpan& span);
  CTimeSpan operator-(const CDateTime& right);
  
  bool operator<(const CDateTime& right) const;
  bool operator>(const CDateTime& right) const  { return right < *this; }
  bool operator<=(const CDateTime& right) const { return !(*this > right); }
  bool operator>=(const CDateTime& right) const { return !(*this < right); }
  bool operator==(const CDateTime& right) const;
  bool operator!=(const CDateTime& right) const { return !(*this == right); }
  
protected:
  uint8_t yOff;   ///< Year offset from 2000
  uint8_t m;      ///< Month 1-12
  uint8_t d;      ///< Day 1-31
  uint8_t hh;     ///< Hours 0-23
  uint8_t mm;     ///< Minutes 0-59
  uint8_t ss;     ///< Seconds 0-59
  
private:
	uint32_t unixtime(void) const;
};

//#include "DateTime.cpp"
