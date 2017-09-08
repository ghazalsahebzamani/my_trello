#include "client_socket.h"
#include <cstdlib>
#include <fstream>
#include "funcs.h"
#include "exp.h"
using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "valid operation: " << argv[0] << " [server address] [server port]\n";
    exit(-1);
  }
  
  ClientSocket socket(string(argv[1]), Tools::mystoi(argv[2]));
  cout << "# connection established\n";
  
  string line;
  // while (getline(cin, line)) {
  //   if (line == ":q")
  //     break;
  //   socket.send(line);
  //   cout << socket.receive() << endl;
  //   socket.status();
  // }
  istream in;
  ostream out;

    while(true){
    try{
      //process(_trello,cin,cout);
      socket.send("show me the state");
      cout<<socket.receive();
    }
    catch(Quit){
      cout<<"Goodbye!"<<endl;
      clear_file("temp2.txt");
      return 0;
    }

  }
  
  return 0;
}
