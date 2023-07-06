#pragma once

#include "player.h"

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>

namespace swe {
	class PlayerAIStockfish : public Player {
	public:
		PlayerAIStockfish(swe::Color color, bool turn, swe::ChessBoard& board) : Player(color, true, turn, board, false) {
			startEngine();
		}

		~PlayerAIStockfish() {
			closeEngine();
		}

		bool turn() override {
			if (mTurn) {
				if (!mPreparation) {
					std::string position = "position fen " + mBoard.getCurBoardFEN() + (mColor == swe::Color::white ? " w" : " b") + "\ngo depth 8\n";

					WriteFile(pipin_w, position.c_str(), position.length(), &writ, NULL);
					mPreparation = true;
					clock.restart();
				}
				else if (clock.getElapsedTime().asMilliseconds() > 10) {
					std::string str;
					PeekNamedPipe(pipout_r, buffer, sizeof(buffer), &read, &available, NULL);
					do
					{
						ZeroMemory(buffer, sizeof(buffer));
						if (!ReadFile(pipout_r, buffer, sizeof(buffer), &read, NULL) || !read) break;
						buffer[read] = 0;
						str += (char*)buffer;
					} while (read >= sizeof(buffer));

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
								calcColFromIdx(mBoard.getPosOfBoardWithString(str, false)), false, promotion);

						mPreparation = false;
						return true;
					}
				}
			}
			return false;
		}

		void startEngine() {
			pipin_w = pipin_r = pipout_w = pipout_r = NULL;
			sats.nLength = sizeof(sats);
			sats.bInheritHandle = TRUE;
			sats.lpSecurityDescriptor = NULL;

			CreatePipe(&pipout_r, &pipout_w, &sats, 0);
			CreatePipe(&pipin_r, &pipin_w, &sats, 0);

			sti.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
			sti.wShowWindow = SW_HIDE;
			sti.hStdInput = pipin_r;
			sti.hStdOutput = pipout_w;
			sti.hStdError = pipout_w;

			const char* narrowStr = "./StockfishEngine/stockfish-windows-x86-64-modern.exe";
			int requiredSize = MultiByteToWideChar(CP_UTF8, 0, narrowStr, -1, NULL, 0);
			LPWSTR path = new wchar_t[requiredSize];
			MultiByteToWideChar(CP_UTF8, 0, narrowStr, -1, path, requiredSize);

			CreateProcess(NULL, path, NULL, NULL, TRUE, 0, NULL, NULL, &sti, &pi);
		}

		void closeEngine()
		{
			WriteFile(pipin_w, "quit\n", 5, &writ, NULL);
			if (pipin_w != NULL) CloseHandle(pipin_w);
			if (pipin_r != NULL) CloseHandle(pipin_r);
			if (pipout_w != NULL) CloseHandle(pipout_w);
			if (pipout_r != NULL) CloseHandle(pipout_r);
			if (pi.hProcess != NULL) CloseHandle(pi.hProcess);
			if (pi.hThread != NULL) CloseHandle(pi.hThread);
		}

	private:
		STARTUPINFO sti = { 0 };
		SECURITY_ATTRIBUTES sats = { 0 };
		PROCESS_INFORMATION pi = { 0 };
		HANDLE pipin_w, pipin_r, pipout_w, pipout_r;
		BYTE buffer[4096];
		DWORD writ, excode, read, available;
		sf::Clock clock;
	};
}