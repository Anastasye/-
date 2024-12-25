#ifndef HEXXAGON_H
#define HEXXAGON_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <map>
#include <sstream>

/*
 * @class GameBoard
 * @brief ���ݧѧ��, ���֧է��ѧӧݧ���ڧ� �ڧԧ��ӧ�� ���ݧ� �էݧ� �ڧԧ�� �� ���֧ܧ�ѧԧ��.
 */
class GameBoard {
public:
    GameBoard();

    /*
     * @brief ���ߧڧ�ڧѧݧڧ٧ڧ��֧� �ڧԧ��ӧ�� ���ݧ� �٧ѧէѧߧߧ�ԧ� ��ѧ٧ާ֧��.
     * @param newSize ����ӧ�� ��ѧ٧ާ֧� �ڧԧ��ӧ�ԧ� ���ݧ�.
     */
    void initializeBoard(int newSize);

    /*
     * @brief ���ѧԧ��اѧ֧� �������ߧڧ� �ڧԧ�� �ڧ� ��ѧۧݧ�.
     * @param filename ���ާ� ��ѧۧݧ�, �ڧ� �ܧ�����ԧ� �٧ѧԧ��اѧ֧��� �������ߧڧ� �ڧԧ��.
     */
    void loadGameState(const std::string& filename);

    /*
     * @brief ���֧�ѧ�ѧ֧� ��֧ܧ��֧� �������ߧڧ� �ڧԧ��ӧ�ԧ� ���ݧ�.
     */
    void printBoard() const;

    /*
     * @brief ������ѧߧ�֧� ��֧ܧ��֧� �������ߧڧ� �ڧԧ�� �� ��ѧۧ�.
     * @param filename ���ާ� ��ѧۧݧ�, �� �ܧ������ �����ѧߧ�֧��� �������ߧڧ� �ڧԧ��.
     */
    void saveGame(const std::string& filename) const;

    /*
     * @brief ���էӧѧڧӧѧ֧� ��ڧ�ܧ� �ߧ� �ڧԧ��ӧ�� ���ݧ�.
     * @param chip ���ڧ�ܧ�, �ܧ������ �ߧ�اߧ� ��էӧ�ڧ��.
     * @param row ������ܧ�, �� �ܧ������ �ߧѧ��էڧ��� ��ڧ�ܧ�.
     * @param column �����ݧҧ֧�, �� �ܧ������ �ߧѧ��էڧ��� ��ڧ�ܧ�.
     * @return true, �֧�ݧ� ��էӧ�֧ߧڧ� �����ݧ� ����֧�ߧ�; �ڧߧѧ�� false.
     */
    bool doubleChip(char chip, int row, int column);

    /*
     * @brief ���֧�֧ާ֧�ѧ֧� ��ڧ�ܧ� �� ��էߧ�ԧ� �ާ֧��� �ߧ� �է��ԧ��.
     * @param sourceRow ������էߧѧ� �����ܧ�.
     * @param sourceColumn ������էߧ�� ����ݧҧ֧�.
     * @param targetRow ���֧ݧ֧ӧѧ� �����ܧ�.
     * @param targetColumn ���֧ݧ֧ӧ�� ����ݧҧ֧�.
     * @param currentPlayer ���֧ܧ��ڧ� �ڧԧ���.
     * @return true, �֧�ݧ� ��֧�֧ާ֧�֧ߧڧ� �����ݧ� ����֧�ߧ�; �ڧߧѧ�� false.
     */
    bool moveChip(int sourceRow, int sourceColumn, int targetRow, int targetColumn, char currentPlayer);

    /*
     * @brief ����� �ܧ�ާ����֧��.
     * @param computerChip ���ڧ�ܧ� �ܧ�ާ����֧��.
     */
    void computerMove(char computerChip);

    /*
     * @brief �����ӧ֧��֧�, �֧��� �ݧ� �� �ڧԧ��ܧ� ��ڧ�ܧ�.
     * @param chip ���ڧ�ܧ�, �ܧ������ �ߧ�اߧ� ����ӧ֧�ڧ��.
     * @return true, �֧�ݧ� ��ڧ�ܧ� �֧���; �ڧߧѧ�� false.
     */
    bool hasChips(char chip) const;

    /*
     * @brief �����ӧ֧��֧�, ��ӧݧ�֧��� �ݧ� ���� �է�����ڧާ��.
     * @param targetRow ���֧ݧ֧ӧѧ� �����ܧ�.
     * @param targetColumn ���֧ݧ֧ӧ�� ����ݧҧ֧�.
     * @return true, �֧�ݧ� ���� �է�����ڧ�; �ڧߧѧ�� false.
     */
    bool isMoveValid(int targetRow, int targetColumn) const;

    /*
     * @brief ����ݧ��ѧ֧� ���ڧ��� �է�����ڧާ�� ���է�� �էݧ� ��ڧ�ܧ�.
     * @param row ������ܧ�, �� �ܧ������ �ߧѧ��էڧ��� ��ڧ�ܧ�.
     * @param column �����ݧҧ֧�, �� �ܧ������ �ߧѧ��էڧ��� ��ڧ�ܧ�.
     * @return ���֧ܧ��� ��ѧ�, ���֧է��ѧӧݧ���ڧ� �է�����ڧާ�� ���է�.
     */
    std::vector<std::pair<int, int>> getValidMoves(int row, int column) const;

