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
  //TODO once filled uavs list, this always returns
  // first in the list, but should let you continue to loop
  // through the buffer
  return &uavs[0];
}

int drones_detected(unsigned long current_milliseconds, int length)
{
    int cnt = 0;
    for (int i = 0; i < MAX_UAVS; i++) {
        if (uavs[i].mac[0] == 0){
            break; //end of the list
      }
      if (current_milliseconds - uavs[i].last_seen < length) {
        cnt++;
      }
      
    }
    return cnt;
}

int total_detected(){
    for (int i = 0; i < MAX_UAVS; i++) {
    if (uavs[i].mac[0] == 0)
      return i;
    }
    return MAX_UAVS;
}