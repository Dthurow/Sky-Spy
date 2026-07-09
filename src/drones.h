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

//either returns pointer to ID matching the mac, or the next empty spot in the list
id_data* next_uav(uint8_t* mac);

// return count of drones currently detected within length milliseconds
int drones_detected(unsigned long current_milliseconds, int length);


// return count of all drones
int total_detected();

#endif