    /*
     * \brief �����ӧ֧��֧�, �֧��� �ݧ� �է�����ߧ�� ���է� �� �ڧԧ��ܧ�.
     * \param [in] playerChip  {���ڧ�ܧ� �ڧԧ��ܧ�.}
     * \return true, �֧�ݧ� �է�����ߧ�� ���է� �֧���; �ڧߧѧ�� false.
     */
    bool hasAvailableMoves(char playerChip) const;

    /*
     * @brief �����ӧ֧��֧�, �٧ѧ��ݧߧ֧ߧ� �ݧ� �ڧԧ��ӧ�� ���ݧ�.
     * @return true, �֧�ݧ� ���ݧ� �٧ѧ��ݧߧ֧ߧ�; �ڧߧѧ�� false.
     */
    bool isFull();

    /*
     * \brief ����ڧ�ѧ֧� �ܧ�ݧڧ�֧��ӧ� ��ڧ�֧� ����֧է֧ݧ֧ߧߧ�ԧ� ��ӧ֧��.
     * \param [in] chip {���ڧ�ܧ�, �ܧ������ �ߧ�اߧ� �����ڧ�ѧ��.}
     * \return ����ݧڧ�֧��ӧ� ��ڧ�֧�.
     */
    int countChips(char chip);

    /*
     * @brief �����ӧ֧��֧�, ��ӧݧ�֧��� �ݧ� ���� �է�����ڧާ��.
     * @param targetRow ���֧ݧ֧ӧѧ� �����ܧ�.
     * @param targetColumn ���֧ݧ֧ӧ�� ����ݧҧ֧�.
     * @return true, �֧�ݧ� ���� �է�����ڧ�; �ڧߧѧ�� false.
     */
    bool isValidMove(int targetRow, int targetColumn);

private:
    std::vector<std::vector<char>> board;  ///< ���ԧ��ӧ�� ���ݧ�.
    int size;                                ///< ���ѧ٧ާ֧� �ڧԧ��ӧ�ԧ� ���ݧ�.

    /*
     * @brief �����ڧ�ݧ�֧� �ܧ�ݧڧ�֧��ӧ� ����ݧҧ��� �� �����ܧ�.
     * @param row ������ܧ�, �էݧ� �ܧ������ �ߧ�اߧ� �ӧ��ڧ�ݧڧ�� �ܧ�ݧڧ�֧��ӧ� ����ݧҧ���.
     * @return ����ݧڧ�֧��ӧ� ����ݧҧ���.
     */
    int calculateColumnCount(int row) const;

    /*
     * @brief �����ӧ֧��֧�, �ާ�ا֧� �ݧ� ��ڧ�ܧ� ��֧�֧���ԧߧ��� ��֧�֧� �է��ԧ�� ��ڧ�ܧ�.
     * @param sourceRow ������էߧѧ� �����ܧ�.
     * @param sourceColumn ������էߧ�� ����ݧҧ֧�.
     * @param targetRow ���֧ݧ֧ӧѧ� �����ܧ�.
     * @param targetColumn ���֧ݧ֧ӧ�� ����ݧҧ֧�.
     * @return true, �֧�ݧ� ��֧�֧���ԧߧ��� �ާ�اߧ�; �ڧߧѧ�� false.
     */
    bool canJumpOverChip(int sourceRow, int sourceColumn, int targetRow, int targetColumn) const;

    /*
     * @brief ���ѧ�ӧѧ��ӧѧ֧� ��ڧ�ܧ� �����ڧӧߧڧܧ�.
     * @param row ������ܧ�, �� �ܧ������ �ߧѧ��էڧ��� ��ڧ�ܧ�.
     * @param column �����ݧҧ֧�, �� �ܧ������ �ߧѧ��էڧ��� ��ڧ�ܧ�.
     * @param chip ���ڧ�ܧ�, �ܧ����ѧ� �٧ѧ�ӧѧ��ӧѧ֧�.
     */
    void captureOpponentChip(int row, int column, char chip);
};
/*
 * @class PlayerStats
 * @brief ���ݧѧ�� �էݧ� ���ѧߧ֧ߧڧ� ���ѧ�ڧ��ڧܧ� �ڧԧ��ܧ�. 
 */
class PlayerStats {
public:
    std::string playerName; ///< ���ާ� �ڧԧ��ܧ�
    int wins;               ///< ����ݧڧ�֧��ӧ� ���ҧ֧�
    int losses;             ///< ����ݧڧ�֧��ӧ� ����ѧا֧ߧڧ�

    /*
     * @brief ����ߧ����ܧ��� ��� ��ާ�ݧ�ѧߧڧ�.
     * ���ߧڧ�ڧѧݧڧ٧ڧ��֧� �ڧާ� �ڧԧ��ܧ� ������� �����ܧ��, �� �ܧ�ݧڧ�֧��ӧ� ���ҧ֧� �� ����ѧا֧ߧڧ� - �ߧ�ݧ֧�.
     */
    PlayerStats() : playerName(""), wins(0), losses(0) {}

