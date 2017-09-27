//
// Summarizer.hpp for summarizer in /home/huyghu/Proj/cpp
// 
// Made by Victor Huyghues-Lacour
// Login   <huyghu@epitech.net>
// 
// Started on  Fri Jul 28 11:53:43 2017 Victor Huyghues-Lacour
// Last update Sun Aug  6 16:17:35 2017 Victor Huyghues-Lacour
//

#ifndef SUMMARIZER_HPP_
# define SUMMARIZER_HPP_

# include <string>
# include <vector>
# include <map>

/*  enum					Information
    {
    PARAGRAPH,
    LINES,
    NB_INFORMATIONS
    };*/

class					Summarizer
{
  std::vector<std::string>		lines;
  //Information				type;
  std::string				fileName;
  std::string				file;
  std::string				fileReduced;
  std::map<std::string, int>		dictionnary;
    
  void				parseFile();
  void				fillDictionnary();
  void				parseLines();

public:
  Summarizer();
  Summarizer(std::string const& _fileName);
  ~Summarizer() = default;
  Summarizer(Summarizer const&);
  Summarizer &operator=(Summarizer const&) = delete;

  std::string				getFileName() const {return(fileName);};
  std::string				getFile() const {return(file);};
  //Information				getType() const {return(type);};
  std::vector<std::string> const&	getLines() const {return(lines);};
  std::map<std::string, int>		getDico() const {return(dictionnary);};
  std::string				getReduced() const {return(fileReduced);};
  
  void				operator()();
  void				operator>>(std::string &str);
  void				operator<<(const std::string &str);
};
  
std::ostream&	operator<<(std::ostream& stream, const Summarizer&);
std::string	stringLow(std::string);

#endif /* !SUMMARIZER_HPP_ */
