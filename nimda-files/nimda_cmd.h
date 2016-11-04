#ifndef NIMDA_CMD_H
#define NIMDA_CMD_H

using namespace std;

void help();
void pcol( string x, string y );
void err_call( string x );
void showUsers( int argc, char* argv[] );
void addUsers( int argc, char* argv[] );
void showGroups( int argc, char* argv[] );
void prompt();
void removeUser( int argc, char* argv[] );
void encryptFile( int argc, char* argv[] );
void serverUtilization( int argc, char* argv[]);
void editFirewall(int argc, char* argv[]);
void showMemory();
void editConfigFile( int argc, char* argv[] );

#endif
