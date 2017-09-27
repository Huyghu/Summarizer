//
// Summarizer.cpp for tldr in /home/huyghu/Proj/cpp
// 
// Made by Victor Huyghues-Lacour
// Login   <huyghu@epitech.net>
// 
// Started on  Fri Jul 28 12:00:35 2017 Victor Huyghues-Lacour
// Last update Sun Aug  6 16:23:20 2017 Victor Huyghues-Lacour
//

#include <iostream>
#include <string>
#include <streambuf>
#include <fstream>
#include <cctype>
#include "Summarizer.hpp"

/*namespace
{
  std::vector<std::regex> const Reg =
    { std::regex("(0|\\+33|0033)[1-9](([ ][0-9])|([0-9])){8}"),
      std::regex("[a-zA-Z0-9_.-]+[@][a-zA-Z0-9_.-]+"),
      std::regex("(1[0-9][0-9]|2[0-4][0-9]|25[0-5]|[1-9][0-9]|[0-9])([.](1[0-9][0-9]|2[0-4][0-9]|25[0-5]|[1-9][0-9]|[0-9])){3}")};
      }*/

Summarizer::Summarizer() : lines(0), fileName(""), file(""), fileReduced(""), dictionnary()
{
}

Summarizer::Summarizer(std::string const& _fileName) : lines(0), fileName(_fileName), fileReduced(""), dictionnary()
{
  std::ifstream	buf(fileName);
  std::string		str((std::istreambuf_iterator<char>(buf)),
			    std::istreambuf_iterator<char>());
  file = str;
}

Summarizer::Summarizer(Summarizer const& _summarizer) : lines(_summarizer.lines), fileName(_summarizer.fileName), file(_summarizer.file), fileReduced(_summarizer.fileReduced), dictionnary(_summarizer.dictionnary)
{
}

void				Summarizer::parseFile() //[Using file, will fill Lines]
{
  size_t			posS = 0;
  size_t			posE = file.find_first_of(".!?\"");

  while (posE != std::string::npos)
    {
      //      std::cout << "posS " << posS << "," << file[posS] << "| posE " << posE << "," << file[posE] << std::endl;
      if (file[posE] == '"')
	{
	  posE = file.find("\"", posE + 1);
	  posE = file.find_first_of(".!?\"", posE + 1);
	}
      else
	{
	  lines.push_back(file.substr(posS, posE - posS + 1));
	  posS = posE + 1;
	  posE = file.find_first_of(".!?\"", posE + 1);
	}
    }
}

void				Summarizer::fillDictionnary() //[Using file, will fill Dictionnary]
{
  size_t posS = 0;
  size_t posE = file.find_first_of(". \t,;:\n\0!?\"");
  while (posE != std::string::npos)
    {
      if (posE && isalnum(file[posE - 1]))
	dictionnary[stringLow(file.substr(posS, posE - posS))] += 1;
      posS = posE + 1;
      posE = file.find_first_of(". \t,;:\n\0!?\"", posE + 1);
    }
}

void				Summarizer::parseLines() //[Using dico and lines, will fill fileReduced]
{
  int				sizeT = lines.size();
  int				score[sizeT];
  int				pos = 0;
  int				requirement = 0;
  
  for (int i = 0; i < sizeT; i += 1)
    score[i] = 0;
  while (pos < sizeT)
    {
      size_t posS = 0;
      size_t posE = lines[pos].find_first_of(". \t,;:\n\0!?\"");
      while (posE != std::string::npos)
	{
	  if (posE && isalnum(lines[pos][posE - 1]))
	    score[pos] += dictionnary[stringLow(lines[pos].substr(posS, posE - posS))];
	  posS = posE + 1;
	  posE = lines[pos].find_first_of(". \t,;:\n\0!?\"", posE + 1);
	}
      pos += 1;
    }
  /*  for (int i = 0; i < sizeT; i += 1)
      std::cout << "Line " << i << " has a score of " << score[i] << std::endl;*/
  for (int i = 0; i < sizeT; i += 1)
    requirement += score[i];
  std::cout << "Total score : " << requirement << std::endl;
  if (requirement != 0)
    requirement = (requirement / sizeT) * 2;
  std::cout << "Requirement : " << requirement << std::endl;

  int printed = 0;
  for (int i = 0; i < sizeT; i += 1)
    if (score[i] >= requirement)
      {
	fileReduced += lines[i];
	printed += score[i];
      }
  std::cout << "Printed : " << printed << std::endl;
  fileReduced += '\n';
}
  
void			Summarizer::operator()()
{
  parseFile();
  fillDictionnary();
  parseLines();
}

void			Summarizer::operator<<(const std::string& str)
{
  fileName = "";
  file = str;
}

void			Summarizer::operator>>(std::string& str)
{
  if (fileReduced == "")
    str += "Original text\n" + fileName + "\n___\n" + file + '\n';
  else
    str += "Reduced text\n" + fileName + "\nFrom " + std::to_string(file.size()) + " to "
      + std::to_string(fileReduced.size()) + "\n___\n" + fileReduced + '\n';
}

std::ostream& operator<<(std::ostream& stream, const Summarizer& summarizer)
{
  std::vector<std::string> lines = summarizer.getLines();
  std::string reduced = summarizer.getReduced();

  if (reduced != "")
    stream << reduced;
  else if (lines.empty() == false)
    for (size_t i = 0; i < lines.size(); i += 1)
      stream << lines[i] << '\n';
  else
    stream << summarizer.getFile();
  return (stream);
}

std::string				stringLow(std::string word) //[ Wtf cpp ?]
{
  for (size_t i = 0; i < word.size(); i += 1)
    if (isupper(word[i]))
      word[i] = tolower(word[i]);
  return (word);
}

int main(int argc, char **argv)
{
  if (argc > 1)
    {
      Summarizer sum(argv[1]);
      sum();
      std::cout << sum << std::endl;
    }
  else
    {
      Summarizer sum;
      std::string msg = "This is a sentence.test ? ok! a quote \" hi there !?!\" !!";
      sum << msg;
      sum();
      std::cout << sum << std::endl;
    }
/*std::vector<std::string> content = sum.getLines();
  for (size_t i = 0; i < content.size(); i += 1)
    std::cout << content[i] << '\n';
  std::map<std::string, int> dico = sum.getDico();
  for (const auto &p : dico)
  std::cout << "dico[" << p.first << "] = " << p.second << '\n';*/
}
