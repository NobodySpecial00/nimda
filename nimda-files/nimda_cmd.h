#ifndef NIMDA_CMD_H
#define NIMDA_CMD_H
using namespace std;
void help();
void showUsers( int argc, char* argv[] );
void addUsers( int argc, char* argv[] );
void showGroups( int argc, char* argv[] );
void removeUser( int argc, char* argv[] );
void serverUtilization( int argc, char* argv[]);
void showMemory();
void editConfigFile( int argc, char* argv[] );
void editPort( int argc, char* argvp[] );
#endif
