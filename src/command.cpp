/*
   Copyright 2011 Carl Anderson

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <sstream>

#include "ash_log.hpp"


using namespace ash;
using std::stringstream;


/**
 * 
 */
const string Command::get_create_table() {
  stringstream ss;
  ss << "CREATE TABLE IF NOT EXISTS commands(\n"
     << "  id integer primary key autoincrement,\n"
     << "  session_id integer not null,\n"
     << "  shell_level integer not null,\n"
     << "  command_no integer,\n"
     << "  tty varchar(20) not null,\n"
     << "  shlvl integer not null,\n"
     << "  euid int(16) not null,\n"
     << "  cwd varchar(256) not null,\n"
     << "  rval int(5) not null,\n"
     << "  start_time integer not null,\n"
     << "  end_time integer not null,\n"
     << "  duration integer not null,\n"
     << "  pipe_cnt int(3),\n"
     << "  pipe_vals varchar(80),\n"
     << "  command varchar(1000) not null\n"
     << ");";
  return ss.str();
}


/**
 * 
 */
Command::Command(const string command, const int rval, const int start_ts, const int end_ts, const int number, const string pipes) {
  values["session_id"] = Unix::env_int(ASH_SESSION_ID);
  values["shell_level"] = Unix::env_int("SHLVL");
  values["command_no"] = Util::to_string(number);
  values["tty"] = Unix::tty();
  values["shlvl"] = Unix::env_int("SHLVL");
  values["euid"] = Unix::euid();
  if (rval == 0 && command.find("cd") == 0) {
    values["cwd"] = Unix::env("OLDPWD");
  } else {
    values["cwd"] = Unix::cwd();
  }
  values["rval"] = Util::to_string(rval);
  values["start_time"] = Util::to_string(start_ts);
  values["end_time"] = Util::to_string(end_ts);
  values["duration"] = Util::to_string(end_ts - start_ts);
  int pipe_cnt = 1;
  for (string::const_iterator i = pipes.begin(), e = pipes.end(); i != e; ++i)
    if ((*i) == ' ') ++pipe_cnt;
  values["pipe_cnt"] = Util::to_string(pipe_cnt);
  values["pipe_vals"] = pipes;
  values["command"] = quote(command);
}


/**
 * 
 */
Command::~Command() {
  // Nothing to do.
}


/**
 * 
 */
const string Command::get_name() const {
  return "commands";
}


/**
 * 
 */
const string Command::get_sql() const {
  stringstream ss;
  ss << DBObject::get_sql();
  ss << "UPDATE sessions ";
  ss << "SET end_time = null, duration = null ";
  ss << "WHERE id = " << Unix::env_int(ASH_SESSION_ID) << ";";
  return ss.str();
}
