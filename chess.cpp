
#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum Piece { EMPTY, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };
enum Color { NONE, WHITE, BLACK };

struct ChessPiece {
    Piece piece;
    Color color;
};

class ChessBoard {
private:
    ChessPiece board[8][8];
    Color currentPlayer;

public:
    ChessBoard() {
        resetBoard();
        currentPlayer = WHITE;
    }

    void resetBoard() {
        // Initialize the board with pieces
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                board[i][j].piece = EMPTY;
                board[i][j].color = NONE;
            }
        }

        // Set up pieces for both players
        for (int i = 0; i < 8; ++i) {
            board[1][i] = { PAWN, WHITE };
            board[6][i] = { PAWN, BLACK };
        }

        board[0][0] = board[0][7] = { ROOK, WHITE };
        board[0][1] = board[0][6] = { KNIGHT, WHITE };
        board[0][2] = board[0][5] = { BISHOP, WHITE };
        board[0][3] = { QUEEN, WHITE };
        board[0][4] = { KING, WHITE };

        board[7][0] = board[7][7] = { ROOK, BLACK };
        board[7][1] = board[7][6] = { KNIGHT, BLACK };
        board[7][2] = board[7][5] = { BISHOP, BLACK };
        board[7][3] = { QUEEN, BLACK };
        board[7][4] = { KING, BLACK };
    }

    void drawBoard() {
        system("clear"); // for Linux/Unix, use system("cls"); for Windows
        cout << "  a b c d e f g h" << endl;
        for (int i = 0; i < 8; ++i) {
            cout << 8 - i << " ";
            for (int j = 0; j < 8; ++j) {
                cout << getPieceSymbol(board[i][j]) << " ";
            }
            cout << 8 - i << endl;
        }
        cout << "  a b c d e f g h" << endl;
    }

    bool movePiece(const string& from, const string& to) {
        int fromRow = 8 - (from[1] - '0');
        int fromCol = from[0] - 'a';
        int toRow = 8 - (to[1] - '0');
        int toCol = to[0] - 'a';

        if (isValidMove(fromRow, fromCol, toRow, toCol)) {
            board[toRow][toCol] = board[fromRow][fromCol];
            board[fromRow][fromCol] = { EMPTY, NONE };
            currentPlayer = (currentPlayer == WHITE) ? BLACK : WHITE;
            return true;
        } else {
            return false;
        }
    }

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol) {
        if (fromRow < 0 || fromRow >= 8 || fromCol < 0 || fromCol >= 8 ||
            toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) {
            return false;
        }
        if (board[fromRow][fromCol].color != currentPlayer) {
            return false;
        }
        if (board[toRow][toCol].color == currentPlayer) {
            return false;
        }
        // Simplified movement validation (should be extended for actual chess rules)
        return true;
    }

    char getPieceSymbol(const ChessPiece& piece) {
        if (piece.color == WHITE) {
            switch (piece.piece) {
                case PAWN: return 'P';
                case ROOK: return 'R';
                case KNIGHT: return 'N';
                case BISHOP: return 'B';
                case QUEEN: return 'Q';
                case KING: return 'K';
                default: return '.';
            }
        } else if (piece.color == BLACK) {
            switch (piece.piece) {
                case PAWN: return 'p';
                case ROOK: return 'r';
                case KNIGHT: return 'n';
                case BISHOP: return 'b';
                case QUEEN: return 'q';
                case KING: return 'k';
                default: return '.';
            }
        }
        return '.';
    }
};

bool playAgain() {
    char choice;
    cout << "Do you want to play again? (y/n): ";
    cin >> choice;
    return choice == 'y' || choice == 'Y';
}

int main() {
    ChessBoard board;
    string from, to;

    do {
        board.resetBoard();

        while (true) {
            board.drawBoard();
            cout << "Player " << (board.currentPlayer == WHITE ? "White" : "Black") << ", enter your move (e.g., e2 e4): ";
            cin >> from >> to;

            if (board.movePiece(from, to)) {
                // Additional checks for check/checkmate, stalemate, etc., would go here
                // For simplicity, this example does not implement these rules
            } else {
                cout << "Invalid move. Try again." << endl;
            }
        }
    } while (playAgain());

    cout << "Thank you for playing!" << endl;
    return 0;
}
