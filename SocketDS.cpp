/*----- PROTECTED REGION ID(SocketDS.cpp) ENABLED START -----*/
static const char *RcsId = "$Id:  $";
//=============================================================================
//
// file :        SocketDS.cpp
//
// description : C++ source for the SocketDS class and its commands.
//               The class is derived from Device. It represents the
//               CORBA servant object which will be accessed from the
//               network. All commands which can be executed on the
//               SocketDS are implemented in this file.
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


#include <SocketDS.h>
#include <SocketDSClass.h>
#include <sstream>
#include <locale.h>

/*----- PROTECTED REGION END -----*/	//	SocketDS.cpp

/**
 *  SocketDS class description:
 *    This class implements basic `socket` IPC.
 */

//================================================================
//  The following table gives the correspondence
//  between command and method names.
//
//  Command name     |  Method name
//================================================================
//  State            |  Inherited (no method)
//  Status           |  Inherited (no method)
//  Write            |  write
//  Read             |  read
//  Reconnect        |  reconnect
//  WriteAndRead     |  write_and_read
//  Readln           |  readln
//  ReadUntil        |  read_until
//  WriteReadUntil   |  write_read_until
//  CheckConnection  |  check_connection
//================================================================

//================================================================
//  Attributes managed is:
//================================================================
//================================================================

namespace SocketDS_ns
{
/*----- PROTECTED REGION ID(SocketDS::namespace_starting) ENABLED START -----*/

//	static initializations

/*----- PROTECTED REGION END -----*/	//	SocketDS::namespace_starting

//--------------------------------------------------------
/**
 *	Method      : SocketDS::SocketDS()
 *	Description : Constructors for a Tango device
 *                implementing the classSocketDS
 */
//--------------------------------------------------------
SocketDS::SocketDS(Tango::DeviceClass *cl, string &s)
 : TANGO_BASE_CLASS(cl, s.c_str())
{
	/*----- PROTECTED REGION ID(SocketDS::constructor_1) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	SocketDS::constructor_1
}
//--------------------------------------------------------
SocketDS::SocketDS(Tango::DeviceClass *cl, const char *s)
 : TANGO_BASE_CLASS(cl, s)
{
	/*----- PROTECTED REGION ID(SocketDS::constructor_2) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	SocketDS::constructor_2
}
//--------------------------------------------------------
SocketDS::SocketDS(Tango::DeviceClass *cl, const char *s, const char *d)
 : TANGO_BASE_CLASS(cl, s, d)
{
	/*----- PROTECTED REGION ID(SocketDS::constructor_3) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	SocketDS::constructor_3
}

//--------------------------------------------------------
/**
 *	Method      : SocketDS::delete_device()
 *	Description : will be called at device destruction or at init command
 */
//--------------------------------------------------------
void SocketDS::delete_device()
{
	DEBUG_STREAM << "SocketDS::delete_device() " << device_name << endl;
	/*----- PROTECTED REGION ID(SocketDS::delete_device) ENABLED START -----*/
	
	//	Delete device allocated objects
	
	delete socket;
	delete ep;
	delete io_service;
	delete buffer;
	
	/*----- PROTECTED REGION END -----*/	//	SocketDS::delete_device
}

//--------------------------------------------------------
/**
 *	Method      : SocketDS::init_device()
 *	Description : will be called at device initialization.
 */
//--------------------------------------------------------
void SocketDS::init_device()
{
	DEBUG_STREAM << "SocketDS::init_device() create device " << device_name << endl;
	/*----- PROTECTED REGION ID(SocketDS::init_device_before) ENABLED START -----*/
	
	//	Initialization before get_device_property() call
	
	/*----- PROTECTED REGION END -----*/	//	SocketDS::init_device_before
	

	//	Get the device properties from database
	get_device_property();
	

	/*----- PROTECTED REGION ID(SocketDS::init_device) ENABLED START -----*/
	
	//	Initialize device
	
	setlocale( LC_ALL,"Russian" );

	std::string ip = (strcmp(hostname.c_str(), "localhost") == 0) ? "127.0.0.1" : hostname;
	DEBUG_STREAM << "Connecting to: " << ip << ":" << port << endl;
	try 
	{
		io_service = new boost::asio::io_service();
		socket = new boost::asio::ip::tcp::socket(*io_service);
		timer = new boost::asio::deadline_timer(*io_service);
		ep = new boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ip), port);
		buffer = new boost::asio::streambuf(1000);
		socket->connect(*ep);
		
		timer->expires_at(boost::posix_time::pos_infin);
		check_deadline();
		
		set_state(Tango::ON);
		set_status("Connected!");
		DEBUG_STREAM << "Success!"<< endl;
	}
	catch(std::exception& e)
	{
		set_state(Tango::FAULT);
		std::stringstream ss;
		ss << "Connection exception: " << e.what();
		set_status(ss.str());
	}
	
	/*----- PROTECTED REGION END -----*/	//	SocketDS::init_device
}

//--------------------------------------------------------
/**
 *	Method      : SocketDS::get_device_property()
 *	Description : Read database to initialize property data members.
 */
//--------------------------------------------------------
void SocketDS::get_device_property()
{
	/*----- PROTECTED REGION ID(SocketDS::get_device_property_before) ENABLED START -----*/
	
	//	Initialize property data members
	hostname = "localhost";
	port = 9999;
	readtimeout = 1000;
	autoReconnect = true;
	
	/*----- PROTECTED REGION END -----*/	//	SocketDS::get_device_property_before


	//	Read device properties from database.
	Tango::DbData	dev_prop;
	dev_prop.push_back(Tango::DbDatum("Hostname"));
	dev_prop.push_back(Tango::DbDatum("Port"));
	dev_prop.push_back(Tango::DbDatum("Readtimeout"));
	dev_prop.push_back(Tango::DbDatum("AutoReconnect"));

	//	is there at least one property to be read ?
	if (dev_prop.size()>0)
	{
		//	Call database and extract values
		if (Tango::Util::instance()->_UseDb==true)
			get_db_device()->get_property(dev_prop);
	
		//	get instance on SocketDSClass to get class property
		Tango::DbDatum	def_prop, cl_prop;
		SocketDSClass	*ds_class =
			(static_cast<SocketDSClass *>(get_device_class()));
		int	i = -1;

		//	Try to initialize Hostname from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  hostname;
		else {
			//	Try to initialize Hostname from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  hostname;
		}
		//	And try to extract Hostname value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  hostname;

		//	Try to initialize Port from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  port;
		else {
			//	Try to initialize Port from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  port;
		}
		//	And try to extract Port value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  port;

		//	Try to initialize Readtimeout from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  readtimeout;
		else {
			//	Try to initialize Readtimeout from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  readtimeout;
		}
		//	And try to extract Readtimeout value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  readtimeout;

		//	Try to initialize AutoReconnect from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  autoReconnect;
		else {
			//	Try to initialize AutoReconnect from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  autoReconnect;
		}
		//	And try to extract AutoReconnect value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  autoReconnect;

	}

	/*----- PROTECTED REGION ID(SocketDS::get_device_property_after) ENABLED START -----*/
	
	//	Check device property data members init
	
	/*----- PROTECTED REGION END -----*/	//	SocketDS::get_device_property_after
}

//--------------------------------------------------------
/**
 *	Method      : SocketDS::always_executed_hook()
 *	Description : method always executed before any command is executed
 */
//--------------------------------------------------------
void SocketDS::always_executed_hook()
{
	INFO_STREAM << "SocketDS::always_executed_hook()  " << device_name << endl;
	/*----- PROTECTED REGION ID(SocketDS::always_executed_hook) ENABLED START -----*/
	
	//	code always executed before all requests
	
	/*----- PROTECTED REGION END -----*/	//	SocketDS::always_executed_hook
}

//--------------------------------------------------------
/**
 *	Method      : SocketDS::read_attr_hardware()
 *	Description : Hardware acquisition for attributes
 */
//--------------------------------------------------------
void SocketDS::read_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
	DEBUG_STREAM << "SocketDS::read_attr_hardware(vector<long> &attr_list) entering... " << endl;
	/*----- PROTECTED REGION ID(SocketDS::read_attr_hardware) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	SocketDS::read_attr_hardware
}


//--------------------------------------------------------
/**
 *	Method      : SocketDS::add_dynamic_attributes()
 *	Description : Create the dynamic attributes if any
 *                for specified device.
 */
//--------------------------------------------------------
void SocketDS::add_dynamic_attributes()
{
	/*----- PROTECTED REGION ID(SocketDS::add_dynamic_attributes) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic attributes if any
	
	/*----- PROTECTED REGION END -----*/	//	SocketDS::add_dynamic_attributes
}

//--------------------------------------------------------
/**
 *	Command Write related method
 *	Description: Command used to send a string to the socket.
 *
 *	@param argin 
 */
