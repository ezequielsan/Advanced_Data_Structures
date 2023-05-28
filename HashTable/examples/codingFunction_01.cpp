/* Problema: 
 * Temos um conjunto de chaves K do tipo string e queremos 
 * construir uma função de codificação f: K → Z 
 * 
 * Dado um valor do tipo string, como transformá-lo em um
 * valor do tipo unsigned int?
 * 
 * Ideia ruin: usar o valor ASCII de cada caractere para 
 * comporo valor de retorno da função
 */

#include <iostream>

size_t hash_string_ruin(std::string x, size_t length) {
  size_t sum = 0;
  for (size_t i = 0; i < length; i++) 
    sum += x[i];
  return sum;
}

/*  
 * Ideia boa: além de usar o valor ASCII de cada caractere
 * usar também um "peso" dependendo da posição
 */

size_t hash_string(std::string x, size_t length) {
  size_t code = 0, BASE = 127;
  for (size_t i = 0; i < length; i++) 
    code = (code * BASE) + x[i];
  return code;
}