// $Id$    --*- c++ -*--

// Copyright (C) 2002 Enrico Scholz <enrico.scholz@informatik.tu-chemnitz.de>
//  
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; version 2 of the License.
//  
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//  
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//  

#ifndef DHCP_FORWARDER_CONFIG_H
#define DHCP_FORWARDER_CONFIG_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <net/if.h>
#include <netinet/in.h>
#include <stdint.h>
#include <limits.h>

#include "util.h"
#include "compat.h"

struct InterfaceInfo {
    char	name[IFNAMSIZ];	//< name of the interface
    char	aid[IFNAMSIZ];	//< agent id
    bool	has_clients;	//< tells if DHCP clients are on this interface
    bool	has_servers;	//< tells if DHCP servers are on this interface
    bool	allow_bcast;	//< honor bcast-flag and send to bcast address?

    unsigned int	if_idx;		//< interface index
    in_addr_t		if_ip;		//< associated ip
    size_t		if_mtu;		//< MTU
    uint8_t		if_mac[16];	//< MAC
    size_t		if_maclen;	//< length of MAC
};

struct InterfaceInfoList {
    /*@only@*/ struct InterfaceInfo	*dta;	//< array of InterfaceInfo
    size_t				len;	//< length of InterfaceInfoList
};

struct ServerInfo {
    enum { svUNICAST, svBCAST }		type;	//< type of server
    union {
	/*@dependent@*/
	struct InterfaceInfo const	*iface;
	struct in_addr			ip;
    }					info;
};

struct ServerInfoList {
    /*@only@*/ struct ServerInfo	*dta;
    size_t				len;
};

struct FdInfo {
    int					fd;
    /*@dependent@*/
    struct InterfaceInfo const		*iface;
};

struct FdInfoList {
    /*@only@*/ struct FdInfo		*dta;
    size_t				len;

    int					sender_fd;
    int					raw_fd;
};

struct ConfigInfo {
    uid_t				uid;
    gid_t				gid;
    char				chroot_path[PATH_MAX];
    
    char				logfile_name[PATH_MAX];
    int					loglevel;

    char				pidfile_name[PATH_MAX];

    struct InterfaceInfoList		interfaces;
    struct ServerInfoList		servers;
};

extern int		initializeSystem(int argc, char *argv[],
					 struct InterfaceInfoList *	ifs,
					 struct ServerInfoList *	servers,
					 struct FdInfoList *		fds);

#endif	// DHCP_FORWARDER_CONFIG_H

  // Local Variables:
  // compile-command: "make -C .. -k"
  // fill-column: 80
  // End:
