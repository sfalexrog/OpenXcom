/*
 * Copyright 2010 Daniel Albano
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef OPENXCOM_MANUFACTURESTATE_H
#define OPENXCOM_MANUFACTURESTATE_H

#include "../Engine/State.h"

class TextButton;
class Window;
class Text;
class TextList;

/**
 * Manufacture screen that lets the player manage
 * all the manufacturing operations of a base.
 */
class ManufactureState : public State
{
private:
	TextButton *_btnNew, *_btnOk;
	Window *_window;
	Text *_txtTitle, *_txtAvailable, *_txtAllocated, *_txtSpace, *_txtFunds, *_txtItem, *_txtEngineers, *_txtProduced, *_txtTotal, *_txtCost, *_txtTimeLeft;
	TextList *_lstManufacture;
public:
	/// Creates the Manufacture state.
	ManufactureState(Game *game);
	/// Cleans up the Manufacture state.
	~ManufactureState();
	/// Handler for clicking the OK button.
	void btnOkClick(Action *action);
};

#endif
