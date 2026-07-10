#include "drones.h"

id_data uavs[MAX_UAVS] = {0};


// TEST DATA
// id_data uavs[MAX_UAVS] =
// {
//     {
//     .mac={0x60,0x60,0x1f,0x85,0x1c,0xbe},
//     .rssi=-64,
//     .last_seen = 0,
//     .lat_d=44.926823,
//     .long_d=-93.232246,
//     .base_lat_d=44.926828,
//     .base_long_d=-93.232215,
//     .altitude_msl=226,
//     },
//         {
//     .mac={0x60,0x60,0x1f,0x63,0x89,0xb0},
//     .rssi=-79,
//     .last_seen = 10,
//     .lat_d=44.9357795,
//     .long_d=-93.2302474,
//     .base_lat_d=44.926828,
//     .base_long_d=-93.232215,
//     .altitude_msl=226,
//     }
    
// };


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

id_data* find_next_active_drone(unsigned long current_milliseconds, int timeout, id_data* current_drone)
{
    bool found_curr = false;

    if (current_drone == nullptr){
        found_curr = true;
    }

    for (int i = 0; i < MAX_UAVS; i++) {
        if (uavs[i].mac[0] == 0){
            break; //end of the list
        }
        if (found_curr && current_milliseconds - uavs[i].last_seen < timeout) {
            return &uavs[i];
        }
        if (current_drone != nullptr && memcmp(uavs[i].mac, current_drone->mac, 6) == 0){
            found_curr = true;
        }
      
    }
    return nullptr;
}

id_data* find_prev_active_drone(unsigned long current_milliseconds, int timeout, id_data* current_drone)
{
    bool found_curr = false;

    if (current_drone == nullptr){
        found_curr = true;
    }

    for (int i = MAX_UAVS - 1; i >= 0; i--) {
        if (uavs[i].mac[0] == 0){
            continue; //outside of the list, keep going until we find the end
        }
        if (found_curr && current_milliseconds - uavs[i].last_seen < timeout) {
            return &uavs[i];
        }
        if (current_drone != nullptr && memcmp(uavs[i].mac, current_drone->mac, 6) == 0){
            found_curr = true;
        }
      
    }
    return nullptr;
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