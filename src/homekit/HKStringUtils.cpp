#include "HKStringUtils.h"

#include <stdio.h>
#ifdef PARTICLE_COMPAT
#include "../../example/HKTester/HKTester/Particle_Compat/particle_compat.h"
#else
#include <Particle.h>
#endif

const char *copyLine(const char *rawData, char *destination) {
    int i;
    for (i = 0; rawData[i] != '\r' && rawData[i] != 0; i++) {
        destination[i] = rawData[i];
    }
    i++;
    if (rawData[i] == '\n')
        return &rawData[i+1];
    else return &rawData[i];
}

const char *skipTillChar(const char *ptr, const char target) {
    for (; (*ptr)!=0&&(*ptr)!=target; ptr++);  ptr++;
    return ptr;
}

void print_hex_memory(void *mem, int count) {
  int i;
  unsigned char *p = (unsigned char *)mem;
  for (i=0; i < count; i++) {
    Serial.printf("0x%02x, ", p[i]);
    if ((i%16==0) && i)
      Serial.printf("\n");
  }
  Serial.printf("\n");
}

std::string format(const std::string& format, ...)
{
    va_list args;
    va_start (args, format);
    size_t len = vsnprintf(NULL, 0, format.c_str(), args);
    va_end (args);
    std::vector<char> vec(len + 1);
    va_start (args, format);
    vsnprintf(&vec[0], len + 1, format.c_str(), args);
    va_end (args);
    return &vec[0];
}
