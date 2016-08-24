/*----- PROTECTED REGION ID(SocketDSStateMachine.cpp) ENABLED START -----*/
static const char *RcsId = "$Id:  $";
//=============================================================================
//
// file :        SocketDSStateMachine.cpp
//
// description : State machine file for the SocketDS class
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

/*----- PROTECTED REGION END -----*/	//	SocketDS::SocketDSStateMachine.cpp

//================================================================
//  States  |  Description
//================================================================
//  ON      |  Normal state when everything is OK.
//  FAULT   |  


namespace SocketDS_ns
{
//=================================================
//		Attributes Allowed Methods
//=================================================


//=================================================
//		Commands Allowed Methods
//=================================================

//--------------------------------------------------------
/**
 *	Method      : SocketDS::is_Write_allowed()
 *	Description : Execution allowed for Write attribute
 */
//--------------------------------------------------------
bool SocketDS::is_Write_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Compare device state with not allowed states.
	if (get_state()==Tango::FAULT)
	{
	/*----- PROTECTED REGION ID(SocketDS::WriteStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	SocketDS::WriteStateAllowed
		return false;
	}
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : SocketDS::is_Read_allowed()
 *	Description : Execution allowed for Read attribute
 */
//--------------------------------------------------------
bool SocketDS::is_Read_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Compare device state with not allowed states.
	if (get_state()==Tango::FAULT)
	{
	/*----- PROTECTED REGION ID(SocketDS::ReadStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	SocketDS::ReadStateAllowed
		return false;
	}
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : SocketDS::is_Reconnect_allowed()
 *	Description : Execution allowed for Reconnect attribute
 */
//--------------------------------------------------------
bool SocketDS::is_Reconnect_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Not any excluded states for Reconnect command.
	/*----- PROTECTED REGION ID(SocketDS::ReconnectStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	SocketDS::ReconnectStateAllowed
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : SocketDS::is_WriteAndRead_allowed()
 *	Description : Execution allowed for WriteAndRead attribute
 */
//--------------------------------------------------------
bool SocketDS::is_WriteAndRead_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Compare device state with not allowed states.
	if (get_state()==Tango::FAULT)
	{
	/*----- PROTECTED REGION ID(SocketDS::WriteAndReadStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	SocketDS::WriteAndReadStateAllowed
		return false;
	}
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : SocketDS::is_Readln_allowed()
 *	Description : Execution allowed for Readln attribute
 */
//--------------------------------------------------------
bool SocketDS::is_Readln_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Compare device state with not allowed states.
	if (get_state()==Tango::FAULT)
	{
	/*----- PROTECTED REGION ID(SocketDS::ReadlnStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	SocketDS::ReadlnStateAllowed
		return false;
	}
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : SocketDS::is_ReadUntil_allowed()
 *	Description : Execution allowed for ReadUntil attribute
 */
//--------------------------------------------------------
bool SocketDS::is_ReadUntil_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Compare device state with not allowed states.
	if (get_state()==Tango::FAULT)
	{
	/*----- PROTECTED REGION ID(SocketDS::ReadUntilStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	SocketDS::ReadUntilStateAllowed
		return false;
	}
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : SocketDS::is_WriteReadUntil_allowed()
 *	Description : Execution allowed for WriteReadUntil attribute
 */
//--------------------------------------------------------
bool SocketDS::is_WriteReadUntil_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Compare device state with not allowed states.
	if (get_state()==Tango::FAULT)
	{
	/*----- PROTECTED REGION ID(SocketDS::WriteReadUntilStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	SocketDS::WriteReadUntilStateAllowed
		return false;
	}
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : SocketDS::is_CheckConnection_allowed()
 *	Description : Execution allowed for CheckConnection attribute
 */
//--------------------------------------------------------
bool SocketDS::is_CheckConnection_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Compare device state with not allowed states.
	if (get_state()==Tango::ON)
	{
	/*----- PROTECTED REGION ID(SocketDS::CheckConnectionStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	SocketDS::CheckConnectionStateAllowed
		return false;
	}
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : SocketDS::is_WriteAndReadBinary_allowed()
 *	Description : Execution allowed for WriteAndReadBinary attribute
 */
//--------------------------------------------------------
bool SocketDS::is_WriteAndReadBinary_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Not any excluded states for WriteAndReadBinary command.
	/*----- PROTECTED REGION ID(SocketDS::WriteAndReadBinaryStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	SocketDS::WriteAndReadBinaryStateAllowed
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : SocketDS::is_ReadBinary_allowed()
 *	Description : Execution allowed for ReadBinary attribute
 */
//--------------------------------------------------------
bool SocketDS::is_ReadBinary_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Not any excluded states for ReadBinary command.
	/*----- PROTECTED REGION ID(SocketDS::ReadBinaryStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	SocketDS::ReadBinaryStateAllowed
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : SocketDS::is_WriteBinary_allowed()
 *	Description : Execution allowed for WriteBinary attribute
 */
//--------------------------------------------------------
bool SocketDS::is_WriteBinary_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Not any excluded states for WriteBinary command.
	/*----- PROTECTED REGION ID(SocketDS::WriteBinaryStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	SocketDS::WriteBinaryStateAllowed
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : SocketDS::is_AvalaibleBytes_allowed()
 *	Description : Execution allowed for AvalaibleBytes attribute
 */
//--------------------------------------------------------
bool SocketDS::is_AvalaibleBytes_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Not any excluded states for AvalaibleBytes command.
	/*----- PROTECTED REGION ID(SocketDS::AvalaibleBytesStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	SocketDS::AvalaibleBytesStateAllowed
	return true;
}


/*----- PROTECTED REGION ID(SocketDS::SocketDSStateAllowed.AdditionalMethods) ENABLED START -----*/

//	Additional Methods

/*----- PROTECTED REGION END -----*/	//	SocketDS::SocketDSStateAllowed.AdditionalMethods

}	//	End of namespace
