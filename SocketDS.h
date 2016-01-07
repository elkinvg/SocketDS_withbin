/*----- PROTECTED REGION ID(SocketDS.h) ENABLED START -----*/
//=============================================================================
//
// file :        SocketDS.h
//
// description : Include file for the SocketDS class
//
// project :     Socket
//
// This file is part of Tango device class.
// 
// Tango is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Tango is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Tango.  If not, see <http://www.gnu.org/licenses/>.
// 
// $Author:  $
//
// $Revision:  $
// $Date:  $
//
// $HeadURL:  $
//
//=============================================================================
//                This file is generated by POGO
//        (Program Obviously used to Generate tango Object)
//=============================================================================


#ifndef SocketDS_H
#define SocketDS_H



//#define _WIN32_WINNT_WIN7 0x0601
//#define _MSC_VER 1700
//#define WINVER 0x0601
#include <tango.h>
#include <cstdlib>
#include <cstring>
#include <boost/asio.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>

#include <boost/array.hpp>



/*----- PROTECTED REGION END -----*/	//	SocketDS.h

/**
 *  SocketDS class description:
 *    This class implements basic `socket` IPC.
 */

namespace SocketDS_ns
{
/*----- PROTECTED REGION ID(SocketDS::Additional Class Declarations) ENABLED START -----*/

//	Additional Class Declarations
	enum { max_length = 1024 };


/*----- PROTECTED REGION END -----*/	//	SocketDS::Additional Class Declarations

class SocketDS : public TANGO_BASE_CLASS
{

/*----- PROTECTED REGION ID(SocketDS::Data Members) ENABLED START -----*/

//	Add your own data members
private:
	boost::asio::io_service *io_service;
	boost::asio::ip::tcp::socket *socket;
	boost::asio::ip::tcp::endpoint *ep;
	boost::asio::streambuf *buffer;
	boost::asio::deadline_timer *timer;


/*----- PROTECTED REGION END -----*/	//	SocketDS::Data Members

//	Device property data members
public:
	//	Hostname:	This is the hostname of the host to connect to.
	string	hostname;
	//	Port:	This is the port number to connect to.
	Tango::DevLong	port;
	//	Readtimeout:	Read timeout in milliseconds.
	Tango::DevShort	readtimeout;
	//	AutoReconnect:	If true, the server try to re-create and re-connect to the socket after a failure.
	//  NOTE : The default values is false.
	Tango::DevBoolean	autoReconnect;


//	Constructors and destructors
public:
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	SocketDS(Tango::DeviceClass *cl,string &s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	SocketDS(Tango::DeviceClass *cl,const char *s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device name
	 *	@param d	Device description.
	 */
	SocketDS(Tango::DeviceClass *cl,const char *s,const char *d);
	/**
	 * The device object destructor.
	 */	
	~SocketDS() {delete_device();};


//	Miscellaneous methods
public:
	/*
	 *	will be called at device destruction or at init command.
	 */
	void delete_device();
	/*
	 *	Initialize the device
	 */
	virtual void init_device();
	/*
	 *	Read the device properties from database
	 */
	void get_device_property();
	/*
	 *	Always executed method before execution command method.
	 */
	virtual void always_executed_hook();


//	Attribute methods
public:
	//--------------------------------------------------------
	/*
	 *	Method      : SocketDS::read_attr_hardware()
	 *	Description : Hardware acquisition for attributes.
	 */
	//--------------------------------------------------------
	virtual void read_attr_hardware(vector<long> &attr_list);


	//--------------------------------------------------------
	/**
	 *	Method      : SocketDS::add_dynamic_attributes()
	 *	Description : Add dynamic attributes if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_attributes();



//	Command related methods
public:
	/**
	 *	Command Write related method
	 *	Description: Command used to send a string to the socket.
	 *
	 *	@param argin 
	 */
	virtual void write(Tango::DevString argin);
	virtual bool is_Write_allowed(const CORBA::Any &any);
	/**
	 *	Command Read related method
	 *	Description: Command used to read a string from the socket.
	 *
	 *	@returns 
	 */
	virtual Tango::DevString read();
	virtual bool is_Read_allowed(const CORBA::Any &any);
	/**
	 *	Command Reconnect related method
	 *	Description: Attempts to re-establish the socket connection.
	 *
	 */
	virtual void reconnect();
	virtual bool is_Reconnect_allowed(const CORBA::Any &any);
	/**
	 *	Command WriteAndRead related method
	 *	Description: Write to the socket and waits for the answer.
	 *               The end of the answer is triggered by the new line character!
	 *
	 *	@param argin Command string.
	 *	@returns Answer string.
	 */
	virtual Tango::DevString write_and_read(Tango::DevString argin);
	virtual bool is_WriteAndRead_allowed(const CORBA::Any &any);
	/**
	 *	Command Readln related method
	 *	Description: Reads from a socket until a "\n" has been received.
	 *
	 *	@returns argout
	 */
	virtual Tango::DevString readln();
	virtual bool is_Readln_allowed(const CORBA::Any &any);
	/**
	 *	Command ReadUntil related method
	 *	Description: This command read data from the socket until the terminator has been reached.
	 *
	 *	@param argin This is the terminator
	 *	@returns This is the read string.
	 */
	virtual Tango::DevString read_until(Tango::DevString argin);
	virtual bool is_ReadUntil_allowed(const CORBA::Any &any);
	/**
	 *	Command WriteReadUntil related method
	 *	Description: Write to the socket and waits for the answer.
	 *               The answer is triggered by select() which indicates that the the anser has arrived.
	 *
	 *	@param argin [0] = Command string to be send, [1] = end of message character
	 *	@returns Answer string.
	 */
	virtual Tango::DevString write_read_until(const Tango::DevVarStringArray *argin);
	virtual bool is_WriteReadUntil_allowed(const CORBA::Any &any);
	/**
	 *	Command CheckConnection related method
	 *	Description: 
	 *
	 */
	virtual void check_connection();
	virtual bool is_CheckConnection_allowed(const CORBA::Any &any);
	/**
	 *	Command WriteAndReadBinary related method
	 *	Description: Write command and read reply (binary)
	 *
	 *	@param argin command
	 *	@returns Reply String
	 */
	virtual Tango::DevString write_and_read_binary(Tango::DevString argin);
	virtual bool is_WriteAndReadBinary_allowed(const CORBA::Any &any);
	/**
	 *	Command ReadBinary related method
	 *	Description: Command used to read a string from the socket.
	 *
	 *	@returns 
	 */
	virtual Tango::DevString read_binary();
	virtual bool is_ReadBinary_allowed(const CORBA::Any &any);
	/**
	 *	Command WriteBinary related method
	 *	Description: Command used to send a string to the socket. (binary)
	 *
	 *	@param argin 
	 */
	virtual void write_binary(Tango::DevString argin);
	virtual bool is_WriteBinary_allowed(const CORBA::Any &any);


/*----- PROTECTED REGION ID(SocketDS::Additional Method prototypes) ENABLED START -----*/

//	Additional Method prototypes
	 void check_deadline();
	 void socket_read();
	 void socket_write(std::string message);
	 //elkin
	 void socket_read_binary();
	 void socket_write_binary(std::string message);
	
/*----- PROTECTED REGION END -----*/	//	SocketDS::Additional Method prototypes
};

/*----- PROTECTED REGION ID(SocketDS::Additional Classes Definitions) ENABLED START -----*/

//	Additional Classes Definitions

/*----- PROTECTED REGION END -----*/	//	SocketDS::Additional Classes Definitions

}	//	End of namespace

#endif   //	SocketDS_H
