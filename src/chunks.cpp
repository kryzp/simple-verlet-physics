#include "chunks.h"

Chunks::Chunks(float width, float height, float chunk_size)
	: CHUNK_SIZE(chunk_size)
	, CHUNKS_X((int)(width / chunk_size) + 1)
	, CHUNKS_Y((int)(height / chunk_size) + 1)
{
	m_chunks = new std::vector<int>[CHUNKS_X * CHUNKS_Y];
}

Chunks::~Chunks()
{
	delete[] m_chunks;
}

void Chunks::clear()
{
	for (int i = 0; i < CHUNKS_X * CHUNKS_Y; i++) {
		m_chunks[i].clear();
	}
}

bool Chunks::exists(int cx, int cy) const
{
	return cx >= 0 && cy >= 0 && cx < CHUNKS_X && cy < CHUNKS_Y;
}

void Chunks::assign(int world_x, int world_y, int idx)
{
	int cx = (int)(world_x / CHUNK_SIZE);
	int cy = (int)(world_y / CHUNK_SIZE);
	m_chunks[(cy * CHUNKS_X) + cx].push_back(idx);
}

const std::vector<int>& Chunks::get(int cx, int cy) const
{
	return m_chunks[(cy * CHUNKS_X) + cx];
}
