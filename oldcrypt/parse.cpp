#include <iostream>
#include <string>
#include <cstring>
#define FOR(n) for(uint32_t i=0;i<n;i++)

#ifndef _is_function
#define _is_function


bool isDigit   (char ch) { return '0' <= ch && ch <= '9'; }
bool isUpper   (char ch) { return 'A' <= ch && ch <= 'Z'; }
bool isLower   (char ch) { return 'a' <= ch && ch <= 'z'; }
bool isAlpha   (char ch) { return isUpper(ch) || isLower(ch); }
bool isAlphaNum(char ch) { return isAlpha(ch) || isDigit(ch); }
bool isLetter  (char ch) { return isAlpha(ch) || ch == '_';   }

#endif

bool match_char(const char* target, const char* check){
  uint32_t tlen = (uint32_t)std::strlen(target);
  uint32_t clen = (uint32_t)std::strlen(check);
  FOR(tlen){
    if(target[i] == check[0] && tlen >= clen+i ){
      for(uint32_t k=0;k< clen;k++){
	std::cout << "match char:"  <<  k+i << std::endl;
	if( target[i+k] != check[k]){
	  break;
	}
	if( clen == k+1){
	  return true;
	}
      }
    }//if match check[0]
  }//for

  return false;
}

