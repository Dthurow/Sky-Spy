#include "drones.h"

id_data uavs[MAX_UAVS] = {0};

id_data* next_uav(uint8_t* mac) {
  for (int i = 0; i < MAX_UAVS; i++) {
    if (memcmp(uavs[i].mac, mac, 6) == 0)
      return &uavs[i];
  }
  for (int i = 0; i < MAX_UAVS; i++) {
    if (uavs[i].mac[0] == 0)
      return &uavs[i];
  }
  return &uavs[0];
}

bool drones_detected(unsigned long current_milliseconds, int length)
{
    for (int i = 0; i < MAX_UAVS; i++) {
      if (uavs[i].mac[0] != 0 && (current_milliseconds - uavs[i].last_seen) < length) {
        return true;
      }
    }
    return false;
}