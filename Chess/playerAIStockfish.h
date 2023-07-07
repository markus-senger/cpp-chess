#pragma once

#include "player.h"

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <random>

namespace swe {
	class PlayerAIStockfish : public Player {
	public:
		PlayerAIStockfish(swe::Color color, bool turn, swe::ChessBoard& board, int delayTime = 10) : mSkillLevel{ 20 }, mDelayTime{ delayTime },
				Player(color, true, turn, board, false) {

			startEngine();
		}

		~PlayerAIStockfish() {
			closeEngine();
		}


		// ----- pure virtuals override ---------------------------------------------------------------------------------

		bool turn() override {
			if (mTurn) {
				if (!mPreparation) {
					std::random_device rd;
					std::mt19937 rng(rd());
					std::uniform_int_distribution<size_t> dist(8, 12);
					size_t randomDepth = dist(rng);

					std::string position;
					position = "position fen " + mBoard.getCurBoardFEN() + (mColor == swe::Color::white ? " w" : " b") 
						+ (mBoard.getRochadePossibleWhite() ? " KQ" : "") + (mBoard.getRochadePossibleBlack() ? " kq" : "") + "\n"
						+ "go depth " + std::to_string(randomDepth) + "\n";

					WriteFile(mPipIn_w, position.c_str(), position.length(), &mWrit, NULL);
					mPreparation = true;
					mClock.restart();
				}
				else if (mClock.getElapsedTime().asMilliseconds() > mDelayTime) {
					std::string str;
					PeekNamedPipe(mPipOut_r, mBuffer, sizeof(mBuffer), &mRead, &mAvailable, NULL);
					do
					{
						ZeroMemory(mBuffer, sizeof(mBuffer));
						if (!ReadFile(mPipOut_r, mBuffer, sizeof(mBuffer), &mRead, NULL) || !mRead) break;
						mBuffer[mRead] = 0;
						str += (char*)mBuffer;
					} while (mRead >= sizeof(mBuffer));

					int n = str.find("bestmove");
					if (n != -1) {
						str = str.substr(n + 9, 5);
						char promotion = ' ';
						if (std::count(str.begin(), str.end(), 'O') == 3) str = (mColor == swe::Color::white ? "e1c1" : "e8c8");
						else if (std::count(str.begin(), str.end(), 'O') == 2) str = (mColor == swe::Color::white ? "e1g1" : "e8g8");
						else if (str[4] != ' ') {
							promotion = str[4];
							str = str.substr(0, 4);
						}
						else str = str.substr(0, 4);

						auto figure = mBoard.getBoardWithFigures()[mBoard.getPosOfBoardWithString(str, true)];
						figure->initPossibleSteps();
						figure->move(calcRowFromIdx(mBoard.getPosOfBoardWithString(str, false)),
							calcColFromIdx(mBoard.getPosOfBoardWithString(str, false)), true, promotion);

						mPreparation = false;
						return true;
					}
					else if (str == "") {
						closeEngine();
						startEngine();
						std::string position = "position fen " + mBoard.getCurBoardFEN() + (mColor == swe::Color::white ? " w" : " b") + "\n"
							+ "go depth 5\n";

						WriteFile(mPipIn_w, position.c_str(), position.length(), &mWrit, NULL);
						mClock.restart();
					}
				}
			}
			return false;
		}


		// ----- virtuals override ---------------------------------------------------------------------------------

		void closeEngine() override
		{
			WriteFile(mPipIn_w, "quit\n", 5, &mWrit, NULL);
		}

	private:
		STARTUPINFO			mSti = { 0 };
		SECURITY_ATTRIBUTES mStats = { 0 };
		PROCESS_INFORMATION mPInfo = { 0 };
		HANDLE				mPipIn_w, mPipIn_r, mPipOut_w, mPipOut_r;
		BYTE				mBuffer[4096];
		DWORD				mWrit, mRead, mAvailable;

		sf::Clock			mClock;
		int					mSkillLevel;
		int					mDelayTime;


		// ----- private methods ---------------------------------------------------------------------------------

		void startEngine() {
			mPipIn_w = mPipIn_r = mPipOut_w = mPipOut_r = NULL;

			// set security attributes
			mStats.nLength = sizeof(mStats);
			mStats.bInheritHandle = TRUE;
			mStats.lpSecurityDescriptor = NULL;

			CreatePipe(&mPipOut_r, &mPipOut_w, &mStats, 0);
			CreatePipe(&mPipIn_r, &mPipIn_w, &mStats, 0);

			// set startup information for process creation
			mSti.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
			mSti.wShowWindow = SW_HIDE;
			mSti.hStdInput = mPipIn_r;
			mSti.hStdOutput = mPipOut_w;
			mSti.hStdError = mPipOut_w;

			DWORD mode = PIPE_READMODE_BYTE | PIPE_NOWAIT;
			SetNamedPipeHandleState(mPipOut_r, &mode, NULL, NULL);

			const char* narrowStr = "./StockfishEngine/stockfish-windows-x86-64-avx2.exe";
			int requiredSize = MultiByteToWideChar(CP_UTF8, 0, narrowStr, -1, NULL, 0);
			LPWSTR path = new wchar_t[requiredSize];
			MultiByteToWideChar(CP_UTF8, 0, narrowStr, -1, path, requiredSize);

			CreateProcess(NULL, path, NULL, NULL, TRUE, 0, NULL, NULL, &mSti, &mPInfo);

			std::string skillLevelCmd = "setoption name Skill Level value " + std::to_string(mSkillLevel) + "\n";
			WriteFile(mPipIn_w, skillLevelCmd.c_str(), skillLevelCmd.length(), &mWrit, NULL);
		}
	};
}