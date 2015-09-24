/*
 * Lumencor Light Engine driver
 * CIA
 *
 * AUTHOR:
 * Louis Ashford
 *
 * Copyright (c)  Ashford Solutions LLC
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _CIA_H_
#define _CIA_H_


#include "..\..\MMDevice\MMDevice.h"
#include "..\..\MMDevice\DeviceBase.h"
#include <string>
#include <map>

//////////////////////////////////////////////////////////////////////////////
// Error codes
//
#define ERR_UNKNOWN_POSITION         10002
#define ERR_PORT_CHANGE_FORBIDDEN    10004
#define ERR_SET_POSITION_FAILED      10005
#define ERR_INVALID_STEP_SIZE        10006
#define ERR_INVALID_MODE             10008
#define ERR_UNRECOGNIZED_ANSWER      10009
#define ERR_UNSPECIFIED_ERROR        10010
#define ERR_COMMAND_ERROR            10201
#define ERR_PARAMETER_ERROR          10202
#define ERR_RECEIVE_BUFFER_OVERFLOW  10204
#define ERR_COMMAND_OVERFLOW         10206
#define ERR_PROCESSING_INHIBIT       10207
#define ERR_PROCESSING_STOP_ERROR    10208

#define ERR_OFFSET 10100
#define ERR_Lumencor_OFFSET 10200

enum ColorNameT {VIOLET,CYAN,GREEN,RED,BLUE,TEAL,RGCU,BT,ALL,WHITE,YELLOW,YGFILTER};

class CIA : public CShutterBase<CIA>
{
public:
   CIA();
   ~CIA();
  
   // Device API
   // ----------
   int Initialize();
   int Shutdown();
  
   void GetName(char* pszName) const;
   bool Busy();

   // Shutter API
   // ---------
   int SetOpen(bool open = true);
   int GetOpen(bool& open);
   int Fire(double /*interval*/) {return DEVICE_UNSUPPORTED_COMMAND; }

   // CIA Commands
	int OnCIAStart(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnRunCommand(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnStop_CIA(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnGetInfo(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnDownLoadSeq(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnStepSeq(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnRewindSeq(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnSetLE_Type(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnSet_Input1_Pol(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnSet_Input2_Pol(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnSetScriptCommand(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnSetBasePathCommand(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnLoadScriptCommand(MM::PropertyBase* pProp, MM::ActionType eAct);
	//int OnSaveScriptCommand(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnAddEventCommand(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnRemoveEventCommand(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnClearSeq(MM::PropertyBase* pProp, MM::ActionType eAct);
	int	OnEventCount(MM::PropertyBase* pProp, MM::ActionType eAct);

   // action interface
   // ----------------
   int OnPort(MM::PropertyBase* pProp, MM::ActionType eAct);
   int OnState(MM::PropertyBase* pProp, MM::ActionType eAct);
   int OnChannel(MM::PropertyBase* pProp, MM::ActionType eAct);
   int OnVersion(MM::PropertyBase* pProp, MM::ActionType eAct);

   int OnRedEnable(MM::PropertyBase* pProp, MM::ActionType eAct);
   int OnGreenEnable(MM::PropertyBase* pProp, MM::ActionType eAct);
   int OnCyanEnable(MM::PropertyBase* pProp, MM::ActionType eAct);
   int OnVioletEnable(MM::PropertyBase* pProp, MM::ActionType eAct);
   int OnTealEnable(MM::PropertyBase* pProp, MM::ActionType eAct);
   int OnBlueEnable(MM::PropertyBase* pProp, MM::ActionType eAct);

   int OnYGFilterEnable(MM::PropertyBase* pProp, MM::ActionType eAct);

   int OnRedValue(MM::PropertyBase* pProp, MM::ActionType eAct);
   int OnGreenValue(MM::PropertyBase* pProp, MM::ActionType eAct);
   int OnCyanValue(MM::PropertyBase* pProp, MM::ActionType eAct);
   int OnVioletValue(MM::PropertyBase* pProp, MM::ActionType eAct);
   int OnTealValue(MM::PropertyBase* pProp, MM::ActionType eAct);
   int OnBlueValue(MM::PropertyBase* pProp, MM::ActionType eAct);

private:
   int SetShutterPosition(bool state);
   int GetVersion();
   int SetColorEnable(ColorNameT ColorName, bool State, char* EnableMask);
   int AddEvent();
   int RemoveEvent();
   int LoadSeq();
   //int SaveSeq();
   int WriteSeqToHW();
   int UpdateColorEnables(unsigned char DataByte);
   int ParseSeqData(std::string buffer);
   int SetScriptName(std::string FileName);
   int GetResponse(const char *command, std::string &answer);
   int SendColorLevelCmd(ColorNameT ColorName,int ColorLevel);
   int SendColorEnableCmd(ColorNameT ColorName,bool State, char* EnableMask);

   // MMCore name of serial port
   std::string port_;
   // Time it takes after issuing Close command to close the shutter         
   double closingTimeMs_;                                                    
   // Time it takes after issuing Open command to open the shutter           
   double openingTimeMs_;                                                    
   // Command exchange with MMCore                                           
   std::string command_;           
   // close (0) or open (1)
   int state_;
   bool initialized_;
   // channel that we are currently working on 
   std::string activeChannel_;
   // version string returned by device
   std::string version_;
   double answerTimeoutMs_;
   // Current Color Selected
   std::string ActiveColor_;
   
};


#endif //_CIA_H_
