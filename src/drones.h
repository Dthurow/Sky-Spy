#ifndef DRONES_H
#define DRONES_H

#include "opendroneid.h"

struct id_data {
  uint8_t  mac[6];
  int      rssi;
  uint32_t last_seen;
  char     op_id[ODID_ID_SIZE + 1];
  char     uav_id[ODID_ID_SIZE + 1];
  double   lat_d;
  double   long_d;
  double   base_lat_d;
  double   base_long_d;
  int      altitude_msl;
  int      height_agl;
  int      speed;
  int      heading;
  int      flag;
};

#define MAX_UAVS 32


id_data* next_uav(uint8_t* mac);

// return true if at least one drone has been detected within length milliseconds
bool drones_detected(unsigned long current_milliseconds, int length);

#endif