//--------------------------------------------------------
void SocketDS::write(Tango::DevString argin)
{
	DEBUG_STREAM << "SocketDS::Write()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(SocketDS::write) ENABLED START -----*/
	
	try
	{
		std::stringstream command;
		command << argin;
		socket_write(command.str());
	}
	catch(std::exception& e)
	{
		set_state(Tango::FAULT);
		std::stringstream desc;
		desc << "Connection exception: " << e.what();
		set_status(desc.str());
		std::stringstream origin;
		origin << "Socket::write(" << argin << ") ";
		Tango::Except::throw_exception((const char *) "SocketError", desc.str(), origin.str());
	}

	/*----- PROTECTED REGION END -----*/	//	SocketDS::write
}
//--------------------------------------------------------
/**
 *	Command Read related method
 *	Description: Command used to read a string from the socket.
 *
 *	@returns 
 */
//--------------------------------------------------------
Tango::DevString SocketDS::read()
{
	Tango::DevString argout;
	DEBUG_STREAM << "SocketDS::Read()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(SocketDS::read) ENABLED START -----*/
	std::stringstream result;	
	result << "";

	try
	{
		socket_read();
		result << buffer;
	}
	catch (std::exception& e)
	{
		set_state(Tango::FAULT);
		std::stringstream desc;
		desc << "Connection exception: " << e.what();
		set_status(desc.str());
		std::stringstream origin;
		origin << "Socket::read()";
		Tango::Except::throw_exception((const char *) "SocketError", desc.str(), origin.str());
	}

	argout = Tango::string_dup(result.str().c_str());

	/*----- PROTECTED REGION END -----*/	//	SocketDS::read
	return argout;
}
//--------------------------------------------------------
/**
 *	Command Reconnect related method
 *	Description: Attempts to re-establish the socket connection.
 *
 */
//--------------------------------------------------------
void SocketDS::reconnect()
{
	DEBUG_STREAM << "SocketDS::Reconnect()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(SocketDS::reconnect) ENABLED START -----*/
	
	delete_device();
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	SocketDS::reconnect
}
//--------------------------------------------------------
/**
 *	Command WriteAndRead related method
 *	Description: Write to the socket and waits for the answer.
 *               The end of the answer is triggered by the new line character!
 *
 *	@param argin Command string.
 *	@returns Answer string.
 */
//--------------------------------------------------------
Tango::DevString SocketDS::write_and_read(Tango::DevString argin)
{
	Tango::DevString argout;
	DEBUG_STREAM << "SocketDS::WriteAndRead()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(SocketDS::write_and_read) ENABLED START -----*/
	
	write(argin);
	argout = read();
		
	/*----- PROTECTED REGION END -----*/	//	SocketDS::write_and_read
	return argout;
}
//--------------------------------------------------------
/**
 *	Command Readln related method
 *	Description: Reads from a socket until a "\n" has been received.
 *
 *	@returns argout
 */
//--------------------------------------------------------
Tango::DevString SocketDS::readln()
{
	Tango::DevString argout;
	DEBUG_STREAM << "SocketDS::Readln()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(SocketDS::readln) ENABLED START -----*/
	std::string line = "";

	try
	{
		socket_read();
		std::istream is(buffer);
		std::getline(is, line);
	}
	catch (std::exception& e)
	{
		set_state(Tango::FAULT);
		std::stringstream desc;
		desc << "Connection exception: " << e.what();
		set_status(desc.str());
		std::stringstream origin;
		origin << "Socket::readln()";
		Tango::Except::throw_exception((const char *) "SocketError", desc.str(), origin.str());
	}

	argout = Tango::string_dup(line.c_str());
	/*----- PROTECTED REGION END -----*/	//	SocketDS::readln
	return argout;
}
//--------------------------------------------------------
/**
 *	Command ReadUntil related method
 *	Description: This command read data from the socket until the terminator has been reached.
 *
 *	@param argin This is the terminator
 *	@returns This is the read string.
 */
//--------------------------------------------------------
Tango::DevString SocketDS::read_until(Tango::DevString argin)
{
	Tango::DevString argout;
	DEBUG_STREAM << "SocketDS::ReadUntil()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(SocketDS::read_until) ENABLED START -----*/
	
	boost::system::error_code error;
	std::stringstream until, result;
	until << argin;
	result << "";
	try
	{
		int size = boost::asio::read_until(*socket, *buffer, until.str());
		char *contents = new char [size];
		buffer->sgetn (contents,size);
		result.write(contents, size);
	}
	catch (std::exception& e)
	{
		set_state(Tango::FAULT);
		std::stringstream desc;
		desc << "Connection exception: " << e.what();
		set_status(desc.str());
		std::stringstream origin;
		origin << "Socket::read_until(" << argin << ") ";
		Tango::Except::throw_exception((const char *) "SocketError", desc.str(), origin.str());
	}

	argout = Tango::string_dup(result.str().c_str());

	/*----- PROTECTED REGION END -----*/	//	SocketDS::read_until
	return argout;
}
//--------------------------------------------------------
/**
 *	Command WriteReadUntil related method
 *	Description: Write to the socket and waits for the answer.
 *               The answer is triggered by select() which indicates that the the anser has arrived.
 *
 *	@param argin [0] = Command string to be send, [1] = end of message character
 *	@returns Answer string.
 */
