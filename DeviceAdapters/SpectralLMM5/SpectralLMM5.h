/*
 * Interface for the Spectral LMM5
 *
 * AUTHOR:
 * Nico Stuurman (nico@cmp.ucf.edu), 2/7/2008
 *
 * Copyright (c) 2009 Regents of the University of California
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

#ifndef _SPECTRALLMM5_H_
#define _SPECTRALLMM5_H_

#include "../../MMDevice/ModuleInterface.h"
#include "../../MMDevice/DeviceBase.h"
#include <stdint.h>
#include <cstdio>
#include <string>

//////////////////////////////////////////////////////////////////////////////
// Error codes
//
#define ERR_UNKNOWN_POSITION         10002
#define ERR_INVALID_SPEED            10003
#define ERR_PORT_CHANGE_FORBIDDEN    10004
#define ERR_SET_POSITION_FAILED      10005
#define ERR_INVALID_STEP_SIZE        10006
#define ERR_LOW_LEVEL_MODE_FAILED    10007
#define ERR_INVALID_MODE             10008
#define ERR_UNEXPECTED_ANSWER        10009

class LMM5Hub : public CGenericBase<LMM5Hub>
{
   public:
      LMM5Hub();
      ~LMM5Hub();

      int Initialize();
      int Shutdown();
      void GetName(char* pszName) const;
      bool Busy();

      int OnPort(MM::PropertyBase* pProp, MM::ActionType eAct);
      // int OnPowerMonitor(MM::PropertyBase* pProp, MM::ActionType eAct);
      int OnTransmission(MM::PropertyBase* pProp, MM::ActionType eAct, long line);
      int OnFlicr(MM::PropertyBase* pProp, MM::ActionType eAct, long line);
      int OnExposureConfig(MM::PropertyBase* pProp, MM::ActionType eAct);
      int OnTriggerOutConfig(MM::PropertyBase* pProp, MM::ActionType eAct);
      int OnTriggerOutExposureTime(MM::PropertyBase* pProp, MM::ActionType eAct);

   private:
      void IntToPerc(uint16_t value, std::string& result);
      void PercToInt(std::string in, uint16_t& result);
      unsigned char majorFWV_, minorFWV_;
      std::map<std::string, uint16_t> triggerConfigMap_;
      uint16_t triggerOutConfig_;
      uint16_t triggerOutExposureTime_;
      uint16_t flicrMaxValue_;
      std::string port_;
      bool initialized_;
      bool flicrAvailable_;
      int nrLines_;
};

class LMM5Shutter : public CShutterBase<LMM5Shutter>
{
public:
   LMM5Shutter();
   ~LMM5Shutter();
  
   // Device API
   // ----------
   int Initialize();
   int Shutdown();
  
   void GetName(char* pszName) const;
   bool Busy();

   // Shutter API
   int SetOpen(bool open = true);
   int GetOpen(bool& open);
   int Fire(double deltaT);

   // action interface
   // ----------------
   int OnState(MM::PropertyBase* pProp, MM::ActionType eAct);
   int OnLabel(MM::PropertyBase* pProp, MM::ActionType eAct);
   int OnStateEx(MM::PropertyBase* pProp, MM::ActionType eAct, long line);
   int OnOutputSelect(MM::PropertyBase* pProp, MM::ActionType eAct);
   unsigned long GetNumberOfPositions();
   int LabelToState(std::string label);
   std::string StateToLabel(int state);

private:
   MM::MMTime changedTime_;
   std::string name_;
   int state_;
   std::string label_;
   bool open_;
   bool initialized_;
   int nrLines_;
    uint16_t nrOutputs_;
};

#endif //_SPECTRALLMM5_H_
