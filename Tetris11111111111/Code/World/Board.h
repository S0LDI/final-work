#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tetramino.h"


class Board : public sf::Transformable, public sf::Drawable
{
public:
	static constexpr int DEFAULT_COLUMNS_COUNT = 10;
	static constexpr int DEFAULT_ROWS_COUNT = 20;
	static constexpr int DEFAULT_CELL_WIDTH = 24;
	static constexpr int DEFAULT_CELL_HEIGHT = 24;
	static constexpr int EMPTY_CELL_NUMBER = -1;

	Board(int rows = DEFAULT_ROWS_COUNT, int columns = DEFAULT_COLUMNS_COUNT, int cellWidth = DEFAULT_CELL_WIDTH, int cellHeight = DEFAULT_CELL_HEIGHT);

	void Spawn(Tetramino& tetramino);
	bool Move(Tetramino& tetramino, int offsetX, int offsetY);
	bool IsFallen(const Tetramino& tetramino);
	void Drop(Tetramino& tetramino);
	bool RotateLeft(Tetramino& tetramino);
	bool RotateRight(Tetramino& tetramino);
	bool IsGameOver();
	int ClearRows(const Tetramino& tetramino);

	int GetWidth() const;
	int GetHeight() const;

private:
	const int ROWS, COLUMNS;
	const int CELL_WIDTH;         
	const int CELL_HEIGHT;        
	const int WIDTH;
	const int HEIGHT;

	bool isGameOver = false;
	sf::VertexArray grid;         
	std::vector<int> gridContent; 

	bool Rotate(Tetramino& tetramino, int rotation);

	void Add(const Tetramino& tetramino);
	void ClearFrom(const Tetramino& tetramino);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;

	

	void PerformFloodFill(const Tetramino& tetramino, int value);
	void PerformFloodFill(
		int gridX, int gridY,
		int tetraminoX, int tetraminoY,
		Tetramino::Type type, int rotation,
		bool visitedCells[][Tetramino::MATRIX_SIZE], int value
	);
	void PerformFloodFill(
		int gridX, int gridY,
		int tetraminoX, int tetraminoY,
		Tetramino::Type type, int rotation,
		bool visitedCells[][Tetramino::MATRIX_SIZE], bool& hasCollision);

	void ShiftRowsDown(int bottomRowIndex);
};
