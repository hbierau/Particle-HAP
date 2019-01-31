#ifndef  HKServer_H
#define HKServer_H
#include "HKConfig.h"
#include "HKBonjour.h"
#include "HKNetworkMessage.h"
#include "HKNetworkMessageData.h"
#include "HKPersistor.h"
#include <Particle.h>
#include <vector>

#include "socket_hal.h"
#include "spark_wiring_network.h"

class HKConnection;

class HKServer {
private:
  sock_result_t server_socket_handle = socket_handle_invalid();
  network_interface_t _nif = 0;

  HKBonjour bonjour;
  UDP udp;
  bool paired = false;
  std::vector<HKConnection*> clients;
public:
  HKPersistor *persistor;
  HKServer();
  void setup ();
  void setPaired(bool paired);
  void handle();
};
#endif /* end of include guard: HKServer */
