/*
 * CSUW1 hub module. Required for operation of all
 * CSUW1 devices
 *
 * AUTHOR:
 * Nico Stuurman, nico@cmp.ucsf.edu, 02/02/2007
 * Based on NikonTE2000 controller adapter by Nenad Amodaj
 *
 * Copyright (c) 2006 Regents of the University of California
 * All rights reserved
 *
 * This is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _CSUW1HUB_H_
#define _CSUW1HUB_H_

#include <string>
#include <deque>
#include <map>
#include "../../MMDevice/MMDevice.h"

/////////////////////////////////////////////////////////////////////////
// Error codes
//
#define ERR_NOT_CONNECTED           10002
#define ERR_COMMAND_CANNOT_EXECUTE  10003
#define ERR_NEGATIVE_RESPONSE 10004

enum CommandMode
{
   Sync = 0,
   Async
};

class CSUW1Hub
{
public:
   CSUW1Hub();
   ~CSUW1Hub();

   void SetPort(const char* port) {port_ = port;}
   bool IsBusy();

   void SetChannel(int channel) {ch_ = channel;};
   void GetChannel(int& channel) {channel = ch_;};

   int SetFilterWheelPosition(MM::Device& device, MM::Core& core, long wheelNr, long pos);
   int GetFilterWheelPosition(MM::Device& device, MM::Core& core, long wheelNr, long& pos);
   int SetFilterWheelSpeed(MM::Device& device, MM::Core& core, long wheelNr, long speed);
   int GetFilterWheelSpeed(MM::Device& device, MM::Core& core, long wheelNr, long& speed);

   int SetDichroicPosition(MM::Device& device, MM::Core& core, long dichroic);
   int GetDichroicPosition(MM::Device& device, MM::Core& core, long &dichroic);

   int SetShutterPosition(MM::Device& device, MM::Core& core, int pos);
   int GetShutterPosition(MM::Device& device, MM::Core& core, int& pos);

   int SetDriveSpeed(MM::Device& device, MM::Core& core, int pos);
   int GetDriveSpeed(MM::Device& device, MM::Core& core, long& pos);
   int GetMaxDriveSpeed(MM::Device& device, MM::Core& core, long& pos);
   int SetAutoAdjustDriveSpeed(MM::Device& device, MM::Core& core, double exposureMs);
   int RunDisk(MM::Device& device, MM::Core& core, bool run);

   int SetBrightFieldPosition(MM::Device& device, MM::Core& core, int pos);
   int GetBrightFieldPosition(MM::Device& device, MM::Core& core, int& pos);

   int SetDiskPosition(MM::Device& device, MM::Core& core, int pos);
   int GetDiskPosition(MM::Device& device, MM::Core& core, int& pos);

   int SetPortPosition(MM::Device& device, MM::Core& core, int pos);
   int GetPortPosition(MM::Device& device, MM::Core& core, int& pos);

   int SetAperturePosition(MM::Device& device, MM::Core& core, int pos);
   int GetAperturePosition(MM::Device& device, MM::Core& core, int& pos);

   int SetFrapPosition(MM::Device& device, MM::Core& core, int pos);
   int GetFrapPosition(MM::Device& device, MM::Core& core, int& pos);

   int SetMagnifierPosition(MM::Device& device, MM::Core& core, int nr, int pos);
   int GetMagnifierPosition(MM::Device& device, MM::Core& core, int nr, int& pos);

   int SetNIRShutterPosition(MM::Device& device, MM::Core& core, int pos);
   int GetNIRShutterPosition(MM::Device& device, MM::Core& core, int& pos);

private:
   int ExecuteCommand(MM::Device& device, MM::Core& core, const char* command);
   int GetAcknowledgment(MM::Device& device, MM::Core& core);
   int Acknowledge();
   int ParseResponse(const char* cmdId, std::string& value);
   void FetchSerialData(MM::Device& device, MM::Core& core);

   static const int RCV_BUF_LENGTH = 1024;
   char rcvBuf_[RCV_BUF_LENGTH];
   char asynchRcvBuf_[RCV_BUF_LENGTH];
   void ClearRcvBuf();
   void ClearAllRcvBuf(MM::Device& device, MM::Core& core);

   int ch_;
   std::string port_;
   std::vector<char> answerBuf_;
   std::multimap<std::string, long> waitingCommands_;
   std::string commandMode_;
   bool driveSpeedBusy_;
};

#endif // _CSUW1HUB_H_
