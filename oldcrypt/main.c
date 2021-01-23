
#include <iostream>
#include <string>
#include "viju2d.hpp"
#include "rot13.hpp"
//#include "parse.cpp"


int32_t main(void){
  char hoge[]="WELCOME{GO_TO_THE_NEXT}\x00";
  viju2d test((uint8_t*)nullptr,(uint8_t*)hoge);
  test.updatekey((uint8_t*)"ABCDEF");
  test.print_plain();
  test.encode();
  test.print_encoded();
  test.decode();
  test.print_all();

  std::string te("W?L?OM??");
  viju2d ex((uint8_t*)"WFNFSRE{IR_YO_VKI_NFZW}",(uint8_t*)nullptr);
  test.find_key(te);
  std::cout << "IC : "<< test.IC() << std::endl;
  return 0;
}



