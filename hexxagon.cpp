#include "hexxagon.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <algorithm>

using namespace std;

/**
 * @brief Конструктор для GameStatistics.
 * @param filename Имя файла для хранения статистики.
 */
GameStatistics::GameStatistics(const std::string& filename) : filename(filename) {
}

/**
 * @brief Добавляет результат игры для игрока.
 * @param playerName Имя игрока.
 * @param won Указывает, выиграл ли игрок (true) или проиграл (false).
 */
void GameStatistics::addGameResult(const std::string& playerName, bool won) {
    auto it = existingStats.find(playerName);
    if (it == existingStats.end()) {
        existingStats[playerName] = PlayerStats(playerName);

    }

    if (won) {
        existingStats[playerName].wins++;
    }
    else {
        existingStats[playerName].losses++;
    }
}

/**
 * @brief Загружает статистику из файла.
 * Читает данные о игроках, их победах и поражениях из указанного файла.
 */
void GameStatistics::loadStatistics() {
    std::ifstream inputFile(filename); 
    if (!inputFile.is_open()) {
        std::cerr << "Ошибка открытия файла для чтения!" << std::endl;
        return; 
    }

    std::string playerName;
    int wins, losses;

    
    while (inputFile >> playerName) {
        inputFile >> wins >> losses; 

        
        if (existingStats.find(playerName) == existingStats.end()) {
            existingStats[playerName] = PlayerStats(playerName);
        }
        existingStats[playerName].wins += wins;    
        existingStats[playerName].losses += losses; 
    }

    inputFile.close(); 
}

/**
 * @brief Сохраняет статистику в файл.
 * Записывает данные о игроках, их победах и поражениях в указанный файл.
 */
void GameStatistics::saveStatistics() {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Ошибка открытия файла для записи!" << std::endl;
        return;
    }

    for (const auto& entry : existingStats) {
        outputFile << entry.second.playerName << "  " << entry.second.wins << "  " << entry.second.losses << std::endl;
    }
    outputFile.close();
}

/**
 * @brief Печатает статистику игры в консоль.
 * Выводит информацию о каждом игроке, его победах и поражениях.
 */
void GameStatistics::printStatistics() {
    std::cout << "Статистика игры:" << std::endl;
    for (const auto& stat : existingStats) {
        std::cout << stat.first << ": " << stat.second.wins << " побед, " << stat.second.losses << " поражений" << std::endl;
    }
}

GameBoard::GameBoard() : size(0) {}

/**
 * @brief Инициализирует игровое поле заданного размера.
 *
 * @param newSize Новый размер игрового поля.
 */
void GameBoard::initializeBoard(int newSize) {
    size = newSize;
    board.resize(size * 2 - 1);

    for (int row = 0; row < size * 2 - 1; row++) {
        board[row].resize(calculateColumnCount(row), '\0');
    }
}

/**
 * @brief Загружает состояние игры из файла.
 *
 * @param filename Имя файла для загрузки состояния игры.
 */
void GameBoard::loadGameState(const std::string& filename) {
    cout << "Загрузка состояния игры из файла: " << filename << endl;
    ifstream inputFile(filename);

    if (!inputFile) {
        cerr << "Ошибка: не удалось открыть файл " << filename << endl;
        std::exit(1);
    }

    inputFile >> size;
    if (size <= 0) {
        cerr << "Ошибка: недопустимый размер поля." << endl;
        std::exit(1);
    }

    initializeBoard(size);

    for (int row = 0; row < size * 2 - 1; row++) {
        for (int column = 0; column < calculateColumnCount(row); column++) {
            char cell;
            inputFile >> cell;
            board[row][column] = (cell == '-' ? '\0' : cell);
        }
    }

    inputFile.close();
    cout << "Состояние игры успешно загружено." << endl;
}

/**
 * @brief Печатает текущее состояние игрового поля.
 */
void GameBoard::printBoard() const {
    for (int row = 0; row < size * 2 - 1; row++) {
        int leadingSpaces = (row < size) ? (size - 1 - row) : (row - size + 1);
        cout << string(leadingSpaces, ' ');

        for (int column = 0; column < calculateColumnCount(row); column++) {
            cout << (board[row][column] ? board[row][column] : '-') << " ";
        }
        cout << endl;
    }
}

/**
 * @brief Сохраняет текущее состояние игры в файл.
 *
 * @param filename Имя файла для сохранения состояния игры.
 */
