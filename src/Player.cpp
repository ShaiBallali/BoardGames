#include "Player.h"
#include "GamePiece.h"

Player::Player(const bool isPlaying, const char whichPlayer) : _isPlaying(isPlaying), _isLoser(false), _whichPlayer(whichPlayer)
{
}
bool				   _isPlaying;
bool				   _isLoser;
char				   _whichPlayer;
int					   _numOfPieces;
int					   _sizeBoard;

void Player::operator=(const Player& other)
{
    _isPlaying = other.getIsPlaying();
    _isLoser = other.getIsLoser();
    _whichPlayer = other.getWhichPlayer();
    _numOfPieces = other.getNumOfPieces();
    _sizeBoard = other.getSizeBoard();
    pieces = other.getPieces();
}

Player::Player(const Player& other)
{
    *this = other;
}

void Player::initPieces(GamePiece*** board, int sizeBoard) {
    _sizeBoard = sizeBoard;
    int i, j;
    position data;
    for (i = 0; i < _sizeBoard; i++)
        for (j = 0; j < _sizeBoard; j++)
        {
            if (board[i][j] != nullptr && board[i][j]->getColor() == _whichPlayer)
            {
                data.x = i + 1;
                data.y = j + 1;
                add<PositionList*, position, positionNode, positionNode*>(&pieces, data, nullptr);
            }
        }
}

void Player::setNumOfPieces(int numOfPieces) {
    _numOfPieces = numOfPieces;
}

const bool Player::getIsPlaying()const
{
    return _isPlaying;
}

const int Player::getSizeBoard() const
{
    return _sizeBoard;
}

const bool Player::getIsLoser() const
{
    return _isLoser;
}

const int  Player::getNumOfPieces() const {
    return _numOfPieces;
}

void Player::setIsPlaying(bool isPlaying)
{
    _isPlaying = isPlaying;
}

void Player::setIsLoser(bool isWinner)
{
    _isLoser = isWinner;
}

const int Player::getWhichPlayer() const {
    return _whichPlayer;
}

void Player::setWhichPlayer(char whichPlayer) {
    _whichPlayer = whichPlayer;
}

PositionList& Player::getPieces() {
    return pieces;
}

const PositionList& Player::getPieces() const {
    return pieces;
}

