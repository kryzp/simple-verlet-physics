#ifndef CHUNKS_H
#define CHUNKS_H

#include <vector>

#include "ball.h"

class Chunks
{
public:
	const float CHUNK_SIZE;

	Chunks(float width, float height, float chunk_size);
	~Chunks();

	void clear();
	bool exists(int cx, int cy) const;
	void assign(int world_x, int world_y, int idx);
	const std::vector<int>& get(int cx, int cy) const;

private:
	const int CHUNKS_X;
	const int CHUNKS_Y;

	std::vector<int>* m_chunks;
};

#endif // CHUNKS_H
