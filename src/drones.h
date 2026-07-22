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
#define ACTIVE_DRONE_TIMEFRAME 7000

//return UAV at index
id_data* get_uav(uint8_t index);

//either returns pointer to ID matching the mac, or the next empty spot in the list
id_data* next_uav(uint8_t* mac);

// return count of drones currently detected within length milliseconds
int drones_detected(unsigned long current_milliseconds, int length);


// return count of all drones
int total_detected();

// finds the next previous active drone in the list that has been detected within the given timeout with an index less than the current_drone
id_data* find_next_active_drone(unsigned long current_milliseconds, int timeout, id_data * current_drone);

// finds the next previous active drone in the list that has been detected within the given timeout with an index less than the current_drone
id_data* find_prev_active_drone(unsigned long current_milliseconds, int timeout, id_data * current_drone);

#endif