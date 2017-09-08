#include "client_socket.h"
#include <cstdlib>
#include <fstream>
#include "newfuncs.h"
#include "exp.h"
using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "valid operation: " << argv[0] << " [server address] [server port]\n";
    exit(-1);
  }
  
  ClientSocket socket(string(argv[1]), Tools::mystoi(argv[2]));
  cout << "# connection established\n";
    string c;
    while(true)
    {
      try{
        while(true){
          try
          {
            string command;
            socket.send("start");
            cout<<socket.receive();
            cin>>c;
            call_write(c);
            if(c.size()>1)
              throw BadIO();
            command="check my order"+c;
            socket.send(command);
            string msg=socket.receive();
            if(msg=="BadIO error!")
              throw BadIO();
            break;
          }
              catch(BadIO& exp)
          {
            cout<<exp.what()<<endl;
          }
        }
          client_event_check(c[0],socket,cout,cin);
        }

        catch(Quit){
          cout<<"Goodbye!"<<endl;
          clear_file("temp2.txt");
          return 0;
        }

  }
  
  return 0;
}
