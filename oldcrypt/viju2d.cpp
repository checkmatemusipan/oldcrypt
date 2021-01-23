#include <iostream>
#include <string>
#include <cstring>
#include "parse.cpp"
//#define FOR(n) for(uint32_t i;i<n;i++)

class viju2d {//: public rot13 {
  private:
    std::string key;
    std::string plain;
    std::string encoded;
    std::string expectedkey;
  public: 
    viju2d(uint8_t* Enc,uint8_t* Plain);//: rot13(uint8_t* Enc,uint8_t* Plain);
    ~viju2d();
    
    bool updatekey(uint8_t* new_key);
    void encode();
    void decode();
    //analyze
    bool find_key(std::string keyword);
    uint32_t IC();
    //print
    void print_encoded() const;
    void print_plain() const;
    void print_expectedkey() const;
    void print_all() const;
};


viju2d::viju2d(uint8_t* Enc,uint8_t* Plain) {//: rot13(Enc,plain){
  if(Enc != nullptr){ this->encoded = (char*)Enc; }
  if(Plain != nullptr){ this->plain   = (char*)Plain; }
}

viju2d::~viju2d(){
}

bool viju2d::updatekey(uint8_t* new_key){
  this->key = (const char*)new_key;
  if(this->key.length() <= 0){ return false; }
  return true;
}

void viju2d::encode(){
  std::string alpha;
  std::string rotate;
  uint8_t offset = 0;
  this->encoded = "";
  FOR(26){
    alpha += 65+i;
  }
  FOR(std::strlen((const char*)this->plain.c_str())){
    if(!isAlpha(this->plain[i]) ){ 
      this->encoded += this->plain[i];
      continue;
    }
    offset = this->key[i%std::strlen((const char*)this->key.c_str())]-65;
    rotate = alpha.substr(offset,26-offset) + alpha.substr(0,offset);
    this->encoded += rotate[this->plain[i]-65] ;
  }
}

void viju2d::decode(){
  std::string alpha;
  std::string rotate;
  uint8_t idx = 0;
  this->plain = "";
  FOR(26){
    alpha += 65+i;
  }
  FOR(this->encoded.length()){
    if(!isAlpha(this->encoded[i]) ){
      this->plain+= this->encoded[i];
      continue;
    }
    idx = this->key[i%this->key.length()]-65;
    rotate = alpha.substr(idx,26-idx) + alpha.substr(0,idx);
    auto offset = rotate.find(this->encoded[i]);
    this->plain+= alpha[offset];
  }
}

// '?' is skipped
// param's keyword is expect plain
bool viju2d::find_key(std::string keyword){
  if(keyword.length() == 0){
    std::cerr << "error viju2d::find_key keyword length is 0 \n";
    return false;
  }
  std::string alpha;
  std::string rotate;
  std::string expectkey;
  uint8_t idx = 0;
  FOR(26){
    alpha += 65+i;
  }
  FOR(keyword.length()){
    if(!isAlpha(this->encoded[i]) ){
      this->plain+= this->encoded[i];
      expectkey += "?";
      continue;
    }
    if(keyword[i] == '?'){
      this->plain+= '?';
      expectkey += '?';
      continue;
    }
    idx = keyword[i]-65;
    for(uint32_t k=0;k< 26;k++){
      rotate = alpha.substr(k,26-k) + alpha.substr(0,k);
      if(rotate[idx] == this->encoded[i]){
	expectkey += alpha[k];
	break;
      }
    }
  }
  std::cout << "expectkey is : " << expectkey << std::endl;
  this->expectedkey = expectkey;
  return true;
}

//index of conincidence
//this function expect key term
uint32_t viju2d::IC(){
  uint32_t sum = 0;
  FOR(26){
    uint32_t alphabet = 65 + i;
    uint32_t tmp = 0;
    for(uint32_t k=0;k<this->encoded.length();k++){
      if( this->encoded[k] == alphabet ){
	tmp += 1;
      }
    }
    sum += tmp == 0 ? 0 : tmp * (tmp-1);
  }
  double expectIC =  (double)sum / ((double)this->encoded.length() * (double)this->encoded.length() - 1.0 );
  if( expectIC >= 0.066){
    return 1;
  }
  else if( expectIC < 0.066 && expectIC >= 0.052){
    return 2;
  }
  else if( expectIC < 0.052 && expectIC >= 0.047){
    return 3;
  }
  else if( expectIC < 0.047 && expectIC >= 0.045){
    return 4;
  }
  else if( expectIC < 0.045 && expectIC >= 0.044){
    return 5;
  }
  else if( expectIC < 0.044 && expectIC >= 0.041){
    return 10;
  }
  else{
    return 11;//cannot expect but over 10
  }
}

void viju2d::print_encoded() const{
  std::cout << this->encoded << std::endl;
}

void viju2d::print_plain() const{
  std::cout << this->plain << std::endl;
}

void viju2d::print_expectedkey() const{
  std::cout << this->expectedkey << std::endl;
}

void viju2d::print_all() const{
  std::cout << "palin text   : " << this->plain   << std::endl;
  std::cout << "encoded text : " << this->encoded << std::endl;
  std::cout << "key     text : " << this->key     << std::endl;
}

//key->ABC
//plain->WELCOME
//enc->WFNCPOE
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
