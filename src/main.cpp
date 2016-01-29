#include <string>


#include <serial/serial.h>


using namespace serial;

using std::string;


int main(){
  Serial port1("/dev/ttyS0");

  port1.close();

  return 1;
}










