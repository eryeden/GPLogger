#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

#include <serial/serial.h>

using namespace serial;

using std::string;
using namespace std;

int main(){

  //ログファイルを分割して保存する
  int log_maxline = 100;	// 最大行数
  int log_filemax = 10;		// 何個ログファイルを作るか
  int strm_idx = 0;		// いま何番目のファイルに書き込んでいるか
  int line_idx = 0;		// いま何行目か
  vector<unique_ptr<ofstream>> strms;	// ファイルストリームベクタ
  for(int i = 0; i < log_filemax; ++i){
    string fname = "log";
    fname += to_string(i+1);
    fname += ".txt";
    strms.emplace_back(new ofstream(fname));
  }
  
  unsigned long baud = 115200;
  string comport = "/dev/ttyACM0";
  
  Serial port1(comport, baud);

  //Check is com port open
  if(port1.isOpen()){
    cout << comport << " is available" << endl;
  }else{
    cout << comport  << " is not available" << endl;
    port1.close();
    return 0;
  }

  string buffer;
  string tmp;
  while(1){

    //改行文字がくるまで受信する Readlineを使うのが一番な気がするがうまく行かない
    buffer.clear();
    while(1){
      if(port1.available() > 0){
	tmp = port1.read();
	if(tmp == "\n"){
	  break;
	}
	buffer += tmp;
      }
    }
    cout << buffer << endl;

    line_idx++;
    *strms[strm_idx] << buffer << endl;
    if(line_idx == log_maxline){
      line_idx = 0;
      strm_idx++;
      if(strm_idx == log_filemax){
	break;
      }
    }
    
    
    
  }
  
  port1.close();

  return 1;
}










