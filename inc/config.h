#ifndef SCF_CONFIG_H
#define SCF_CONFIG_H

#include "server.h"

#include <stdio.h>

void load_server_config (struct server_info *);
void load_server_directories_config (struct server_info *, FILE *);
void load_server_files_config (struct server_info *, FILE *);
void load_server_network_config (struct server_info *, FILE *);

#endif
