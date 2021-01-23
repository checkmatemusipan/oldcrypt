#include <iostream>
#include <string>
#include <cstring>
//user lib
#include "parse.cpp"

//#define FOR(n) for(uint32_t i=0;i<n;i++)
#ifndef _rot13_
#define _rot13_
class rot13 {
  protected:
   uint32_t elen;
   uint32_t plen;
   uint8_t* enc;
   uint8_t* plain;
  public:
   //constructor
   rot13(uint8_t* Enc,uint8_t* Plain);
   //destructor
   ~rot13();
   //getter
   uint8_t* get_plain();
   uint8_t* get_enc();
   //mov ...
   bool mov_plain(uint8_t* text);
   bool mov_enc(uint8_t* text);
   //rotate
   void rotN(uint8_t N);
   void rotN_dec(uint8_t N);
   //find key
//   bool decode(uint8_t* keyword);
   //print
   void print_plain() const;
   void print_enc() const;
   void print_all() const;
};

uint8_t* rot13::get_plain(){
  return this->plain;
}

uint8_t* rot13::get_enc(){
  return this->enc;
}

bool rot13::mov_plain(uint8_t* text){
   uint64_t len = 0;
   len = std::strlen((const char*)text);
   if(len <= 0 ){
     return false;
   }
   this->plen = len;
   this->plain = new uint8_t[sizeof(uint8_t)*(len/sizeof(uint8_t)+1)];
   FOR(len){
      this->plain[i] = text[i];
   }
   if( std::strcmp((char*)this->plain,(char*)text) != 0){
      return false;
   }
   return true;
}
/*
 [&len](uint8_t* text) => bool {
    len = std::strlen((const char*)text);
    if(len <= 0 ){
      return false;
    }
    return true;
 }
 */

bool rot13::mov_enc(uint8_t* text){
   uint64_t len = 0;
      len = std::strlen((const char*)text);
   if(len <= 0 ){
     return false;
   }
   this->elen = len;
   this->enc = new uint8_t[sizeof(uint8_t)*(len/sizeof(uint8_t)+1)];
   FOR(len){
      this->enc[i] = text[i];
   }
   if( std::strcmp((char*)this->enc,(char*)text) != 0){
      return false;
   }
   return true;
}

//encode
void rot13::rotN(uint8_t N){
  if(this->enc == nullptr || this->elen == 0){
    if(this->plen == 0 || this->plain == nullptr ){
      std::cerr << "rot13::rotN cannot encode b/c plain length is 0 or plainptr is nullptr\n";
      return;
    }
    this->elen= this->plen;
    this->enc = new uint8_t [this->plen+1];
  }else if(this->plen > this->elen ){
    delete [] this->enc;
    this->enc = new uint8_t [this->plen+1];
    this->elen= this->plen;
  }

  FOR(this->plen){
    if(isUpper(this->plain[i]) ){
      if((this->plain[i]+N) > 'Z' ){
	this->enc[i] = this->plain[i]+N-26;
      }else{
	this->enc[i] = this->plain[i]+N;
      }
    }else if(isLower(this->plain[i]) ){
      if((this->plain[i]+N) > 'z'){
	this->enc[i] = this->plain[i]+N-26;
      }else{
        this->enc[i] = this->plain[i]+N;
      }	
    }else{
	this->enc[i] = this->plain[i];
    }
  }
}

void rot13::rotN_dec(uint8_t N){
  if(this->enc == nullptr || this->elen == 0){
    std::cerr << "rot13::rotN_dec connot encode b/c enc length is 0 or encptr is nullptr\n";
    return;
  }else if(this->plain == nullptr || this->plen == 0){
    this->plain = new uint8_t [this->elen+1];
    this->plen  = this->elen;
  }
  if(this->elen > this->plen ){
   delete [] this->plain;
   this->plain = new uint8_t [this->elen+1];
   this->plen  = this->elen;
  }
  FOR(this->elen){
    if(isUpper(this->enc[i]) ){
      if((this->enc[i]-N) < 'A'){
	this->plain[i] = this->enc[i]-N+26;
      }else{
	this->plain[i] = this->enc[i]-N;
      }
    }else if(isLower(this->enc[i])){
	if((this->enc[i]-N) < 'a'){
          this->plain[i] = this->enc[i]-N+26;
	}else{
	  this->plain[i] = this->enc[i]-N;
	}
    }else{
      this->plain[i] = this->enc[i];
    }
  }
  return;
}

void rot13::print_plain() const{
   std::cout << this->plain << std::endl;
}

void rot13::print_enc() const{
   std::cout << this->enc << std::endl;
}

void rot13::print_all() const{
   std::cout << "Plain   text length: "<< this->plen << " text: "<< this->plain << std::endl;
   std::cout << "Encoded text length: "<< this->elen << " text: "<< this->enc   << std::endl;
}

rot13::rot13(uint8_t* Enc,uint8_t* Plain){
   this->enc = nullptr;
   this->plain = nullptr;
   this->elen = 0;
   this->plen = 0;
// mov param
   this->elen = Enc == nullptr ? 0 : (uint32_t)std::strlen((char*)Enc);
   this->plen = Plain == nullptr ? 0 : (uint32_t)std::strlen((char*)Plain);

//   this->enc  = Enc; <-local
   if( Enc != nullptr ){
     if(!this->mov_enc(Enc)){
       std::cerr << "error: rot13::rot13 method mov_enc\n";
     }
   }
   if( Plain != nullptr ){
     if(!this->mov_plain(Plain)){
       std::cerr << "error: rot13::rot13 method mov_plain\n";
     }
   }
}

rot13::~rot13(){
   if(this->enc != nullptr){
     delete [] this->enc;
   }
   if(this->plain != nullptr){
     delete [] this->plain;
   }
}

#endif

/*
int32_t main(void){
  char ret[]="CVE0cve\x99Z";
  rot13 plain(nullptr,(uint8_t*)"ABC");
  plain.mov_plain((uint8_t*)ret);
  plain.rotN(5);
  plain.print_all();
  plain.mov_plain((uint8_t*)"CCC");  
  plain.rotN_dec(5);
  plain.print_all();
//  std::cout << match_char("ABCDEFG","\x90") << std::endl;
  return 0xdeadbeef;
}
*/
