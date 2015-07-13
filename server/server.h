#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <cstring>
#include <map>
#include <vector>

#include "log.h"

#define USER_DB_PATH "usr.data"
#define MSGLEN 100

static std::map<std::string,std::string> user_pass;
static std::string root_dir;

static int openListenfd(int port);
static std::string hash(std::string input);
static int findCommand(std::string command);

const std::vector<std::string> command_vec
{
	"QUIT",
	"USER",
	"PASS",
	"SIZE",
	"CD",
	"LS",
	"GET",
	"MGET",
	"PUT",
	"MPUT",
	"MKDIR",
	"PWD",
	"RM",
	"RMDIR",
};

class ServerBox
{
public:
	explicit ServerBox(int port,std::string root_dir_input);
	~ServerBox();
	int startServe();
private:
	ServerBox();
	int listenfd;
};

class Server
{
public:
	explicit Server(int clientfd_input,std::string clientip_input);
	~Server();
	int startServe();
private:
	std::string current_dir;
	int clientfd;
	std::string clientip;

	bool is_login;

	Server();
	int sendMsg(std::string msg);
	int recvMsg(std::string& command,std::string& arg);

	int do_user(std::string arg);
	int do_size(std::string arg);
	int do_cd(std::string arg);
	int check_filename(std::string filename);
	int check_filename_out_of_bound(std::string filename);
};

#endif