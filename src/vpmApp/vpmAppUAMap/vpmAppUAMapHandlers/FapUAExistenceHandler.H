// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_UA_EXISTENCE_HANDLER_H
#define FAP_UA_EXISTENCE_HANDLER_H

#include <cstddef> // To ensure NULL is defined
#include <set>
#include <map>
#include <vector>

#include "FFaLib/FFaTypeCheck/FFaTypeCheck.H"

class FFuUAExistenceHandler;
class FFuComponentBase;


class FapUAExistenceHandler
{
  Fmd_BASE_HEADER_INIT();

public:
  FapUAExistenceHandler(FFuUAExistenceHandler* ui = NULL);
  virtual ~FapUAExistenceHandler();

  // This initiation must be done before the creation of ui's. It sets up the
  // creation process between ui and UA.

  static void init();

  // Bookkeeping interface

  static void getAllOfType(int typeId, std::vector<FapUAExistenceHandler*>& toFillUp);

  static FapUAExistenceHandler* getUA(FFuUAExistenceHandler* ui);
  void getUA(FapUAExistenceHandler*& ua) { ua = this; }

  FFuUAExistenceHandler* getUI() { return this->ui; }
  FFuComponentBase* getCompBaseUI();
  bool isUIPoppedUp();

  // Sending application events :

  static void doUpdateState(int oldState, int newState, int mode);
  static void doUpdateUI(const std::set<int>& uiTypesToUpdate);
  static void doUpdateUI();
  static void doUpdateSession();

protected:
  virtual void updateState(int, int, int) {}

private:
  // These methods are used as callbacks in FFuUAExistenceHandler.
  // If ui has an UA, then this method creates it based on the ui's type
  static void createUA(FFuUAExistenceHandler* ui);

  // Deletes this object
  void destruct();

private:
  FFuUAExistenceHandler* ui;
  static std::set<FapUAExistenceHandler*> ourSelfSet;
  static std::map<FFuUAExistenceHandler*,FapUAExistenceHandler*> ourUIToUAMap;
};

#endif
