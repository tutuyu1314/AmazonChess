#include "SearchEngine.h"

SearchEngine::SearchEngine() {}

SearchEngine::~SearchEngine() {
  if (m_pEvaluateEngine != nullptr) {
    delete m_pEvaluateEngine;
    m_pEvaluateEngine = nullptr;
  }
  if (m_pMoveGenerator != nullptr) {
    delete m_pEvaluateEngine;
    m_pEvaluateEngine = nullptr;
  }
}

void SearchEngine::MakeMove(const ChessMove &move) {
  m_Board[move.From.x][move.From.y] = EMPTY;
  m_Board[move.To.x][move.To.y] = move.chessID;
  m_Board[move.Bar.x][move.Bar.y] = BARRIER;
}

void SearchEngine::UnMakeMove(const ChessMove &move) {
  m_Board[move.From.x][move.From.y] = move.chessID;
  m_Board[move.To.x][move.To.y] = EMPTY;
  m_Board[move.Bar.x][move.Bar.y] = EMPTY;
}

int SearchEngine::IsGameOver(int Board[10][10]) {
  int nBlack = 0, nWhite = 0;  // 被堵死的棋子的数量
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      if (Board[i][j] != EMPTY && Board[i][j] != BARRIER) {
        int n = 0;
        // 8个方向判别
        for (int k = 0; k < 8; ++k) {
          int a = i + offset[k][0];
          int b = j + offset[k][1];
          if (a < 0 || a > 9 || b < 0 || b > 9 || Board[a][b] != EMPTY) {
            ++n;
          }
        }
        // 8个方向都被堵死，判别棋子的种类
        if (n >= 8) {
          if (Board[i][j] == BLACK) {
            ++nBlack;
          } else {
            ++nWhite;
          }
        }
      }
    }
  }
  if (nBlack >= 4) {
    return BLACK;
  } else if (nWhite >= 4) {
    return WHITE;
  } else {
    return 0;
  }
}
