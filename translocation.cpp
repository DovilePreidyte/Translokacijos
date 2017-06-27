#include <Rcpp.h>
#include <fstream>
#include <iostream>
using namespace Rcpp;
#include <time.h>

// [[Rcpp::export]]
CharacterVector read_fasta(std::string file1, std::string file2,
                   int start, int end, int position, std::string out, std::string out2) {
  
  CharacterVector records1;
  CharacterVector records2;
  std::string sequence1;
  std::string sequence2;
  std::string header1;
  std::string header2;
 
  
  time_t now = time(0);
  
  std::ifstream first(file1.c_str());
  first.get(); // remove first '>'
  std::string rec;
  while(getline(first,rec,'>')){
    int newLineLoc = rec.find('\n');
    header1 = rec.substr(0,newLineLoc);
    sequence1 = rec.substr(newLineLoc+1, rec.length()-newLineLoc-2);
    sequence1.erase(std::remove(sequence1.begin(),sequence1.end(),'\n'),sequence1.end());
    records1[header1]=sequence1;
    
  }
  
  first.close();
  
  std::ifstream second(file2.c_str());
  second.get(); // remove first '>'
  std::string rec2;
  while(getline(second,rec2,'>')){
    int newLineLoc = rec2.find('\n');
    header2 = rec2.substr(0,newLineLoc);
    sequence2 = rec2.substr(newLineLoc+1, rec2.length()-newLineLoc-2);
    sequence2.erase(std::remove(sequence2.begin(),sequence2.end(),'\n'),sequence2.end());
    records2[header2]=sequence2;
  }
  
  std::string first_cut = sequence1.substr(start, end);
  std::string erase = sequence1.erase(start, end);
  std::string second_put = sequence2.insert(position, first_cut);
  
 Rcout << "Iskirpta: " << first_cut << std::endl;
 // Rcout << "Iklijuota: " << second_put << std::endl;
  
  std::ofstream output;
  output.open (out.c_str());
  output << ">",
  output << header1;
  output << "\n";
  output << erase;
  
  output.close();
  
  std::ofstream output2;
  output2.open (out2.c_str());
  output2 << ">";
  output2 << header2;
  output2 <<"\n";
  output2 << second_put;
  
  output2.close();
  
  time_t after = time(0);
  Rcout << "Laikas:" << after - now;
  Rcout << "\n";
  
  return 0;

}


/*** R
read_fasta("chr20.fa", "chr21.fa", 20000000, 30000, 20000000, "delecija.fa", "insercija.fa")

*/  
