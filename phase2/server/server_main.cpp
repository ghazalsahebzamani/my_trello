#include <iostream>
#include "Myserver.h"
using namespace std;
// #include "exp.h"
// 'Server' is an abstract class, so define your own server class inheriting from the 'Server'
int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "valid operation: " << argv[0] << " [port number]\n";
    exit(-1);
  }
  
  MyServer server(Tools::mystoi(argv[1]));
  server.run();
  return 0;
}