void GameBoard::saveGame(const std::string& filename) const {
    std::ofstream outputFile(filename);
    if (!outputFile) {
        std::cerr << "Ошибка: не удалось открыть файл для записи " << filename << std::endl;
        return;
    }

    outputFile << size << std::endl;
    for (const auto& row : board) {
        for (const auto& cell : row) {

            outputFile << (cell ? cell : '-') << ' ';
        }
        outputFile << std::endl;
    }

    outputFile.close();
    std::cout << "Состояние игры сохранено в файл: " << filename << std::endl;
}


/**
 * @brief Захватывает фишку противника, если она находится рядом.
 *
 * @param row Строка, в которой находится фишка.
 * @param column Столбец, в котором находится фишка.
 * @param chip Фишка игрока, которая захватывает противника.
 */
void GameBoard::captureOpponentChip(int row, int column, char chip) {
    int neighborDirections[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

    for (const auto& direction : neighborDirections) {
        int neighborRow = row + direction[0];
        int neighborColumn = column + direction[1];

        if (isMoveValid(neighborRow, neighborColumn) &&
            board[neighborRow][neighborColumn] != chip &&
            board[neighborRow][neighborColumn] != '\0') {

            board[neighborRow][neighborColumn] = chip;
            cout << "Фишка противника на позиции (" << neighborRow + 1 << ", " << neighborColumn + 1 << ") захвачена!" << endl;
        }
    }
}

/**
 * @brief Удваивает фишку на указанной позиции.
 *
 * Функция проверяет, можно ли удвоить фишку на заданной позиции.
 * Если фишка успешно удвоена, захватываются фишки противника,
 * находящиеся рядом с новой фишкой.
 *
 * @param chip Символ фишки, которую нужно удвоить.
 * @param row Номер строки, где находится фишка (1-индексированный).
 * @param column Номер столбца, где находится фишка (1-индексированный).
 * @return true Если фишка успешно удвоена.
 * @return false Если произошла ошибка при удвоении фишки.
 */
bool GameBoard::doubleChip(char chip, int row, int column) {
    cout << "Попытка удвоить фишку " << chip << " на позиции (" << row << ", " << column << ")" << endl;

    row--;
    column--;


    if (!isMoveValid(row, column) || board[row][column] != '\0') {
        cout << "Ошибка: недопустимые координаты или ячейка занята." << endl;
        return false;
    }

    int neighborDirections[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
    bool hasAdjacentChip = false;

    for (auto& direction : neighborDirections) {
        int neighborRow = row + direction[0];
        int neighborColumn = column + direction[1];

        if (isMoveValid(neighborRow, neighborColumn) && board[neighborRow][neighborColumn] == chip) {
            hasAdjacentChip = true;
            break;
        }
    }

    if (!hasAdjacentChip) {
        cout << "Ошибка: можно удваивать только на соседние ячейки." << endl;
        return false;
    }

    board[row][column] = chip;
    cout << "Фишка успешно удвоена!" << endl;

    captureOpponentChip(row, column, chip);


    for (auto& direction : neighborDirections) {
        int neighborRow = row + direction[0];
        int neighborColumn = column + direction[1];

        if (isMoveValid(neighborRow, neighborColumn) &&
            board[neighborRow][neighborColumn] != chip &&
            board[neighborRow][neighborColumn] != '\0') {

            board[neighborRow][neighborColumn] = chip;
            cout << "Фишка противника на позиции (" << neighborRow + 1 << ", " << neighborColumn + 1 << ") захвачена и теперь принадлежит " << chip << "!" << endl;
        }
    }

    return true;
}

/**
 * @brief Перемещает фишку с одной позиции на другую.
 *
 * Функция проверяет, можно ли переместить фишку с исходной позиции на целевую.
 * Если перемещение допустимо, фишка перемещается, и захватываются фишки противника.
 *
 * @param sourceRow Номер строки исходной позиции (1-индексированный).
 * @param sourceColumn Номер столбца исходной позиции (1-индексированный).
 * @param targetRow Номер строки целевой позиции (1-индексированный).
 * @param targetColumn Номер столбца целевой позиции (1-индексированный).
 * @param currentPlayer Символ текущего игрока.
 * @return true Если перемещение успешно.
 * @return false Если произошла ошибка при перемещении.
 */
bool GameBoard::moveChip(int sourceRow, int sourceColumn, int targetRow, int targetColumn, char currentPlayer) {
    sourceRow--;
    sourceColumn--;
    targetRow--;
    targetColumn--;

    if (board[sourceRow][sourceColumn] != currentPlayer) {
        cout << "Ошибка: это не ваша фишка." << endl;
        return false;
    }

    int deltaRow = targetRow - sourceRow;
    int deltaColumn = targetColumn - sourceColumn;


    if ((abs(deltaRow) == 2 && abs(deltaColumn) <= 1) ||
        (abs(deltaColumn) == 2 && abs(deltaRow) <= 1) ||
        (abs(deltaRow) == 2 && abs(deltaColumn) == 2)) {


        int intermediateRow = sourceRow + (deltaRow / 2);
        int intermediateColumn = sourceColumn + (deltaColumn / 2);

        if (!isMoveValid(intermediateRow, intermediateColumn)) {
            cout << "Ошибка: недопустимая промежуточная позиция." << endl;
            return false;
        }

        if (board[intermediateRow][intermediateColumn] != '\0' &&
            board[intermediateRow][intermediateColumn] != currentPlayer) {

            board[intermediateRow][intermediateColumn] = currentPlayer; // Меняем цвет захваченной фишки на цвет текущего игрока
            cout << "Фишка противника на позиции (" << intermediateRow + 1 << ", " << intermediateColumn + 1 << ") захвачена и теперь принадлежит " << currentPlayer << "!" << endl;
        }
    }
    else {
        cout << "Ошибка: перемещение возможно только через одну ячейку." << endl;
        return false;
    }

    if (!isMoveValid(targetRow, targetColumn) || board[targetRow][targetColumn] != '\0') {
        cout << "Ошибка: недопустимая целевая позиция." << endl;
        return false;
    }

    board[targetRow][targetColumn] = board[sourceRow][sourceColumn];
    board[sourceRow][sourceColumn] = '\0';

    captureOpponentChip(targetRow, targetColumn, currentPlayer);

    return true;
}

/**
 * @brief Проверяет, есть ли фишки заданного типа на доске.
 *
 * Функция проходит по всей доске и проверяет наличие фишек указанного типа.
 *
 * @param chip Символ фишки, которую нужно проверить.
 * @return true Если фишки найдены.
 * @return false Если фишки не найдены.
 */
bool GameBoard::hasChips(char chip) const {
    for (int i = 0; i < size * 2 - 1; ++i) {
        for (int j = 0; j < calculateColumnCount(i); ++j) {
            if (board[i][j] == chip) {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Получает все допустимые ходы для фишки на заданной позиции.
 *
 * @param row Номер строки, где находится фишка.
 * @param column Номер столбца, где находится фишка.
 * @return std::vector<std::pair<int, int>> Список допустимых ходов в формате (строка, столбец).
 */
std::vector<std::pair<int, int>> GameBoard::getValidMoves(int row, int column) const {
    std::vector<std::pair<int, int>> validMoves;
    int directions[8][2] = { {-2, 0}, {2, 0}, {0, -2}, {0, 2}, {-2, -2}, {-2, 2}, {2, -2}, {2, 2} };

    for (const auto& direction : directions) {
        int targetRow = row + direction[0];
        int targetColumn = column + direction[1];

        if (isMoveValid(targetRow, targetColumn) && board[targetRow][targetColumn] == '\0') {
            validMoves.emplace_back(targetRow, targetColumn);
        }
    }

    return validMoves;
}

/**
 * @brief Проверяет, является ли перемещение допустимым.
 *
 * @param row Номер строки для проверки.
 * @param column Номер столбца для проверки.
 * @return true Если перемещение допустимо.
 * @return false Если перемещение недопустимо.
 */
bool GameBoard::isMoveValid(int row, int column) const {
    return row >= 0 && row < size * 2 - 1 && column >= 0 && column < calculateColumnCount(row);
}

/**
 * @brief Выполняет ход компьютера.
 *
 * @param computerChip Символ фишки компьютера.
 */
void GameBoard::computerMove(char computerChip) {
    std::cout << "Компьютер выполняет ход с фишкой " << computerChip << "..." << std::endl;

    bool moveMade = false;


    for (int row = 1; row <= size; row++) {
        for (int column = 1; column <= calculateColumnCount(row); column++) {
            if (board[row - 1][column - 1] == computerChip) {

                for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
                    for (int deltaColumn = -1; deltaColumn <= 1; deltaColumn++) {
                        if ((abs(deltaRow) == 1 && deltaColumn == 0) || (deltaRow == 0 && abs(deltaColumn) == 1)) {
                            int targetRow = row + deltaRow;
                            int targetCol = column + deltaColumn;


                            if (targetRow >= 1 && targetRow <= size &&
                                targetCol >= 1 && targetCol <= calculateColumnCount(targetRow) &&
                                board[targetRow - 1][targetCol - 1] == '\0') {


                                if (doubleChip(computerChip, targetRow, targetCol)) {
                                    moveMade = true;
                                    std::cout << "Компьютер удвоил фишку на позиции (" << targetRow << ", " << targetCol << ")." << std::endl;
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
    }


    for (int row = 1; row <= size; row++) {
        for (int column = 1; column <= calculateColumnCount(row); column++) {
            if (board[row - 1][column - 1] == computerChip) {
                for (int deltaRow = -2; deltaRow <= 2; deltaRow++) {
                    for (int deltaColumn = -2; deltaColumn <= 2; deltaColumn++) {
                        if ((abs(deltaRow) == 2 && abs(deltaColumn) <= 1) ||
                            (abs(deltaColumn) == 2 && abs(deltaRow) <= 1)) {
                            int targetRow = row + deltaRow;
                            int targetCol = column + deltaColumn;
                            if (targetRow >= 1 && targetRow <= size &&
                                targetCol >= 1 && targetCol <= calculateColumnCount(targetRow) &&
                                isValidMove(targetRow, targetCol) &&
                                canJumpOverChip(row - 1, column - 1, targetRow - 1, targetCol - 1)) {
                                moveChip(row - 1, column - 1, targetRow - 1, targetCol - 1, computerChip);
                                std::cout << "Компьютер перемещает фишку с (" << row << ", " << column << ") на ("
                                    << targetRow << ", " << targetCol << ")." << std::endl;


                                captureOpponentChip(targetRow - 1, targetCol - 1, computerChip);
                                moveMade = true;
                                return;
                            }
                        }
                    }
                }
            }
        }
    }

    
    if (!moveMade) {
        std::cout << "У компьютера нет доступных ходов!" << std::endl;
    }
}

/**
 * @brief Проверяет, является ли перемещение допустимым.
 *
 * @param targetRow Целевая строка.
 * @param targetColumn Целевая колонка.
 * @return true Если перемещение допустимо.
 * @return false Если перемещение недопустимо.
 */
bool GameBoard::isValidMove(int targetRow, int targetColumn) {
    return (targetRow >= 1 && targetRow <= size) &&
        (targetColumn >= 1 && targetColumn <= calculateColumnCount(targetRow)) &&
        (board[targetRow - 1][targetColumn - 1] == '\0');
}


/**
 * @brief Вычисляет количество колонок в заданной строке.
 *
 * @param row Номер строки.
 * @return Количество колонок в строке.
 */
int GameBoard::calculateColumnCount(int row) const {
    return (size * 2 - 1) - abs(size - row - 1);
}

/**
 * @brief Проверяет, можно ли перепрыгнуть через фишку.
 *
 * @param sourceRow Исходная строка.
 * @param sourceColumn Исходная колонка.
 * @param targetRow Целевая строка.
 * @param targetColumn Целевая колонка.
 * @return true Если можно перепрыгнуть.
 * @return false Если нельзя перепрыгнуть.
 */
bool GameBoard::canJumpOverChip(int sourceRow, int sourceColumn, int targetRow, int targetColumn) const {
    int rowDifference = targetRow - sourceRow;
    int columnDifference = targetColumn - sourceColumn;

    if ((abs(rowDifference) == 2 && abs(columnDifference) == 0) ||
        (abs(rowDifference) == 0 && abs(columnDifference) == 2) ||
        (abs(rowDifference) == 2 && abs(columnDifference) == 2)) {

        int middleRow = (sourceRow + targetRow) / 2;
        int middleColumn = (sourceColumn + targetColumn) / 2;
        return (board[middleRow][middleColumn] != '\0');
    }

    return false;
}

/**
 * @brief Проверяет, есть ли доступные ходы для игрока.
 *
 * @param playerChip Фишка игрока.
 * @return true Если есть доступные ходы.
 * @return false Если доступных ходов нет.
 */
bool GameBoard::hasAvailableMoves(char playerChip) const {
    for (int row = 0; row < size * 2 - 1; row++) {
        for (int column = 0; column < calculateColumnCount(row); column++) {
            if (board[row][column] == playerChip) {
                if (!getValidMoves(row, column).empty()) {
                    return true;
                }
            }
        }
    }
    return false;
}
/**
 * @brief Конструктор игры.
 *
 * @param inputFile Имя входного файла.
 * @param outputFile Имя выходного файла.
 */
Game::Game(const std::string& inputFile, const std::string& outputFile)
    : inputFilename(inputFile), outputFilename(outputFile), currentPlayer('R'), gameMode(0), stats("game_statistics.txt") {
}

/**
 * @brief Проверяет, заполнено ли игровое поле.
 *
 * @return true Если поле заполнено.
 * @return false Если поле не заполнено.
 */

bool GameBoard::isFull() {
    for (int i = 0; i < size * 2 - 1; ++i) {
        for (int j = 0; j < calculateColumnCount(i); ++j) {
            if (board[i][j] == '\0') {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief Считает количество фишек заданного типа на поле.
 *
 * @param chip Тип фишки.
 * @return Количество фишек заданного типа.
 */
int GameBoard::countChips(char chip) {
    int count = 0;
    for (int i = 0; i < size * 2 - 1; ++i) {
        for (int j = 0; j < calculateColumnCount(i); ++j) {
            if (board[i][j] == chip) {
                count++;
            }
        }
    }
    return count;
}

/**
 * @brief Запускает игру, загружает состояние игры и управляет игровым процессом.
 *
 * Этот метод отвечает за инициализацию игры, выбор режима игры,
 * загрузку статистики и управление ходами игроков.
 * В зависимости от выбранного режима игры, он позволяет игрокам
 * выполнять действия, такие как удвоение фишки или перемещение фишки.
 */
void Game::start() {
    gameBoard.loadGameState(inputFilename); // Загружаем состояние игры из файла
    selectGameMode(); // Выбираем режим игры

    std::string statsFilename = "game_statistics.txt"; // Имя файла для статистики
    stats.loadStatistics(); // Загружаем статистику игр

    std::string player1, player2; // Имена игроков

    if (gameMode == 1) {
       
        std::cout << "Введите имя первого игрока: ";
        std::cin >> player1;
        std::cout << "Введите имя второго игрока: ";
        std::cin >> player2;
        std::cout << player1 << " будет играть красными (R), а " << player2 << " - синими (B)." << std::endl;
    }
    else if (gameMode == 2) {
        
        std::cout << "Введите имя игрока: ";
        std::cin >> player1;
        player2 = "Computer";
        std::cout << player1 << " будет играть красными (R), а " << player2 << " - синими (B)." << std::endl;
    }

    currentPlayer = 'R'; 

    while (true) {
        gameBoard.printBoard(); 
        std::cout << "Ход игрока: " << (currentPlayer == 'R' ? player1 : player2) << std::endl;

        if (gameMode == 2 && currentPlayer == 'B') {
            
            std::cout << "Ход компьютера..." << std::endl;
            gameBoard.computerMove('B'); 

            if (!gameBoard.hasChips('R')) {
                std::cout << "Компьютер выиграл!" << std::endl;
                stats.addGameResult(player2, true);   
                stats.addGameResult(player1, false);
                break; 
            }

            
            if (!gameBoard.hasAvailableMoves('B')) {
                std::cout << "Компьютер не может сделать ход! Игра окончена! Победил " << player1 << "!" << std::endl;
                stats.addGameResult(player1, true);
                stats.addGameResult(player2, false);
                break; 
            }

            currentPlayer = 'R'; 
        }
        else {
            
            int action = 0;
            do {
                std::cout << "Введите 1 для удвоения или 2 для перемещения фишки (или 0 для выхода): ";
                std::cin >> action;
                if (action != 1 && action != 2 && action != 0) {
                    std::cout << "Некорректный выбор действия. Попробуйте еще раз." << std::endl;
                }
            } while (action != 1 && action != 2 && action != 0);

            if (action == 0) {
                gameBoard.saveGame(outputFilename); 
                break;
            }

            if (action == 1) {
                
                int row, col;
                while (true) {
                    std::cout << "Введите координаты для удвоения (строка, столбец): ";
                    std::cin >> row >> col;

                    if (gameBoard.doubleChip(currentPlayer, row, col)) {
                        std::cout << "Фишка успешно удвоена!" << std::endl;
                        break;
                    }
                    else {
                        std::cout << "Ошибка: недопустимые координаты или ячейка занята. Попробуйте еще раз." << std::endl;
                    }
                }
            }
            else if (action == 2) {
                
                int fromRow, fromCol, toRow, toCol;
                while (true) {
                    std::cout << "Введите координаты фишки для перемещения (строка, столбец): ";
                    std::cin >> fromRow >> fromCol;
                    std::cout << "Введите координаты для перемещения (строка, столбец): ";
                    std::cin >> toRow >> toCol;

                    if (gameBoard.moveChip(fromRow, fromCol, toRow, toCol, currentPlayer)) {
                        std::cout << "Фишка перемещена!" << std::endl;
                        break; 
                    }
                    else {
                        std::cout << "Ошибка: недопустимый ход или ячейка занята. Попробуйте еще раз." << std::endl;
                    }
                }
            }

            
            if (!gameBoard.hasChips(currentPlayer == 'R' ? 'B' : 'R')) {
                std::cout << "Игрок " << (currentPlayer == 'R' ? player1 : player2) << " выиграл! Противник не имеет фишек!" << std::endl;
                if (currentPlayer == 'R') {
                    stats.addGameResult(player1, true);
                    stats.addGameResult(player2, false);
                }
                else {
                    stats.addGameResult(player1, false);
                    stats.addGameResult(player2, true);
                }
                break; 
            }

            currentPlayer = (currentPlayer == 'R') ? 'B' : 'R'; 
        }
    }

    gameBoard.saveGame(outputFilename);  
    stats.saveStatistics(); 
    stats.printStatistics(); 
}


/**
 * @brief Выбор режима игры.
 *
 * Этот метод позволяет игроку выбрать режим игры:
 * 1 - против другого игрока,
 * 2 - против компьютера.
 *
 * Если введено некорректное значение, пользователю будет предложено
 * повторить ввод до тех пор, пока не будет введено корректное значение.
 */
void Game::selectGameMode() {
    cout << "Выберите режим игры: 1 - против другого игрока, 2 - против компьютера: ";

    while (!(cin >> gameMode) || (gameMode != 1 && gameMode != 2)) {
        cout << "Некорректный выбор. Пожалуйста, выберите 1 или 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
/**
 * @brief Выполняет ход игрока.
 * 
 * Запрашивает у игрока действие: удвоение фишки, перемещение фишки или выход из игры.
 * Если действие недопустимо, запрашивает повторный ввод.
 * 
 * @return true Если ход был успешно выполнен, false если игрок выбрал выход.
 */
bool Game::playerTurn() {
    cout << "Введите 1 для удвоения или 2 для перемещения фишки (или 0 для выхода): ";
    int action;
    cin >> action;

    if (action == 1) {
        int row, column;
        cout << "Введите координаты для удвоения (строка, столбец): ";
        cin >> row >> column;
        while (!gameBoard.doubleChip(currentPlayer, row, column)) {
            cout << "Попробуйте снова, введите координаты для удвоения (строка, столбец): ";
            cin >> row >> column;
        }
        return true;
    }
    else if (action == 2) {
        int sourceRow, sourceColumn, targetRow, targetColumn;

        cout << "Введите координаты фишки для перемещения (строка, столбец): ";
        cin >> sourceRow >> sourceColumn;
        cout << "Введите координаты для перемещения (строка, столбец): ";
        cin >> targetRow >> targetColumn;

        while (!gameBoard.moveChip(sourceRow, sourceColumn, targetRow, targetColumn, currentPlayer)) {
            cout << "Попробуйте снова, введите координаты фишки для перемещения (строка, столбец): ";
            cin >> sourceRow >> sourceColumn;
            cout << "Введите координаты для перемещения (строка, столбец): ";
            cin >> targetRow >> targetColumn;
        }
        return true;
    }
    else if (action == 0) {
        return false;
    }
    else {
        cout << "Некорректный выбор действия. Попробуйте еще раз." << endl;
        return playerTurn();
    }
}
/**
 * @brief Переключает текущего игрока.
 *
 * Если игра в режиме противостояния, меняет текущего игрока с 'R' на 'B' или наоборот.
 */
void Game::switchPlayers() {
    if (gameMode == 1) {
        currentPlayer = (currentPlayer == 'R') ? 'B' : 'R';
    }
}