//--------------------------------------------------------
Tango::DevString SocketDS::write_read_until(const Tango::DevVarStringArray *argin)
{
	Tango::DevString argout;
	DEBUG_STREAM << "SocketDS::WriteReadUntil()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(SocketDS::write_read_until) ENABLED START -----*/

	stringstream command, until;
	command << (*argin)[0];
	until << (*argin)[1];
	write(Tango::string_dup(command.str().c_str()));
	argout = read_until(Tango::string_dup(until.str().c_str()));
	
	/*----- PROTECTED REGION END -----*/	//	SocketDS::write_read_until
	return argout;
}
//--------------------------------------------------------
/**
 *	Command CheckConnection related method
 *	Description: 
 *
 */
//--------------------------------------------------------
void SocketDS::check_connection()
{
	DEBUG_STREAM << "SocketDS::CheckConnection()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(SocketDS::check_connection) ENABLED START -----*/
	
	reconnect();
	
	/*----- PROTECTED REGION END -----*/	//	SocketDS::check_connection
}

/*----- PROTECTED REGION ID(SocketDS::namespace_ending) ENABLED START -----*/

//	Additional Methods
void SocketDS::check_deadline()
{
	if (timer->expires_at() <= boost::asio::deadline_timer::traits_type::now())
	{
		// The deadline has passed. The socket is closed so that any outstanding
		// asynchronous operations are cancelled. This allows the blocked
		// connect(), read_line() or write_line() functions to return.
		boost::system::error_code ignored_ec;
		socket->close(ignored_ec);
		set_state(Tango::FAULT);
		set_status("Socket timeout..");

		// There is no longer an active deadline. The expiry is set to positive
		// infinity so that the actor takes no action until a new deadline is set.
		timer->expires_at(boost::posix_time::pos_infin);
	}

	// Put the actor back to sleep.
	timer->async_wait(bind(&SocketDS::check_deadline, this));
}

void SocketDS::socket_read()
{
	// Set a deadline for the asynchronous operation. Since this function uses
    // a composed operation (async_read_until), the deadline applies to the
    // entire operation, rather than individual reads from the socket.
	timer->expires_from_now(boost::posix_time::milliseconds(readtimeout));

	// Set up the variable that receives the result of the asynchronous
    // operation. The error code is set to would_block to signal that the
    // operation is incomplete. Asio guarantees that its asynchronous
    // operations will never fail with would_block, so any other value in
    // ec indicates completion.
    boost::system::error_code ec = boost::asio::error::would_block;

	// Start the asynchronous operation itself. The boost::lambda function
    // object is used as a callback and will update the ec variable when the
    // operation completes. The blocking_udp_client.cpp example shows how you
    // can use boost::bind rather than boost::lambda.
    boost::asio::async_read_until(*socket, *buffer, '\n', boost::lambda::var(ec) = boost::lambda::_1);

	// Block until the asynchronous operation has completed.
    do io_service->run_one(); while (ec == boost::asio::error::would_block);

    if (ec)
      throw boost::system::system_error(ec);
}

void SocketDS::socket_write(std::string message)
{
    std::string data = message + "\n";

    // Set a deadline for the asynchronous operation. Since this function uses
    // a composed operation (async_write), the deadline applies to the entire
    // operation, rather than individual writes to the socket.
    timer->expires_from_now(boost::posix_time::milliseconds(readtimeout));

    // Set up the variable that receives the result of the asynchronous
    // operation. The error code is set to would_block to signal that the
    // operation is incomplete. Asio guarantees that its asynchronous
    // operations will never fail with would_block, so any other value in
    // ec indicates completion.
    boost::system::error_code ec = boost::asio::error::would_block;

    // Start the asynchronous operation itself. The boost::lambda function
    // object is used as a callback and will update the ec variable when the
    // operation completes. The blocking_udp_client.cpp example shows how you
    // can use boost::bind rather than boost::lambda.
    boost::asio::async_write(*socket, boost::asio::buffer(data), boost::lambda::var(ec) = boost::lambda::_1);

    // Block until the asynchronous operation has completed.
    do io_service->run_one(); while (ec == boost::asio::error::would_block);

    if (ec)
      throw boost::system::system_error(ec);
}

/*----- PROTECTED REGION END -----*/	//	SocketDS::namespace_ending
} //	namespace