    /*
     * @brief ����ߧ����ܧ��� �� ��ѧ�ѧާ֧����.
     * @param [in] name ���ާ� �ڧԧ��ܧ�.
     * ���ߧڧ�ڧѧݧڧ٧ڧ��֧� �ڧާ� �ڧԧ��ܧ� �٧ѧէѧߧߧ�� �٧ߧѧ�֧ߧڧ֧�, �� �ܧ�ݧڧ�֧��ӧ� ���ҧ֧� �� ����ѧا֧ߧڧ� - �ߧ�ݧ֧�.
     */
    PlayerStats(const std::string& name)
        : playerName(name), wins(0), losses(0) {
    }

    /*
     * @brief ����ߧ����ܧ��� �էݧ� �ڧߧڧ�ڧѧݧڧ٧ѧ�ڧ� �� �էѧߧߧ�ާ�.
     * @param  name ���ާ� �ڧԧ��ܧ�.
     * @param  w ����ݧڧ�֧��ӧ� ���ҧ֧�.
     * @param l ����ݧڧ�֧��ӧ� ����ѧا֧ߧڧ�.
     * ���ߧڧ�ڧѧݧڧ٧ڧ��֧� �ڧާ� �ڧԧ��ܧ�, �ܧ�ݧڧ�֧��ӧ� ���ҧ֧� �� ����ѧا֧ߧڧ� �٧ѧէѧߧߧ�ާ� �٧ߧѧ�֧ߧڧ�ާ�.
     */
    PlayerStats(const std::string& name, int w, int l)
        : playerName(name), wins(w), losses(l) {
    }
};


/*
 * @class GameStatistics
 * @brief ���ݧѧ��, ���֧է��ѧӧݧ���ڧ� ���ѧ�ڧ��ڧܧ� �ڧԧ�.
 */
class GameStatistics {
public:
    GameStatistics(const std::string& filename);

    /*
     * @brief ����ҧѧӧݧ�֧� ��֧٧�ݧ��ѧ� �ڧԧ��.
     * @param playerName ���ާ� �ڧԧ��ܧ�.
     * @param won ���֧٧�ݧ��ѧ� �ڧԧ�� (�ӧ�ڧԧ�ѧ� �ڧݧ� ����ڧԧ�ѧ�).
     */
    void addGameResult(const std::string& playerName, bool won);

    /*
     * @brief ������ѧߧ�֧� ���ѧ�ڧ��ڧܧ� �� ��ѧۧ�.
     */
    void saveStatistics();
    void loadStatistics();
    /*
     * @brief ���֧�ѧ�ѧ֧� ���ѧ�ڧ��ڧܧ� �ڧԧ�.
     */
    void printStatistics();

private:
    std::string filename;  ///< ���ާ� ��ѧۧݧ� �էݧ� �����ѧߧ֧ߧڧ� ���ѧ�ڧ��ڧܧ�.
    std::map<std::string, PlayerStats> existingStats;   ///< (�ڧާ� �ڧԧ��ܧ�, (���ҧ֧է�, ����ѧا֧ߧڧ�))
};

/*
 * @class Game
 * @brief ���ݧѧ��, ���֧է��ѧӧݧ���ڧ� �ڧԧ�� �� ���֧ܧ�ѧԧ��.
 */
class Game {
public:
    Game(const std::string& inputFile, const std::string& outputFile);

    /*
     * @brief ���ѧ���ܧѧ֧� �ڧԧ��.
     */
    void start();

private:
    GameBoard gameBoard;                   ///< ���ԧ��ӧ�� ���ݧ�.
    std::string inputFilename;             ///< ���ާ� ��ѧۧݧ� �էݧ� �٧ѧԧ��٧ܧ� �������ߧڧ� �ڧԧ��.
    std::string outputFilename;            ///< ���ާ� ��ѧۧݧ� �էݧ� �����ѧߧ֧ߧڧ� �������ߧڧ� �ڧԧ��.
    char currentPlayer;                    ///< ���֧ܧ��ڧ� �ڧԧ���.
    int gameMode;                          ///< ���֧اڧ� �ڧԧ�� (��֧ݧ�ӧ֧� �ڧݧ� �ܧ�ާ����֧�).
    GameStatistics stats;                  ///< ����ѧ�ڧ��ڧܧ� �ڧԧ�.
    std::string player1, player2;          ///< ���ާ֧ߧ� �ڧԧ��ܧ��.

    /*
     * @brief ����ҧڧ�ѧ֧� ��֧اڧ� �ڧԧ��.
     */
    void selectGameMode();

    /*
     * @brief ������ݧߧ�֧� ���� �ڧԧ��ܧ�.
     * @return true, �֧�ݧ� ���� �ҧ�� ����֧�ߧ��; �ڧߧѧ�� false.
     */
    bool playerTurn();

    /*
     * @brief ���֧ߧ�֧� ��֧ܧ��֧ԧ� �ڧԧ��ܧ�.
     */
    void switchPlayers();
};

#endif 