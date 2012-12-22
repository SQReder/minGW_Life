#ifndef LIFE_H
#define LIFE_H

typedef char lType;

class tlife {
public:
	tlife(int w, int h);
	~tlife();

	void seed(int count);
	void step();
	
	const int get_stage() const;
	const lType **get_grid() const ;

private:
	int w;
	int h;

	lType **grid;
	lType **buff;

	void process(int x, int y);
	int neighbour(int x, int y);

	unsigned int stage = 0;
};
#endif
