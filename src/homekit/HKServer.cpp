#include "HKServer.h"
#include "HKConnection.h"

using namespace spark;

HKServer::HKServer() {
  persistor = new HKPersistor();

}
void HKServer::setup () {
  persistor->loadRecordStorage();

  //bonjour.setUDP( &udp );
  //bonjour.begin(deviceName);
  //setPaired(false);
}

void HKServer::setPaired(bool p) {
  paired = p;
  bonjour.removeAllServiceRecords();
  int r = bonjour.addServiceRecord(deviceName "._hap",
                          TCP_SERVER_PORT,
                          MDNSServiceTCP,
                          "\x4sf=1\x14id=" deviceIdentity "\x6pv=1.0\x04\c#=1\x04s#=1\x04\ff=1\x0Bmd=" deviceName "\x4\ci=5"); //ci=5-lightbulb, ci=2 bridge
  Serial.printf("Bonjour paired %d, r: %d\n", paired,r);
}

TCPClient client;
HKConnection *connection = NULL;
void HKServer::handle() {
  //bonjour.run();

  if (!socket_handle_valid(server_socket_handle)) {
      server_socket_handle = socket_create_tcp_server(TCP_SERVER_PORT, _nif);
      if (socket_handle_valid(server_socket_handle)) {
        Serial.printf("Socket server created at port %d\n", TCP_SERVER_PORT);
        Serial.println(WiFi.localIP());
      }
  }

  if (socket_handle_valid(server_socket_handle)) {
    int client_socket = socket_accept(server_socket_handle);

    if (socket_handle_valid(client_socket))
    {
      Serial.println("Client connected.");
      clients.push_back(client_socket);
    }
  }

  int i = clients.size() - 1;
  while(i >= 0) {
    int s = clients.at(i);
    socklen_t size = 1024;
    uint8_t buffer[size];
    memset(buffer,0,size);
    int total = 0;
    int result = 0;

    while (result = socket_receive(s, buffer + total, size - total, 0) > 0)   {
      total += result;
    }
    if(result < 0) {
      //error or closed
      Serial.println("Client disconnected.");
      clients.erase(clients.begin() + i);
    }
    if(total > 0) {
      Serial.printf("Read from socket %d count %d\n", s, total);
      Serial.printf("%s\n", buffer);

      socket_send(s,buffer, total);
    }
    if(!socket_handle_valid(s)) {
      Serial.printf("Socket not valid %d\n", s);
      Serial.println("Client disconnected.");
      clients.erase(clients.begin() + i);
    }

    i--;
  }
  //Serial.println(WiFi.localIP());

/*
  if(!connection) {
    TCPClient newClient = server.available();
    if(newClient) {
      Serial.println("Client connected.");
      //clients.insert(clients.begin(),new HKConnection(this,newClient));
      connection = new HKConnection(this,newClient);
    }

  }
  if(connection) {
    if(connection->isConnected()) {
      connection->handleConnection();
    } else {
      //connection.close();
      free(connection);
      connection = NULL;
    }
  }
*/
  /*
  int i = clients.size() - 1;
  while(i >= 0) {
    HKConnection *conn = clients.at(i);

    conn->handleConnection();
    if(!conn->isConnected()) {
      conn->close();
      Serial.println("Client removed.");
      clients.erase(clients.begin() + i);
    }

    i--;
  }
  */


}
