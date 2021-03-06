/*
 * Copyright 2010-2014 OpenXcom Developers.
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
#include "BaseNameState.h"
#include "../Engine/Game.h"
#include "../Engine/Action.h"
#include "../Resource/ResourcePack.h"
#include "../Engine/Language.h"
#include "../Engine/Palette.h"
#include "../Interface/Window.h"
#include "../Interface/Text.h"
#include "../Interface/TextEdit.h"
#include "../Interface/TextButton.h"
#include "../Savegame/Base.h"
#include "../Basescape/PlaceLiftState.h"
#include "../Engine/Options.h"

namespace OpenXcom
{

/**
 * Initializes all the elements in a Base Name window.
 * @param game Pointer to the core game.
 * @param base Pointer to the base to name.
 * @param globe Pointer to the Geoscape globe.
 * @param first Is this the first base in the game?
 */
BaseNameState::BaseNameState(Base *base, Globe *globe, bool first) : _base(base), _globe(globe), _first(first)
{
	_globe->onMouseOver(0);

	_screen = false;

	// Create objects
#ifdef __ANDROID__
	int windowTop = 15;
	int windowLeft = 32;
#else
	int windowTop = 60;
	int windowLeft = 32;
#endif
	_window = new Window(this, 192, 80, windowLeft, windowTop, POPUP_BOTH);
#ifdef __ANDROID__
	if(_first)
	{
		_btnOk = new TextButton(81, 12, windowLeft + 15, windowTop + 58);
	}
	else
	{
		_btnOk = new TextButton(162, 12, windowLeft + 15, windowTop + 58);
	}
	_btnCancel = new TextButton(81, 12, windowLeft + 15 + 81, windowTop + 58);
#else
	_btnOk = new TextButton(162, 12, windowLeft + 15, windowTop + 58);
#endif
	_txtTitle = new Text(182, 17, windowLeft + 5, windowTop + 10);
	_edtName = new TextEdit(this, 127, 16, windowLeft + 27, windowTop + 34);

	// Set palette
	setPalette("PAL_GEOSCAPE", 0);

	add(_window);
	add(_btnOk);
	add(_txtTitle);
	add(_edtName);
#ifdef __ANDROID__
	add(_btnCancel);
#endif
	centerAllSurfaces();

	// Set up objects
	_window->setColor(Palette::blockOffset(8)+5);
	_window->setBackground(_game->getResourcePack()->getSurface("BACK01.SCR"));

	_btnOk->setColor(Palette::blockOffset(8)+5);
	_btnOk->setText(tr("STR_OK"));
	_btnOk->onMouseClick((ActionHandler)&BaseNameState::btnOkClick);
	//_btnOk->onKeyboardPress((ActionHandler)&BaseNameState::btnOkClick, Options::keyOk);
	_btnOk->onKeyboardPress((ActionHandler)&BaseNameState::btnOkClick, Options::keyCancel);
#ifdef __ANDROID__
	_btnCancel->setColor(Palette::blockOffset(8) + 5);
	_btnCancel->setText(tr("STR_CANCEL_UC"));
	_btnCancel->onMouseClick((ActionHandler)&BaseNameState::btnCancelClick); /* That _will_ bite me in the ass, won't it? */

	_btnCancel->setVisible(_first);
#endif

	//something must be in the name before it is acceptable
	_btnOk->setVisible(false);

	_txtTitle->setColor(Palette::blockOffset(8)+5);
	_txtTitle->setAlign(ALIGN_CENTER);
	_txtTitle->setBig();
	_txtTitle->setText(tr("STR_BASE_NAME"));

	_edtName->setColor(Palette::blockOffset(8)+5);
	_edtName->setBig();
	_edtName->setFocus(true, false);
	_edtName->onChange((ActionHandler)&BaseNameState::edtNameChange);
}

/**
 *
 */
BaseNameState::~BaseNameState()
{

}

/**
 * Updates the base name and disables the OK button
 * if no name is entered.
 * @param action Pointer to an action.
 */
void BaseNameState::edtNameChange(Action *action)
{
	_base->setName(_edtName->getText());
	if (action->getDetails()->key.keysym.sym == SDLK_RETURN ||
		action->getDetails()->key.keysym.sym == SDLK_KP_ENTER)
	{
		if (!_edtName->getText().empty())
		{
			btnOkClick(action);
		}
	}
	else
	{
		_btnOk->setVisible(!_edtName->getText().empty());
	}
}

/**
 * Returns to the previous screen
 * @param action Pointer to an action.
 */
void BaseNameState::btnOkClick(Action *)
{
	if (!_edtName->getText().empty())
	{
#ifdef __ANDROID__
		// Hide the keyboard (it won't hide itself)!
		if (SDL_IsScreenKeyboardShown(NULL))
		{
			SDL_StopTextInput();
		}
#endif
		_game->popState();
		_game->popState();
		if (!_first || Options::customInitialBase)
		{
			if (!_first)
			{
				_game->popState();
			}
			_game->pushState(new PlaceLiftState(_base, _globe, _first));
		}
	}
}

#ifdef __ANDROID__
/**
 * Hopefully this will pop enough states to get back to the base placing view
 */
void BaseNameState::btnCancelClick(Action *)
{
#ifdef __ANDROID__
	if (SDL_IsScreenKeyboardShown(NULL))
	{
		SDL_StopTextInput();
	}
#endif
	_globe->onMouseOver(0);
	_game->popState();
}


#endif


}


