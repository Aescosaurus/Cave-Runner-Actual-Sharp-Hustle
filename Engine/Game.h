/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Player.h"
#include "Platform.h"
#include "Map.h"
#include <vector>
#include "Spike.h"
#include "Font.h"
#include "Enemy.h"
#include "Button.h"
#include "LevelEditor.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	void Restart();
	void HardRestart();
	void SoftRestart();
	/********************************/
private:
	MainWindow & wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	enum class GameState
	{
		Menu,
		Started,
		LevelEditor
	};
	Font fixedSys = Font( "Fonts/FixedSys16x28.bmp" );
	Font crOrig = Font( "Fonts/CaveRunnerOriginal5x7.bmp",800,105 );
	static constexpr float moveSpeed = 320.0f;
	// static constexpr int nMaxLevels = 3;
	int nMaxLevels = 3;
	// bool started = false;
	Player pl = Vei2( 128,256 );
	std::vector<Platform> plats;
	std::vector<Spike> spikes;
	std::vector<Enemy> enemies;
	Button start = Button( { 100,360 },{ 145,55 },
		"Start",Colors::DarkGray,Colors::SoftGreen,
		crOrig );
	Button quit = Button( { 700,360 },{ 125,55 },
		"Quit",Colors::DarkGray,Colors::SoftRed,
		crOrig );
	Button lvlEditor = Button( { 295,360 },{ 355,55 },
		"Level Editor",Colors::DarkGray,Colors::LightGray,
		crOrig );
	Button restart = Button( { 100,360 },{ 200,55 },
		"Restart",Colors::DarkGray,Colors::LightGray,
		crOrig );
	Button menu = Button( { 700,360 },{ 125,55 },
		"Menu",Colors::DarkGray,Colors::LightGray,
		crOrig );
	float dtMult = 1.0f;
	float curTime = 0.0f;
	GameState state = GameState::Menu;
	LevelEditor le = LevelEditor( crOrig );
	/********************************/
};